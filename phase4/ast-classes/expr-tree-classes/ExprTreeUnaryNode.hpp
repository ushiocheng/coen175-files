#if !defined(EXPR_TREE_UNARY_NODE_HPP)
#define EXPR_TREE_UNARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

class ExprTreeUnaryNode : public ExprTreeNode {
   protected:
    ExprTreeNode* arg1;

   public:
    ExprTreeUnaryNode(ExprTreeNode* arg1) : arg1(arg1) {}
};

}  // namespace SCCASTClasses::ExprTreeClasses

#include "_expr-tree-node-unary/ExprTreeNodeUnaryAddrOf.hpp"
#include "_expr-tree-node-unary/ExprTreeNodeUnaryDeref.hpp"
#include "_expr-tree-node-unary/ExprTreeNodeUnaryNegation.hpp"
#include "_expr-tree-node-unary/ExprTreeNodeUnaryNot.hpp"
#include "_expr-tree-node-unary/ExprTreeNodeUnarySizeof.hpp"

#endif  // EXPR_TREE_UNARY_NODE_HPP
