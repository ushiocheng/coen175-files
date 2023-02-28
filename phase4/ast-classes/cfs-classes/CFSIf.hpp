#if !defined(SCC_AST_CFS_IF_HPP)
#define SCC_AST_CFS_IF_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"

namespace SCCASTClasses {
class CFSIf : public CtrFlowStmt {
   public:
    Expression* expr1;
    Statement* stmt1;
    Statement* stmt2;

    // if(expr1) stmt1 [else stmt2]
    CFSIf(SCCScope* enclosingScope, Expression* expr1, Statement* stmt1,
          Statement* stmt2 = nullptr)
        : CtrFlowStmt(enclosingScope),
          expr1(expr1),
          stmt1(stmt1),
          stmt2(stmt2) {}
    StmtType identify() const { return StmtType::IF; }
    bool performTypeChecking() const {
        // TODO: check HERE
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_IF_HPP
