#if !defined(EXPR_TREE_NODE_BINARY_MOD_HPP)
#define EXPR_TREE_NODE_BINARY_MOD_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryMod : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_MOD; }
   private:
    void _checkAndSetTypeOfNode() const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_MOD_HPP
