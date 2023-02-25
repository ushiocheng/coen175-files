#include "SCCASTControlFlowStatement.hpp"

#include "../semantic-classes/SCCTypeChecker.hpp"

bool SCCASTClasses::CtrFlowStmt::performTypeCheck() {
    switch (_cfsType) {
        case RETURN:
            checkReturnType(enclosingScope(), _expr1->typeOf());
            break;
        case WHILE:
        case FOR:
        case IF:
            SCCType e1Type = _expr1->typeOf();
            if (e1Type.declaratorType() == SCCType::ERROR) return true;
            else return e1.Type.isPredicate();
        default:
            return false;
    }
    return true;
}

SCCASTClasses::CtrFlowStmt::CtrFlowStmt(SCCScope* enclosingScope,
                                        CFSType cfsType, ExprStmt* expr1,
                                        Statement* stmt1, Statement* stmt2,
                                        Statement* assignment1,
                                        Statement* assignment2)
    : Statement(enclosingScope),
      _cfsType(cfsType),
      _expr1(expr1),
      _stmt1(stmt1),
      _stmt2(stmt2),
      _assignment1(assignment1),
      _assignment2(assignment2) {}

#define SAFE_DELETE(a) \
    if (a) delete (a)

SCCASTClasses::CtrFlowStmt::~CtrFlowStmt() {
    SAFE_DELETE(this->_expr1);
    SAFE_DELETE(this->_stmt1);
    SAFE_DELETE(this->_stmt2);
    SAFE_DELETE(this->_assignment1);
    SAFE_DELETE(this->_assignment2);
}
