#include "SCCScope.hpp"

#include <iostream>

#include "../GlobalConfig.hpp"
#include "../exceptions/SCCError.hpp"
#include "SCCType.hpp"

#ifdef DEBUG
// #define DEBUG_PRINT_FUNC_TRACE_FLG
// #define DEBUG_PRINT_MATCHING
#define PRINT_IF_DEBUG(sth) std::cerr << sth << std::endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED                                              \
    std::cerr << "[DEBUG] Running " << __func__ << " on line " << __LINE__ \
              << std::endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

/**
 * Constructor
 * @remark should only be used to make global scope
 */
SCCScope::SCCScope(SCCScope *outerScope)
    : 
      _enclosingFunc(NULL),
      _outerScope(outerScope),
      _innerScopes() {
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

void SCCScope::setEnclosingFunc(SCCSymbol *func) {
    this->_enclosingFunc = func;
}

const SCCSymbol *SCCScope::getEnclosingFunc() const {
    const SCCScope *tp = this;
    while (tp != NULL) {
        if (tp->_enclosingFunc != NULL) {
            return tp->_enclosingFunc;
        }
        tp = tp->_outerScope;
    }
    return NULL;
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
        const SCCSymbol* symbolInArr = this->_symbols.at(i);
        if (symbolInArr->id() == symbol.id()) {
            //! Not Checking E5 in this scope since any redeclaration/definition
            //! means E5 already checked.
            //! ----- For Variables -----
            if (!(this->isGlobal())) {
                //! Check E3
                printAndReport("Redeclaration in non-global scope",
                               REDECLARATION, symbol.id());
                return;
            }
            if (!symbol.type().isFunc()) {
                if (symbolInArr->type() != symbol.type()) {
                    //! Check E2 for variable
                    printAndReport("Conflict type declaration", CONFLICT_TYPE,
                                   symbol.id());
                    return;
                }
                // Good old redeclearation of variable in global scope
                // Nothing need to be done
                return;
            }
            //! ----- For Function -----
            //! Check E1
            if ((!symbolInArr->type().noParam()) && (!symbol.type().noParam())) {
                // If both are definition
                printAndReport("Redefinition of function", REDEFINITION,
                               symbol.id());
                //! ACCEPT inbound definition per specification
                this->_symbols.at(i) = new SCCSymbol(symbol);
                symbol.validatePhase3E5();
                return;
            }
            //! Check E2 for func
            if (symbolInArr->type() != symbol.type()) {
                printAndReport("Conflict type declaration", CONFLICT_TYPE,
                               symbol.id());
                return;
            }
            //! This func sym have no error, update it if necessary
            if (symbol.type().noParam()) {
                // If inbound is declearation
                // Nothing needs to be done
                return;
            }
            // function decleared but not defined, incoming definition
            this->_symbols.at(i) = new SCCSymbol(symbol);
            return;
        }
    }
    //! Check E5
    symbol.validatePhase3E5();
    this->_symbols.push_back(new SCCSymbol(symbol));
}

/**
 * Lookup a symbol in symbol table
 * @return symbol with type error if symbol not found
 */
const SCCSymbol *SCCScope::lookupSymbol(const std::string &id) const {
    PRINT_FUNC_IF_ENABLED;
    const SCCSymbol *ptr = this->_findSymbol(id);
    if (!ptr) printAndReport("Symbol not declared", UNDECLARED, id);
    return ptr;
}

const SCCSymbol *SCCScope::_findSymbol(const std::string &id) const {
    for (size_t i = 0; i < this->_symbols.size(); i++) {
        const SCCSymbol *symbolInArr = this->_symbols.at(i);
        if (symbolInArr->id() == id) {
            return symbolInArr;
        }
    }
    if (this->_outerScope) {
        return this->_outerScope->_findSymbol(id);
    } else {
        return NULL;
    }
}

std::vector<SCCSymbol *> SCCScope::getStatics() {
    std::vector<SCCSymbol *> res;
    size_t readPtr = 0;
    if (this->_enclosingFunc) {
        readPtr += this->_enclosingFunc->type().parameters()->size();
    }
    while (readPtr < this->_symbols.size()) {
        res.push_back(this->_symbols.at(readPtr));
        readPtr++;
    }
    return res;
}
std::vector<SCCSymbol *> SCCScope::getFunctionParams() {
    std::vector<SCCSymbol *> res;
    size_t readPtr = 0;
    if (!this->_enclosingFunc) return res;
    size_t argc = this->_enclosingFunc->type().parameters()->size();
    while (readPtr < argc) {
        res.push_back(this->_symbols.at(readPtr));
        readPtr++;
    }
    return res;
}


size_t SCCScope::maxSizeUtilization() const{
    size_t currentScopeUtilization = 0;
    for (const SCCSymbol* sym: this->_symbols) {
        currentScopeUtilization += sym->type().sizeOf();
    }
    size_t maxInnerScopeUtilization = 0;
    for (const SCCScope* scope : this->_innerScopes) {
        size_t a = scope->maxSizeUtilization();
        if (a > maxInnerScopeUtilization) maxInnerScopeUtilization = a;
    }
    return currentScopeUtilization + maxInnerScopeUtilization;
}

void SCCScope::performStackAllocation(size_t stackBaseOffset) {
    for (SCCSymbol* sym : this->getStatics()) {
        stackBaseOffset+= sym->type().sizeOf();
        sym->location = new SCCDataLocationStack(stackBaseOffset);
    }
    for (SCCScope* innerScope : this->_innerScopes) {
        // Intentional pass by value so nested stack var can be reclaimed.
        innerScope->performStackAllocation(stackBaseOffset);
    }
}

void SCCScope::_dump() const {
    std::cerr << "==================== BEGIN SCOPE " << this
              << " ====================" << std::endl;
    std::cerr << "EnclosingFunc: " << _enclosingFunc << std::endl;
    std::cerr << "OuterScope: " << _outerScope << std::endl;
    for (SCCSymbol* symbol : _symbols) {
        std::cerr << *symbol << std::endl;
    }
    for (SCCScope *scope : _innerScopes) {
        scope->_dump();
    }
    std::cerr << "==================== END SCOPE " << this
              << " ====================" << std::endl;
}

SCCScope::~SCCScope() {
    _enclosingFunc = NULL;
    _outerScope = NULL;
    for (SCCSymbol *symbol : _symbols) {
        if (symbol->type().declaratorType() == SCCType::ERROR) continue;
        if (symbol->type().parameters()) delete symbol->type().parameters();
        delete symbol;
    }
    for (SCCScope *scope : _innerScopes) {
        delete scope;
    }
}
