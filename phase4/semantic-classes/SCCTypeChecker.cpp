#include "SCCTypeChecker.hpp"
#include "SCCType.hpp"


SCCType typeOfExpression(
    SCCTypeChecker::SCCUnaryOperation op,
    SCCType operand1)
{
    switch (op)
    {
    case OP_NOT:
        if (operand1.isPredicate())
            break;
        return SCCType(SCCType::INT);

    default:
        return SCCType();
    }
    return SCCType();
}

SCCType typeOfExpression(
    SCCTypeChecker::SCCBinaryOperation op,
    SCCType operand1,
    SCCType operand2)
{
}

SCCType typeOfExpression(
    SCCType func,
    std::vector<SCCType> parameters)
{
}

SCCType typeOfExpression(
    SCCType func)
{
    return SCCType(func.specifier(), SCCType::SCALAR, func.indirection());
}
