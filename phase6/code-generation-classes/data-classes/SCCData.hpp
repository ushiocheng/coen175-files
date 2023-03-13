#if !defined(SCC_DATA_HPP)
#define SCC_DATA_HPP

#include <iostream>
#include "../register-classes/SCCX86Register.hpp"
#include "../data-location-classes/SCCDataLocation.hpp"

std::ostream& SCCCodeGeneration_outputStream = std::cout;

/**
 * (Dynamic) Data
 * Abstract representation of data
 * including static, variables, and intermediate values
 * Provides unified interface to load and access a data in code generation
 * @remark need to set Global `SCCCodeGeneration_outputStream` to indicate
 *         output location
 */
class SCCData {
   protected:
    // Indicate this data must be loaded to a register when accessed
    bool _isReg;
    unsigned char _size;  // Size of this data, can be 1,2,4,8 bytes
    SCCDataLocation* _location;
   public:
    SCCData(bool isReg, unsigned char size) : _isReg(isReg), _size(size) {}
    ~SCCData();

    bool isReg() const { return _isReg; }

    bool size() const { return _size; }

    /**
     * Load this Data for access
     */
    virtual void load() = 0;
    /**
     * Load this Data to a specific register (for Division or argument)
    */
    virtual void loadTo(SCCX86Register::SizeIndependentRegCode regCode) {
        if (this->_location->requireMemoryAccess()) {
            // mov to regCode
        }
    }
    /**
     * Load this Data for access
     */
    virtual void access() = 0;
};

#endif  // SCC_DATA_HPP
