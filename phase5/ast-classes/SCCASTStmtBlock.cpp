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

// #define DEBUG_OUTPUT_STMT_CODE
static const char* stmtTypeStr[] = {"ASSIGN", "EXPR  ", "RETURN", "WHILE ",
                                    "FOR   ", "IF    ", "BLOCK "};

void SCCASTClasses::StmtBlock::generateCode(std::ostream& out,
                                            const char* indentation) const {
    using std::endl;
    for (Statement* stmt : *(this->innerStatements)) {
        #ifdef DEBUG_OUTPUT_STMT_CODE
        out << indentation << "  # " << stmtTypeStr[stmt->identify()] << endl;
        #endif
        stmt->generateCode(out,indentation);
    }
}
