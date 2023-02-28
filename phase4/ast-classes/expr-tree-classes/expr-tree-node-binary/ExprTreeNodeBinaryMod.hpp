#if !defined(EXPR_TREE_NODE_BINARY_MOD_HPP)
#define EXPR_TREE_NODE_BINARY_MOD_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryMod : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() { return NodeType::OP_MOD; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_MOD_HPP
