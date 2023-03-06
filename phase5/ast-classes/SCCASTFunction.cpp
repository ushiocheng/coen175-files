#include "SCCASTFunction.hpp"

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTStmtBlock.hpp"
#include "../GlobalConfig.hpp"
#include <cassert>

SCCASTClasses::Function::Function(SCCScope* functionScope) {
    this->innerBlock = new StmtBlock(functionScope);
    this->haveFunctionCall = false;
}

SCCASTClasses::Function::~Function() { delete innerBlock; }

bool SCCASTClasses::Function::performTypeChecking() {
    return innerBlock->performTypeChecking();
}

void SCCASTClasses::Function::generateCode(std::ostream& out) const {
    using std::endl;
    const SCCSymbol* func = this->innerBlock->scope()->getEnclosingFunc();
    out << func->id() << ":" << endl;
    //! Setup parameters
    std::vector<SCCSymbol*> params =
        const_cast<SCCScope*>(this->innerBlock->scope())->getFunctionParams();
    size_t spillParamStackUsage = 0;
    size_t stackAllocationOffset = 0;

    for (size_t paramNum = 0; paramNum < params.size(); paramNum++) {
        SCCSymbol* param = params.at(paramNum);
        switch (paramNum) {
            case 0:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg0Reg);
                break;
            case 1:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg1Reg);
                break;
            case 2:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg2Reg);
                break;
            case 3:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg3Reg);
                break;
            case 4:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg4Reg);
                break;
            case 5:
                param->location =
                    new SCCDataLocationRegister(X86Register::Arg5Reg);
                break;
            default:
                // TODO Phase 6
                assert(false);  // For now
                break;
        }
        if (this->haveFunctionCall && paramNum < 6) {
            //! Prepare to Spill parameters
            spillParamStackUsage += param->type().sizeOf();
        }
    }
    //! Setup Stack Variables
    size_t functionStackSize =
        this->innerBlock->scope()->maxSizeUtilization() + spillParamStackUsage;
    if (functionStackSize & 0xFFFF)
        functionStackSize = (functionStackSize & (!0xFFFF)) + 16;
    //! Generate Prologue
    out << "    pushq   %rbp" << endl;
    out << "    movq    %rsq, %rbp" << endl;
    out << "    subq    $" << functionStackSize
        << ", %rsp \t\t# Allocate Stack Space" << endl;
    //! spill params
    if (this->haveFunctionCall) {
        out << "    # Spilling Parameters" << endl;
        for (size_t paramNum = 0; paramNum < params.size(); paramNum++) {
            if (paramNum >= 6) break;
            SCCSymbol* param = params.at(paramNum);
            stackAllocationOffset += param->type().sizeOf();
            SCCDataLocationStack* newLocation =
                new SCCDataLocationStack(stackAllocationOffset);
            out << "    mov"
                << X86Register::sizeSpecifier(param->type().sizeOf()) << "    "
                << param->location->generateAccess() << ", "
                << newLocation->generateAccess() << endl;
            delete param->location;
            param->location = newLocation;
        }
    }
    out << "    # Function Body" << endl;
    this->innerBlock->generateCode(out, "    ");
    out << "    # Function Epilogue" << endl;
    out << "    movq    %rbp, %rsp" << endl;
    out << "    popq    %rbp" << endl;
    out << "    ret" << endl;
}
