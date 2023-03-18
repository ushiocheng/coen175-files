#include "SCCAST.hpp"

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTFunction.hpp"

SCCAST::SCCAST() {
    this->globalScope = new SCCScope(nullptr);
    this->functionDefinitions = std::vector<SCCASTClasses::Function*>();
}

SCCAST::~SCCAST() {
    delete globalScope;
    for (SCCASTClasses::Function* funcDef : functionDefinitions) {
        delete funcDef;
    }
}

bool SCCAST::performTypeChecking() {
    bool noError = true;
    for (SCCASTClasses::Function* funcDef : functionDefinitions) {
        if (!funcDef->performTypeChecking()) noError = false;
    }
    return noError;
}