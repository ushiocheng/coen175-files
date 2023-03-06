#include "SCCRegister.hpp"

namespace X86Register{

    const char* nameStr[] = {
        "rax" ,  "eax" ,  "ax"  ,  "al"  ,
        "rbx" ,  "ebx" ,  "bx"  ,  "bl"  ,
        "rcx" ,  "ecx" ,  "cx"  ,  "cl"  ,
        "rdx" ,  "edx" ,  "dx"  ,  "dl"  ,
        "rsi" ,  "esi" ,  "si"  ,  "sil" ,
        "rdi" ,  "edi" ,  "di"  ,  "dil" ,
        "r8"  , "r8d"  ,  "r8w" ,  "r8b" ,
        "r9"  , "r9d"  ,  "r9w" ,  "r9b" ,
        "r10" , "r10d" , "r10w" , "r10b" ,
        "r11" , "r11d" , "r11w" , "r11b" ,
        "r12" , "r12d" , "r12w" , "r12b" ,
        "r13" , "r13d" , "r13w" , "r13b" ,
        "r14" , "r14d" , "r14w" , "r14b" ,
        "r15" , "r15d" , "r15w" , "r15b" ,
        "rsp" ,
        "rfp" ,
        "rip"
    };
    
    //TODO Phase 6
    // support any reg size
    const int FPArgcReg = RAX;
    const int Arg0Reg = EDI;
    const int Arg1Reg = ESI;
    const int Arg2Reg = EDX;
    const int Arg3Reg = ECX;
    const int Arg4Reg = R8D;
    const int Arg5Reg = R9D;
    
    const int ReturnReg = RAX;
    
    char sizeSpecifier(size_t size){
        if (size == 1) return 'b';
        if (size == 2) return 'w';
        if (size == 4) return 'l';
        return 'q';
    }
}