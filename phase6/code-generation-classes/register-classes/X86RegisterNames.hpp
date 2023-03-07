#if !defined(X86_REGISTER_NAMES_HPP)
#define X86_REGISTER_NAMES_HPP

namespace X86Reg {
    enum Reg {
    //! Sequence here affects the behavior of SCCX86Register::SCCX86Register()
    //! 64 bit variant of a reg = reg&(!0x3)+0x0
    //! 32 bit variant of a reg = reg&(!0x3)+0x1
    //! 16 bit variant of a reg = reg&(!0x3)+0x2
    //! 08 bit variant of a reg = reg&(!0x3)+0x3
    //! !! but only for reg < RSP
    //   64 ,  32  ,  16  ,  08  bit size
    RAX = 0 ,  EAX ,  AX  ,  AL  ,
        RBX ,  EBX ,  BX  ,  BL  ,
        RCX ,  ECX ,  CX  ,  CL  ,
        RDX ,  EDX ,  DX  ,  DL  ,
        RSI ,  ESI ,  SI  ,  SIL ,
        RDI ,  EDI ,  DI  ,  DIL ,
        R8  , R8D  ,  R8W ,  R8B ,
        R9  , R9D  ,  R9W ,  R9B ,
        R10 , R10D , R10W , R10B ,
        R11 , R11D , R11W , R11B ,
        R12 , R12D , R12W , R12B ,
        R13 , R13D , R13W , R13B ,
        R14 , R14D , R14W , R14B ,
        R15 , R15D , R15W , R15B ,
        RSP , //! Control registers do not have size variants
        RFP ,
        RIP
    };
    inline const char* nameOf(Reg reg);
}

#endif // X86_REGISTER_NAMES_HPP
