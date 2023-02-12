#if !defined(SCC_SYMBOL_HPP)
#define SCC_SYMBOL_HPP

#include <string>
#include <ostream>
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
    void validateType() const;
    /**
     * Deleting Params which is allocated dynamically.
     * @remark this is dangerous and should ONLY be used for deallocating objects.
    */
    void _deleteParams();
};

std::ostream& operator<<(std::ostream& out, const SCCSymbol& rhs);

#endif  // SCC_SYMBOL_HPP
