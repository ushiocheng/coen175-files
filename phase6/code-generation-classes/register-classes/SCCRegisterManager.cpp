#include "SCCRegisterManager.hpp"

#include <cassert>
#include <ostream>
#include <vector>

#include "../../GlobalConfig.hpp"
#include "../data-location-classes/SCCDataLocation.hpp"
#include "../instruction-helper/X86InstructionHelper.hpp"
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

// static vector<SCCVirtualRegister*> _virtualRegisters;
typedef struct _regTableEntry {
    SCCX86Register::SizeIndependentRegCode regCode;
    bool regInUse = false;
    bool preemptable = false;
    bool movable = false;
    SCCVirtualRegister* vRegPtr = nullptr;
} RegTableEntry;

//! private function signatures

inline RegTableEntry constructRegTableEntry(
    SCCX86Register::SizeIndependentRegCode rc);
inline void advanceNextAvailableReg();
RegTableEntry* getNextAvailableRegister(std::ostream& out);
void preemptVReg(std::ostream& out, RegTableEntry* regToPreempt);
void moveVReg(std::ostream& out, RegTableEntry* regToMove);
RegTableEntry* findRegTableEntry(
    SCCX86Register::SizeIndependentRegCode regCode);
RegTableEntry* findRegTableEntry(SCCVirtualRegister* vRegPtr);

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

inline void advanceNextAvailableReg() {
    nextAvailableReg++;
    if (nextAvailableReg >= physicalRegEnd) nextAvailableReg = physicalRegStart;
}

/**
 * Get any physical register that is preemptable
 * @remark this func won't move vreg around since there is no point to do so, it
 * would only preempt the oldest allocated vreg
 * @remark this func also advances nextAvailableReg
 */
RegTableEntry* getNextAvailableRegister(std::ostream& out) {
    auto tmp = nextAvailableReg;
    while ((!nextAvailableReg->preemptable) && nextAvailableReg->regInUse) {
        // while nextAvailReg is not preemptable and in use
        advanceNextAvailableReg();
        //! Fail assertion if there is no register available
        assert(nextAvailableReg != tmp);
    }
    if (nextAvailableReg->regInUse) {
        // Preempt VReg (at this point next reg must be preemptable)
        preemptVReg(out, nextAvailableReg);
    }
    return nextAvailableReg;
}

RegTableEntry* findRegTableEntry(
    SCCX86Register::SizeIndependentRegCode regCode) {
    for (RegTableEntry* i = physicalRegStart; i < physicalRegEnd; i++) {
        if (i->regCode == regCode) {
            return i;
        }
    }
    assert(false);
    return nullptr;
}

RegTableEntry* findRegTableEntry(SCCVirtualRegister* vRegPtr) {
    for (RegTableEntry* i = physicalRegStart; i < physicalRegEnd; i++) {
        if (i->vRegPtr == vRegPtr) {
            return i;
        }
    }
    assert(false);
    return nullptr;
}

void preemptVReg(std::ostream& out, RegTableEntry* regToPreempt) {
    SCCStackManager::pushRegister(out, SCCX86Register(regToPreempt->regCode));
    // Update VReg location
    delete regToPreempt->vRegPtr->location;
    regToPreempt->vRegPtr->location =
        new SCCDataLocationStack(SCCStackManager::currentRSP);
    regToPreempt->regInUse = false;
    regToPreempt->vRegPtr = nullptr;
}

void moveVReg(std::ostream& out, RegTableEntry* regToMove) {
    assert(regToMove->movable);
    assert(!regToMove->preemptable);
    //! This func also advances nextAvailableReg
    getNextAvailableRegister(out);
    //* assert that the vreg are not going to be moved to the same place
    //* i.e. all other reg is filled and non-preemptable
    assert(nextAvailableReg != regToMove);
    //! Move regToMove to nextAvailableReg
    SCCDataLocationRegister* oldLocation =
        ((SCCDataLocationRegister*)nextAvailableReg->vRegPtr->location);
    SCCDataLocationRegister* newLocation =
        new SCCDataLocationRegister(SCCX86Register(
            nextAvailableReg->regCode, oldLocation->reg().getSize()));

    oldLocation->reg().moveTo(out, nextAvailableReg->regCode);

    delete oldLocation;
    nextAvailableReg->vRegPtr->location = newLocation;

    nextAvailableReg->regInUse = true;
    nextAvailableReg->preemptable = false;
    nextAvailableReg->movable = true;
    nextAvailableReg->vRegPtr = regToMove->vRegPtr;
    regToMove->regInUse = false;
    regToMove->preemptable = false;
    regToMove->movable = false;
    regToMove->vRegPtr = nullptr;
    //! Incriment nextReg
    advanceNextAvailableReg();
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
    auto rte = findRegTableEntry(reg.siRegCode());
    if (rte->regInUse) {
        if (rte->preemptable) {
            preemptVReg(out, rte);
        } else if (rte->movable) {
            // A VReg is holding the register requested, it is non
            // preemptable but can be moved to another reg
            moveVReg(out, rte);
        } else {
            assert(false);
        }
    }
    rte->regInUse = true;
    rte->preemptable = false;
    rte->movable = false;
}

void releaseReg(std::ostream& out, SCCX86Register reg) {
    auto rte = findRegTableEntry(reg.siRegCode());
    assert(rte->regInUse);
    assert(!rte->preemptable);
    assert(!rte->movable);
    assert(!rte->vRegPtr);
    rte->regInUse = false;
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

SCCVirtualRegister* allocateAndHoldVReg(std::ostream& out, unsigned char size) {
    auto reg = new SCCVirtualRegister(size);
    loadVReg(out, reg);
    return reg;
}

SCCVirtualRegister* createVRegFromReg(SCCX86Register reg) {
    auto vreg = new SCCVirtualRegister(reg.getSize());
    auto i = findRegTableEntry(reg.siRegCode());
    assert(!i->regInUse);
    vreg->location = new SCCDataLocationRegister(
        SCCX86Register(nextAvailableReg->regCode, reg.getSize()));
    vreg->locationValid = true;
    i->regInUse = true;
    i->preemptable = false;
    i->movable = true;
    return vreg;
}

void deallocateVReg(std::ostream& out, SCCVirtualRegister* reg) {
    // Check reg is allocated
    if (!reg->locationValid) return;
    //! release Register allocation
    if (reg->location->requireMemoryAccess()) {
        // reg is on stack
        // do nothing?
    } else {
        auto i = findRegTableEntry(reg);
        i->regInUse = false;
        i->vRegPtr == nullptr;
    }
    // VReg not found
    assert(false);
}

void loadVReg(std::ostream& out, SCCVirtualRegister* reg) {
    if (reg->locationValid && (!reg->location->requireMemoryAccess())) {
        // Vreg already in register, set it to non-preemptable
        auto i = findRegTableEntry(reg);
        i->preemptable = false;
        i->movable = true;
        return;
    }
    //! Put Vreg to register
    getNextAvailableRegister(out);
    // No point to move things around for a new arbitary vreg allocation
    nextAvailableReg->regInUse = true;
    nextAvailableReg->preemptable = false;
    nextAvailableReg->movable = true;
    nextAvailableReg->vRegPtr = reg;
    if (!reg->locationValid) {
        //! Vreg does not have a value
        reg->locationValid = true;
    } else {
        //! VReg is on stack, move the value to register and cleanup data
        //! location
        out << "    " << X86InstructionHelper::movForSize(reg->getSize())
            << reg->location->generateAccess() << ", %"
            << SCCX86Register(nextAvailableReg->regCode, reg->getSize())
                   .getName()
            << std::endl;
        delete reg->location;
    }
    reg->location = new SCCDataLocationRegister(
        SCCX86Register(nextAvailableReg->regCode, reg->getSize()));
    advanceNextAvailableReg();
}

void loadVReg(std::ostream& out, SCCVirtualRegister* reg, SCCX86Register dest) {
    auto destRTE = findRegTableEntry(dest.siRegCode());
    SCCDataLocation* newLocation = new SCCDataLocationRegister(
        SCCX86Register(destRTE->regCode, reg->getSize()));

    if (!reg->locationValid) {
        // If Vreg is not created, find reg and use it as vreg location
        if (destRTE->regInUse) {
            // ! Two non-preemptable allocation at same physical
            // register
            assert(destRTE->preemptable || destRTE->movable);
            if (destRTE->preemptable)
                preemptVReg(out, destRTE);
            else
                moveVReg(out, destRTE);
        }
        reg->locationValid = true;
        return;
    } else if (!reg->location->requireMemoryAccess()) {
        //! VReg is in register
        if (((SCCDataLocationRegister*)reg->location)
                ->reg()
                .conflictsWith(dest)) {
            //! v reg alreay in dest, set dest to non-movable
            destRTE->movable = false;
            return;
        }
        // Vreg is in another register
        auto oldRegRTE = findRegTableEntry(reg);
        SCCDataLocationRegister* oldLocation =
            (SCCDataLocationRegister*)reg->location;
        oldLocation->reg().moveTo(out, newLocation);
        //! update VReg
        delete oldLocation;
        //! configure src RT
        oldRegRTE->regInUse = false;
        oldRegRTE->vRegPtr = nullptr;
    } else {
        out << "    " << X86InstructionHelper::movForSize(reg->getSize())
            << "    " << reg->location->generateAccess() << ", "
            << newLocation->generateAccess() << std::endl;
        //! update VReg
        delete reg->location;
    }

    reg->location = newLocation;
    //! configure dest RT
    destRTE->regInUse = true;
    destRTE->preemptable = false;
    destRTE->movable = false;
    destRTE->vRegPtr = reg;
}

void releaseVReg(SCCVirtualRegister* reg) {
    auto rte = findRegTableEntry(reg);
    rte->preemptable = true;
}

}  // namespace SCCRegisterManager
