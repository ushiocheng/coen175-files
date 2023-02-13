#ifndef SCC_TYPE_HPP
#define SCC_TYPE_HPP

#include <ostream>
#include <string>
#include <vector>

#include "../GlobalConfig.hpp"
#include "../tokens.h"

class SCCType {
   public:
    typedef std::vector<class SCCType> SCCType_Parameters;
    enum SCCType_Specifier { VOID, INT, LONG, CHAR };
    enum SCCType_DeclaratorType { SCALAR, ARRAY, FUNCTION, ERROR };

   private:
    SCCType_Specifier _specifier;
    size_t _indirection;
    SCCType_DeclaratorType _declaratorType;
    // Optionals
    size_t _arrLength;  // Valid & required for _declaratorType == ARRAY
    SCCType_Parameters
        *_parameters;  // Valid & optional for _declaratorType == FUNCTION

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
    /**
     * Check for E5: type not void
     */
    bool typeIsNotValid() const;
    bool isArray() const;
    bool isFunc() const;
    bool noParam() const;
    const SCCType_Parameters *parameters() const;
    SCCType_Specifier specifier() const;
    bool operator==(const SCCType &that) const;
    bool operator!=(const SCCType &that) const;
    void printTo(std::ostream &out, const std::string &base = "") const;
    /**
     * Deleting Params which is allocated dynamically.
     * @remark this is dangerous and should ONLY be used for deallocating
     * objects.
     */
    void _deleteParams();
    ~SCCType();
};

std::ostream &operator<<(std::ostream &out, const SCCType &rhs);

#endif
