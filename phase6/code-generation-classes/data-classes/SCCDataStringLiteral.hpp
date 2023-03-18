#if !defined(SCC_DATA_STRING_LITERAL_HPP)
#define SCC_DATA_STRING_LITERAL_HPP

#include <string>

#include "SCCData.hpp"

class SCCDataStringLiteral : public SCCData {
   private:
    std::string _label;

   public:
    SCCDataStringLiteral(unsigned char size, const std::string& label)
        : SCCData(size), _label(label) {}

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

#endif  // SCC_DATA_STRING_LITERAL_HPP
