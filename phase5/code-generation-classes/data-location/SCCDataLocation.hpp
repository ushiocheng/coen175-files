#if !defined(SCC_DATA_LOCATION_HPP)
#define SCC_DATA_LOCATION_HPP

#include <string>
#include "../SCCRegisterManager.hpp"
#include <sstream>

class SCCDataLocation {
public:
    virtual ~SCCDataLocation() {};
    virtual bool requireMemoryAccess() = 0;
    virtual std::string generateAccess() = 0;
    virtual SCCDataLocation* copy() = 0;
};

class SCCDataLocationStatic : public SCCDataLocation {
private:
    std::string _name;
public:
    SCCDataLocationStatic(std::string name) : _name(name) {}
    bool requireMemoryAccess() { return true; };
    std::string generateAccess() {
        return this->_name;
    }
    SCCDataLocation* copy() {
        return new SCCDataLocationStatic(_name);
    }
};

class SCCDataLocationLiteral : public SCCDataLocation {
private:
    long _value;
public:
    SCCDataLocationLiteral(long value) : _value(value) {}
    bool requireMemoryAccess() { return false; };
    std::string generateAccess() {
        std::stringstream ss;
        ss << "$" << _value;
        return ss.str();
    }
    SCCDataLocation* copy(){
        return new SCCDataLocationLiteral(_value);
    }
};

class SCCDataLocationStack : public SCCDataLocation {
private:
    // Offset from rbp
    // Variable is at -offset(rbp)
    size_t _offset;
public:
    SCCDataLocationStack(size_t offset) : _offset(offset) {}
    bool requireMemoryAccess() { return true; };
    std::string generateAccess() {
        std::stringstream ss;
        ss << "-" << _offset << "(%rbp)";
        return ss.str();
    }
    SCCDataLocation* copy(){
        return new SCCDataLocationStack(_offset);
    }
};

class SCCDataLocationRegister : public SCCDataLocation {
private:
    int _register;
public:
    SCCDataLocationRegister(int reg) : _register(reg) {}
    bool requireMemoryAccess() { return false; };
    std::string generateAccess() {
        std::stringstream ss;
        ss << "%" << X86Register::nameStr[this->_register];
        return ss.str();
    }
    SCCDataLocation* copy() {
        return new SCCDataLocationRegister(_register);
    }
};

#endif // SCC_DATA_LOCATION_HPP
