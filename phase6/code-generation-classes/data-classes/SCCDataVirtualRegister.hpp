#if !defined(SCC_DATA_VIRTUAL_REGISTER_HPP)
#define SCC_DATA_VIRTUAL_REGISTER_HPP

#include "SCCData.hpp"

/**
 * (Dynamic) Virtual Register
 * Represent a virtual register that can be placed in any physical register
 * unless special flags are declared
 */
class SCCDataVirtualRegister : public SCCData {
   public:
    /**
     * Flags that informs register manager where to place this VReg
     */
    enum RegDeclarationFlags {
        F_REG,
        //! This flag does nothing here, it informs certain ExprTreeNode's
        //! decision
        F_LVALUE, // This VReg would be used as a location
        //! The following flag enforces which reg this must be placed when
        //! accessed
        F_DIV,
        F_ARG0,
        F_ARG1,
        F_ARG2,
        F_ARG3,
        F_ARG4,
        F_ARG5
    };

   private:
    /* data */
   public:
    SCCVirtualRegister(/* args */);
    ~SCCVirtualRegister();

    /**
     * move this register to AX until next register load
     * used before function return
     * @remark this is done this way rather than declare another flag because
     *         the upper expr tree node owns VReg and can declear it as F_ARG0
     *         or F_DIV, which should be enforced when load() is called
     */
    void moveToReturnReg();
};

#endif  // SCC_DATA_VIRTUAL_REGISTER_HPP
