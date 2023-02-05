#if !defined(SCC_SYMBOL_HPP)
#define SCC_SYMBOL_HPP

#include <string>
#include "SCCType.hpp"

typedef struct _SCC_Symbol
{
    std::string name;
    SCCType type;
} SCCSymbol;

#endif // SCC_SYMBOL_HPP
