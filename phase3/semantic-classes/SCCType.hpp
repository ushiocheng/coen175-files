#ifndef SCC_TYPE_HPP
#define SCC_TYPE_HPP

#include <vector>
#include <ostream>
#include "GlobalConfig.hpp"

typedef std::vector<class SCCType> SCCType_Parameters;
enum SCCType_Specifier { VOID, INT, LONG, CHAR };
enum SCCType_DeclaratorType { SCALAR, ARRAY, FUNCTION, ERROR };

class SCCType {
   private:
    SCCType_Specifier _specifier;
    size_t _indirection;
    SCCType_DeclaratorType _declaratorType;
    size_t _arrLength;
    SCCType_Parameters* _parameters;

   public:
    SCCType(const SCCType_Specifier specifier,
            const SCCType_DeclaratorType declaratorType,
            const unsigned int indirection = 0, size_t arrLength = 0,
            SCCType_Parameters* parameters = nullptr);
    bool isArray() const;
    SCCType_Specifier specifier() const;
    bool operator==(const SCCType& that) const;
    bool operator!=(const SCCType& that) const;
    std::ostream& printTo(const std::ostream& out);
    ~SCCType();
};

std::ostream& operator<<(const std::ostream& out, const SCCType& rhs);

#endif