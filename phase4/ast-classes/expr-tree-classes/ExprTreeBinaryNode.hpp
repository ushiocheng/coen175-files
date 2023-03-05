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

#include "_expr-tree-node-binary/ExprTreeNodeBinaryAdd.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryAnd.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryDiv.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryEQ.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryGE.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryGT.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryLE.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryLT.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryMinus.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryMod.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryMul.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryNEQ.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinaryOr.hpp"
#include "_expr-tree-node-binary/ExprTreeNodeBinarySubscript.hpp"

#endif  // EXPR_TREE_BINARY_NODE_HPP
