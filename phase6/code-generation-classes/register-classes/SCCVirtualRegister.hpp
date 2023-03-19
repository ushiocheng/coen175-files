#if !defined(SCC_VIRTUAL_REGISTER)
#define SCC_VIRTUAL_REGISTER

#include <ostream>

#include "SCCRegisterManager.hpp"
#include "SCCX86Register.hpp"

class SCCDataLocation;

/**
 * (Dynamic) Virtual Register
 * Can be mapped to a register or a Stack location
 */
class SCCVirtualRegister {
   private:
    unsigned _size;

   public:
    SCCDataLocation* location;
    bool locationValid = false;
    /**
     * Constructor
     * @param size size of this register in bytes (supports 1,2,4,8)
     * @remark would assert fail if size is not 1/2/4/8 (or use 8 in prod)
     */
    SCCVirtualRegister(unsigned char size = 8)
        : _size(size), location(nullptr) {}
    SCCVirtualRegister(const SCCVirtualRegister& rhs);
    ~SCCVirtualRegister();

    /**
     * Load this VReg to a physical register
     * It will stay there until another VReg is loaded
     * To hold it for longer, load to a specific register and reserve it
     * manually
     */
    void loadToRegister(std::ostream& out);
    // Load to specific register
    void loadToRegister(std::ostream& out, SCCX86Register reg);

    void release();

    /**
     * Cast this register to a specific size and sign extend as needed
     */
    void castTo(std::ostream& out, unsigned char size);

    /**
     * get size of this register
     */
    unsigned char getSize();
};

#endif  // SCC_VIRTUAL_REGISTER
