#if !defined(EXPR_TREE_BINARY_NODE_HPP)
#define EXPR_TREE_BINARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

class ExprTreeBinaryNode : public ExprTreeNode {
   protected:
    ExprTreeNode* arg1;
    ExprTreeNode* arg2;

   public:
    ExprTreeBinaryNode(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : arg1(arg1), arg2(arg2) {}
};

}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_BINARY_NODE_HPP
