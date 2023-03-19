#include "SCCASTFunction.hpp"

#include "../code-generation-classes/data-classes/SCCDataArguments.hpp"
#include "../code-generation-classes/data-classes/SCCDataStackVariable.hpp"
#include "../code-generation-classes/data-classes/SCCDataTempValue.hpp"
#include "../code-generation-classes/stack-classes/SCCStackManager.hpp"
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
    using std::endl;
    const SCCSymbol* func = this->innerBlock->scope()->getEnclosingFunc();
    //! generate function label
    out << ".globl  " << func->id() << endl;
    out << func->id() << ":" << endl;
    //! Reset register manager
    SCCRegisterManager::enterFunc(false);
    // TODO: to use callee save, modify enterFunc() to generate callee saves as
    // VRegs
    //! setup parameters
    std::vector<SCCSymbol*> params =
        const_cast<SCCScope*>(this->innerBlock->scope())->getFunctionParams();
    for (size_t i = 0; i < params.size(); i++) {
        auto param = params.at(i);
        if (i < 6) {
            param->data = new SCCDataTempValue(
                SCCX86Register(getRegForArg(i), param->type().sizeOf()));

        } else {
            // Additional param -> on stack
            param->data = new SCCDataArgument(param->type().sizeOf(), i);
        }
    }
    //! Setup Stack Variables
    size_t funcStackSize = this->innerBlock->scope()->maxSizeUtilization();
    SCCStackManager::generatePrelogue(out, funcStackSize);
    const_cast<SCCScope*>(this->innerBlock->scope())->performStackAllocation(0);
    out << "    # Function Body" << endl;
    this->innerBlock->generateCode(out);
    out << ".exit." << func->id() << ":" << endl;
    SCCStackManager::generateEpilogue(out);
    //! Release VRegs for params
    for (auto param : params) {
        delete param->data;
        param->data = nullptr;
    }
    SCCRegisterManager::exitFunc();
}