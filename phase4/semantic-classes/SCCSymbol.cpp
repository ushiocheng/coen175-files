#include "SCCSymbol.hpp"

#include <iostream>
#include <string>

#include "SCCError.hpp"

SCCSymbol::SCCSymbol(const std::string &id)
    : _id(id),
      _type(SCCType::SCCType_Specifier::VOID,
            SCCType::SCCType_DeclaratorType::ERROR) {}

SCCSymbol::SCCSymbol(const std::string &id, const SCCType &type)
    : _id(id), _type(type) {}
const std::string &SCCSymbol::id() const { return this->_id; }
const SCCType &SCCSymbol::type() const { return this->_type; }

void SCCSymbol::validateType() const {
    if (_type.typeIsNotValid()) {
        printAndReport("Type is not valid.", SCCSemanticError::VOID_VARIABLE,
                       this->id());
        std::cout << *this;
    }
    //! Function parameter is deliberately not checked since this object have no
    //! idea what they are called (id). Func Param will be validated when they
    //! are added to function scope
}

void SCCSymbol::_deleteParams() { this->_type._deleteParams(); }

std::ostream &operator<<(std::ostream &out, const SCCSymbol &rhs) {
    out << "SCCSymbol{ id: " << rhs.id() << "   type: " << rhs.type() << "}";
    return out;
}
