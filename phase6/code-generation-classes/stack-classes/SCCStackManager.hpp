#if !defined(SCC_STACK_MANAGER_HPP)
#define SCC_STACK_MANAGER_HPP

#include "../register-classes/SCCX86Register.hpp"
#include <ostream>

/**
 * (Static) Stack Manager
 * Manages Stack Frame
*/
namespace SCCStackManager {
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
            Spilled Registers
            Args for called func (need to be 16 byte align)
        -- RSP when calling func --
    */

    /**
     * Generate Function Prelogue
     * @param funcStackSize sizeof SpilledArgs + sizeof StackVariables
    */
    void generatePrelogue(std::ostream& out, size_t funcStackSize);

    /**
     * Push a register onto stack
     * @return offset on stack, can be accessed by offset(%rbp)
    */
    size_t pushRegister(std::ostream& out, SCCX86Register reg);
    void popRegister(std::ostream& out, SCCX86Register reg);

    /**
     * move RSP down by 8 bytes to align func call arguments
    */
    void pushNullArg(std::ostream& out);
    
    /**
     * Align the current Stack to 16 bytes in preparation for Func Call
    */
    void alignTo16(std::ostream& out);

    /**
     * Generate function epilogue
    */
    void generateEpilogue(std::ostream& out);
}

#endif // SCC_STACK_MANAGER_HPP
