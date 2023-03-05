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
        printAndReport("Phase4: Assigning to RValue",
                       EXP_INV_EXPECT_LVALUE);
        return false;
    }
    //! Check compatible
    if (!rhsType.isCompatible(lhsType)) {
        printAndReport("Phase4: Assign to imcompatible type",
                       EXP_INV_OP_BIN, "=");
        return false;
    }
    return true;
}
