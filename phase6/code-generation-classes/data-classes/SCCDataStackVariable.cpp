#include "SCCDataStackVariable.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

void SCCDataStackVariable::loadTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    " << X86InstructionHelper::movForSize(this->_size)
        << this->access() << ", %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

std::string SCCDataStackVariable::access() {
    return this->_location->generateAccess();
}

SCCDataStackVariable::DataType SCCDataStackVariable::ident() {
    return DataType::StackVariable;
}
