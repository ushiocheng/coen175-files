#if !defined(EXPR_TREE_NODE_UNARY_NOT_HPP)
#define EXPR_TREE_NODE_UNARY_NOT_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryNot : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_NOT; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_NOT_HPP
