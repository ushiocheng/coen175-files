
namespace SCC {

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

}  // namespace SCC
