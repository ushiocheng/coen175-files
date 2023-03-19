#include "SCCDataWrapper.hpp"

SCCDataWrapper::SCCDataWrapper(SCCData* original)
    : SCCData(original->size()), _actual(original) {}

SCCDataWrapper::~SCCDataWrapper() { _actual = nullptr; }

SCCData::DataType SCCDataWrapper::ident() { return this->_actual->ident(); }

//! Implement Interfaces

/**
 * Load this Data to a specific register
 * Overrides _placeInSpecificRegister Flag
 */
void SCCDataWrapper::loadTo(std::ostream& out,
                            SCCX86Register::SizeIndependentRegCode regCode) {
    _actual->loadTo(out, regCode);
}

bool SCCDataWrapper::requireMemoryAccess() {
    return _actual->requireMemoryAccess();
}

/**
 * Generate access to this data
 * @remark this should not be used to generate LValue access
 */
std::string SCCDataWrapper::access() { return _actual->access(); }