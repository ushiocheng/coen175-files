#if !defined(SCC_SYMBOL_HPP)
#define SCC_SYMBOL_HPP

#include <ostream>
#include <string>

#include "../code-generation-classes/data-location/SCCDataLocation.hpp"
#include "SCCType.hpp"

class SCCSymbol {
   private:
    std::string _id;
    SCCType _type;

   public:
    SCCDataLocation *location;
    /**
     * Default Constructor, returns error type
     * @remark only use for returning an error
     */
    SCCSymbol(const std::string &id);
    SCCSymbol(const std::string &id, const SCCType &type);
    SCCSymbol(const SCCSymbol &that);
    ~SCCSymbol() {
        if (this->location) delete location;
    }
    const std::string &id() const;
    const SCCType &type() const;
    /**
     * Check for Phase 3 E5
     */
    void validatePhase3E5() const;
    /**
     * Clearing param ptr
     * ! @remark NOT Deleting Params which is allocated dynamically.
     * @remark this is dangerous and should ONLY be used when deallocating scope
     */
    void _clearParams();
};

std::ostream &operator<<(std::ostream &out, const SCCSymbol &rhs);

#endif  // SCC_SYMBOL_HPP
