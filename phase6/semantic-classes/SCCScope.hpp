#if !defined(SCC_SCOPE_HPP)
#define SCC_SCOPE_HPP

#include <cassert>
#include <string>
#include <vector>

#include "../GlobalConfig.hpp"
#include "SCCSymbol.hpp"
#include "SCCType.hpp"

class SCCScope {
   private:
    std::vector<SCCSymbol> _symbols;
    SCCSymbol* _enclosingFunc;
    SCCScope* _outerScope;
    std::vector<SCCScope*> _innerScopes;

    const SCCSymbol* _findSymbol(const std::string& id) const;

   public:
    /**
     * Constructor
     * @remark should only be used to make global scope
     */
    SCCScope(SCCScope* outerScope = nullptr);
    /**
     * Create a inner
     */
    SCCScope* createScope();
    void setEnclosingFunc(SCCSymbol* func);
    const SCCSymbol* getEnclosingFunc() const;
    /**
     * Exit to outer scope
     * @remark returns this & print warning if already at root/global scope
     */
    SCCScope* exitScope();
    /**
     * Check if this scope is Global scope i.e. do not have parent scope
     */
    bool isGlobal();
    /**
     * add symbol to this scope
     * @param symbol will be copied
     * @remark this function will report eror if a new symbol are attempt to be
     * added that is of a different type
     */
    void addSymbol(const SCCSymbol& symbol);
    /**
     * Lookup a symbol in symbol table
     * @return symbol with type error if symbol not found
     */
    const SCCSymbol* lookupSymbol(const std::string& id) const;
    // Dump content for debug purpose
    void _dump() const;
    ~SCCScope();
};

#endif  // SCC_SCOPE_HPP
