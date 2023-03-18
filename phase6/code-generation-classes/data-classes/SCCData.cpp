#include "SCCData.hpp"

#include <cassert>

#include "../../GlobalConfig.hpp"

SCCData::SCCData(unsigned char size) : _size(size), _location(nullptr) {}

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
