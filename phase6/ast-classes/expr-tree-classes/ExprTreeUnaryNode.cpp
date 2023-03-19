#include "ExprTreeUnaryNode.hpp"

#include <cassert>
#include <iostream>
#include <string>

#include "../../GlobalConfig.hpp"
#include "../../SCCOperators.hpp"
#include "../../code-generation-classes/data-classes/SCCData_All.hpp"
#include "../../code-generation-classes/instruction-helper/X86InstructionHelper.hpp"
#include "../../exceptions/SCCError.hpp"
#include "../../semantic-classes/SCCScope.hpp"
#include "../../semantic-classes/SCCType.hpp"

#ifdef DEBUG
// #define DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_IF_DEBUG(sth) std::cout << "[DEBUG] " << sth << std::endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED                                              \
    std::cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ \
              << std::endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

static std::string unaryOperatorStr[5] = {
    "!",      // OP_NOT
    "-",      // OP_NEGATION
    "&",      // OP_ADDR_OF
    "*",      // OP_DEREF
    "sizeof"  // OP_SIZEOF
};

using std::endl;

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryAddrOf::generateCode(
    std::ostream& out) const {
    if (arg1->identify() == NodeType::OP_DEREF) {
        auto tmp =
            ((ExprTreeUnaryNode*)const_cast<ExprTreeNodeUnaryAddrOf*>(this)
                 ->arg1);
        const_cast<ExprTreeNodeUnaryAddrOf*>(this)->arg1 = tmp->arg1;
        tmp->arg1 = nullptr;
        delete tmp;
        return arg1->generateCode(out);
    }
    SCCData* arg1Val = arg1->generateCode(out);
    auto reg = SCCRegisterManager::useAnyReg(out, 8);
    while (arg1Val->ident() == SCCData::Wrapper) {
        auto tmp = arg1Val;
        arg1Val = ((SCCDataWrapper*)arg1Val)->_actual;
        delete tmp;
    }
    switch (arg1Val->ident()) {
        case SCCData::StackVariable:
            out << "    movq    %rbp, %" << reg.getName() << endl;
            out << "    subq    $"
                << ((SCCDataLocationStack*)(arg1Val->location()))->offset
                << ", %" << reg.getName() << endl;
            break;
        case SCCData::StaticVariable:
            out << "    leaq    "
                << ((SCCDataLocationStatic*)(arg1Val->location()))->name
                << ", %" << reg.getName() << endl;
            break;
        case SCCData::Indirect:
            ((SCCDataContentOfAddress*)arg1Val)
                ->loadAddrTo(out, reg.siRegCode());
            break;
        case SCCData::Arguments:
            ((SCCDataArgument*)arg1Val)->loadAddrTo(out, reg.siRegCode());
            break;
        case SCCData::TempValue:
            ((SCCDataTempValue*)arg1Val)->loadAddrTo(out, reg.siRegCode());
            break;
        default:
            assert(false);
    }
    SCCRegisterManager::releaseReg(reg);
    auto tmp = new SCCDataTempValue(reg);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryDeref::generateCode(
    std::ostream& out) const {
    return new SCCDataContentOfAddress(this->getType().sizeOf(),
                                       arg1->generateCode(out));
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryDeref::generateCode(
    std::ostream& out, bool retLValue) const {
    return generateCode(out);
}

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryNegation::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    auto reg = SCCRegisterManager::useAnyReg(out, arg1Val->size());
    arg1Val->loadTo(out, reg.siRegCode());
    reg.castTo(out, this->getType().sizeOf());
    out << "    neg     %" << reg.getName() << endl;
    SCCRegisterManager::releaseReg(reg);
    auto tmp = new SCCDataTempValue(reg);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryNot::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    auto reg = SCCRegisterManager::useAnyReg(out, arg1Val->size());
    arg1Val->loadTo(out, reg.siRegCode());
    reg.castTo(out, this->getType().sizeOf());
    out << "    cmp" << X86InstructionHelper::postfixForSize(reg.getSize())
        << "    $0, %" << reg.getName() << endl;
    auto flagReg = SCCX86Register(reg.siRegCode(), 1);
    out << "    setne   %" << flagReg.getName() << endl;
    out << "    movzbq  %" << flagReg.getName() << ", %" << reg.get64bitName()
        << endl;
    SCCRegisterManager::releaseReg(reg);
    auto tmp = new SCCDataTempValue(reg);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnarySizeof::generateCode(
    std::ostream& out) const {
    return new SCCDataNumericLiteral(8, this->arg1->getType().sizeOf());
}

SCCType typeOfUnaryExpression(SCC::SCCUnaryOperation op, SCCType operand1);

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryAddrOf::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(
        typeOfUnaryExpression(SCC::OP_ADDR_OF, this->arg1->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryDeref::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(
        typeOfUnaryExpression(SCC::OP_DEREF, this->arg1->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryNegation::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(
        typeOfUnaryExpression(SCC::OP_NEGATION, this->arg1->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryNot::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(
        typeOfUnaryExpression(SCC::OP_NOT, this->arg1->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnarySizeof::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(
        typeOfUnaryExpression(SCC::OP_SIZEOF, this->arg1->getType()));
}

SCCType typeOfUnaryExpression(SCC::SCCUnaryOperation op, SCCType operand1) {
    PRINT_FUNC_IF_ENABLED;
    //! If operand is error type, ignore all check and return error
    if (operand1.declaratorType() == SCCType::ERROR) {
        return SCCType();
    }
    //! operands cannot be of invalid type (VOID)
    if (operand1.typeIsNotValid()) {
        printAndReport("Phase4: passing invalid type to unary op.",
                       EXP_INV_OP_UNI, unaryOperatorStr[op]);
        return SCCType();
    }
    //! Promote to Scalar if is array
    operand1.promoteArray();
    // Not promoting Function since function call are also handled as an
    // operator, instead, if a function is treated as a scalar, an error will be
    // thrown
    if (operand1.isFunc()) {
        if (op == SCC::OP_ADDR_OF) {
            printAndReport("Phase4: passing function as value.",
                           EXP_INV_EXPECT_LVALUE);
        } else {
            printAndReport("Phase4: passing function as value.", EXP_INV_OP_UNI,
                           unaryOperatorStr[op]);
        }
        return SCCType();
    }

//! => At this point, op1 must be scalar
#ifdef DEBUG
    if (!(operand1.declaratorType() == SCCType::SCALAR)) {
        std::cout << "Assertion Failed, op1: " << operand1 << std::endl;
        assert(false);
    }
#endif
    //! Handle each operator
    switch (op) {
        case SCC::OP_NOT:
            if (!operand1.isPredicate()) {
                printAndReport("Phase4: OP_NOT arg1 is not predicate.",
                               EXP_INV_OP_UNI, unaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);

        case SCC::OP_NEGATION:
            if (!operand1.isNumeric()) {
                printAndReport("Phase4: OP_NEGATION arg1 is not numeric.",
                               EXP_INV_OP_UNI, unaryOperatorStr[op]);
                break;
            }
            return SCCType(((operand1.specifier() == SCCType::CHAR)
                                ? (SCCType::INT)
                                : (operand1.specifier())),
                           operand1.declaratorType(), operand1.indirection(), 0,
                           nullptr, false);

        case SCC::OP_ADDR_OF:
            if (!operand1.isLValue()) {
                printAndReport("Phase4: Cannot get addr of RValue.",
                               EXP_INV_EXPECT_LVALUE);
                break;
            }
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection() + 1, 0, nullptr, false);

        case SCC::OP_DEREF:
            if (!(operand1.isDereferencablePtr())) {
                printAndReport("Phase4: cannot deref whatever this is.",
                               EXP_INV_OP_UNI, unaryOperatorStr[op]);
                break;
            }
            //! Return LValue, this fact is be checked on addrof or runtime
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection() - 1, 0, nullptr, true);

        case SCC::OP_SIZEOF:
            //* Sizeof (predicate)
            // Everything is a predicate at this point
            return SCCType(SCCType::LONG, SCCType::SCALAR, 0, 0, nullptr,
                           false);

        default:
            break;
    }
//! Error Handeling
#ifdef VERBOSE_ERROR_MSG
    PRINT_IF_DEBUG("Operator: " << unaryOperatorStr[op]
                                << "; Arg1: " << operand1);
#endif
    return SCCType();
}
