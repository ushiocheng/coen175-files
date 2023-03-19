#if !defined(SCC_REGISTER_MANAGER_HPP)
#define SCC_REGISTER_MANAGER_HPP

#include <ostream>

#include "SCCX86Register.hpp"

class SCCVirtualRegister;
class SCCDataLocation;

/**
 * (Static) Register Manager
 * Manages register usage, VReg
 * Manage spilling register
 */
namespace SCCRegisterManager {

/**
 * What can be done on a register
 * - hold
 * - release
 *
 * What can be done on a VReg
 * - allocateAndHold
 * - deallocate
 * - put in reg
 * - put In Specific Register
 * - release/preempt to stack
 * - move to another reg
 */

void enterFunc(bool useCalleeSave);
void exitFunc();

void useReg(std::ostream& out, SCCX86Register reg);
SCCX86Register useAnyReg(std::ostream& out, unsigned char size);
void releaseReg(SCCX86Register reg);

void holdCallerSaves(std::ostream& out);
void releaseCallerSaves(std::ostream& out);

SCCVirtualRegister* allocateAndHoldVReg(std::ostream& out, unsigned char size);
SCCVirtualRegister* createVRegFromReg(SCCX86Register reg);
void deallocateVReg(std::ostream& out, SCCVirtualRegister* reg);
void loadVReg(std::ostream& out, SCCVirtualRegister* reg);
void loadVReg(std::ostream& out, SCCVirtualRegister* reg, SCCX86Register dest);
void releaseVReg(SCCVirtualRegister* reg);
}  // namespace SCCRegisterManager

#endif  // SCC_REGISTER_MANAGER_HPP
