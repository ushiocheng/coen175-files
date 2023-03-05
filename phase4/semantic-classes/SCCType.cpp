#include "SCCType.hpp"

#include <iostream>
#include <string>

#include "../GlobalConfig.hpp"
#include <cassert>

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#define DEBUG_PRINT_FUNC_TRACE_FLG
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

SCCType::SCCType() {
    this->_declaratorType = ERROR;
    this->_isLValue = false;
}

SCCType::SCCType(const SCCType_Specifier specifier,
                 const SCCType_DeclaratorType declaratorType,
                 const unsigned int indirection, size_t arrLength,
                 SCCType_Parameters *parameters, bool isLValue)
    : _specifier(specifier),
      _indirection(indirection),
      _declaratorType(declaratorType),
      _isLValue(isLValue),
      _arrLength(arrLength),
      _parameters(parameters) {
    // //! Enforce array cannot be of size 0
    // if (this->_declaratorType == ARRAY) {
    //     if (this->_arrLength == 0) {
    //         reportError("SCCType: Declaration Invalid: array cannot be of
    //         size 0"); this->_declaratorType = SCCType_DeclaratorType::ERROR;
    //     }
    // }
    //! Make sure to catch error (that should not exist)
    if (declaratorType == ARRAY || declaratorType == FUNCTION) {
        assert(!_isLValue);
    }
}

SCCType::SCCType(const SCCType &that)
    : _specifier(that._specifier),
      _indirection(that._indirection),
      _declaratorType(that._declaratorType),
      _isLValue(that._isLValue),
      _arrLength(that._arrLength),
      _parameters(that._parameters) {}

SCCType &SCCType::operator=(const SCCType &rhs) {
    this->_declaratorType = rhs._declaratorType;
    this->_specifier = rhs._specifier;
    this->_isLValue = rhs._isLValue;
    this->_indirection = rhs._indirection;
    this->_arrLength = rhs._arrLength;
    this->_parameters = rhs._parameters;
    return *this;
}

bool SCCType::typeIsNotValid() const {
    PRINT_FUNC_IF_ENABLED;
    //* arr(void) is invalid
    //* ptr(void) is valid
    //* void is invalid
    return (_specifier == VOID) && (_indirection == 0) &&
           (_declaratorType != FUNCTION);
}

bool SCCType::isArray() const { return this->_declaratorType == ARRAY; }
bool SCCType::isFunc() const { return this->_declaratorType == FUNCTION; }
bool SCCType::noParam() const { return !(this->_parameters); }
bool SCCType::isPredicate() const {
    PRINT_FUNC_IF_ENABLED;
    return this->isPointer() || this->isNumeric();
}
bool SCCType::isNumeric() const {
    PRINT_FUNC_IF_ENABLED;
    if (this->_declaratorType != SCALAR) return false;
    if (this->_indirection > 0) return false;
    return (this->_specifier != VOID);
}
bool SCCType::isPointer() const {
    PRINT_FUNC_IF_ENABLED;
    if (this->_declaratorType == ARRAY) return true;
    if (this->_declaratorType != SCALAR) return false;
    // type is scalar
    return this->_indirection > 0;
}

bool SCCType::isDereferencablePtr() const {
    PRINT_FUNC_IF_ENABLED;
    //* Ptr(Arr(void,n)) is valid
    //* Ptr(Ptr(void)) is valid
    if (!this->isPointer()) return false;
    if (this->_specifier != VOID) return true;
    if (this->_indirection > 1) return true;
    return (this->_declaratorType == ARRAY) && (this->_indirection > 0);
}

bool SCCType::isCompatible(const SCCType &that) const {
    PRINT_FUNC_IF_ENABLED;
#ifdef DEBUG
    std::cout << "[DEBUG] Comparing: " << *this << " to " << that << std::endl;
#endif
    // Is Compatible are not responsible for checking error
    // if (this->declaratorType() == ERROR) return true;
    // if (that.declaratorType() == ERROR) return true;
    if (this->isNumeric() && that.isNumeric()) return true;
    SCCType promotionOfThis = *this;
    SCCType promotionOfThat = that;
    promotionOfThis.promoteArray();
    promotionOfThat.promoteArray();
    //! only valid case at this point is ptr(T)=ptr(T) or ptr(T)=ptr(void)
    if (!(promotionOfThis.isPointer())) return false;
    if (!(promotionOfThat.isPointer())) return false;
    if ((promotionOfThis.specifier() == VOID) &&
        (promotionOfThis.indirection() == 1))
        return true;
    if ((promotionOfThat.specifier() == VOID) &&
        (promotionOfThat.indirection() == 1))
        return true;
    return (promotionOfThis.specifier() == promotionOfThat.specifier()) &&
           (promotionOfThis.indirection() == promotionOfThat.indirection());
}

void SCCType::promoteArray() {
    PRINT_FUNC_IF_ENABLED;
    if (this->isArray()) {
        this->_indirection++;
        this->_declaratorType = SCALAR;
        this->_arrLength = 0;
        this->_isLValue = false;
    }
}
void SCCType::promoteFunc() {
    PRINT_FUNC_IF_ENABLED;
    if (this->isFunc()) {
        this->_declaratorType = SCALAR;
        this->_parameters = nullptr;
        // Function return result cannot be an LValue
        this->_isLValue = false;
    }
}

size_t SCCType::sizeOf() const {
    if (this->_declaratorType == ERROR) return SIZEOF_ERROR;
    if (this->_declaratorType == FUNCTION) return SIZEOF_ERROR;
    if (this->_declaratorType == ARRAY) return ARCH_PTR_SIZE;
    if (this->_indirection > 0) return ARCH_PTR_SIZE;
    // Otherwise this can be one of 3 thing, int, long, char
    switch (this->_specifier) {
        case INT:
#ifdef SIZEOF_INT
            return SIZEOF_INT;
#else
            return ARCH_PTR_SIZE;
#endif
        case LONG:
#ifdef SIZEOF_LONG
            return SIZEOF_LONG;
#else
            return ARCH_PTR_SIZE;
#endif
        case CHAR:
#ifdef SIZEOF_CHAR
            return SIZEOF_CHAR;
#else
            return ARCH_PTR_SIZE;
#endif
        default:
            return SIZEOF_ERROR;
    }
}

const SCCType::SCCType_Parameters *SCCType::parameters() const {
    return this->_parameters;
}

SCCType::SCCType_Specifier SCCType::specifier() const {
    return this->_specifier;
}

bool SCCType::operator==(const SCCType &that) const {
    PRINT_FUNC_IF_ENABLED;
    //! Ignore type check if declaratorType is ERROR
    if (this->_declaratorType == ERROR) return true;
    if (that._declaratorType == ERROR) return true;

    //! Check Declarator type
    if (this->_declaratorType != that._declaratorType) return false;
    //! Check Specifier
    if (this->_specifier != that._specifier) return false;
    //! Check indirection
    if (this->_indirection != that._indirection) return false;

    //! For SCALAR, no more checks
    if (this->_declaratorType == SCALAR) return true;
    if (this->_declaratorType == ARRAY) {
        //! declaratorType is ARRAY
        return this->_arrLength == that._arrLength;
    } else {
        //! declaratorType is FUNCTION
        if (!this->_parameters) return true;
        if (!that._parameters) return true;
        return this->_parameters == that._parameters;
    }
}

bool SCCType::operator!=(const SCCType &that) const {
    PRINT_FUNC_IF_ENABLED;
    return !((*this) == that);
}

void SCCType::printTo(std::ostream &out, const std::string &base) const {
    out << base << "SCCType {\n";
    switch (this->_declaratorType) {
        case ERROR:
            out << base << "    Declarator Type: ERROR\n";
            break;
        case SCALAR:
            out << base << "    Declarator Type: SCALAR\n";
            break;
        case ARRAY:
            out << base << "    Declarator Type: ARRAY\n";
            break;
        case FUNCTION:
            out << base << "    Declarator Type: FUNCTION\n";
            break;
        default:
            out << base << "    Declarator Type: UNKNOWN\n";
            break;
    }
    out << base << "    Specifier:" << this->specifier() << "\n";
    out << base << "    Indirection: " << this->_indirection << "\n";
    out << base << "    Array Length: " << this->_arrLength << "\n";
    out << base << (this->isLValue() ? "Is lvalue" : "Is rvalue") << "\n";
    out << base << "    Parameters: [";
    if (this->_declaratorType != ERROR) {
        if (!this->_parameters) {
            out << "undefined ]\n";
        } else {
            out << "\n";
            for (size_t i = 0; i < (this->_parameters->size()); i++) {
                this->_parameters->at(i).printTo(out, base + "    ");
            }
            out << base << "    ]\n";
        }
    }
    out << base << "}" << std::endl;
}

void SCCType::_clearParams() { this->_parameters = nullptr; }

SCCType::~SCCType() {
    PRINT_FUNC_IF_ENABLED;
    _parameters = nullptr;
    //! Intentionally choose not to delete _parameters
    //! Since SCCType are passed by value.
    //! Deletion is handled by `SCCScope` when main scope exits
}

std::ostream &operator<<(std::ostream &out, const SCCType &rhs) {
    rhs.printTo(out);
    return out;
}
