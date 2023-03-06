#include "SCCTypeChecker.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../GlobalConfig.hpp"
#include "../exceptions/SCCError.hpp"
#include "SCCScope.hpp"
#include "SCCType.hpp"

#ifdef DEBUG
// #define DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_IF_DEBUG(sth) std::cerr << "[DEBUG] " << sth << std::endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED                                              \
    std::cerr << "[DEBUG] Running " << __func__ << " on line " << __LINE__ \
              << std::endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

SCCType typeOfExpression(SCCType func, std::vector<SCCType>* parameters) {
    PRINT_FUNC_IF_ENABLED;
    //! Check func is FUNCTION
    if (!func.isFunc()) {
        printAndReport("Phase4: Callee not function.",
                       EXP_NOT_FUNC);
#ifdef VERBOSE_ERROR_MSG
        PRINT_IF_DEBUG("Calling: " << func);
#endif
    }
    //! check if func is defined/declared
    if (func.parameters() == NULL) {
        //! Function is undefined in this scope, skip param checking
        // // return SCCType();
        func.promoteFunc();
        return func;
    }
    //! Function is defined at this point
    //! Check parameter count matches
    size_t expectedArgCount = func.parameters()->size();
    size_t actualArgCount = parameters ? parameters->size() : 0;
    if (expectedArgCount != actualArgCount) {
        printAndReport("Phase4: Calling function with mismatched param count.",
                       EXP_INV_ARG);
#ifdef VERBOSE_ERROR_MSG
        std::cerr << "[DEBUG] Calling function " << func << "with param: ";
        if (parameters) {
            std::cerr << parameters;
        } else {
            std::cerr << "[]";
        }
        std::cerr << std::endl;
#endif
        return SCCType();
    }
    //! Check param matches
    if (expectedArgCount > 0) {
        const std::vector<SCCType>* expectedParams = func.parameters();
        for (size_t i = 0; i < expectedParams->size(); i++) {
            if (parameters->at(i).isCompatible(expectedParams->at(i)) &&
                parameters->at(i).isPredicate())
                continue;
            // Mis match params
            printAndReport("Phase4: Calling function with mismatched params.",
                           EXP_INV_ARG);
#ifdef VERBOSE_ERROR_MSG
            PRINT_IF_DEBUG("Func: " << func << "Parameter: " << parameters);
#endif
            return SCCType();
        }
    }
    //! Promote Function to its return value
    func.promoteFunc();
    return func;
}

void checkAssign(SCCType lhs, SCCType rhs) {
    PRINT_FUNC_IF_ENABLED;
    //! if any have error type, skip check
    if (lhs.declaratorType() == SCCType::ERROR) return;
    if (rhs.declaratorType() == SCCType::ERROR) return;
    //! Check is LValue
    if (!lhs.isLValue()) {
        printAndReport("Phase4: Assigning to RValue",
                       EXP_INV_EXPECT_LVALUE);
        return;
    }
    //! Check compatible
    if (!rhs.isCompatible(lhs)) {
        printAndReport("Phase4: Assign to imcompatible type",
                       EXP_INV_OP_BIN, "=");
        return;
    }
}

void checkTestExpr(SCCType testExpr) {
    PRINT_FUNC_IF_ENABLED;
    PRINT_IF_DEBUG(testExpr);
    //! if expr have error type, skip check
    if (testExpr.declaratorType() == SCCType::ERROR) return;
    //! check is Predicate
    if (!testExpr.isPredicate()) {
        printAndReport("Phase4: test expr is not Predicate",
                       EXP_INV_TEST);
        return;
    }
}

void checkReturnType(SCCScope* context, SCCType returnType) {
    PRINT_FUNC_IF_ENABLED;
    //! if expr have error type, skip check
    if (returnType.declaratorType() == SCCType::ERROR) return;
    //! get expected return type
    const SCCSymbol* enclosingFunc = context->getEnclosingFunc();
    assert(enclosingFunc);
    //! Check compatible
    SCCType expectedReturnType(enclosingFunc->type());
    //! If expected return type are error, skip check
    if (expectedReturnType.declaratorType() == SCCType::ERROR) return;
    expectedReturnType.promoteFunc();
    if (!returnType.isCompatible(expectedReturnType)) {
        printAndReport("Phase4: return type incompatible",
                       EXP_INV_RETURN);
        return;
    }
}
