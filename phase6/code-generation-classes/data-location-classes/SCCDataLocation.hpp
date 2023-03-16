#if !defined(SCC_DATA_LOCATION_HPP)
#define SCC_DATA_LOCATION_HPP

#include <string>
#include "../register-classes/SCCRegisterManager.hpp"
#include "../register-classes/SCCX86Register.hpp"
#include <sstream>

class SCCDataLocation {
public:
    virtual ~SCCDataLocation() {};
    virtual bool requireMemoryAccess() = 0;
    virtual std::string generateAccess() = 0;
    virtual std::string toString() = 0;
    virtual SCCDataLocation* copy() = 0;
    void movTo(SCCDataLocation* location, unsigned char size) {
        
    }
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
    std::string toString(){
        std::stringstream ss;
        ss << "SCCDataLocationStatic " << this->generateAccess();
        return ss.str();
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
    std::string toString(){
        std::stringstream ss;
        ss << "SCCDataLocationLiteral " << this->generateAccess();
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
    std::string toString(){
        std::stringstream ss;
        ss << "SCCDataLocationStack " << this->generateAccess();
        return ss.str();
    }
    SCCDataLocation* copy(){
        return new SCCDataLocationStack(_offset);
    }
};

class SCCDataLocationRegister : public SCCDataLocation {
private:
    SCCX86Register _register;
public:
    SCCDataLocationRegister(SCCX86Register reg) : _register(reg) {}
    bool requireMemoryAccess() { return false; };
    std::string generateAccess() {
        std::stringstream ss;
        ss << "%" << this->_register.getName();
        return ss.str();
    }
    std::string toString(){
        std::stringstream ss;
        ss << "SCCDataLocationRegister " << this->generateAccess();
        return ss.str();
    }
    SCCDataLocation* copy() {
        return new SCCDataLocationRegister(_register);
    }
    SCCX86Register reg() const { return _register; }
};

#endif // SCC_DATA_LOCATION_HPP
