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

SCCType::SCCType(const SCCType_Specifier specifier,
                 const SCCType_DeclaratorType declaratorType,
                 const unsigned int indirection, size_t arrLength,
                 SCCType_Parameters* parameters)
    : _specifier(specifier),
      _indirection(indirection),
      _declaratorType(declaratorType),
      _arrLength(arrLength),
      _parameters(parameters) {
    if (this->_declaratorType != ARRAY) {
        this->_arrLength = 0;
    } else {
    }
}

bool SCCType::isArray() const {}

SCCType_Specifier SCCType::specifier() const {}

bool SCCType::operator==(const SCCType& that) const {}

bool SCCType::operator!=(const SCCType& that) const {}

std::ostream& SCCType::printTo(const std::ostream& out) {}

SCCType::~SCCType() {}

std::ostream& operator<<(const std::ostream& out, const SCCType& rhs) {}
