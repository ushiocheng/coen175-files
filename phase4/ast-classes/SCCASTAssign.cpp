#include "SCCASTAssign.hpp"

SCCASTClasses::Assignment::Assignment(SCCScope* enclosingScope,
                                      ExprTreeClasses::ExprTreeNode* lhs,
                                      ExprTreeClasses::ExprTreeNode* rhs)
    : Statement(enclosingScope), lhs(lhs), rhs(rhs) {}

SCCASTClasses::Assignment::~Assignment() {
    delete lhs;
    delete rhs;
}

bool SCCASTClasses::Assignment::performTypeChecking() const {
    // TODO: check assignment here
}