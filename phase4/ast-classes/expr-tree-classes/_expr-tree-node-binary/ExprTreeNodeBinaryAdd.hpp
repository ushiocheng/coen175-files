#if !defined(EXPR_TREE_NODE_BINARY_ADD_HPP)
#define EXPR_TREE_NODE_BINARY_ADD_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryAdd : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_ADD; }
   private:
    void _checkAndSetTypeOfNode() const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_ADD_HPP
