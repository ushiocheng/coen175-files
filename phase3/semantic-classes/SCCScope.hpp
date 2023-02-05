#if !defined(SCC_SCOPE_HPP)
#define SCC_SCOPE_HPP

#include "../GlobalConfig.hpp"
#include "SCCSymbol.hpp"
#include "SCCType.hpp"
#include <vector>
#include <string>

class SCCScope
{
private:
    std::vector<SCCSymbol> _symbols;
    SCCScope* _outerScope;
    std::vector<SCCScope*> _innerScopes;
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
    /**
     * Exit to outer scope
    */
    SCCScope* exitScope();
    /**
     * add symbol to this scope
     * @param symbol will be copied
     * @remark this function will report eror if a new symbol are attempt to be added that is of a different type
    */
    void addSymbol(const SCCSymbol symbol);
    /**
     * Lookup a symbol in symbol table
     * @return symbol with type error if symbol not found
    */
    SCCSymbol lookupSymbol(const std::string id);
    ~SCCScope();
};

#endif // SCC_SCOPE_HPP
