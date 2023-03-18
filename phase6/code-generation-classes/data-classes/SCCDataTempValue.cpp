#include "SCCDataTempValue.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

void SCCDataTempValue::loadTo(std::ostream& out,
                              SCCX86Register::SizeIndependentRegCode regCode) {
    this->vreg->loadToRegister(out, SCCX86Register(regCode, this->_size));
}

std::string SCCDataTempValue::access() {
    return this->vreg->location->generateAccess();
}