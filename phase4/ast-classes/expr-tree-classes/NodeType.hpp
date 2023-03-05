#if !defined(NODE_TYPE_HPP)
#define NODE_TYPE_HPP

namespace SCCASTClasses {
namespace ExprTreeClasses {
enum NodeType {
    // OP UNARY
    OP_NOT = 0,
    OP_NEGATION,
    OP_ADDR_OF,
    OP_DEREF,
    OP_SIZEOF,
    // OP BINARY
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
    OP_SUBSCRIPT,
    // Term
    T_FUNC_CALL,
    T_VAR,
    T_LITERAL_NUM,
    T_LITERAL_STR,
    T_LITERAL_CHAR
};
}
}  // namespace SCCASTClasses

#endif  // NODE_TYPE_HPP
