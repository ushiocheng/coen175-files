#if !defined(SCC_REGISTER_HPP)
#define SCC_REGISTER_HPP

#include <ostream>

namespace X86Register{
    enum RegisterName {
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
        RSP ,
        RFP ,
        RIP
    };
    extern const char* nameStr[];
    
    extern const int FPArgcReg;
    extern const int Arg0Reg;
    extern const int Arg1Reg;
    extern const int Arg2Reg;
    extern const int Arg3Reg;
    extern const int Arg4Reg;
    extern const int Arg5Reg;

    extern const int ReturnReg;
    char sizeSpecifier(size_t size);
}

#endif // SCC_REGISTER_HPP
