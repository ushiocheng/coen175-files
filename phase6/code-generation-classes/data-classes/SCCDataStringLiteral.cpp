#include "SCCDataStringLiteral.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

void SCCDataStringLiteral::loadTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    leaq    " << this->_label << ", %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

std::string SCCDataStringLiteral::access() { return std::string(this->_label); }

SCCDataStringLiteral::DataType SCCDataStringLiteral::ident() {
    return DataType::StringLiteral;
}
