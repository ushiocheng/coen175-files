#include "SCCStackManager.hpp"

#include "../../GlobalConfig.hpp"

namespace SCCStackManager {
static size_t currentRSP;
/*
    A full stack frame of a function can look like this
        Args (Multiple of 16 bytes)
        ret RIP (8 byte)
    -- Initial RSP --
        Caller RBP (8 byte)
    !-- This RBP -- position 0 for this class
        Spilled Args (Multiple of 8 bytes)
        Stack Variables (May not be all used, anyway)
        // align this to 16 bytes just because
    -- RSP when func start --
        Spilled Registers (Multiple of 8 bytes)
        Args for called func (need to be 16 byte align)
    -- RSP when calling func --
*/

/**
 * Generate Function Prelogue
 * @param funcStackSize sizeof SpilledArgs + sizeof StackVariables
 */
void generatePrelogue(std::ostream& out, size_t funcStackSize) {
    assert(!currentRSP);  // Assert epilogue is generated
    currentRSP += funcStackSize;
    using std::endl;
    //! Generate Prologue
    out << "    # generating func Prologue" << endl;
    out << "    pushq   %rbp" << endl;
    out << "    movq    %rsp, %rbp" << endl;
    out << "    subq    $" << funcStackSize
        << ", %rsp \t\t# Allocate Stack Space" << endl;
    alignTo16(out);
}

size_t pushRegister(std::ostream& out, SCCX86Register reg) {
    out << "    pushq   %" << reg.get64bitName() << std::endl;
    currentRSP += 8;
    return currentRSP;
}

void popRegister(std::ostream& out, SCCX86Register reg) {
    out << "    popq    %" << reg.get64bitName() << std::endl;
    currentRSP -= 8;
}

/**
 * move RSP down by 8 bytes to align func call arguments
 */
void pushNullArg(std::ostream& out) {
    out << "    subq    $8, %rsp  \t\t# push null arg for stack alignment"
        << std::endl;
    currentRSP += 8;
}

/**
 * Align the current Stack to 16 bytes in preparation for Func Call
 */
void alignTo16(std::ostream& out) {
    if (!(currentRSP % 16)) return;
    out << "    subq    $" << currentRSP % 16
        << ", %rsp  \t\t# align stack to 16 bytes" << std::endl;
    currentRSP += currentRSP % 16;
}

/**
 * Generate function epilogue
 */
void generateEpilogue(std::ostream& out) {
    using std::endl;
    out << "    # generating func Epilogue" << endl;
    out << "    movq    %rbp, %rsp" << endl;
    out << "    popq    %rbp" << endl;
    out << "    ret" << endl;
    currentRSP = 0;
}
}  // namespace SCCStackManager
