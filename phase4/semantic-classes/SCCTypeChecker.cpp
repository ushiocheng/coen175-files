#include "SCCTypeChecker.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../GlobalConfig.hpp"
#include "SCCError.hpp"
#include "SCCScope.hpp"
#include "SCCType.hpp"

#ifdef DEBUG
#define PRINT_IF_DEBUG(sth) std::cout << "[DEBUG] " << sth << std::endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

static std::string unaryOperatorStr[5] = {
    "!",      // OP_NOT
    "-",      // OP_NEGATION
    "&",      // OP_ADDR_OF
    "*",      // OP_DEREF
    "sizeof"  // OP_SIZEOF
};
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
    // TODO: [Q7] What should I output for subscript operator? `[]` or `[ ]`?
};

SCCType typeOfExpression(SCCTypeChecker::SCCUnaryOperation op,
                         SCCType operand1) {
    //! If operand is error type, ignore all check and return error
    if (operand1.declaratorType() == SCCType::ERROR) {
        return SCCType();
    }
    //! operands cannot be of invalid type (VOID)
    if (operand1.typeIsNotValid()) {
        printAndReport("Phase4: passing invalid type to unary op.",
                       SCCSemanticError::EXP_INV_OP_UNI, unaryOperatorStr[op]);
        return SCCType();
    }
    //! Promote to Scalar if is array
    operand1.promoteArray();
    // Not promoting Function since function call are also handled as an
    // operator, instead, if a function is treated as a scalar, an error will be
    // thrown
    if (operand1.isFunc()) {
        printAndReport("Phase4: passing function as value.",
                       SCCSemanticError::EXP_INV_OP_UNI, unaryOperatorStr[op]);
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
        case SCCTypeChecker::SCCUnaryOperation::OP_NOT:
            if (!operand1.isPredicate()) {
                printAndReport("Phase4: OP_NOT arg1 is not predicate.",
                               SCCSemanticError::EXP_INV_OP_UNI,
                               unaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);

        case SCCTypeChecker::SCCUnaryOperation::OP_NEGATION:
            if (!operand1.isNumeric()) {
                printAndReport("Phase4: OP_NEGATION arg1 is not numeric.",
                               SCCSemanticError::EXP_INV_OP_UNI,
                               unaryOperatorStr[op]);
                break;
            }
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection(), 0, nullptr, false);

        case SCCTypeChecker::SCCUnaryOperation::OP_ADDR_OF:
            if (!operand1.isLValue()) {
                // TODO: [Q1] check spec to make sure LVALUE error should be
                // returned instead of INV_OP_UNI
                printAndReport("Phase4: Cannot get addr of RValue.",
                               SCCSemanticError::EXP_INV_EXPECT_LVALUE);
                break;
            }
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection() + 1, 0, nullptr, false);

        case SCCTypeChecker::SCCUnaryOperation::OP_DEREF:
            if (!(operand1.isDereferencablePtr())) {
                printAndReport("Phase4: cannot deref whatever this is.",
                               SCCSemanticError::EXP_INV_OP_UNI,
                               unaryOperatorStr[op]);
                break;
            }
            //! Return LValue, this fact is be checked on addrof or runtime
            // TODO: [Q4] Is this the case?
            return SCCType(operand1.specifier(), operand1.declaratorType(),
                           operand1.indirection() - 1, 0, nullptr, true);

        case SCCTypeChecker::SCCUnaryOperation::OP_SIZEOF:
            // TODO: [Q5] Is sizeof function valid? what should it return?
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

SCCType typeOfExpression(SCCTypeChecker::SCCBinaryOperation op,
                         SCCType operand1, SCCType operand2) {
    //! if any op is ERROR type, skip all check and return ERROR
    if (operand1.declaratorType() == SCCType::ERROR) return SCCType();
    if (operand2.declaratorType() == SCCType::ERROR) return SCCType();
    //! operands cannot be of invalid type (VOID)
    if (operand1.typeIsNotValid() || operand2.typeIsNotValid()) {
        printAndReport("Phase4: passing invalid type to bin op.",
                       SCCSemanticError::EXP_INV_OP_BIN, binaryOperatorStr[op]);
    }
    //! promote array to ptr
    operand1.promoteArray();
    operand2.promoteArray();
    // Not promoting Function since function call are also handled as an
    // operator, instead, if a function is treated as a scalar, an error will be
    // thrown
    if (operand1.isFunc() || operand2.isFunc()) {
        printAndReport("Phase4: passing function as value.",
                       SCCSemanticError::EXP_INV_OP_BIN, binaryOperatorStr[op]);
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
        case SCCTypeChecker::SCCBinaryOperation::OP_OR:
        case SCCTypeChecker::SCCBinaryOperation::OP_AND:
            PRINT_IF_DEBUG("Handeling OR/AND");
            if (!(operand1.isPredicate() && operand2.isPredicate())) {
                printAndReport("Phase4: OP_OR/OP_AND arg not predicate",
                               SCCSemanticError::EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCCTypeChecker::SCCBinaryOperation::OP_EQ:
        case SCCTypeChecker::SCCBinaryOperation::OP_NEQ:
            PRINT_IF_DEBUG("Handeling EQ/NEQ");
            if (!operand1.isCompatible(operand2)) {
                printAndReport("Phase4: ops not comparable.",
                               SCCSemanticError::EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCCTypeChecker::SCCBinaryOperation::OP_LT:
        case SCCTypeChecker::SCCBinaryOperation::OP_GT:
        case SCCTypeChecker::SCCBinaryOperation::OP_LE:
        case SCCTypeChecker::SCCBinaryOperation::OP_GE:
            PRINT_IF_DEBUG("Handeling comparators");
            //! [spec] op1 and op2 MUST both be numeric or identital predicate
            //! types, after promotion
            if (!((operand1.isNumeric() && operand2.isNumeric()) ||
                  (operand1.isPredicate() && (operand1 == operand2)))) {
                printAndReport("Phase4: ops not comparable.",
                               SCCSemanticError::EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
                break;
            }
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        case SCCTypeChecker::SCCBinaryOperation::OP_MINUS:
            PRINT_IF_DEBUG("Handeling MINUS");
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
        case SCCTypeChecker::SCCBinaryOperation::OP_ADD:
            PRINT_IF_DEBUG("Handeling MINUS/ADD");
            //! [spec] `num+ptr(T)` OR `ptr(T)+num`
            //! where T is not VOID (T can be ptr(VOID))
            //! [spec] `num+num`

            //! Special case for pointer arithmatic `ptr(T)+-num -> ptr(T)`
            if (operand1.isDereferencablePtr() && operand2.isNumeric()) {
                return SCCType(operand1.specifier(), SCCType::SCALAR,
                               operand1.indirection(), 0, nullptr, false);
            } else if (  //! Special case for `num+ptr(T) -> ptr(T)`
                op == SCCTypeChecker::SCCBinaryOperation::OP_ADD &&
                operand1.isNumeric() && operand2.isDereferencablePtr()) {
                return SCCType(operand2.specifier(), SCCType::SCALAR,
                               operand2.indirection(), 0, nullptr, false);
            }
            //* Intentional fall though for arithmatic op & type checking
        case SCCTypeChecker::SCCBinaryOperation::OP_MUL:
        case SCCTypeChecker::SCCBinaryOperation::OP_DIV:
        case SCCTypeChecker::SCCBinaryOperation::OP_MOD:
            PRINT_IF_DEBUG("Handeling MINUS/ADD/MUL/DIV/MOD");
            //! [spec] op1 & op2 both num
            //! + - * / % shared code region for numeric arithmatic operation
            if (!(operand1.isNumeric() && operand2.isNumeric())) {
                printAndReport("Phase4: ops not compatible with +/-.",
                               SCCSemanticError::EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
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
        case SCCTypeChecker::SCCBinaryOperation::OP_SUBSCRIPT:
            PRINT_IF_DEBUG("Handeling SUBSCRIPT");
            //! [spec] op1 must be ptr(T) where T is not void, op2 must be num
            if (!(operand1.isDereferencablePtr() && operand2.isNumeric())) {
                printAndReport("Phase4: ops not compatible with []",
                               SCCSemanticError::EXP_INV_OP_BIN,
                               binaryOperatorStr[op]);
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

SCCType typeOfExpression(SCCType func, std::vector<SCCType>* parameters) {
    //! Check func is FUNCTION
    if (!func.isFunc()) {
        printAndReport("Phase4: Callee not function.",
                       SCCSemanticError::EXP_NOT_FUNC);
#ifdef VERBOSE_ERROR_MSG
        PRINT_IF_DEBUG("Calling: " << func);
#endif
    }
    //! check if func is defined/declared
    if (func.parameters() == nullptr) {
        //! Function is undefined in this scope.
        // TODO: [Q6] should I return error or skip param type checking?
        // // return SCCType();
        func.promoteFunc();
        return func;
    }
    //! Function is defined at this point
    //! Check parameter count matches
    size_t expectedArgCount = func.parameters()->size();
    size_t actualArgCount = parameters ? parameters->size() : 0;
    if (expectedArgCount != actualArgCount) {
        printAndReport("Phase4: Calling function with mismatched param count.",
                       SCCSemanticError::EXP_INV_ARG);
#ifdef VERBOSE_ERROR_MSG
        std::cout << "[DEBUG] Calling function " << func << "with param: ";
        if (parameters) {
            std::cout << parameters;
        } else {
            std::cout << "[]";
        }
        std::cout << std::endl;
#endif
        return SCCType();
    }
    //! Check param matches
    if (expectedArgCount > 0) {
        const std::vector<SCCType>* expectedParams = func.parameters();
        for (size_t i = 0; i < expectedParams->size(); i++) {
            if (parameters->at(i).isCompatible(expectedParams->at(i)) &&
                parameters->at(i).isPredicate())
                continue;
            // Mis match params
            printAndReport("Phase4: Calling function with mismatched params.",
                           SCCSemanticError::EXP_INV_ARG);
#ifdef VERBOSE_ERROR_MSG
            PRINT_IF_DEBUG("Func: " << func << "Parameter: " << parameters);
#endif
            return SCCType();
        }
    }
    //! Promote Function to its return value
    func.promoteFunc();
    return func;
}

void checkAssign(SCCType lhs, SCCType rhs) {
    //! if any have error type, skip check
    if (lhs.declaratorType() == SCCType::ERROR) return;
    if (rhs.declaratorType() == SCCType::ERROR) return;
    //! Check is LValue
    if (!lhs.isLValue()) {
        printAndReport("Phase4: Assigning to RValue",
                       SCCSemanticError::EXP_INV_EXPECT_LVALUE);
    }
    //! Check compatible
    if (!rhs.isCompatible(lhs)) {
        printAndReport("Phase4: Assign to imcompatible type",
                       SCCSemanticError::EXP_INV_OP_BIN, "=");
    }
}

void checkTestExpr(SCCType testExpr) {
    //! if expr have error type, skip check
    if (testExpr.declaratorType() == SCCType::ERROR) return;
    //! check is Predicate
    if (!testExpr.isPredicate()) {
        printAndReport("Phase4: test expr is not Predicate",
                       SCCSemanticError::EXP_INV_TEST);
    }
}

void checkReturnType(SCCScope* context, SCCType returnType) {
    //! if expr have error type, skip check
    if (returnType.declaratorType() == SCCType::ERROR) return;
    //! get expected return type
    const SCCSymbol* enclosingFunc = context->getEnclosingFunc();
    assert(enclosingFunc);
    //! Check compatible
    SCCType expectedReturnType(enclosingFunc->type());
    expectedReturnType.promoteFunc();
    if (!returnType.isCompatible(expectedReturnType)) {
        printAndReport("Phase4: return type incompatible",
                       SCCSemanticError::EXP_INV_RETURN);
    }
}
