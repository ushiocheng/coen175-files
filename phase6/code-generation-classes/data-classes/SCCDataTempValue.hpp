#if !defined(SCC_DATA_TEMP_VALUE_HPP)
#define SCC_DATA_TEMP_VALUE_HPP

#include <string>

#include "../register-classes/SCCRegisterManager.hpp"
#include "../register-classes/SCCVirtualRegister.hpp"
#include "SCCData.hpp"

class SCCDataTempValue : public SCCData {
   private:
    SCCVirtualRegister* vreg;

   public:
    SCCDataTempValue(unsigned char size, std::ostream& out);

    SCCDataTempValue(SCCX86Register reg);

    SCCDataTempValue(const SCCDataTempValue& that);

    virtual ~SCCDataTempValue();

    DataType ident();

    //! Implement Interfaces

    /**
     * Load this Data to a specific register
     * Overrides _placeInSpecificRegister Flag
     */
    void loadTo(std::ostream& out,
                SCCX86Register::SizeIndependentRegCode regCode);

    bool requireMemoryAccess() {
        return this->vreg->location->requireMemoryAccess();
    }

    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    std::string access();

    SCCData* copy() const { return new SCCDataTempValue(*this); }

    void loadAddrTo(std::ostream& out,
                    SCCX86Register::SizeIndependentRegCode regCode);
};

#endif  // SCC_DATA_TEMP_VALUE_HPP
