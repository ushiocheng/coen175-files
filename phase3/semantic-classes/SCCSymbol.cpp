#include "SCCSymbol.hpp"

#include <string>

SCCSymbol::SCCSymbol(const std::string &id)
    : _id(id),
      _type(SCCType::SCCType_Specifier::VOID,
            SCCType::SCCType_DeclaratorType::ERROR) {}

SCCSymbol::SCCSymbol(const std::string &id, const SCCType &type)
    : _id(id), _type(type) {}
const std::string &SCCSymbol::id() const { return this->_id; }
const SCCType &SCCSymbol::type() const { return this->_type; }
