#if !defined(SCC_TYPE_CHECKER_HPP)
#define SCC_TYPE_CHECKER_HPP

#include "SCCType.hpp"

namespace SCCTypeChecker {
enum SCCUnaryOperation {
    OP_NOT = 0,
    OP_NEGATION,
    OP_ADDR_OF,
    OP_DEREF,
    OP_SIZEOF
};
enum SCCBinaryOperation {
    OP_OR = 0,
    OP_AND,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_ADD,
    OP_MINUS,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_SUBSCRIPT
};
}  // namespace SCCTypeChecker

SCCType typeOfExpression(SCCTypeChecker::SCCUnaryOperation op,
                         SCCType operand1);

SCCType typeOfExpression(SCCTypeChecker::SCCBinaryOperation op,
                         SCCType operand1, SCCType operand2);

SCCType typeOfExpression(SCCType func,
                         std::vector<SCCType>* parameters = nullptr);

void checkAssign(SCCType lhs, SCCType rhs);

void checkTestExpr(SCCType testExpr);

class SCCScope;
void checkReturnType(SCCScope* context, SCCType returnType);

#endif  // SCC_TYPE_CHECKER_HPP
