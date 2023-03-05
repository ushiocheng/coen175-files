#if !defined(SCC_TYPE_CHECKER_HPP)
#define SCC_TYPE_CHECKER_HPP

#include "SCCType.hpp"
#include <vector>

class SCCScope;

SCCType typeOfExpression(SCCType func, std::vector<SCCType>* parameters);
void checkAssign(SCCType lhs, SCCType rhs);
void checkTestExpr(SCCType testExpr);
void checkReturnType(SCCScope* context, SCCType returnType);

#endif // SCC_TYPE_CHECKER_HPP
