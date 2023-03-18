#if !defined(SCC_DATA_HPP)
#define SCC_DATA_HPP

#include <iostream>

#include "../data-location-classes/SCCDataLocation.hpp"
#include "../register-classes/SCCX86Register.hpp"

/**
 * (Dynamic) Data
 * Abstract representation of data
 * including static, variables, and intermediate values
 * Provides unified interface to load and access a data in code generation
 */
class SCCData {
   protected:
    // To be placed in
    bool _placeInRegister;
    bool _placeInSpecifiedReg;  // Return value / Dividend
    SCCX86Register::SizeIndependentRegCode _specifiedReg;
    // To be used as LHS in assignment
    bool _useAsLValue;
    // Size of this data, can be 1,2,4,8 bytes
    unsigned char _size;
    SCCDataLocation* _location;

   public:
    SCCData(bool placeInReg, bool placeInSpecificReg, bool useAsLValue,
            unsigned char size,
            SCCX86Register::SizeIndependentRegCode regToPlaceIn =
                SCCX86Register::SizeIndependentRegCode::AX);
    ~SCCData();

    //! Setters and getters

    bool placeInRegister() const { return _placeInRegister; }
    bool placeInSpecifiedReg() const { return _placeInSpecifiedReg; }
    SCCX86Register::SizeIndependentRegCode specifiedReg() const {
        return _specifiedReg;
    }
    bool useAsLValue() const { return _useAsLValue; }
    unsigned char size() const { return _size; }
    const SCCDataLocation* location() const { return _location; }
    SCCDataLocation* location() { return _location; }
    void setLocation(SCCDataLocation* newLocation) {
        this->_location = newLocation;
    }

    //! Interfaces

    /**
     * Load this Data for access
     */
    virtual void load(std::ostream& out) = 0;
    /**
     * Load this Data to a specific register
     * Overrides _placeInSpecificRegister Flag
     */
    virtual void loadTo(SCCX86Register::SizeIndependentRegCode regCode) = 0;
    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    virtual std::string access();
};

#endif  // SCC_DATA_HPP
