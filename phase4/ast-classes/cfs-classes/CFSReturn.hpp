#if !defined(SCC_AST_CFS_RETURN_HPP)
#define SCC_AST_CFS_RETURN_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"

namespace SCCASTClasses {
class CFSReturn : public CtrFlowStmt {
   public:
    Expression* expr1;

    // return expr1
    CFSReturn(SCCScope* enclosingScope, Expression* expr1)
        : CtrFlowStmt(enclosingScope), expr1(expr1) {}
    StmtType identify() const { return StmtType::RETURN; }
    bool performTypeChecking() const {
        // TODO: check HERE
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_RETURN_HPP
