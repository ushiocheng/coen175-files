#include "SCCScope.hpp"

#include "GlobalConfig.hpp"

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#endif


// ===== Function Definition =====

static void reportError(std::string str);

// ===== Function Implementation =====

static void reportError(std::string str) {
#ifdef DEBUG_ADDITIONAL_WARNING
    std::cout << "[WARN] " << str << std::endl;
#endif
}

/**
 * Constructor
 * @remark should only be used to make global scope
 */
SCCScope::SCCScope(SCCScope* outerScope = nullptr)
    : _symbols(), _outerScope(outerScope), _innerScopes() {
    if (outerScope) {
        outerScope->_innerScopes.push_back(this);
    }
}

/**
 * Create a inner
 */
SCCScope* SCCScope::createScope() {
    return new SCCScope(this);
}

/**
 * Exit to outer scope
 */
SCCScope* SCCScope::exitScope() {
    return this->_outerScope;
}

/**
 * add symbol to this scope
 * @param symbol will be copied
 * @remark this function will report eror if a new symbol are attempt to be
 * added that is of a different type
 */
void SCCScope::addSymbol(const SCCSymbol symbol) {
    for (SCCSymbol& symbolInArr : this->_symbols) {
        if (symbolInArr.name == symbol.name) {
            if (symbolInArr.type != symbol.type) reportError("Conflict type declaration");
            return;
        }
    }
    this->_symbols.push_back(symbol);
}

/**
 * Lookup a symbol in symbol table
 * @return symbol with type error if symbol not found
 */
SCCSymbol SCCScope::lookupSymbol(const std::string id) {
    for (SCCSymbol& symbolInArr : this->_symbols) {
        if (symbolInArr.name == id) {
            return symbolInArr;
        }
    }
    reportError("Symbol not declared");
    return SCCSymbol();
}

SCCScope::~SCCScope() {}