#include "SCCRegisterManager.hpp"
#include <ostream>
#include "SCCX86Register.hpp"
#include "SCCVirtualRegister.hpp"
#include <vector>

/**
 * (Static) Register Manager
 * Manages register usage, VReg
 * Manage spilling register
*/
namespace SCCRegisterManager {
    using std::vector;
    bool useCalleeSave = false;

    static vector<SCCVirtualRegister*> virtualRegisters;
    typedef struct _regTableEntry {
        SCCX86Register::SizeIndependentRegCode regCode;
        bool regInUse = false;
        SCCVirtualRegister* vRegPtr = nullptr;
    } RegTableEntry;
    
    // 14 General purpose registers
    SCCX86Register::SizeIndependentRegCode callerSaves[] = {
        SCCX86Register::AX,
        SCCX86Register::CX,
        SCCX86Register::DX,
        SCCX86Register::SI,
        SCCX86Register::DI,
        SCCX86Register::R8,
        SCCX86Register::R9,
        SCCX86Register::R10,
        SCCX86Register::R11
    };
    SCCX86Register::SizeIndependentRegCode calleeSaves[] = {
        SCCX86Register::BX,
        SCCX86Register::R12,
        SCCX86Register::R13,
        SCCX86Register::R14,
        SCCX86Register::R15
    };

    void allocateVReg(SCCVirtualRegister* reg) {
        virtualRegisters.push_back(reg);

    }
    void deallocateVReg(SCCVirtualRegister* reg) {
        for (auto iter = virtualRegisters.begin(); iter < virtualRegisters.end(); iter++) {
            if (*iter == reg) {
                //! Found VReg
                virtualRegisters.erase(iter);
                return;
            }
        }
    }

    void useReg(SCCX86Register reg) {

    }
    void reselaseReg(SCCX86Register reg) {

    }

    void holdCallerSaves() {

    }
    void releaseCallerSaves() {

    }
}
