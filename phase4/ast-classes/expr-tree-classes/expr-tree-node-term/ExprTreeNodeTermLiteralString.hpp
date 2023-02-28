#if !defined(EXPR_TREE_NODE_TERM_LITERAL_STR_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_STR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralString : ExprTreeTermNode {
   private:
   public:
    NodeType identify() { return NodeType::T_LITERAL_STR; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_STR_HPP
