#include "SCCLabelHelper.hpp"

#include <ostream>
#include <sstream>
#include <string>

namespace SCCLabelHelper {

size_t labeluid = 0;

/**
 * Output a new label and return the label
 * @remark label would be in format `.L<num>.<postfix>` where num is a counter
 * tracked internally
 * @remark `<label>:\n` would be outputed and `<label>` would be returned
 */
std::string generateNewLabel(std::ostream& out, const char* postfix) {
    labeluid++;
    std::stringstream sstr;
    sstr << ".L" << labeluid << "." << postfix;
    std::string tmp = sstr.str();
    out << tmp << ":" << std::endl;
    return tmp;
}
}  // namespace SCCLabelHelper
