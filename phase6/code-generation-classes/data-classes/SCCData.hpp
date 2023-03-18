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
    // Size of this data, can be 1,2,4,8 bytes
    unsigned char _size;
    SCCDataLocation* _location;

   public:
    SCCData(unsigned char size);

    virtual ~SCCData();

    //! Setters and getters

    unsigned char size() const { return _size; }
    const SCCDataLocation* location() const { return _location; }
    SCCDataLocation* location() { return _location; }
    void setLocation(SCCDataLocation* newLocation) {
        this->_location = newLocation;
    }

    //! Interfaces

    /**
     * Load this Data to a specific register
     * Overrides _placeInSpecificRegister Flag
     */
    virtual void loadTo(std::ostream& out,
                        SCCX86Register::SizeIndependentRegCode regCode) = 0;

    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    virtual std::string access();
};

#endif  // SCC_DATA_HPP
