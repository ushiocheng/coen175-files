#if !defined(EXPR_TREE_NODE_UNARY_DEREF_HPP)
#define EXPR_TREE_NODE_UNARY_DEREF_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryDeref : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_DEREF; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_DEREF_HPP
