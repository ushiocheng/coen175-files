#if !defined(SCC_DATA_LOCATION_HPP)
#define SCC_DATA_LOCATION_HPP

#include <sstream>
#include <string>

#include "../register-classes/SCCRegisterManager.hpp"
#include "../register-classes/SCCX86Register.hpp"

/**
 * (Dynamic) Represents a location of a data
 * This does not imply LValue/RValue as intermediate values can be on stack or
 * in register.
 * This abstracts the structure used to access a location
 */

class SCCDataLocation {
   public:
    enum LocationType { Static, Stack, Register };
    virtual ~SCCDataLocation(){};
    virtual bool requireMemoryAccess() = 0;
    virtual LocationType ident() = 0;
    virtual std::string generateAccess() = 0;
    virtual std::string toString() = 0;
    virtual SCCDataLocation* copy() = 0;
};

class SCCDataLocationStatic : public SCCDataLocation {
   private:
   public:
    std::string name;
    SCCDataLocationStatic(std::string name);
    bool requireMemoryAccess();
    LocationType ident();
    std::string generateAccess();
    std::string toString();
    SCCDataLocation* copy();
};

class SCCDataLocationStack : public SCCDataLocation {
   private:
   public:
    // Offset from rbp
    // Variable is at -offset(rbp)
    size_t offset;
    SCCDataLocationStack(size_t offset);
    bool requireMemoryAccess();
    LocationType ident();
    std::string generateAccess();
    std::string toString();
    SCCDataLocation* copy();
};

class SCCDataLocationStackPositiveOffset : public SCCDataLocation {
   private:
    // Offset from rbp
    // Variable is at offset(rbp)
    size_t _offset;

   public:
    SCCDataLocationStackPositiveOffset(size_t offset);
    bool requireMemoryAccess();
    LocationType ident();
    std::string generateAccess();
    std::string toString();
    SCCDataLocation* copy();
};

class SCCDataLocationRegister : public SCCDataLocation {
   private:
    SCCX86Register _register;

   public:
    SCCDataLocationRegister(SCCX86Register reg);
    bool requireMemoryAccess();
    LocationType ident();
    std::string generateAccess();
    std::string toString();
    SCCDataLocation* copy();
    SCCX86Register reg() const { return _register; }
};

// class SCCDataLocationLiteral : public SCCDataLocation {
//    private:
//     long _value;

//    public:
//     SCCDataLocationLiteral(long value);
//     bool requireMemoryAccess();
//     LocationType ident();
//     std::string generateAccess();
//     std::string toString();
//     SCCDataLocation* copy();
// };

#endif  // SCC_DATA_LOCATION_HPP
