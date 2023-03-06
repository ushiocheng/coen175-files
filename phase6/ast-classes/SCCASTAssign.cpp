#include "SCCASTAssign.hpp"
#include "../GlobalConfig.hpp"
#include <cassert>

SCCASTClasses::Assignment::Assignment(ExprTreeClasses::ExprTreeNode* lhs,
                                      ExprTreeClasses::ExprTreeNode* rhs)
    : lhs(lhs), rhs(rhs) {}

SCCASTClasses::Assignment::~Assignment() {
    delete lhs;
    delete rhs;
}

#include "../exceptions/SCCError.hpp"

bool SCCASTClasses::Assignment::performTypeChecking() const {
    SCCType lhsType = lhs->getType();
    if (lhsType.isError()) return false;
    SCCType rhsType = rhs->getType();
    if (rhsType.isError()) return false;
    //! Check is LValue
    if (!lhsType.isLValue()) {
        return false;
    }
    //! Check compatible
    if (!rhsType.isCompatible(lhsType)) {
        return false;
    }
    return true;
}

#include "expr-tree-classes/ExprTreeTermNode.hpp"

void SCCASTClasses::Assignment::generateCode(std::ostream& out, const char* indentation) const{
    //! For Phase 5 ONLY, lhs will always be a scalar int
    assert(lhs->identify() == ExprTreeClasses::T_VAR);
    SCCDataLocation* targetLocation = lhs->generateCodeToEvaluateExprNode(out, indentation);
    SCCDataLocation* sourceLocation = rhs->generateCodeToEvaluateExprNode(out, indentation);
    if (sourceLocation->requireMemoryAccess()) {
        out << indentation << "movl    " << sourceLocation->generateAccess() << ", %eax" << std::endl;
        delete sourceLocation;
        sourceLocation = new SCCDataLocationRegister(X86Register::EAX);
    }
    out << indentation << "movl    " << sourceLocation->generateAccess() << ", " << targetLocation->generateAccess() << std::endl;
}
