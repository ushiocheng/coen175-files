#include "SCCError.hpp"

#include "../lexer.h"
#include <iostream>

void reportSemanticError(const SCCSemanticError errorType,
                         const std::string &symbolName) {
    switch (errorType) {
        case SCCSemanticError::REDEFINITION:
            report("E1. redefinition of '%s'", symbolName);
            break;
        case SCCSemanticError::REDECLARATION:
            report("E2. conflicting types for '%s'", symbolName);
            break;
        case SCCSemanticError::CONFLICT_TYPE:
            report("E3. redeclaration of '%s'", symbolName);
            break;
        case SCCSemanticError::UNDECLARED:
            report("E4. '%s' undeclared", symbolName);
            break;
        case SCCSemanticError::VOID_VARIABLE:
            report("E5. '%s' has type void", symbolName);
            break;
        default:
            report("SCCSemanticError: unknown error type!!",NULL);
            std::cout << "[ERROR] SCCSemanticError: unknown error type!!" << std::endl;
            exit(1);
    }
}