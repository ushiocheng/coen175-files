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
    bool _isLValue;
    /**
     * Recursive helper for equalAfterPromotion()
     */
    bool _equalAfterPromotionHelper(const SCCType &that);

   public:
    /**
     * Default constructor
     * Return type of ERROR
     */
    SCCType();
    SCCType(const SCCType_Specifier specifier,
            const SCCType_DeclaratorType declaratorType = SCCType::SCALAR,
            const unsigned int indirection = 0, size_t arrLength = 0,
            SCCType_Parameters *parameters = nullptr, bool isLValue = true);
    SCCType(const SCCType &that);
    SCCType &operator=(const SCCType &rhs);
    /**
     * Check if type is valid
     * @remark Check for ERROR type in addition to check VOID types
     */
    bool typeIsNotValid() const;
    bool isArray() const;
    bool isFunc() const;
    bool isPredicate() const;
    bool isNumeric() const;
    bool isPointer() const;
    /**
     * Check if this can be dereferenced
     * @return false if this is not ptr
     */
    bool isDereferencablePtr() const;
    /**
     * Check equal with promotion applied
     * @remark *this will be promoted to match that, thus, a warning will be
     * printed in verbose mode to signify when a larger object is implicitly
     * cast into a smaller one.
     * TODO: [Q10] Should I allow promote in opposite direction?
     * TODO-cont: ex. can long be assigned to int
     */
    bool equalAfterPromotion(const SCCType &that) const;
    /**
     * Promote Array -> Ptr
     * @remark changes how sizeof() behaves!
     */
    void promoteArray();
    /**
     * Promote Func -> RValue
     */
    void promoteFunc();
    size_t sizeOf() const;
    /**
     * whether param is defined
     * @return true if param==nullptr
     */
    bool noParam() const;
    SCCType_Specifier specifier() const;
    size_t indirection() const { return _indirection; };
    SCCType_DeclaratorType declaratorType() const { return _declaratorType; };
    size_t arrLength() const { return _arrLength; };
    bool isLValue() const { return _isLValue; };

    const SCCType_Parameters *parameters() const;
    /**
     * Comparator
     * @remark Only compares type, one can be LValue while another one being
     * RValue
     */
    bool operator==(const SCCType &that) const;
    bool operator!=(const SCCType &that) const;
    void printTo(std::ostream &out, const std::string &base = "") const;
    /**
     * Deleting Params which is allocated dynamically.
     * @remark this is dangerous and should ONLY be used for deallocating
     * objects.
     */
    void _clearParams();
    ~SCCType();
};

std::ostream &operator<<(std::ostream &out, const SCCType &rhs);

#endif
