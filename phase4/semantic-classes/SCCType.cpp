#include "SCCType.hpp"

#include <iostream>
#include <string>

#include "../GlobalConfig.hpp"

#ifdef DEBUG
#define DEBUG_ADDITIONAL_WARNING
#endif

SCCType::SCCType()
{
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
      _arrLength(arrLength),
      _parameters(parameters),
      _isLValue(isLValue)
{
    // //! Enforce array cannot be of size 0
    // if (this->_declaratorType == ARRAY) {
    //     if (this->_arrLength == 0) {
    //         reportError("SCCType: Declaration Invalid: array cannot be of
    //         size 0"); this->_declaratorType = SCCType_DeclaratorType::ERROR;
    //     }
    // }
}

SCCType::SCCType(const SCCType &that)
{
    this->_declaratorType = that._declaratorType;
    this->_specifier = that._specifier;
    this->_indirection = that._indirection;
    this->_arrLength = that._arrLength;
    this->_parameters = that._parameters;
    this->_isLValue = that._isLValue;
}

SCCType &SCCType::operator=(const SCCType &rhs)
{
    if (this->_parameters)
        delete this->_parameters;
    this->_declaratorType = rhs._declaratorType;
    this->_specifier = rhs._specifier;
    this->_indirection = rhs._indirection;
    this->_arrLength = rhs._arrLength;
    this->_parameters = rhs._parameters;
    this->_isLValue = rhs._isLValue;
    return *this;
}

bool SCCType::typeIsNotValid() const
{
    return (_specifier == VOID) && (_indirection == 0) &&
           (_declaratorType != FUNCTION);
}

bool SCCType::isArray() const { return this->_declaratorType == ARRAY; }
bool SCCType::isFunc() const { return this->_declaratorType == FUNCTION; }
bool SCCType::noParam() const { return !(this->_parameters); }
bool SCCType::isPredicate() const
{
    return this->isPointer() || this->isNumeric();
}
bool SCCType::isNumeric() const
{
    if (this->_declaratorType != SCALAR)
        return false;
    if (this->_indirection > 0)
        return false;
    return (this->_specifier != VOID);
}
bool SCCType::isPointer() const
{
    if (this->_declaratorType == ARRAY)
        return true;
    if (this->_declaratorType != SCALAR)
        return false;
    // type is scalar
    return this->_indirection > 0;
}

bool SCCType::equalAfterPromotion(const SCCType &that) const
{
    if (*this == that)
        return true;
    // declType cannot be error
    SCCType promotions = *this;
    return promotions._equalAfterPromotionHelper(that);
}

bool SCCType::_equalAfterPromotionHelper(const SCCType &that)
{
    if (*this == that)
        return true;
    // declType cannot be error
    if (this->_declaratorType == FUNCTION)
    {
        this->_declaratorType = SCALAR;
        // Function return result cannot be an LValue
        this->_isLValue = false;
        return this->_equalAfterPromotionHelper(that);
    }
    if (this->_declaratorType == ARRAY)
    {
        this->_indirection++;
        this->_declaratorType = SCALAR;
        return this->_equalAfterPromotionHelper(that);
    }
    // declType must be SCALAR
    if (this->_specifier == CHAR)
    {
        this->_specifier == INT;
        return this->_equalAfterPromotionHelper(that);
    }
    if (this->_specifier == INT)
    {
        this->_specifier == LONG;
        return this->_equalAfterPromotionHelper(that);
    }
    return false;
}

const SCCType::SCCType_Parameters *SCCType::parameters() const
{
    return this->_parameters;
}

SCCType::SCCType_Specifier SCCType::specifier() const
{
    return this->_specifier;
}

bool SCCType::operator==(const SCCType &that) const
{
    //! Ignore type check if declaratorType is ERROR
    if (this->_declaratorType == ERROR)
        return true;
    if (that._declaratorType == ERROR)
        return true;

    //! Check Declarator type
    if (this->_declaratorType != that._declaratorType)
        return false;
    //! Check Specifier
    if (this->_specifier != that._specifier)
        return false;
    //! Check indirection
    if (this->_indirection != that._indirection)
        return false;

    //! For SCALAR, no more checks
    if (this->_declaratorType == SCALAR)
        return true;
    if (this->_declaratorType == ARRAY)
    {
        //! declaratorType is ARRAY
        return this->_arrLength == that._arrLength;
    }
    else
    {
        //! declaratorType is FUNCTION
        if (!this->_parameters)
            return true;
        if (!that._parameters)
            return true;
        return this->_parameters == that._parameters;
    }
}

bool SCCType::operator!=(const SCCType &that) const
{
    return !((*this) == that);
}

void SCCType::printTo(std::ostream &out, const std::string &base) const
{
    out << base << "SCCType {\n";
    switch (this->_declaratorType)
    {
    case ERROR:
        out << base << "    Declarator Type: ERROR\n";
        break;
    case SCALAR:
        out << base << "    Declarator Type: SCALAR\n"
            << base << "    Specifier:" << this->specifier() << "\n"
            << base << "    " << (this->isLValue()?"Is lvalue":"Is rvalue") << "\n";
        break;
    case ARRAY:
        out << base << "    Declarator Type: ARRAY\n"
            << base << "    Specifier:" << this->specifier() << "\n"
            << base << "    " << (this->isLValue()?"Is lvalue":"Is rvalue") << "\n"
            << base << "    Indirection: " << this->_indirection << "\n"
            << base << "    Array Length: " << this->_arrLength << "\n";
        break;
    case FUNCTION:
        out << base << "    Declarator Type: FUNCTION\n"
            << base << "    Specifier:" << this->specifier() << "\n"
            << base << "    Indirection: " << this->_indirection << "\n"
            << base << "    Parameters: [";
        if (!this->_parameters)
        {
            out << "undefined ]\n";
            break;
        }
        out << "\n";
        for (size_t i = 0; i < (this->_parameters->size()); i++)
        {
            this->_parameters->at(i).printTo(out, base + "    ");
        }
        out << base << "    ]\n";
        break;
    default:
        out << base << "    Declarator Type: UNKNOWN\n";
        break;
    }
    out << base << "}" << std::endl;
}

void SCCType::_deleteParams()
{
    if (this->_parameters)
        delete this->_parameters;
    this->_parameters = nullptr;
}

SCCType::~SCCType()
{
    //! Intentionally choose not to delete _parameters
    //! Since SCCType are passed by value.
    //! Deletion is handled by `SCCScope` when main scope exits
}

std::ostream &operator<<(std::ostream &out, const SCCType &rhs)
{
    rhs.printTo(out);
    return out;
}
