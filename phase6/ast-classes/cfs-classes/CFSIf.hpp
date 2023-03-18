#if !defined(SCC_AST_CFS_IF_HPP)
#define SCC_AST_CFS_IF_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"
#include "../helper-classes/checkTestExpr.hpp"

namespace SCCASTClasses {
class CFSIf : public CtrFlowStmt {
   public:
    Expression* expr1;
    Statement* stmt1;
    Statement* stmt2;

    // if(expr1) stmt1 [else stmt2]
    CFSIf(Expression* expr1, Statement* stmt1, Statement* stmt2 = nullptr)
        : expr1(expr1), stmt1(stmt1), stmt2(stmt2) {}
    StmtType identify() const { return StmtType::IF; }
    bool performTypeChecking() const {
        SCCType expr1Type = expr1->getType();
        return checkTestExpr(expr1Type);
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_IF_HPP
