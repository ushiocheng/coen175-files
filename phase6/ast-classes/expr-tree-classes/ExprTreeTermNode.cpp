#include "ExprTreeTermNode.hpp"

#include <vector>

#include "../../exceptions/SCCError.hpp"
#include "../../semantic-classes/SCCSymbol.hpp"
#include "../SCCASTExpression.hpp"

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::generateCode(
    std::ostream& out) const {
    // TODO
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralChar::generateCode(
    std::ostream& out) const {
    // TODO
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralNumber::generateCode(
    std::ostream& out) const {
    // TODO
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralString::generateCode(
    std::ostream& out) const {
    // TODO
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermVariable::generateCode(
    std::ostream& out) const {
    // TODO
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermVariable::generateCode(
    std::ostream& out, bool retLValue) const {
    // TODO
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralString::
    generateStringLiterals(std::ostream& out) const {
    // TODO
}

SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    ExprTreeNodeTermFuncCall(const SCCSymbol* func)
    : function(func) {
    this->paramList = new std::vector<SCCASTClasses::Expression*>();
}

SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall::
    ~ExprTreeNodeTermFuncCall() {
    for (Expression* nodes : *paramList) {
        delete nodes;
    }
    delete paramList;
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
