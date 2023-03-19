#include "SCCDataWrapper.hpp"

#include "SCCData_All.hpp"

SCCDataWrapper::SCCDataWrapper(SCCData* original)
    : SCCData(original->size()), _actual(original) {}

SCCDataWrapper::~SCCDataWrapper() { _actual = nullptr; }

SCCData::DataType SCCDataWrapper::ident() { return Wrapper; }

//! Implement Interfaces

/**
 * Load this Data to a specific register
 * Overrides _placeInSpecificRegister Flag
 */
void SCCDataWrapper::loadTo(std::ostream& out,
                            SCCX86Register::SizeIndependentRegCode regCode) {
    _actual->loadTo(out, regCode);
}

void SCCDataWrapper::loadAddrTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    using std::endl;
    auto reg = SCCX86Register(regCode);
    switch (_actual->ident()) {
        case SCCData::StackVariable:
            out << "    movq    %rbp, %" << reg.getName() << endl;
            out << "    subq    $"
                << ((SCCDataLocationStack*)(_actual->location()))->offset
                << ", %" << reg.getName() << endl;
            break;
        case SCCData::StaticVariable:
            out << "    leaq    "
                << ((SCCDataLocationStatic*)(_actual->location()))->name
                << ", %" << reg.getName() << endl;
            break;
        case SCCData::Indirect:
            ((SCCDataContentOfAddress*)_actual)
                ->loadAddrTo(out, reg.siRegCode());
            break;
        case SCCData::Arguments:
            ((SCCDataArgument*)_actual)->loadAddrTo(out, reg.siRegCode());
            break;
        case SCCData::TempValue:
            ((SCCDataTempValue*)_actual)->loadAddrTo(out, reg.siRegCode());
            break;
        case SCCData::Wrapper:
            ((SCCDataWrapper*)_actual)->loadAddrTo(out, reg.siRegCode());
        default:
            assert(false);
    }
}

bool SCCDataWrapper::requireMemoryAccess() {
    return _actual->requireMemoryAccess();
}

/**
 * Generate access to this data
 * @remark this should not be used to generate LValue access
 */
std::string SCCDataWrapper::access() { return _actual->access(); }