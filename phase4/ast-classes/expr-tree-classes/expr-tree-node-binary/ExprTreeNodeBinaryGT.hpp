#if !defined(EXPR_TREE_NODE_BINARY_GT_HPP)
#define EXPR_TREE_NODE_BINARY_GT_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryGT : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_GT; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_GT_HPP
