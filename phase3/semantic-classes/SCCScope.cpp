#include "SCCScope.hpp"

#include <cassert>
#include <iostream>

#include "../GlobalConfig.hpp"
#include "SCCError.hpp"
#include "SCCType.hpp"

#ifdef DEBUG
#define DEBUG_PRINT_FUNC_TRACE_FLG
// #define DEBUG_PRINT_MATCHING
#define PRINT_IF_DEBUG(sth) std::cout << sth << std::endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED                                              \
    std::cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ \
              << std::endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

/**
 * Constructor
 * @remark should only be used to make global scope
 */
SCCScope::SCCScope(SCCScope *outerScope)
    : _symbols(), _outerScope(outerScope), _innerScopes() {
    if (outerScope) {
        outerScope->_innerScopes.push_back(this);
    }
}

/**
 * Create a inner
 */
SCCScope *SCCScope::createScope() {
    PRINT_FUNC_IF_ENABLED;
    return new SCCScope(this);
}

/**
 * Exit to outer scope
 */
SCCScope *SCCScope::exitScope() {
    PRINT_FUNC_IF_ENABLED;
    if (!this->_outerScope) {
        printAndReport("Trying to exit global!");
    }
    return this->_outerScope;
}

bool SCCScope::isGlobal() { return !(this->_outerScope); }

/**
 * add symbol to this scope
 * @param symbol will be copied
 * @remark this function will report eror if a new symbol are attempt to be
 * added that is of a different type
 */
void SCCScope::addSymbol(const SCCSymbol &symbol) {
    PRINT_FUNC_IF_ENABLED;
    if (symbol.type().isFunc()) {
        assert(this->isGlobal());
    }
    for (size_t i = 0; i < this->_symbols.size(); i++) {
        const SCCSymbol &symbolInArr = this->_symbols.at(i);
        if (symbolInArr.id() == symbol.id()) {
            //! E1 cannot happen if E2, thus check E2 first
            if (symbolInArr.type() != symbol.type()) {
                printAndReport("Conflict type declaration",
                               SCCSemanticError::CONFLICT_TYPE, symbol.id());
                return;
            }
            //! Check E1
            if (symbol.type().isFunc()) {
                if (symbolInArr.type().noParam()) {
                    // function have not been defined
                    if (symbol.type().parameters()->size() > 0) {
                        // if incoming symbol is func definition
                        this->_symbols.at(i) = symbol;
                        //! Check E5 here just before return
                        symbol.validateType();
                    }
                    return;
                }
                // Function is already defined
                if (!symbol.type().noParam()) {
                    printAndReport("Redefinition of function",
                                   SCCSemanticError::REDEFINITION, symbol.id());
                }
                return;
            }
            //! Check E3
            if (!this->isGlobal()) {
                printAndReport("Redeclaration in non-global scope",
                               SCCSemanticError::REDECLARATION, symbol.id());
                return;
            }
            //* Not Checking E5 since redeclaration means already checked.
            return;  // If this is a good old redeclaration to global variable
        }
    }
    //! Check E5
    symbol.validateType();
    this->_symbols.push_back(symbol);
}

/**
 * Lookup a symbol in symbol table
 * @return symbol with type error if symbol not found
 */
const SCCSymbol *SCCScope::lookupSymbol(const std::string &id) const {
    PRINT_FUNC_IF_ENABLED;
    const SCCSymbol *ptr = this->_findSymbol(id);
    if (!ptr)
        printAndReport("Symbol not declared", SCCSemanticError::UNDECLARED, id);
    return ptr;
}

const SCCSymbol *SCCScope::_findSymbol(const std::string &id) const {
    for (size_t i = 0; i < this->_symbols.size(); i++) {
        const SCCSymbol *symbolInArr = &(this->_symbols[i]);
        if (symbolInArr->id() == id) {
            return symbolInArr;
        }
    }
    if (this->_outerScope) {
        return this->_outerScope->_findSymbol(id);
    } else {
        return nullptr;
    }
}

SCCScope::~SCCScope() {
    for (SCCSymbol symbol : _symbols) symbol._deleteParams();
    for (SCCScope *scope : _innerScopes) {
        if (scope) delete scope;
    }
    _innerScopes.clear();
}
