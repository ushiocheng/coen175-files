#if !defined(EXPR_TREE_NODE_BINARY_MINUS_HPP)
#define EXPR_TREE_NODE_BINARY_MINUS_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryMinus : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_MINUS; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_MINUS_HPP
