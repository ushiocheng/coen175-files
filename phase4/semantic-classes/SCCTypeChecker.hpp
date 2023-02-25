#if !defined(SCC_TYPE_CHECKER_HPP)
#define SCC_TYPE_CHECKER_HPP

#include "SCCType.hpp"

#include "../SCCOperators.hpp"

SCCType typeOfExpression(SCC::SCCUnaryOperation op,
                         SCCType operand1);

SCCType typeOfExpression(SCC::SCCBinaryOperation op,
                         SCCType operand1, SCCType operand2);

SCCType typeOfExpression(SCCType func,
                         std::vector<SCCType>* parameters = nullptr);

void checkAssign(SCCType lhs, SCCType rhs);

void checkTestExpr(SCCType testExpr);

class SCCScope;
void checkReturnType(const SCCScope* context, const SCCType& returnType);

#endif  // SCC_TYPE_CHECKER_HPP
