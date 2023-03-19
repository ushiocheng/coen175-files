#if !defined(SCC_DATA_CONTENT_OF_ADDRESS_HPP)
#define SCC_DATA_CONTENT_OF_ADDRESS_HPP

#include "SCCData.hpp"

class SCCDataContentOfAddress : public SCCData {
   private:
    SCCData* _address;

   public:
    SCCDataContentOfAddress(unsigned char size, SCCData* address);
    ~SCCDataContentOfAddress();

    DataType ident();

    //! Implement Interfaces

    /**
     * Load this Data to a specific register
     * Overrides _placeInSpecificRegister Flag
     */
    void loadTo(std::ostream& out,
                SCCX86Register::SizeIndependentRegCode regCode);

    bool requireMemoryAccess();

    /**
     * Generate access to this data
     * @remark this should not be used to generate LValue access
     */
    std::string access();

    void loadAddrTo(std::ostream& out,
                    SCCX86Register::SizeIndependentRegCode regCode);
};

#endif  // SCC_DATA_CONTENT_OF_ADDRESS_HPP
