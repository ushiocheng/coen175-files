#include "SCCType.hpp"

#include <iostream>
#include <string>

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

SCCType::SCCType() {
    this->_declaratorType = ERROR;
}

SCCType::SCCType(const SCCType_Specifier specifier,
                 const SCCType_DeclaratorType declaratorType,
                 const unsigned int indirection, size_t arrLength,
                 SCCType_Parameters* parameters)
    : _specifier(specifier),
      _indirection(indirection),
      _declaratorType(declaratorType),
      _arrLength(arrLength),
      _parameters(parameters) {
    // //! Enforce array cannot be of size 0
    // if (this->_declaratorType == ARRAY) {
    //     if (this->_arrLength == 0) {
    //         reportError("SCCType: Declaration Invalid: array cannot be of
    //         size 0"); this->_declaratorType = SCCType_DeclaratorType::ERROR;
    //     }
    // }
    // //! Enforce function must have parameters
    // if (this->_declaratorType == FUNCTION) {
    //     if (!this->_parameters) {
    //         reportError("SCCType: Declaration Invalid: function must have
    //         parameters"); this->_declaratorType =
    //         SCCType_DeclaratorType::ERROR;
    //     }
    // }
}

bool SCCType::isArray() const { return this->_declaratorType == ARRAY; }

SCCType_Specifier SCCType::specifier() const { return this->_specifier; }

bool SCCType::operator==(const SCCType& that) const {
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

bool SCCType::operator!=(const SCCType& that) const {
    return !((*this) == that);
}

std::ostream& SCCType::printTo(const std::ostream& out,
                               const std::string base) {
    std::ostream& res = (out << base << "SCCType {\n");
    if (this->_declaratorType == ERROR) {
        return (res << base << "    Declarator Type: ERROR\n"
                    << base << "}" << std::endl);
    } else if (this->_declaratorType == SCALAR) {
        return (res << base << "    Declarator Type: SCALAR\n"
                    << base << "    Specifier:" << this->specifier() << "\n"
                    << base << "    Indirection: " << this->_indirection << "\n"
                    << base << "}" << std::endl);
    } else if (this->_declaratorType == ARRAY) {
        return (res << base << "    Declarator Type: ARRAY\n"
                    << base << "    Specifier:" << this->specifier() << "\n"
                    << base << "    Indirection: " << this->_indirection << "\n"
                    << base << "    Array Length: " << this->_arrLength << "\n"
                    << base << "}" << std::endl);
    } else if (this->_declaratorType == FUNCTION) {
        res = (res << base << "    Declarator Type: FUNCTION\n"
                   << base << "    Specifier:" << this->specifier() << "\n"
                   << base << "    Indirection: " << this->_indirection << "\n"
                   << base << "    Parameters: ["
                   << "\n");
        for (SCCType paramType : this->_parameters) {
            res = paramType.printTo(res, base + "    ");
        }
        res = (res << base << "    ]");
        return (res << base << "}" << std::endl);
    } else {
        return (res << base << "    Declarator Type: UNKNOWN\n"
                    << base << "}" << std::endl);
    }
}

SCCType::~SCCType() {
    delete this->_parameters;
}

std::ostream& operator<<(const std::ostream& out, const SCCType& rhs) {
    return rhs.printTo(out);
}
