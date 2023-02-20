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

SCCSymbol::SCCSymbol(const SCCSymbol &that)
    : _id(that._id), _type(that._type) {}

const std::string &SCCSymbol::id() const { return this->_id; }
const SCCType &SCCSymbol::type() const { return this->_type; }

void SCCSymbol::validatePhase3E5() const {
    if (_type.typeIsNotValid()) {
        //! do not output E5 if type is error
        if (_type.declaratorType() == SCCType::ERROR) return;
        printAndReport("Type is not valid.", SCCSemanticError::VOID_VARIABLE,
                       this->id());
        std::cout << *this;
    }
    //! Function parameter is deliberately not checked since this object have no
    //! idea what they are called (id). Func Param will be validated when they
    //! are added to function scope
}

void SCCSymbol::_clearParams() { this->_type._clearParams(); }

std::ostream &operator<<(std::ostream &out, const SCCSymbol &rhs) {
    out << "SCCSymbol{ id: " << rhs.id() << "   type: " << rhs.type() << "}";
    return out;
}
