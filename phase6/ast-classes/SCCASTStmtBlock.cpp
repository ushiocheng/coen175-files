#include "SCCASTStmtBlock.hpp"

SCCASTClasses::StmtBlock::StmtBlock(SCCScope* scope) : _scope(scope) {
    this->innerStatements = new std::vector<Statement*>();
}

SCCASTClasses::StmtBlock::~StmtBlock() {
    for (Statement* stmt : *innerStatements) delete stmt;
    delete innerStatements;
}

SCCASTClasses::Statement::StmtType SCCASTClasses::StmtBlock::identify() const {
    return BLOCK;
}

const SCCScope* SCCASTClasses::StmtBlock::scope() const { return this->_scope; }

bool SCCASTClasses::StmtBlock::performTypeChecking() const {
    bool noError = true;
    for (Statement* stmt : *innerStatements) {
        if (!stmt->performTypeChecking()) noError = false;
    }
    return noError;
}

void SCCASTClasses::StmtBlock::generateStringLiterals(std::ostream& out) const {
    for (Statement* stmt : *innerStatements) stmt->generateStringLiterals(out);
}

void SCCASTClasses::StmtBlock::generateCode(std::ostream& out) const {
    for (Statement* stmt : *innerStatements) {
        stmt->generateCode(out);
    }
}
