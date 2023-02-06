#include "SCCScope.hpp"

#include <iostream>
#include "../GlobalConfig.hpp"
#include "SCCError.hpp"
#ifndef DEBUG
#define NDEBUG // to suppress assert
#endif
#include <cassert>

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#endif

// ===== Function Definition =====

static void printAndReport(const std::string &str, SCCSemanticError errType, const std::string &id);

// ===== Function Implementation =====

static void printAndReport(const std::string &str, SCCSemanticError errType = EXTRA_ERROR, const std::string &id = "")
{
#ifdef DEBUG_ADDITIONAL_WARNING
    std::cout << "[WARN] " << str << std::endl;
#endif
    reportSemanticError(errType, id);
}

/**
 * Constructor
 * @remark should only be used to make global scope
 */
SCCScope::SCCScope(SCCScope *outerScope)
    : _symbols(), _outerScope(outerScope), _innerScopes()
{
    if (outerScope)
    {
        outerScope->_innerScopes.push_back(this);
    }
}

/**
 * Create a inner
 */
SCCScope *SCCScope::createScope()
{
    return new SCCScope(this);
}

/**
 * Exit to outer scope
 */
SCCScope *SCCScope::exitScope()
{
    if (!this->_outerScope)
    {
        printAndReport("Trying to exit global!");
    }
    return this->_outerScope;
}

bool SCCScope::isGlobal()
{
    return !(this->_outerScope);
}

/**
 * add symbol to this scope
 * @param symbol will be copied
 * @remark this function will report eror if a new symbol are attempt to be
 * added that is of a different type
 */
void SCCScope::addSymbol(const SCCSymbol &symbol)
{
    if (symbol.type().isFunc())
    {
        assert(this->isGlobal());
    }
    for (size_t i = 0; i < this->_symbols.size(); i++)
    {
        const SCCSymbol &symbolInArr = this->_symbols.at(i);
        if (symbolInArr.id() == symbol.id())
        {
            if (!this->isGlobal())
            {
                printAndReport("Redeclaration in non-global scope", SCCSemanticError::REDECLARATION, symbol.id());
                return;
            }
            if (symbolInArr.type() != symbol.type())
            {
                printAndReport("Conflict type declaration", SCCSemanticError::CONFLICT_TYPE, symbol.id());
                return;
            }
            if (symbol.type().isFunc())
            {
                if (symbolInArr.type().noParam())
                {
                    // function have not been defined
                    this->_symbols.at(i) = symbol;
                    return;
                }
                // Function is already defined
                if (!symbol.type().noParam())
                {
                    printAndReport("Redefinition of function", SCCSemanticError::REDEFINITION, symbol.id());
                }
                return;
            }
            return; // If this is a good old redeclaration to global variable
        }
    }
    this->_symbols.push_back(symbol);
}

/**
 * Lookup a symbol in symbol table
 * @return symbol with type error if symbol not found
 */
SCCSymbol SCCScope::lookupSymbol(const std::string &id)
{
    for (SCCSymbol &symbolInArr : this->_symbols)
    {
        if (symbolInArr.id() == id)
        {
            return symbolInArr;
        }
    }
    printAndReport("Symbol not declared", SCCSemanticError::UNDECLARED, id);
    return SCCSymbol(id);
}

SCCScope::~SCCScope() {}
