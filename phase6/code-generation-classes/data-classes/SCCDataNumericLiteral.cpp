#include "SCCDataNumericLiteral.hpp"

#include <sstream>

#include "../instruction-helper/X86InstructionHelper.hpp"

/**
 * Load this Data to a specific register
 * Overrides _placeInSpecificRegister Flag
 */
void SCCDataNumericLiteral::loadTo(
    std::ostream& out, SCCX86Register::SizeIndependentRegCode regCode) {
    out << "    " << X86InstructionHelper::movForSize(this->size())
        << this->access() << ", "
        << "%" << SCCX86Register(regCode, this->size()).getName() << std::endl;
}

/**
 * Generate access to this data
 * @remark this should not be used to generate LValue access
 */
std::string SCCDataNumericLiteral::access() {
    std::stringstream ss;
    ss << "$" << this->_value;
    return ss.str();
}

SCCDataNumericLiteral::DataType SCCDataNumericLiteral::ident() {
    return DataType::NumericLiteral;
}
