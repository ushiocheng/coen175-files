#include "ExprTreeBinaryNode.hpp"

#include <cassert>
#include <iostream>
#include <string>

#include "../../GlobalConfig.hpp"
#include "../../SCCOperators.hpp"
#include "../../code-generation-classes/data-classes/SCCData_All.hpp"
#include "../../code-generation-classes/instruction-helper/X86InstructionHelper.hpp"
#include "../../code-generation-classes/label-classes/SCCLabelHelper.hpp"
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
static std::string binaryOperatorStr[14] = {
    "||",  // OP_OR
    "&&",  // OP_AND
    "==",  // OP_EQ
    "!=",  // OP_NEQ
    "<",   // OP_LT
    ">",   // OP_GT
    "<=",  // OP_LE
    ">=",  // OP_GE
    "+",   // OP_ADD
    "-",   // OP_MINUS
    "*",   // OP_MUL
    "/",   // OP_DIV
    "%",   // OP_MOD
    "[]"   // OP_SUBSCRIPT
};

using std::endl;

//! AND and OR have short circuit evaluation -> special cases

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAnd::generateCode(
    std::ostream& out) const {
    std::string shortCircuitLabel = SCCLabelHelper::reserveNewLabel("and1");
    std::string exitLabel = SCCLabelHelper::reserveNewLabel("and2");
    SCCData* arg1Val = arg1->generateCode(out);
    auto reg = SCCRegisterManager::useAnyReg(out, arg1Val->size());
    arg1Val->loadTo(out, reg.siRegCode());
    delete arg1Val;
    out << "    cmp" << X86InstructionHelper::postfixForSize(reg.getSize())
        << "    $0, %" << reg.getName() << endl;
    out << "    je      " << shortCircuitLabel << endl;
    out << "    nop" << endl;
    SCCData* arg2Val = arg2->generateCode(out);
    arg2Val->loadTo(out, reg.siRegCode());
    reg = SCCX86Register(reg.siRegCode(), arg2Val->size());
    delete arg2Val;
    out << "    cmp" << X86InstructionHelper::postfixForSize(reg.getSize())
        << "    $0, %" << reg.getName() << endl;
    out << "    je      " << shortCircuitLabel << endl;
    out << "    nop" << endl;
    //! Compute return value
    out << "    movq    $1, %" << reg.get64bitName() << endl;
    out << "    jmp     " << exitLabel << endl;
    out << "    nop" << endl;
    SCCLabelHelper::generateReservedLabel(out, shortCircuitLabel);
    out << "    movq    $0, %" << reg.get64bitName() << endl;
    SCCLabelHelper::generateReservedLabel(out, exitLabel);
    SCCRegisterManager::releaseReg(reg);
    return new SCCDataTempValue(SCCX86Register(reg.siRegCode()));
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryOR::generateCode(
    std::ostream& out) const {
    std::string shortCircuitLabel = SCCLabelHelper::reserveNewLabel("and1");
    std::string exitLabel = SCCLabelHelper::reserveNewLabel("and2");
    SCCData* arg1Val = arg1->generateCode(out);
    auto reg = SCCRegisterManager::useAnyReg(out, arg1Val->size());
    arg1Val->loadTo(out, reg.siRegCode());
    delete arg1Val;
    out << "    cmp" << X86InstructionHelper::postfixForSize(reg.getSize())
        << "    $0, %" << reg.getName() << endl;
    out << "    jne     " << shortCircuitLabel << endl;
    out << "    nop" << endl;
    SCCData* arg2Val = arg2->generateCode(out);
    arg2Val->loadTo(out, reg.siRegCode());
    reg = SCCX86Register(reg.siRegCode(), arg2Val->size());
    delete arg2Val;
    out << "    cmp" << X86InstructionHelper::postfixForSize(reg.getSize())
        << "    $0, %" << reg.getName() << endl;
    out << "    jne     " << shortCircuitLabel << endl;
    out << "    nop" << endl;
    //! Compute return value
    out << "    movq    $0, %" << reg.get64bitName() << endl;
    out << "    jmp     " << exitLabel << endl;
    out << "    nop" << endl;
    SCCLabelHelper::generateReservedLabel(out, shortCircuitLabel);
    out << "    movq    $1, %" << reg.get64bitName() << endl;
    SCCLabelHelper::generateReservedLabel(out, exitLabel);
    SCCRegisterManager::releaseReg(reg);
    return new SCCDataTempValue(SCCX86Register(reg.siRegCode()));
}

//! Arithmatic Binary Ops

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAdd::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Add arg1Val reg2 -> reg2
    out << "    add" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMinus::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Minus arg1Val reg2 -> reg2
    out << "    sub" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryDiv::generateCode(
    std::ostream& out) const {
        SCCData* arg1Val = arg1->generateCode(out);
        SCCData* arg2Val = arg2->generateCode(out);
        unsigned char resSize = arg1Val->size();
        if (arg2Val->size() > resSize) resSize = arg2Val->size();
        auto reg10 = SCCX86Register(SCCX86Register::AX, resSize);
        auto reg11 = SCCX86Register(SCCX86Register::DX, resSize);
        SCCRegisterManager::useReg(out, reg10);
        arg1Val->loadTo(out, reg10.siRegCode());
        reg10.castTo(out, 8);
        SCCRegisterManager::useReg(out, reg11);
        out << "    " << X86InstructionHelper::movForSize(8) << "    "
            << "%" << reg10.get64bitName() << ", %" << reg11.get64bitName()
            << endl;
        out << "    sar" << X86InstructionHelper::postfixForSize(8) << "    "
            << "$" << X86InstructionHelper::numBitForSize(resSize) - 1 << ", %"
            << reg11.getName() << endl;
        out << "    idiv" << X86InstructionHelper::postfixForSize(resSize)
            << "   " << arg2Val->access() << endl;
        SCCRegisterManager::releaseReg(reg11);
        SCCRegisterManager::releaseReg(reg10);
        return new SCCDataTempValue(reg10);
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMod::generateCode(
    std::ostream& out) const {
        SCCData* arg1Val = arg1->generateCode(out);
        SCCData* arg2Val = arg2->generateCode(out);
        unsigned char resSize = arg1Val->size();
        if (arg2Val->size() > resSize) resSize = arg2Val->size();
        auto reg10 = SCCX86Register(SCCX86Register::AX, resSize);
        auto reg11 = SCCX86Register(SCCX86Register::DX, resSize);
        SCCRegisterManager::useReg(out, reg10);
        arg1Val->loadTo(out, reg10.siRegCode());
        reg10.castTo(out, 8);
        SCCRegisterManager::useReg(out, reg11);
        out << "    " << X86InstructionHelper::movForSize(8) << "    "
            << "%" << reg10.get64bitName() << ", %" << reg11.get64bitName()
            << endl;
        out << "    sar" << X86InstructionHelper::postfixForSize(8) << "    "
            << "$" << X86InstructionHelper::numBitForSize(resSize) - 1 << ", %"
            << reg11.getName() << endl;
        out << "    idiv" << X86InstructionHelper::postfixForSize(resSize)
            << "   " << arg2Val->access() << endl;
        SCCRegisterManager::releaseReg(reg10);
        SCCRegisterManager::releaseReg(reg11);
        return new SCCDataTempValue(reg11);
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMUL::generateCode(
    std::ostream& out) const {
        SCCData* arg1Val = arg1->generateCode(out);
        SCCData* arg2Val = arg2->generateCode(out);
        auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
        arg2Val->loadTo(out, reg2.siRegCode());
        //! Cast Size
        unsigned char resSize = arg1Val->size();
        if (arg2Val->size() > resSize) resSize = arg2Val->size();
        delete arg2Val;
        reg2.castTo(out, resSize);
        //! Multiply arg1Val reg2 -> reg2
        out << "    imul" << X86InstructionHelper::postfixForSize(resSize)
            << "   " << arg1Val->access() << ", %" << reg2.getName() << endl;
        SCCRegisterManager::releaseReg(reg2);
        auto tmp = new SCCDataTempValue(reg2);
        delete arg1Val;
        return tmp;
}

//! Comparasions

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryEQ::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    sete    %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}

SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGE::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    setge   %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGT::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    setg    %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLE::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    setle   %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLT::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    setl     %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}
SCCData* SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryNEQ::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    //! Cast Size
    unsigned char resSize = arg1Val->size();
    if (arg2Val->size() > resSize) resSize = arg2Val->size();
    delete arg2Val;
    reg2.castTo(out, resSize);
    //! Compare arg1Val reg2 -> reg2
    out << "    cmp" << X86InstructionHelper::postfixForSize(resSize) << "    "
        << arg1Val->access() << ", %" << reg2.getName() << endl;
    out << "    setne   %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << endl;
    out << "    movzbq  %" << SCCX86Register(reg2.siRegCode(), 1).getName()
        << ", %" << reg2.get64bitName() << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return tmp;
}

//! Subscript operator => special case

SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinarySubscript::generateCode(
    std::ostream& out) const {
    SCCData* arg1Val = arg1->generateCode(out);
    SCCData* arg2Val = arg2->generateCode(out);
    auto reg2 = SCCRegisterManager::useAnyReg(out, arg2Val->size());
    arg2Val->loadTo(out, reg2.siRegCode());
    delete arg2Val;
    //! Cast Size
    unsigned char resSize = 8;
    reg2.castTo(out, resSize);
    //! *( arg2 * sizeof (*arg1) + arg1 )
    unsigned char shift = 0;
    switch (this->getType().sizeOf()) {
        case 8:
            shift = 3;
            break;
        case 4:
            shift = 2;
            break;
        case 2:
            shift = 1;
            break;
        default:
            break;
    }
    if (shift > 0) {
        out << "    salq    $" << shift << ", %" << reg2.get64bitName() << endl;
    }
    out << "    addq    " << arg1Val->access() << ", %" << reg2.get64bitName()
        << endl;
    SCCRegisterManager::releaseReg(reg2);
    auto tmp = new SCCDataTempValue(reg2);
    delete arg1Val;
    return new SCCDataContentOfAddress(this->getType().sizeOf(), tmp);
}
SCCData*
SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinarySubscript::generateCode(
    std::ostream& out, bool retLValue) const {
    return generateCode(out);
}

SCCType typeOfBinaryExpression(SCC::SCCBinaryOperation op, SCCType operand1,
                               SCCType operand2);

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAdd::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_ADD, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAnd::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_AND, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryDiv::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_DIV, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryEQ::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_EQ, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGE::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_GE, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGT::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_GT, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLE::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_LE, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLT::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_LT, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMinus::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_MINUS, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMod::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_MOD, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMUL::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_MUL, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryNEQ::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_NEQ, this->arg1->getType(), this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryOR::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(SCC::OP_OR, this->arg1->getType(),
                                              this->arg2->getType()));
}

void SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinarySubscript::
    _checkAndSetTypeOfNode() const {
    this->_setNodeType(typeOfBinaryExpression(
        SCC::OP_SUBSCRIPT, this->arg1->getType(), this->arg2->getType()));
}

SCCType typeOfBinaryExpression(SCC::SCCBinaryOperation op, SCCType operand1,
                               SCCType operand2) {
    PRINT_FUNC_IF_ENABLED;
    //! if any op is ERROR type, skip all check and return ERROR
    if (operand1.declaratorType() == SCCType::ERROR) return SCCType();
    if (operand2.declaratorType() == SCCType::ERROR) return SCCType();
    //! operands cannot be of invalid type (VOID)
    if (operand1.typeIsNotValid() || operand2.typeIsNotValid()) {
        printAndReport("Phase4: passing invalid type to bin op.",
                       EXP_INV_OP_BIN, binaryOperatorStr[op]);
        return SCCType();
    }
    //! promote array to ptr
    operand1.promoteArray();
    operand2.promoteArray();
    // Not promoting Function since function call are also handled as an
    // operator, instead, if a function is treated as a scalar, an error will be
    // thrown
    if (operand1.isFunc() || operand2.isFunc()) {
        printAndReport("Phase4: passing function as value.", EXP_INV_OP_BIN,
                       binaryOperatorStr[op]);
        return SCCType();
    }

//! op1 & op2 must be SCALAR
#ifdef DEBUG
    if (!(operand1.declaratorType() == SCCType::SCALAR)) {
        std::cout << "Assertion Failed, op1: " << operand1 << std::endl;
        assert(false);
    }
    if (!(operand2.declaratorType() == SCCType::SCALAR)) {
        std::cout << "Assertion Failed, op2: " << operand2 << std::endl;
        assert(false);
    }
#endif
    //! handle each operator
    switch (op) {
        case SCC::OP_OR:
        case SCC::OP_AND:
            // PRINT_IF_DEBUG("Handeling OR/AND");
            if (!(operand1.isPredicate() && operand2.isPredicate())) {
                printAndReport("Phase4: OP_OR/OP_AND arg not predicate",
                               EXP_INV_OP_BIN, binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCC::OP_EQ:
        case SCC::OP_NEQ:
            // PRINT_IF_DEBUG("Handeling EQ/NEQ");
            if (!operand1.isCompatible(operand2)) {
                printAndReport("Phase4: ops not comparable.", EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCC::OP_LT:
        case SCC::OP_GT:
        case SCC::OP_LE:
        case SCC::OP_GE:
            // PRINT_IF_DEBUG("Handeling comparators");
            //! [spec] op1 and op2 MUST both be numeric or identital predicate
            //! types, after promotion
            if (!((operand1.isNumeric() && operand2.isNumeric()) ||
                  (operand1.isPredicate() && (operand1 == operand2)))) {
                printAndReport("Phase4: ops not comparable.", EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCC::OP_MINUS:
            // PRINT_IF_DEBUG("Handeling MINUS");
            //! [spec] `ptr(T)-ptr(T)` OR `ptr(T)-num`
            //! where T is not VOID (T can be ptr(VOID))
            //! [spec] `num-num`

            //! Special case for pointer arithmatic `ptr(T)-ptr(T) -> long`
            if (operand1.isDereferencablePtr() &&
                operand2.isDereferencablePtr() && (operand1 == operand2)) {
                return SCCType(SCCType::LONG, SCCType::SCALAR, 0, 0, nullptr,
                               false);
            }
            //* Intentional fall though for arithmatic op & type checking
        case SCC::OP_ADD:
            // PRINT_IF_DEBUG("Handeling MINUS/ADD");
            //! [spec] `num+ptr(T)` OR `ptr(T)+num`
            //! where T is not VOID (T can be ptr(VOID))
            //! [spec] `num+num`

            //! Special case for pointer arithmatic `ptr(T)+-num -> ptr(T)`
            if (operand1.isDereferencablePtr() && operand2.isNumeric()) {
                return SCCType(operand1.specifier(), SCCType::SCALAR,
                               operand1.indirection(), 0, nullptr, false);
            } else if (  //! Special case for `num+ptr(T) -> ptr(T)`
                op == SCC::OP_ADD && operand1.isNumeric() &&
                operand2.isDereferencablePtr()) {
                return SCCType(operand2.specifier(), SCCType::SCALAR,
                               operand2.indirection(), 0, nullptr, false);
            }
            //* Intentional fall though for arithmatic op & type checking
        case SCC::OP_MUL:
        case SCC::OP_DIV:
        case SCC::OP_MOD:
            // PRINT_IF_DEBUG("Handeling MINUS/ADD/MUL/DIV/MOD");
            //! [spec] op1 & op2 both num
            //! + - * / % shared code region for numeric arithmatic operation
            if (!(operand1.isNumeric() && operand2.isNumeric())) {
                printAndReport("Phase4: ops not compatible with +/-.",
                               EXP_INV_OP_BIN, binaryOperatorStr[op]);
                break;
            }
            //! op1 and op2 both numeric
            if (operand1.specifier() == SCCType::LONG ||
                operand2.specifier() == SCCType::LONG) {
                return SCCType(SCCType::LONG, SCCType::SCALAR, 0, 0, nullptr,
                               false);
            } else {
                return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr,
                               false);
            }
        case SCC::OP_SUBSCRIPT:
            // PRINT_IF_DEBUG("Handeling SUBSCRIPT");
            //! [spec] op1 must be ptr(T) where T is not void, op2 must be num
            if (!(operand1.isDereferencablePtr() && operand2.isNumeric())) {
                printAndReport("Phase4: ops not compatible with []",
                               EXP_INV_OP_BIN, binaryOperatorStr[op]);
                break;
            }
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection() - 1, 0, nullptr, true);
        default:
            break;
    }
//! Error Handeling
#ifdef VERBOSE_ERROR_MSG
    PRINT_IF_DEBUG("Operator: " << binaryOperatorStr[op] << "; Arg1: "
                                << operand1 << "; Arg2: " << operand2);
#endif
    return SCCType();
}