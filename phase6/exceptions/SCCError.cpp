#include "SCCError.hpp"

#include <iostream>

#include "../GlobalConfig.hpp"
#include "../lexer.h"

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#endif

/**
 * Report a semantic error use `report()` from lexer.h
 * @param arg1 use in Phase3 errs and phase4 E4-5, id for Phase3 and operator
 * for Phase4
 */
static void reportSemanticError(const SCCSemanticError errorType,
                                const std::string &arg1);

static void reportSemanticError(const SCCSemanticError errorType,
                                const std::string &arg1) {
    switch (errorType) {
        case REDEFINITION:
            report("redefinition of '%s'", arg1);
            break;
        case REDECLARATION:
            report("redeclaration of '%s'", arg1);
            break;
        case CONFLICT_TYPE:
            report("conflicting types for '%s'", arg1);
            break;
        case UNDECLARED:
            report("'%s' undeclared", arg1);
            break;
        case VOID_VARIABLE:
            report("'%s' has type void", arg1);
            break;
        case EXP_INV_RETURN:
            report("invalid return type");
            break;
        case EXP_INV_TEST:
            report("invalid type for test expression");
            break;
        case EXP_INV_EXPECT_LVALUE:
            report("lvalue required in expression");
            break;
        case EXP_INV_OP_BIN:
            report("invalid operands to binary %s", arg1);
            break;
        case EXP_INV_OP_UNI:
            report("invalid operand to unary %s", arg1);
            break;
        case EXP_NOT_FUNC:
            report("called object is not a function");
            break;
        case EXP_INV_ARG:
            report("invalid arguments to called function");
            break;
        case EXTRA_ERROR:
            break;  //! Extra errors that should not be report to stderr
        default:
            report("SCCSemanticError: unknown error type!!", NULL);
            std::cerr << "[ERROR] SCCSemanticError: unknown error type!!"
                      << std::endl;
            exit(1);
    }
}

void printAndReport(const std::string &str, SCCSemanticError errType,
                    const std::string &arg1) {
#ifdef DEBUG_ADDITIONAL_WARNING
    std::cerr << "[WARN] " << str << std::endl;
#endif
    reportSemanticError(errType, arg1);
}
