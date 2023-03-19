
#if !defined(CHECK_TEST_EXPR_HPP)
#define CHECK_TEST_EXPR_HPP

#include "../../exceptions/SCCError.hpp"
namespace SCCASTClasses {
bool checkTestExpr(SCCType testExpr) {
    //! if expr have error type, skip check
    if (testExpr.declaratorType() == SCCType::ERROR) return false;
    //! check is Predicate
    if (!testExpr.isPredicate()) {
        return false;
    }
    return true;
}
}  // namespace SCCASTClasses

#endif  // CHECK_TEST_EXPR_HPP
