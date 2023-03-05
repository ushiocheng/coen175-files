#if !defined(EXPR_TREE_NODE_BINARY_LE_HPP)
#define EXPR_TREE_NODE_BINARY_LE_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryLE : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_LE; }
   private:
    void _checkAndSetTypeOfNode() const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_LE_HPP
