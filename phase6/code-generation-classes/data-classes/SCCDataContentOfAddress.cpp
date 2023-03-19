#include "SCCDataContentOfAddress.hpp"

#include <cassert>

#include "../instruction-helper/X86InstructionHelper.hpp"

SCCDataContentOfAddress::SCCDataContentOfAddress(unsigned char size,
                                                 SCCData* address)
    : SCCData(size), _address(address) {}

SCCDataContentOfAddress::~SCCDataContentOfAddress() { delete _address; }

SCCData::DataType SCCDataContentOfAddress::ident() { return SCCData::Indirect; }

//! Implement Interfaces

/**
 * Load this Data to a specific register
 * Overrides _placeInSpecificRegister Flag
 */
void SCCDataContentOfAddress::loadTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    _address->loadTo(out, regCode);
    out << "    " << X86InstructionHelper::movForSize(_address->size())
        << "    "
        << "(%" << SCCX86Register(regCode, _address->size()).getName() << "), %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

bool SCCDataContentOfAddress::requireMemoryAccess() { return true; }

/**
 * Generate access to this data
 * @remark this should not be used to generate LValue access
 */
std::string SCCDataContentOfAddress::access() { assert(false); }

void SCCDataContentOfAddress::loadAddrTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    _address->loadTo(out, regCode);
}
