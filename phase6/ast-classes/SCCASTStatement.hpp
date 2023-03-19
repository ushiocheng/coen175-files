#if !defined(SCC_AST_STATEMENT)
#define SCC_AST_STATEMENT
#include "../semantic-classes/SCCScope.hpp"

namespace SCCASTClasses {

/**
 * Virtual class, enclosing CFS and Expr
 */
class Statement {
   public:
    virtual ~Statement();

    enum StmtType { ASSIGN, EXPR, RETURN, WHILE, FOR, IF, BLOCK };
    /**
     * idenitfy API for RTTI
     */
    virtual StmtType identify() const = 0;

    /**
     * Phase 4 - Perform Static Type Checking
     * @return true if no error is generated on type checking
     */
    virtual bool performTypeChecking() const = 0;
    // Code generation Interfaces
    virtual void generateStringLiterals(std::ostream& out) const = 0;
    virtual void generateCode(std::ostream& out) const = 0;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_STATEMENT
