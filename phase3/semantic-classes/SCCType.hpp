#ifndef SCC_TYPE_HPP
#define SCC_TYPE_HPP

#include <ostream>
#include <string>
#include <vector>

#include "../GlobalConfig.hpp"

class SCCType
{
public:
    typedef std::vector<class SCCType> SCCType_Parameters;
    enum SCCType_Specifier
    {
        VOID,
        INT,
        LONG,
        CHAR
    };
    enum SCCType_DeclaratorType
    {
        SCALAR,
        ARRAY,
        FUNCTION,
        ERROR
    };

private:
    SCCType_Specifier _specifier;
    size_t _indirection;
    SCCType_DeclaratorType _declaratorType;
    // Optionals
    size_t _arrLength; // Valid & required for _declaratorType == ARRAY
    SCCType_Parameters *
        _parameters; // Valid & optional for _declaratorType == FUNCTION

public:
    /**
     * Default constructor
     * Return type of ERROR
     */
    SCCType();
    SCCType(const SCCType_Specifier specifier,
            const SCCType_DeclaratorType declaratorType,
            const unsigned int indirection = 0, size_t arrLength = 0,
            SCCType_Parameters *parameters = nullptr);
    SCCType(const SCCType &that);
    SCCType &operator=(const SCCType &rhs);
    bool isArray() const;
    bool isFunc() const;
    bool noParam() const;
    SCCType_Specifier specifier() const;
    bool operator==(const SCCType &that) const;
    bool operator!=(const SCCType &that) const;
    void printTo(std::ostream &out, const std::string &base = "") const;
    ~SCCType();
};

std::ostream &operator<<(std::ostream &out, const SCCType &rhs);

#endif
