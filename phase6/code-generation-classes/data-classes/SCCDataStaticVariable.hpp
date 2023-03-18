#if !defined(SCC_DATA_STATIC_VARIABLE_HPP)
#define SCC_DATA_STATIC_VARIABLE_HPP

#include <string>

#include "SCCData.hpp"

class SCCDataStaticVariable : public SCCData {
   private:

   public:
    SCCDataStaticVariable(unsigned char size, const std::string& name)
        : SCCData(size) {
        this->_location = new SCCDataLocationStatic(name);
    }

    //! Implement Interfaces

    /**
     * Load this Data to a specific register
     * Overrides _placeInSpecificRegister Flag
     */
    void loadTo(std::ostream& out,
                SCCX86Register::SizeIndependentRegCode regCode);

    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    std::string access();
};

#endif  // SCC_DATA_STATIC_VARIABLE_HPP
