#include "SCCVirtualRegister.hpp"
#include "../data-location-classes/SCCDataLocation.hpp"
#include "SCCRegisterManager.hpp"

SCCVirtualRegister::~SCCVirtualRegister() {
    if (this->location) delete this->location;
}

/**
 * Load this VReg to a physical register
 * It will stay there until another VReg is loaded
 * To hold it for longer, load to a specific register and reserve it manually
 */
void SCCVirtualRegister::loadToRegister(std::ostream& out) {
    SCCRegisterManager::loadVReg(out, this);
}
// Load to specific register
void SCCVirtualRegister::loadToRegister(std::ostream& out, SCCX86Register reg) {
    SCCRegisterManager::loadVReg(out, this, reg);
}

/**
 * Cast this register to a specific size and sign extend as needed
 */
void SCCVirtualRegister::castTo(std::ostream& out, unsigned char size) {
    if (!this->location->requireMemoryAccess()) {
        ((SCCDataLocationRegister*) this->location)->reg().castTo(out, size);
    }
    // If this is stack then it doesn't matter
    this->_size = size;
}

/**
 * get size of this register
 */
unsigned char SCCVirtualRegister::getSize() {
    return this->_size;
}