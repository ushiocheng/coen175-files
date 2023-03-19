#include "SCCASTAssign.hpp"

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

void SCCASTClasses::Assignment::generateCode(std::ostream& out) const {
    // TODO
}
