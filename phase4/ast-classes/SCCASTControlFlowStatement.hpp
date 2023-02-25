#if !defined(SCC_AST_CONTROL_FLOW_STATEMENT_HPP)
#define SCC_AST_CONTROL_FLOW_STATEMENT_HPP

#include "SCCASTExpression.hpp"
#include "SCCASTStatement.hpp"

namespace SCCASTClasses {

class CtrFlowStmt : public Statement {
   public:
    enum CFSType { RETURN, WHILE, FOR, IF };
    // return _expr1
    // while (expr1) stmt1
    // for (assignment1; expr1; assignment2) stmt1
    // if (expr1) stmt1 [else stmt2]
   private:
    CFSType _cfsType;
    ExprStmt* _expr1;
    Statement* _stmt1;
    Statement* _stmt2;
    Statement* _assignment1;
    Statement* _assignment2;

   public:
    bool performTypeCheck();
    CtrFlowStmt(SCCScope* enclosingScope, CFSType cfsType, ExprStmt* expr1, Statement* stmt1 = nullptr,
                Statement* stmt2 = nullptr, Statement* assignment1 = nullptr,
                Statement* assignment2 = nullptr);
    ~CtrFlowStmt();
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_CONTROL_FLOW_STATEMENT_HPP
