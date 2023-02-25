#if !defined(SCC_AST_STATEMENT)
#define SCC_AST_STATEMENT
#include "../semantic-classes/SCCScope.hpp"

namespace SCCASTClasses {

/**
 * Virtual class, enclosing CFS and Expr
 */
class Statement {
   private:
    SCCScope* _enclosingScope;

   public:
    Statement(SCCScope* enclosingScope) : _enclosingScope(enclosingScope){};
    ~Statement();
    const SCCScope* enclosingScope() const { return _enclosingScope; }

    /**
     * Perform Type check on Stmt
     * @return true if no error
     */
    virtual bool performTypeCheck() const = 0;

    // Stuff for phase 5?
    // virtual void generateAsm(const ostream& output) = 0;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_STATEMENT
