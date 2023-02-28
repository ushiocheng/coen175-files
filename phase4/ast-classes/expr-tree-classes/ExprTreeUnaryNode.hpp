#if !defined(EXPR_TREE_UNARY_NODE_HPP)
#define EXPR_TREE_UNARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

class ExprTreeUnaryNode : public ExprTreeNode {
   protected:
    ExprTreeNode* arg1;
   public:
      ExprTreeUnaryNode(ExprTreeNode* arg1) : arg1(arg1) { }
};

}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_UNARY_NODE_HPP
