#include "SCCASTFunction.hpp"

#include "SCCASTStmtBlock.hpp"

SCCASTClasses::Function::Function(SCCScope* functionScope) {
    this->innerBlock = new StmtBlock(functionScope);
}

SCCASTClasses::Function::~Function() { delete innerBlock; }

bool SCCASTClasses::Function::performTypeChecking() {
    return innerBlock->performTypeChecking();
}

void SCCASTClasses::Function::generateStringLiterals(std::ostream& out) const {
    this->innerBlock->generateStringLiterals(out);
}

void SCCASTClasses::Function::generateCode(std::ostream& out) const {
    this->innerBlock->generateCode(out);
}