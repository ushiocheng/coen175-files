#if !defined(SCC_SEMANTIC_ERROR_HPP)
#define SCC_SEMANTIC_ERROR_HPP

#include <exception>
#include <string>

enum SCCSemanticError {
    //! Phase 3 Stuff

    // Phase 3 E1. redefinition of '{{name}}'
    REDEFINITION,
    // Phase 3 E2. conflicting types of '{{name}}'
    CONFLICT_TYPE,
    // Phase 3 E3. redeclaration of '{{name}}'
    REDECLARATION,
    // Phase 3 E4. '{{name}}' undeclaared
    UNDECLARED,
    // Phase 3 E5. '{{name}}' has type void
    VOID_VARIABLE,
    //! Phase 4 Stuff

    // Phase 4 E1. invalid return type
    EXP_INV_RETURN,
    // Phase 4 E2. invalid type for test expression
    EXP_INV_TEST,
    // Phase 4 E3. lvalue required in expression
    EXP_INV_EXPECT_LVALUE,
    // Phase 4 E4. invalid operands to binary {{operator}}
    EXP_INV_OP_BIN,
    // Phase 4 E5. invalid operand to unary {{operator}}
    EXP_INV_OP_UNI,
    // Phase 4 E6. called object is not a function
    EXP_NOT_FUNC,
    // Phase 4 E7. invalid arguments to called function
    EXP_INV_ARG,

    // Extra errors that are not required by spec, generate no output to stderr
    EXTRA_ERROR
};

/**
 * Report an Error (or not if errType is EXTRA_ERROR)
 * and print to stdout when DEBUG is set.
 *
 * @param errType Type of error, default to EXTRA_ERROR which do not output
 * anything
 * @param arg1 id or operator, used only for reporting Error to stderr
 */
void printAndReport(const std::string &str,
                    SCCSemanticError errType = EXTRA_ERROR,
                    const std::string &arg1 = "");

class SCCError : public std::exception {
   private:
    const std::string &_str1;
    SCCSemanticError _errType;
    const std::string &_arg1;

   public:
    SCCError(const std::string &str1, SCCSemanticError errType = EXTRA_ERROR,
             const std::string &arg1 = "")
        : _str1(str1), _errType(errType), _arg1(arg1) {}
    void report() const throw() { printAndReport(_str1, _errType, _arg1); }
};

#endif  // SCC_SEMANTIC_ERROR_HPP
