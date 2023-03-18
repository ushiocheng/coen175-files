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
    ExprTreeUnaryNode(ExprTreeNode* arg1) : arg1(arg1) {
        this->performTypeChecking();
    }
};

class ExprTreeNodeUnaryAddrOf : public ExprTreeUnaryNode {
   public:
    ExprTreeNodeUnaryAddrOf(ExprTreeNode* arg1) : ExprTreeUnaryNode(arg1) {}
    NodeType identify() const { return OP_ADDR_OF; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeUnaryDeref : public ExprTreeUnaryNode {
   public:
    ExprTreeNodeUnaryDeref(ExprTreeNode* arg1) : ExprTreeUnaryNode(arg1) {}
    NodeType identify() const { return OP_DEREF; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeUnaryNegation : public ExprTreeUnaryNode {
   public:
    ExprTreeNodeUnaryNegation(ExprTreeNode* arg1) : ExprTreeUnaryNode(arg1) {}
    NodeType identify() const { return OP_NEGATION; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeUnaryNot : public ExprTreeUnaryNode {
   public:
    ExprTreeNodeUnaryNot(ExprTreeNode* arg1) : ExprTreeUnaryNode(arg1) {}
    NodeType identify() const { return OP_NOT; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeUnarySizeof : public ExprTreeUnaryNode {
   public:
    ExprTreeNodeUnarySizeof(ExprTreeNode* arg1) : ExprTreeUnaryNode(arg1) {}
    NodeType identify() const { return OP_SIZEOF; }

   private:
    void _checkAndSetTypeOfNode() const;
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_UNARY_NODE_HPP
