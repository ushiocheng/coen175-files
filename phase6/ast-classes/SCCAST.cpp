#include "SCCAST.hpp"

#include <vector>

#include "../code-generation-classes/data-classes/SCCDataStaticVariable.hpp"
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

void SCCAST::generateCode(std::ostream& out) const {
    using std::endl;
    //! Generate Global Variables
    for (SCCSymbol* statics : this->globalScope->getStatics()) {
        if (statics->type().isFunc()) continue;
        //! Declare global variables
        out << ".comm   " << statics->id() << ", " << statics->type().sizeOf()
            << endl;
        statics->data =
            new SCCDataStaticVariable(statics->type().sizeOf(), statics->id());
    }
    out << endl;
    //! Generate String Literals
    for (SCCASTClasses::Function* funcDef : this->functionDefinitions) {
        funcDef->generateStringLiterals(out);
    }
    out << endl;
    //! Generate Functions
    for (SCCASTClasses::Function* funcDef : this->functionDefinitions) {
        funcDef->generateCode(out);
        out << endl;
    }
}