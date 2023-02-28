#if !defined(SCC_AST_CFS_WHILE_HPP)
#define SCC_AST_CFS_WHILE_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"

namespace SCCASTClasses {
class CFSWhile : public CtrFlowStmt {
   public:
    Expression* expr1;
    Statement* body;

    // While (expr1) stmt1
    CFSWhile(SCCScope* enclosingScope, Statement* assign1, Expression* expr1,
             Statement* assign2, Statement* body)
        : CtrFlowStmt(enclosingScope), expr1(expr1), body(body) {}
    StmtType identify() const { return StmtType::WHILE; }
    bool performTypeChecking() const {
        // TODO: check HERE
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_WHILE_HPP
