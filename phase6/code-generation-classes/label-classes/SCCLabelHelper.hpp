#if !defined(SCC_LABEL_MANAGER_HPP)
#define SCC_LABEL_MANAGER_HPP

#include <ostream>
#include <string>

/**
 * (Static) Helper class for generate labels, tracks label count to ensures every label is unique
*/
namespace SCCLabelHelper {
    /**
     * Output a new label and return the label
     * @remark label would be in format `.L<num>.<postfix>` where num is a counter tracked internally
     * @remark `<label>:\n` would be outputed and `<label>` would be returned
    */
    std::string generateNewLabel(std::ostream& out, const char* postfix = "");
} // namespace SCCLabelHelper

#endif // SCC_LABEL_MANAGER_HPP
