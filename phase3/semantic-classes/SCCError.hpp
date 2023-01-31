#if !defined(SCC_SEMANTIC_ERROR_HPP)
#define SCC_SEMANTIC_ERROR_HPP

#include <string>

enum SCCSemanticError {
    REDEFINITION, CONFLICT_TYPE, REDECLARATION, UNDECLARED, VOID_VARIABLE
};

void reportSemanticError(const SCCSemanticError errorType, const std::string &symbolName);

#endif // SCC_SEMANTIC_ERROR_HPP
