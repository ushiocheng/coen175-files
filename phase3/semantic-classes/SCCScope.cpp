#include "SCCScope.hpp"

/**
 * Constructor
 * @remark should only be used to make global scope
 */
SCCScope::SCCScope(SCCScope* outerScope = nullptr){}
/**
 * Create a inner
 */
SCCScope* SCCScope::createScope(){}
/**
 * Exit to outer scope
 */
SCCScope* SCCScope::exitScope(){}
/**
 * add symbol to this scope
 * @param symbol will be copied
 * @remark this function will report eror if a new symbol are attempt to be
 * added that is of a different type
 */
void SCCScope::addSymbol(const SCCSymbol symbol){}
/**
 * Lookup a symbol in symbol table
 * @return symbol with type error if symbol not found
 */
SCCSymbol SCCScope::lookupSymbolType(const std::string id){}
SCCScope::~SCCScope(){}