#include "SCCDataArguments.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

void SCCDataArgument::loadTo(std::ostream& out,
                             SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    " << X86InstructionHelper::movForSize(this->_size)
        << this->access() << ", %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

std::string SCCDataArgument::access() {
    return this->_location->generateAccess();
}

SCCDataArgument::DataType SCCDataArgument::ident() {
    return DataType::Arguments;
}

void SCCDataArgument::loadAddrTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    movq    %rbp, %" << SCCX86Register(regCode).get64bitName()
        << std::endl;
    out << "    addq    $"
        << ((SCCDataLocationStackPositiveOffset*)this->_location)->_offset
        << ", %" << SCCX86Register(regCode).get64bitName() << std::endl;
}