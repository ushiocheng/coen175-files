#include "SCCASTExpression.hpp"

SCCASTClasses::Expression::Expression(
    ExprTreeClasses::ExprTreeNode* exprTreeRoot)
    : exprTreeRoot(exprTreeRoot) {}

#ifdef DEBUG
#include <iostream>
#endif

SCCASTClasses::Expression::~Expression() {}

void SCCASTClasses::Expression::deleteInnerNode() {
    if (this->exprTreeRoot) {
        auto tmp = exprTreeRoot;
        this->exprTreeRoot = nullptr;
        delete tmp;
    }
}

SCCASTClasses::Statement::StmtType SCCASTClasses::Expression::identify() const {
    return StmtType::EXPR;
}

bool SCCASTClasses::Expression::performTypeChecking() const {
    return exprTreeRoot->performTypeChecking();
}

SCCType SCCASTClasses::Expression::getType() const {
    return exprTreeRoot->getType();
}

// Code generation Interfaces
void SCCASTClasses::Expression::generateStringLiterals(
    std::ostream& out) const {
    exprTreeRoot->generateStringLiterals(out);
}
void SCCASTClasses::Expression::generateCode(std::ostream& out) const {
    auto res = exprTreeRoot->generateCode(out);
    if (res) delete res;
}
SCCData* SCCASTClasses::Expression::generateCodeAndReturnValue(
    std::ostream& out) const {
    return exprTreeRoot->generateCode(out);
}