
#if !defined(CHECK_TEST_EXPR_HPP)
#define CHECK_TEST_EXPR_HPP

#include "../../exceptions/SCCError.hpp"

bool checkTestExpr(SCCType testExpr) {
    //! if expr have error type, skip check
    if (testExpr.declaratorType() == SCCType::ERROR) return false;
    //! check is Predicate
    if (!testExpr.isPredicate()) {
        printAndReport("Phase4: test expr is not Predicate",
                       EXP_INV_TEST);
        return false;
    }
    return true;
}

#endif  // CHECK_TEST_EXPR_HPP
