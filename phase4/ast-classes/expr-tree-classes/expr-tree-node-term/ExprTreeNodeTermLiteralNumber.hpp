#if !defined(EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralNumber : ExprTreeTermNode {
   private:
   public:
    NodeType identify() { return NodeType::T_LITERAL_NUM; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP
