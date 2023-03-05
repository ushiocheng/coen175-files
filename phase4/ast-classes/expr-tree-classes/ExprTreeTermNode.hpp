#if !defined(EXPR_TREE_TERM_NODE_HPP)
#define EXPR_TREE_TERM_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

class ExprTreeTermNode : public ExprTreeNode {
   protected:
   public:
};

}  // namespace SCCASTClasses::ExprTreeClasses

#include "_expr-tree-node-term/ExprTreeNodeTermFuncCall.hpp"
#include "_expr-tree-node-term/ExprTreeNodeTermLiteralChar.hpp"
#include "_expr-tree-node-term/ExprTreeNodeTermLiteralNumber.hpp"
#include "_expr-tree-node-term/ExprTreeNodeTermLiteralString.hpp"
#include "_expr-tree-node-term/ExprTreeNodeTermVariable.hpp"

#endif  // EXPR_TREE_TERM_NODE_HPP
