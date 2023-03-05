#if !defined(EXPR_TREE_UNARY_NODE_HPP)
#define EXPR_TREE_UNARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses {
namespace ExprTreeClasses {

class ExprTreeUnaryNode : public ExprTreeNode {
   protected:
    ExprTreeNode* arg1;

   public:
    ExprTreeUnaryNode(ExprTreeNode* arg1) : arg1(arg1) {}
};

class ExprTreeNodeUnaryAddrOf : public ExprTreeUnaryNode {
   public:
    NodeType identify() const { return NodeType::OP_ADDR_OF; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeUnaryDeref : public ExprTreeUnaryNode {
   public:
    NodeType identify() const { return NodeType::OP_DEREF; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeUnaryNegation : public ExprTreeUnaryNode {
   public:
    NodeType identify() const { return NodeType::OP_NEGATION; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeUnaryNot : public ExprTreeUnaryNode {
   public:
    NodeType identify() const { return NodeType::OP_NOT; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeUnarySizeof : public ExprTreeUnaryNode {
   public:
    NodeType identify() const { return NodeType::OP_SIZEOF; }
   private:
    void _checkAndSetTypeOfNode() const { }
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_UNARY_NODE_HPP
