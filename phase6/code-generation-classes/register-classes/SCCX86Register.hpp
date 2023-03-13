#if !defined(SCC_X86_REGISTER_HPP)
#define SCC_X86_REGISTER_HPP

#include <ostream>

/**
 * (Stack) X86 Register object
 * This is a helper class to declear register in a size-aware way
 * and test if 2 register are the same in a size-independent way
 */
class SCCX86Register {
   public:
    /**
     * Size Independent Register Codes
     * @remark Sequence here affects the behavior of SCCX86Register::SCCX86Register()
     * ---
     * 64 bit variant of a reg = (reg<<2) + 0x0
     * 32 bit variant of a reg = (reg<<2) + 0x1
     * 16 bit variant of a reg = (reg<<2) + 0x2
     * 08 bit variant of a reg = (reg<<2) + 0x3
     * ! but only for reg < RSP
     */
    enum SizeIndependentRegCode {
        AX = 0,
        BX,
        CX,
        DX,
        SI,
        DI,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        //! Regs below are not size independent
        RSP,
        RFP,
        RIP
    };

   private:
    // Actually X86Reg:Reg, but to avoid including another header
    int _actualRegCode;

   public:
    /**
     * Constructor
     * @param size size of this register in bytes (supports 1,2,4,8)
     * @remark would assert fail if size is not 1/2/4/8 (or use 8 in prod)
    */
    SCCX86Register(SizeIndependentRegCode regCode, unsigned char size = 8);
    
    /**
     * check if this and that would take the same physical register space
     * ex. RAX and EAX use the same physical space
    */
    bool conflictsWith(SCCX86Register that);

    /**
     * get name of this register
    */
    inline const char* getName();

    /**
     * get name of 64 bit version of this register
    */
    inline const char* get64bitName();

    /**
     * Cast this register to a specific size and sign extend as needed
    */
    void castTo(std::ostream& out, unsigned char size);

    /**
     * get size of this register
    */
    unsigned char getSize();

    ~SCCX86Register();
};

#endif  // SCC_X86_REGISTER_HPP
