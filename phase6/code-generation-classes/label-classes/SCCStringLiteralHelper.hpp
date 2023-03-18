#if !defined(SCC_STRING_LITERAL_HELPER_HPP)
#define SCC_STRING_LITERAL_HELPER_HPP

#include <ostream>
#include <string>

namespace SCCStringLiteralHelper {
/**
 * Generate string literals
 * @returns label to the string literal
 * @param labelPostfix would be appended to label for clearity & debugging
 * purposes
 */
std::string generateStringLiteral(std::ostream& out, const std::string& value,
                                  const char* labelPostfix = "");
}  // namespace SCCStringLiteralHelper

#endif  // SCC_STRING_LITERAL_HELPER_HPP
