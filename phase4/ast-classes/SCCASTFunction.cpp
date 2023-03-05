#include "SCCASTFunction.hpp"

#include "../semantic-classes/SCCScope.hpp"
#include "SCCAST.hpp"
#include "SCCASTStatement.hpp"
#include "SCCASTStmtBlock.hpp"

SCCASTClasses::Function::Function(SCCScope* functionScope) {
    this->innerBlock = new StmtBlock(functionScope);
}

SCCASTClasses::Function::~Function() { delete innerBlock; }

bool SCCASTClasses::Function::performTypeChecking() {
    return innerBlock->performTypeChecking();
}