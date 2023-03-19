#if !defined(SCC_DATA_ARGUMENT_HPP)
#define SCC_DATA_ARGUMENT_HPP

#include "SCCData.hpp"

class SCCDataArgument : public SCCData {
   private:
   public:
    SCCDataArgument(unsigned char size, size_t argNum) : SCCData(size) {
        this->_location =
            new SCCDataLocationStackPositiveOffset(16 + 8 * (argNum - 6));
    }

    DataType ident();
    //! Implement Interfaces

    /**
     * Load this Data to a specific register
     */
    void loadTo(std::ostream& out,
                SCCX86Register::SizeIndependentRegCode regCode);

    bool requireMemoryAccess() { return true; }
    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    std::string access();
    void loadAddrTo(std::ostream& out,
                    SCCX86Register::SizeIndependentRegCode regCode);
};

#endif  // SCC_DATA_ARGUMENT_HPP
