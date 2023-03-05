#include "SCCASTAssign.hpp"

SCCASTClasses::Assignment::Assignment(ExprTreeClasses::ExprTreeNode* lhs,
                                      ExprTreeClasses::ExprTreeNode* rhs)
    : lhs(lhs), rhs(rhs) {}

SCCASTClasses::Assignment::~Assignment() {
    delete lhs;
    delete rhs;
}

bool SCCASTClasses::Assignment::performTypeChecking() const {
    // TODO: check assignment here
}