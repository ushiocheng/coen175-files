#include "SCCData.hpp"

#include <cassert>

#include "../../GlobalConfig.hpp"

SCCData::SCCData(bool placeInReg, bool placeInSpecificReg, bool useAsLValue,
                 unsigned char size,
                 SCCX86Register::SizeIndependentRegCode regToPlaceIn =
                     SCCX86Register::SizeIndependentRegCode::AX)
    : _placeInRegister(placeInReg),
      _placeInSpecifiedReg(placeInSpecificReg),
      _useAsLValue(useAsLValue),
      _size(size),
      _specifiedReg(regToPlaceIn),
      _location(nullptr) {}

SCCData::~SCCData() {
    if (_location) delete _location;
}

std::string SCCData::access() {
    if (!this->_location) {
        assert(false);
        return "";
    }
    return this->_location->generateAccess();
}
