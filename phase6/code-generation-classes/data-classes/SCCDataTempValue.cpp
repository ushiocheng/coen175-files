#include "SCCDataTempValue.hpp"

#include "../instruction-helper/X86InstructionHelper.hpp"

SCCDataTempValue::SCCDataTempValue(unsigned char size, std::ostream& out)
    : SCCData(size) {
    vreg = SCCRegisterManager::allocateAndHoldVReg(out, size);
}

SCCDataTempValue::SCCDataTempValue(SCCX86Register reg)
    : SCCData(reg.getSize()) {
    this->vreg = SCCRegisterManager::createVRegFromReg(reg);
}

SCCDataTempValue::SCCDataTempValue(const SCCDataTempValue& that)
    : SCCData(that._size) {
    this->vreg = new SCCVirtualRegister(*(that.vreg));
}

void SCCDataTempValue::loadTo(std::ostream& out,
                              SCCX86Register::SizeIndependentRegCode regCode) {
    if (!this->vreg->location->requireMemoryAccess()) {
        if (((SCCDataLocationRegister*)this->vreg->location)
                ->reg()
                .conflictsWith(SCCX86Register(regCode))) {
            return;
        }
    }
    out << "    " << X86InstructionHelper::movForSize(this->_size) << "    "
        << this->access() << ", %"
        << SCCX86Register(regCode, this->_size).getName() << std::endl;
}

std::string SCCDataTempValue::access() {
    return this->vreg->location->generateAccess();
}

SCCDataTempValue::DataType SCCDataTempValue::ident() {
    return DataType::TempValue;
}

SCCDataTempValue::~SCCDataTempValue() {
    if (this->vreg) {
        SCCRegisterManager::deallocateVReg(this->vreg);
        delete this->vreg;
        this->vreg = nullptr;
    }
}

void SCCDataTempValue::loadAddrTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    auto reg = SCCX86Register(regCode);
    SCCRegisterManager::forcePreemptVReg(out, this->vreg);
    out << "    movq    %rbp, %" << reg.getName() << std::endl;
    out << "    subq    $"
        << ((SCCDataLocationStack*)this->vreg->location)->offset << ", %"
        << reg.getName() << std::endl;
}