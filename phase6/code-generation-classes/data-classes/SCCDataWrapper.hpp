#if !defined(SCC_DATA_WRAPPER_HPP)
#define SCC_DATA_WRAPPER_HPP

#include "SCCData.hpp"

class SCCDataWrapper : public SCCData {
   private:
    SCCData* _actual;

   public:
    SCCDataWrapper(SCCData* original);
    ~SCCDataWrapper();

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
};

#endif  // SCC_DATA_WRAPPER_HPP
