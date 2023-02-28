#if !defined(EXPR_TREE_NODE_BINARY_NEQ_HPP)
#define EXPR_TREE_NODE_BINARY_NEQ_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryNEQ : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_NEQ; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_NEQ_HPP
