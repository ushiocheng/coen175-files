#include "SCCError.hpp"

#include <iostream>

#include "../GlobalConfig.hpp"
#include "../lexer.h"

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#endif

void reportSemanticError(const SCCSemanticError errorType,
                         const std::string &symbolName) {
    switch (errorType) {
        case SCCSemanticError::REDEFINITION:
            report("redefinition of '%s'", symbolName);
            break;
        case SCCSemanticError::REDECLARATION:
            report("redeclaration of '%s'", symbolName);
            break;
        case SCCSemanticError::CONFLICT_TYPE:
            report("conflicting types for '%s'", symbolName);
            break;
        case SCCSemanticError::UNDECLARED:
            report("'%s' undeclared", symbolName);
            break;
        case SCCSemanticError::VOID_VARIABLE:
            report("'%s' has type void", symbolName);
            break;
        case SCCSemanticError::EXTRA_ERROR:
            //! Extra errors that should not be report to stderr
            break;
        default:
            report("SCCSemanticError: unknown error type!!", NULL);
            std::cout << "[ERROR] SCCSemanticError: unknown error type!!"
                      << std::endl;
            exit(1);
    }
}

void printAndReport(const std::string &str, SCCSemanticError errType,
                    const std::string &id) {
#ifdef DEBUG_ADDITIONAL_WARNING
    std::cout << "[WARN] " << str << std::endl;
#endif
    reportSemanticError(errType, id);
}
