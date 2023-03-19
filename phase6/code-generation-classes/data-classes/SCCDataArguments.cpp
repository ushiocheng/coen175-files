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
