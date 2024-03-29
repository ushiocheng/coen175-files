#if !defined(SCC_SEMANTIC_ERROR_HPP)
#define SCC_SEMANTIC_ERROR_HPP

#include <string>

enum SCCSemanticError {
    REDEFINITION,
    CONFLICT_TYPE,
    REDECLARATION,
    UNDECLARED,
    VOID_VARIABLE,
    EXTRA_ERROR
};

void reportSemanticError(const SCCSemanticError errorType,
                         const std::string &symbolName);

void printAndReport(const std::string &str,
                    SCCSemanticError errType = EXTRA_ERROR,
                    const std::string &id = "");

#endif  // SCC_SEMANTIC_ERROR_HPP
