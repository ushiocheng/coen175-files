#include "SCCRegisterManager.hpp"

#include <ostream>
#include <vector>

#include "../../GlobalConfig.hpp"
#include "../data-location-classes/SCCDataLocation.hpp"
#include "../stack-classes/SCCStackManager.hpp"
#include "SCCVirtualRegister.hpp"
#include "SCCX86Register.hpp"

/**
 * (Static) Register Manager
 * Manages register usage, VReg
 * Manage spilling register
 */
namespace SCCRegisterManager {
using std::vector;
bool _useCalleeSave = false;

//static vector<SCCVirtualRegister*> _virtualRegisters;
typedef struct _regTableEntry {
    SCCX86Register::SizeIndependentRegCode regCode;
    bool regInUse = false;
    bool preemptable = false;
    bool movable = false;
    SCCVirtualRegister* vRegPtr = nullptr;
} RegTableEntry;

inline RegTableEntry constructRegTableEntry(SCCX86Register::SizeIndependentRegCode rc);

// 14 General purpose registers
RegTableEntry _physicalRegs[] = {constructRegTableEntry(SCCX86Register::R11),
                                constructRegTableEntry(SCCX86Register::R10),
                                constructRegTableEntry(SCCX86Register::R9),
                                constructRegTableEntry(SCCX86Register::R8),
                                constructRegTableEntry(SCCX86Register::CX),
                                constructRegTableEntry(SCCX86Register::DX),
                                constructRegTableEntry(SCCX86Register::SI),
                                constructRegTableEntry(SCCX86Register::DI),
                                constructRegTableEntry(SCCX86Register::AX),
                                // Callee Saves 9-13
                                constructRegTableEntry(SCCX86Register::BX),
                                constructRegTableEntry(SCCX86Register::R12),
                                constructRegTableEntry(SCCX86Register::R13),
                                constructRegTableEntry(SCCX86Register::R14),
                                constructRegTableEntry(SCCX86Register::R15)};
RegTableEntry* nextAvailableReg;  // FIFO VReg replacement
RegTableEntry* physicalRegStart;
RegTableEntry* physicalRegEnd;

//! ---------- Helper funcs ----------

void preemptVReg(std::ostream& out, RegTableEntry* regToPreempt) {
    SCCStackManager::pushRegister(out, SCCX86Register(regToPreempt->regCode));
    delete regToPreempt->vRegPtr->location;
    regToPreempt->vRegPtr->location =
        new SCCDataLocationStack(SCCStackManager::currentRSP);
    regToPreempt->regInUse = false;
    regToPreempt->vRegPtr = nullptr;
}

void moveVReg(std::ostream& out, RegTableEntry* regToMove) {
    assert(regToMove->movable);
    assert(!regToMove->preemptable);
    auto tmp = nextAvailableReg;
    while ((!nextAvailableReg->preemptable) && nextAvailableReg->regInUse) {
        // while nextAvailReg is not preemptable and in use
        nextAvailableReg++;
        //! Fail assertion if there is no register available
        assert(nextAvailableReg != tmp);
        if (nextAvailableReg == physicalRegEnd)
            nextAvailableReg = physicalRegStart;
    }
    if (nextAvailableReg->regInUse) {
        // Preempt VReg (at this point next reg must be preemptable)
        preemptVReg(out, nextAvailableReg);
    }
    //! Move regToMove to nextAvailableReg
    SCCDataLocationRegister* oldLocation = ((SCCDataLocationRegister *)nextAvailableReg->vRegPtr->location);
    SCCDataLocationRegister* newLocation = new SCCDataLocationRegister(SCCX86Register(nextAvailableReg->regCode, oldLocation->reg().getSize()));
    oldLocation->reg().moveTo(out, nextAvailableReg->regCode);
    nextAvailableReg->regInUse = true;
    nextAvailableReg->preemptable = false;
    nextAvailableReg->movable = true;
    nextAvailableReg->vRegPtr = regToMove->vRegPtr;
    regToMove->regInUse = false;
    regToMove->preemptable = false;
    regToMove->movable = false;
    regToMove->vRegPtr = nullptr;
    delete oldLocation;
    nextAvailableReg->vRegPtr->location = newLocation;
    //! Incriment nextReg
    nextAvailableReg++;
    if (nextAvailableReg == physicalRegEnd) nextAvailableReg = physicalRegStart;
}

inline RegTableEntry constructRegTableEntry(
    SCCX86Register::SizeIndependentRegCode rc) {
    RegTableEntry res;
    res.regCode = rc;
    return res;
}

//! ========== Setup functions ==========

void enterFunc(bool useCalleeSave) {
    _useCalleeSave = useCalleeSave;
    if (_useCalleeSave) {
        physicalRegStart =
            _physicalRegs + 9;  // So that Callee saved is used first
        physicalRegEnd = _physicalRegs + 14;
    } else {
        physicalRegStart = _physicalRegs;
        physicalRegEnd = _physicalRegs + 9;
    }
    nextAvailableReg = physicalRegStart;
}

void exitFunc() {}

//! ========== Register Methods ==========

void useReg(std::ostream& out, SCCX86Register reg) {
    for (RegTableEntry* i = physicalRegStart; i<physicalRegEnd; i++) {
        if (i->regCode == reg.siRegCode()) {
            if (i->regInUse) {
                if (i->preemptable) {
                    preemptVReg(out, i);
                } else if (i->movable) {
                    // A VReg is holding the register requested, it is non preemptable but can be moved to another reg
                    moveVReg(out, i);
                } else {
                    assert(false);
                }
            }
            i->regInUse = true;
            i->preemptable = false;
            i->movable = false;
        }
    }
}

void releaseReg(std::ostream& out, SCCX86Register reg) {
    for (RegTableEntry* i = physicalRegStart; i<physicalRegEnd; i++) {
        if (i->regCode == reg.siRegCode()) {
            assert(i->regInUse);
            assert(!i->preemptable);
            assert(!i->movable);
            assert(!i->vRegPtr);
            i->regInUse = false;
        }
    }
}

void holdCallerSaves(std::ostream& out) {
    useReg(out, SCCX86Register(SCCX86Register::R11));
    useReg(out, SCCX86Register(SCCX86Register::R10));
    useReg(out, SCCX86Register(SCCX86Register::R9));
    useReg(out, SCCX86Register(SCCX86Register::R8));
    useReg(out, SCCX86Register(SCCX86Register::CX));
    useReg(out, SCCX86Register(SCCX86Register::DX));
    useReg(out, SCCX86Register(SCCX86Register::SI));
    useReg(out, SCCX86Register(SCCX86Register::DI));
    useReg(out, SCCX86Register(SCCX86Register::AX));
}

void releaseCallerSaves(std::ostream& out) {
    releaseReg(out, SCCX86Register(SCCX86Register::R11));
    releaseReg(out, SCCX86Register(SCCX86Register::R10));
    releaseReg(out, SCCX86Register(SCCX86Register::R9));
    releaseReg(out, SCCX86Register(SCCX86Register::R8));
    releaseReg(out, SCCX86Register(SCCX86Register::CX));
    releaseReg(out, SCCX86Register(SCCX86Register::DX));
    releaseReg(out, SCCX86Register(SCCX86Register::SI));
    releaseReg(out, SCCX86Register(SCCX86Register::DI));
    releaseReg(out, SCCX86Register(SCCX86Register::AX));
}

//! ========== Virtual Register Methods ==========

SCCVirtualRegister* allocateAndHoldVReg(std::ostream& out, SCCVirtualRegister* reg) {
    auto tmp = nextAvailableReg;
    while ((!nextAvailableReg->preemptable) && nextAvailableReg->regInUse) {
        // while nextAvailReg is not preemptable and in use
        nextAvailableReg++;
        assert(nextAvailableReg != tmp);
        if (nextAvailableReg == physicalRegEnd)
            nextAvailableReg = physicalRegStart;
    }
    if (nextAvailableReg->regInUse) {
        // Preempt VReg ( at this point next reg must be preemptable)
        preemptVReg(out, nextAvailableReg);
    }
    // No point to move things around for a new arbitary vreg allocation
    nextAvailableReg->regInUse = true;
    nextAvailableReg->preemptable = true;
    nextAvailableReg->movable = true;
    nextAvailableReg->vRegPtr = reg;
    reg->location = new SCCDataLocationRegister(
        SCCX86Register(nextAvailableReg->regCode, reg->getSize()));
    reg->locationValid = true;
    nextAvailableReg++;
    if (nextAvailableReg == physicalRegEnd) nextAvailableReg = physicalRegStart;
}

void deallocateVReg(std::ostream& out, SCCVirtualRegister* reg) {
    // Check reg is allocated
    if (!reg->locationValid) return;
    //! release Register allocation
    if (reg->location->requireMemoryAccess()) {
        // reg is on stack
        // do nothing?
    } else {
        for (RegTableEntry* i = physicalRegStart; i < physicalRegEnd; i++) {
            if (i->vRegPtr == reg) {
                i->regInUse = false;
                i->vRegPtr == nullptr;
            }
        }
    }
    // VReg not found
    assert(false);
}

void loadVReg(std::ostream& out, SCCVirtualRegister* reg) {
    // TODO
}

void loadVReg(std::ostream& out, SCCVirtualRegister* reg, SCCX86Register dest) {
    // TODO
}
void releaseVReg(SCCVirtualRegister* reg) {
    // TODO
}

}  // namespace SCCRegisterManager
