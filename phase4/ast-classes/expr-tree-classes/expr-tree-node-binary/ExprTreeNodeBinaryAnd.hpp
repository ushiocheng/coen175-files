#if !defined(EXPR_TREE_NODE_BINARY_AND_HPP)
#define EXPR_TREE_NODE_BINARY_AND_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryAnd : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_AND; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_AND_HPP
