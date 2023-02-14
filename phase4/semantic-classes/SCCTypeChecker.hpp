#if !defined(SCC_TYPE_CHECKER_HPP)
#define SCC_TYPE_CHECKER_HPP

#include "SCCType.hpp"

namespace SCCTypeChecker
{
    enum SCCUnaryOperation
    {
        OP_NOT,
        OP_NEGATION,
        OP_ADDR_OF,
        OP_DEREF,
        OP_SIZEOF
    };
    enum SCCBinaryOperation
    {
        OP_OR,
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
}

SCCType typeOfExpression(
    SCCTypeChecker::SCCUnaryOperation op,
    SCCType operand1);

SCCType typeOfExpression(
    SCCTypeChecker::SCCBinaryOperation op,
    SCCType operand1,
    SCCType operand2);

SCCType typeOfExpression(
    SCCType func,
    std::vector<SCCType> parameters);

SCCType typeOfExpression(
    SCCType func
);

#endif // SCC_TYPE_CHECKER_HPP
