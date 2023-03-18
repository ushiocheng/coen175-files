#if !defined(X86_INSTRUCTION_HELPER_HPP)
#define X86_INSTRUCTION_HELPER_HPP

namespace X86InstructionHelper {
/**
 * Get mov instruction for specific size
 * @param size size of operands, can be {1,2,4,8}
 */
const char* movForSize(unsigned char size);
}  // namespace X86InstructionHelper

#endif  // X86_INSTRUCTION_HELPER_HPP
