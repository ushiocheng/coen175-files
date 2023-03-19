#include "X86InstructionHelper.hpp"

#include <cassert>

#include "../../GlobalConfig.hpp"

namespace X86InstructionHelper {
/**
 * Get mov instruction for specific size
 * @param size size of operands, can be {1,2,4,8}
 */
const char* movForSize(unsigned char size) {
    switch (size) {
        case 1:
            return "movb";
        case 2:
            return "movs";
        case 4:
            return "movl";
        case 8:
            return "movq";
        default:
            assert(false);
    }
}

const char* postfixForSize(unsigned char size) {
    switch (size) {
        case 1:
            return "b";
        case 2:
            return "s";
        case 4:
            return "l";
        case 8:
            return "q";
        default:
            assert(false);
    }
}

const unsigned char numBitForSize(unsigned char size) {
    switch (size) {
        case 1:
            return 8;
        case 2:
            return 16;
        case 4:
            return 32;
        case 8:
            return 64;
        default:
            assert(false);
    }
}
}  // namespace X86InstructionHelper