#if !defined(SCC_AST_CFS_WHILE_HPP)
#define SCC_AST_CFS_WHILE_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"
#include "../helper-classes/checkTestExpr.hpp"

namespace SCCASTClasses {
class CFSWhile : public CtrFlowStmt {
   public:
    Expression* expr1;
    Statement* body;

    // While (expr1) stmt1
    CFSWhile(Expression* expr1, Statement* body)
        : expr1(expr1), body(body) {}
    StmtType identify() const { return StmtType::WHILE; }
    bool performTypeChecking() const {
        SCCType expr1Type = expr1->getType();
        return checkTestExpr(expr1Type);
    }
    void generateCode(std::ostream& out, const char* indentation = "") const{} // TODO Phase 6
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_WHILE_HPP
