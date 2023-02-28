#include "SCCASTFunction.hpp"

#include "../semantic-classes/SCCScope.hpp"
#include "SCCAST.hpp"
#include "SCCASTStatement.hpp"

SCCASTClasses::Function::Function(SCCAST* astRoot, SCCScope* functionScope)
    : astRoot(astRoot), functionScope(functionScope) {
    this->statements = std::vector<Statement*>();
}

SCCASTClasses::Function::~Function() {
    //! Scope memory managed in SCCScope
    // delete functionScope;
    for (Statement* stmt : statements) {
        delete stmt;
    }
}

bool SCCASTClasses::Function::performTypeChecking() {
    bool noError = true;
    for (Statement* stmt : statements) {
        if (!stmt->performTypeChecking()) noError = false;
    }
    return noError;
}