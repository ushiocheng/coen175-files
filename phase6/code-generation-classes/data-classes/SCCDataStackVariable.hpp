#if !defined(SCC_DATA_STACK_VARIABLE_HPP)
#define SCC_DATA_STACK_VARIABLE_HPP

#include "SCCData.hpp"

class SCCDataStackVariable : public SCCData {
   private:
   public:
    SCCDataStackVariable(unsigned char size, size_t offset) : SCCData(size) {
        this->_location = new SCCDataLocationStack(offset);
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

#endif  // SCC_DATA_STACK_VARIABLE_HPP
