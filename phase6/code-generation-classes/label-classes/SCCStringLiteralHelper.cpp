#include "SCCStringLiteralHelper.hpp"

#include <string>
#include <ostream>
#include <sstream>
#include "SCCLabelHelper.hpp"

namespace SCCStringLiteralHelper
{
    /**
     * Generate string literals
     * @returns label to the string literal
     * @param labelPostfix would be appended to label for clearity & debugging purposes
    */
    std::string generateStringLiteral(std::ostream& out, const std::string& value, const char* labelPostfix) {
        std::stringstream ss;
        ss << "str." << labelPostfix;
        // Label name strucure: .L<uid>.str.<strname>
        std::string label = SCCLabelHelper::generateNewLabel(out, ss.str().c_str());
        out << "\t.asciz \"" << value << "\"" << std::endl;
        return label;
    }
} // namespace SCCStringLiteralHelper

