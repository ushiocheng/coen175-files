#if !defined(EXPR_TREE_NODE_BINARY_EQ_HPP)
#define EXPR_TREE_NODE_BINARY_EQ_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryEQ : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_EQ; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_EQ_HPP
