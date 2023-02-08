#if !defined(SCC_SYMBOL_HPP)
#define SCC_SYMBOL_HPP

#include <string>

#include "SCCType.hpp"

class SCCSymbol {
   private:
    std::string _id;
    SCCType _type;

   public:
    /**
     * Default Constructor, returns error type
     * @remark only use for returning an error
     */
    SCCSymbol(const std::string &id);
    SCCSymbol(const std::string &id, const SCCType &type);
    const std::string &id() const;
    const SCCType &type() const;
};

#endif  // SCC_SYMBOL_HPP
