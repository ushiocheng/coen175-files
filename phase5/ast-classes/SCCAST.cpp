#include "SCCAST.hpp"

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "../semantic-classes/SCCSymbol.hpp"
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

void SCCAST::generateCode(std::ostream& out) const {
    //! Generate Statics
    using std::endl;
    for (SCCSymbol* statics : this->globalScope->getStatics()) {
        if (statics->type().isFunc()) continue;
        out << ".comm   " << statics->id() << "," << statics->type().sizeOf() << endl; 
    }
    out << endl;
    for (SCCASTClasses::Function* funcDef : this->functionDefinitions) {
        funcDef->generateCode(out);
        out << endl;
    }
}