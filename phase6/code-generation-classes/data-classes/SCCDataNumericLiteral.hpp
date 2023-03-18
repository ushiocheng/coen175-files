#if !defined(SCC_DATA_NUMERIC_LITERAL_HPP)
#define SCC_DATA_NUMERIC_LITERAL_HPP

#include "SCCData.hpp"

class SCCDataNumericLiteral : public SCCData {
   private:
    size_t _value;

   public:
    SCCDataNumericLiteral(unsigned char size, size_t value)
        : SCCData(size), _value(value) {}

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

#endif  // SCC_DATA_NUMERIC_LITERAL_HPP
