#if !defined(SCC_AST_CFS_FOR_HPP)
#define SCC_AST_CFS_FOR_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"

namespace SCCASTClasses {
class CFSFor : public CtrFlowStmt {
   public:
    Statement* assign1;
    Expression* expr1;
    Statement* assign2;
    Statement* body;

    // For (assignment; expression; assignment) statement
    CFSFor(SCCScope* enclosingScope, Statement* assign1, Expression* expr1,
           Statement* assign2, Statement* body)
        : CtrFlowStmt(enclosingScope),
          assign1(assign1),
          expr1(expr1),
          assign2(assign2),
          body(body) {}
    StmtType identify() const { return StmtType::FOR; }
    bool performTypeChecking() const {
        // TODO: check HERE
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_FOR_HPP
