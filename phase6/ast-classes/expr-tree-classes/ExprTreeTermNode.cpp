#include "ExprTreeTermNode.hpp"

#include <string>
#include <vector>

#include "../../code-generation-classes/data-classes/SCCData.hpp"
#include "../../code-generation-classes/data-classes/SCCDataNumericLiteral.hpp"
#include "../../code-generation-classes/data-classes/SCCDataStackVariable.hpp"
#include "../../code-generation-classes/data-classes/SCCDataStaticVariable.hpp"
#include "../../code-generation-classes/data-classes/SCCDataStringLiteral.hpp"
#include "../../code-generation-classes/data-classes/SCCDataTempValue.hpp"
#include "../../code-generation-classes/data-classes/SCCDataWrapper.hpp"
#include "../../code-generation-classes/label-classes/SCCStringLiteralHelper.hpp"
#include "../../code-generation-classes/register-classes/SCCRegisterManager.hpp"
#include "../../code-generation-classes/stack-classes/SCCStackManager.hpp"
#include "../../exceptions/SCCError.hpp"
#include "../../semantic-classes/SCCSymbol.hpp"
#include "../SCCASTExpression.hpp"

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::generateCode(
    std::ostream& out) const {
    std::vector<SCCData*> paramEvalResults;
    for (SCCASTClasses::Expression* paramExpr : *paramList) {
        paramEvalResults.push_back(paramExpr->generateCodeAndReturnValue(out));
    }
    // Make sure all VReg are on stack
    SCCRegisterManager::preemptCallerSaves(out);
    //! setup stack frame
    size_t funcCallBasePtr = SCCStackManager::currentRSP;
    if (paramEvalResults.size() > 6) {
        if (paramEvalResults.size() & 0x1) {
            if (!(SCCStackManager::currentRSP % 16)) {
                SCCStackManager::pushNullArg(out);
            }
        }
        for (size_t i = paramEvalResults.size(); i >= 6; i--) {
            auto paramVal = paramEvalResults.at(i);
            // Push all paramVal>=6 to stack
            if (paramVal->requireMemoryAccess()) {
                paramVal->loadTo(out, SCCX86Register::AX);
                SCCStackManager::pushRegister(
                    out, SCCX86Register(SCCX86Register::AX));
            } else {
                out << "    pushq   " << paramVal->access();
                SCCStackManager::currentRSP += 8;
            }
        }
    } else {
        SCCStackManager::alignTo16(out);
    }
    for (size_t i = 0; i < 6; i++) {
        if (i >= paramEvalResults.size()) break;
        auto paramVal = paramEvalResults.at(i);
        SCCRegisterManager::useReg(out, SCCX86Register(getRegForArg(i)));
        paramVal->loadTo(out, getRegForArg(i));
    }
    //! Generate Call
    out << "    call    " << this->function->id() << std::endl;
    //! Cleanup params
    for (auto paramVal : paramEvalResults) {
        delete paramVal;
    }
    paramEvalResults.empty();
    //! Cleanup Stack and handle return Value
    SCCRegisterManager::releaseCallerSaves(out);
    // SCCRegisterManager::useReg(out, SCCX86Register(getRegForRet()));
    SCCStackManager::resetRSPTo(out, funcCallBasePtr);
    SCCType funcType = this->function->type();
    funcType.promoteFunc();
    if (funcType.sizeOf() == 0) return nullptr;
    return new SCCDataTempValue(
        SCCX86Register(getRegForRet(), funcType.sizeOf()));
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralChar::generateCode(
    std::ostream& out) const {
    return new SCCDataNumericLiteral(1, this->_valueOfLiteral);
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralNumber::generateCode(
    std::ostream& out) const {
    return new SCCDataNumericLiteral(this->getType().sizeOf(), this->_value);
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralString::generateCode(
    std::ostream& out) const {
    return new SCCDataStringLiteral(8, _label);
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermVariable::generateCode(
    std::ostream& out) const {
    if (this->getType().isArray()) {
        auto locationOfThis = this->_symbol->data->location();
        auto reg = SCCRegisterManager::useAnyReg(out, 8);
        if (locationOfThis->ident() == SCCData::StackVariable) {
            out << "    movq    %rbp, %" << reg.getName() << std::endl;
            out << "    subq    $"
                << ((SCCDataLocationStack*)locationOfThis)->offset << ", %"
                << reg.getName() << std::endl;
        } else {
            assert(locationOfThis->ident() == SCCData::StaticVariable);
            out << "    leaq    "
                << ((SCCDataLocationStatic*)locationOfThis)->name << ", %"
                << reg.getName() << std::endl;
        }
        SCCRegisterManager::releaseReg(reg);
        return new SCCDataTempValue(reg);
    }
    return new SCCDataWrapper(this->_symbol->data);
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermVariable::generateCode(
    std::ostream& out, bool retLValue) const {
    return this->generateCode(out);
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    generateStringLiterals(std::ostream& out) const {
    for (SCCASTClasses::Expression* param : *paramList) {
        param->generateStringLiterals(out);
    }
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralString::
    generateStringLiterals(std::ostream& out) const {
    const_cast<ExprTreeNodeTermLiteralString*>(this)->_label =
        SCCStringLiteralHelper::generateStringLiteral(out, this->_value);
}

SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    ExprTreeNodeTermFuncCall(const SCCSymbol* func)
    : function(func) {
    this->paramList = new std::vector<SCCASTClasses::Expression*>();
}

SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    ~ExprTreeNodeTermFuncCall() {
    for (Expression* nodes : *paramList) {
        nodes->deleteInnerNode();
        delete nodes;
    }
    paramList->clear();
    delete paramList;
    paramList = nullptr;
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    _checkAndSetTypeOfNode() const {
    assert(!_typeOfNodeSet);
    assert(this->function);
    //! Evaluate Parameters
    std::vector<SCCType> typeOfParams;
    for (const SCCASTClasses::Expression* expr : *(this->paramList)) {
        // This also performs type checking for expr
        SCCType typeOfParam = expr->getType();
        if (typeOfParam.isError()) {
            //! If any param has error, stop evaluation for this subtree
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                SCCType();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
        typeOfParams.push_back(typeOfParam);
    }
    SCCType func = this->function->type();
    //! if func type is error, ignore checks and propergate error state
    if (func.isError()) {
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = SCCType();
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
        return;
    }
    //! Check func is FUNCTION
    if (!func.isFunc()) {
        printAndReport("Phase4: Callee not function.", EXP_NOT_FUNC);
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = SCCType();
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
        return;
    }
    //! check if func is defined/declared
    if (func.parameters() == nullptr) {
        //! Function is undefined in this scope, skip param checking
        // // return SCCType();
        func.promoteFunc();
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
        return;
    }
    //! Function is defined at this point
    //! Check parameter count matches
    size_t expectedArgCount = func.parameters()->size();
    size_t actualArgCount = typeOfParams.size();
    if (expectedArgCount != actualArgCount) {
        printAndReport("Phase4: Calling function with mismatched param count.",
                       EXP_INV_ARG);
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = SCCType();
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
        return;
    }
    //! Check param matches
    if (expectedArgCount > 0) {
        const std::vector<SCCType>* expectedParams = func.parameters();
        for (size_t i = 0; i < expectedParams->size(); i++) {
            if (typeOfParams.at(i).isCompatible(expectedParams->at(i)) &&
                typeOfParams.at(i).isPredicate())
                continue;
            // Mis match params
            printAndReport("Phase4: Calling function with mismatched params.",
                           EXP_INV_ARG);
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                SCCType();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
    }
    //! Promote Function to its return value
    func.promoteFunc();
    const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
    const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
    return;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralChar::
    ExprTreeNodeTermLiteralChar(const std::string& value) {
    if (value.length() < 3) {
        // Invalid literal
        this->_valueOfLiteral = 0;
    } else if (value.at(1) == '\\') {
        //! literal with escape chars
        if ((value.at(2) >= '0') && (value.at(2) <= '9')) {
            unsigned char d1 = value.at(2) - '0';
            unsigned char d2 = value.at(3) - '0';
            unsigned char d3 = (value.length() >= 5) ? value.at(4) - '0' : 10;
            this->_valueOfLiteral = 0;
            // next char is num, i.e. '\0'
            if (d2 < 10) {
                if (d3 < 10) {
                    // 3 digit
                    this->_valueOfLiteral += d3 * 100;
                    this->_valueOfLiteral += d2 * 10;
                    this->_valueOfLiteral += d1;
                } else {
                    // 2 digit
                    this->_valueOfLiteral += d2 * 10;
                    this->_valueOfLiteral += d1;
                }
            } else {
                // 1 digit
                this->_valueOfLiteral += d1;
            }
        } else if (value.at(2) == 't') {
            this->_valueOfLiteral = '\t';
        } else if (value.at(2) == 'n') {
            this->_valueOfLiteral = '\n';
        } else if (value.at(2) == '\\') {
            this->_valueOfLiteral = '\\';
        } else {
            this->_valueOfLiteral = 0;
        }
    } else {
        //! simple literals
        // ex. 'a'
        this->_valueOfLiteral = value.at(1);
    }
}
