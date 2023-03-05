#if !defined(EXPR_TREE_NODE_UNARY_DEREF_HPP)
#define EXPR_TREE_NODE_UNARY_DEREF_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryDeref : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_DEREF; }
   private:
    void _checkAndSetTypeOfNode() const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_DEREF_HPP
