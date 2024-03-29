#include "SCCDataLocation.hpp"

#include <sstream>
#include <string>

#include "../register-classes/SCCRegisterManager.hpp"
#include "../register-classes/SCCX86Register.hpp"

SCCDataLocationStatic::SCCDataLocationStatic(std::string name) : name(name) {}
SCCDataLocationStack::SCCDataLocationStack(size_t offset) : offset(offset) {}
SCCDataLocationStackPositiveOffset::SCCDataLocationStackPositiveOffset(
    size_t offset)
    : _offset(offset) {}
SCCDataLocationRegister::SCCDataLocationRegister(SCCX86Register reg)
    : _register(reg) {}

SCCDataLocation* SCCDataLocationStatic::copy() {
    return new SCCDataLocationStatic(name);
}
SCCDataLocation* SCCDataLocationStack::copy() {
    return new SCCDataLocationStack(offset);
}
SCCDataLocation* SCCDataLocationStackPositiveOffset::copy() {
    return new SCCDataLocationStackPositiveOffset(_offset);
}
SCCDataLocation* SCCDataLocationRegister::copy() {
    return new SCCDataLocationRegister(_register);
}

bool SCCDataLocationStatic::requireMemoryAccess() { return true; };
bool SCCDataLocationStack::requireMemoryAccess() { return true; };
bool SCCDataLocationStackPositiveOffset::requireMemoryAccess() { return true; };
bool SCCDataLocationRegister::requireMemoryAccess() { return false; };

SCCDataLocation::LocationType SCCDataLocationStatic::ident() { return Static; }
SCCDataLocation::LocationType SCCDataLocationStack::ident() { return Stack; }
SCCDataLocation::LocationType SCCDataLocationStackPositiveOffset::ident() {
    return Stack;
}
SCCDataLocation::LocationType SCCDataLocationRegister::ident() {
    return Register;
}

std::string SCCDataLocationStatic::generateAccess() { return this->name; }
std::string SCCDataLocationStack::generateAccess() {
    std::stringstream ss;
    ss << "-" << offset << "(%rbp)";
    return ss.str();
}
std::string SCCDataLocationStackPositiveOffset::generateAccess() {
    std::stringstream ss;
    ss << _offset << "(%rbp)";
    return ss.str();
}
std::string SCCDataLocationRegister::generateAccess() {
    std::stringstream ss;
    ss << "%" << this->_register.getName();
    return ss.str();
}

std::string SCCDataLocationStatic::toString() {
    std::stringstream ss;
    ss << "SCCDataLocationStatic " << this->generateAccess();
    return ss.str();
}
std::string SCCDataLocationStack::toString() {
    std::stringstream ss;
    ss << "SCCDataLocationStack " << this->generateAccess();
    return ss.str();
}
std::string SCCDataLocationStackPositiveOffset::toString() {
    std::stringstream ss;
    ss << "SCCDataLocationStack " << this->generateAccess();
    return ss.str();
}
std::string SCCDataLocationRegister::toString() {
    std::stringstream ss;
    ss << "SCCDataLocationRegister " << this->generateAccess();
    return ss.str();
}

// SCCDataLocationLiteral::SCCDataLocationLiteral(long value) : _value(value) {}
// bool SCCDataLocationLiteral::requireMemoryAccess() { return false; };
// std::string SCCDataLocationLiteral::generateAccess() {
//     std::stringstream ss;
//     ss << "$" << _value;
//     return ss.str();
// }
// std::string SCCDataLocationLiteral::toString() {
//     std::stringstream ss;
//     ss << "SCCDataLocationLiteral " << this->generateAccess();
//     return ss.str();
// }
// SCCDataLocation* SCCDataLocationLiteral::copy() {
//     return new SCCDataLocationLiteral(_value);
// }
