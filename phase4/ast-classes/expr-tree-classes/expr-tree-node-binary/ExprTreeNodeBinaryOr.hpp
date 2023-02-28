#if !defined(EXPR_TREE_NODE_BINARY_OR_HPP)
#define EXPR_TREE_NODE_BINARY_OR_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryOR : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_OR; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_OR_HPP
