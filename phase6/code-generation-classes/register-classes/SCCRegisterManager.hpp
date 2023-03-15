#if !defined(SCC_REGISTER_MANAGER_HPP)
#define SCC_REGISTER_MANAGER_HPP

#include <ostream>

class SCCVirtualRegister;

/**
 * (Static) Register Manager
 * Manages register usage, VReg
 * Manage spilling register
*/
namespace SCCRegisterManager {
    extern bool useCalleeSave;

    void enterFunc();
    void exitFunc();

    void allocateVReg(std::ostream& out, SCCVirtualRegister* reg);
    void deallocateVReg(std::ostream& out, SCCVirtualRegister* reg);

    void useReg(std::ostream& out, SCCX86Register reg);
    void reselaseReg(std::ostream& out, SCCX86Register reg);

    void holdCallerSaves(std::ostream& out);
    void releaseCallerSaves(std::ostream& out);
}

#endif // SCC_REGISTER_MANAGER_HPP
