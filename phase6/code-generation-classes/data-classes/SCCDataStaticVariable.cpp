#include "SCCDataStaticVariable.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

void SCCDataStaticVariable::loadTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    " << X86InstructionHelper::movForSize(this->_size)
        << this->access() << ", %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

std::string SCCDataStaticVariable::access() {
    return this->_location->generateAccess();
}

SCCDataStaticVariable::DataType SCCDataStaticVariable::ident() {
    return DataType::StaticVariable;
}
