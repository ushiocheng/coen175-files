#if !defined(EXPR_TREE_NODE_BINARY_MUL_HPP)
#define EXPR_TREE_NODE_BINARY_MUL_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryMUL : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_MUL; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_MUL_HPP
