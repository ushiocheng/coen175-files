#if !defined(EXPR_TREE_BINARY_NODE_HPP)
#define EXPR_TREE_BINARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses {
namespace ExprTreeClasses {

class ExprTreeBinaryNode : public ExprTreeNode {
   protected:
    ExprTreeNode* arg1;
    ExprTreeNode* arg2;

   public:
    ExprTreeBinaryNode(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : arg1(arg1), arg2(arg2) {}
};


class ExprTreeNodeBinaryAdd : public ExprTreeBinaryNode {
   public:
    NodeType identify() const { return NodeType::OP_ADD; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryAnd : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_AND; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryDiv : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_DIV; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryEQ : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_EQ; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryGE : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_GE; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryGT : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_GT; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryLE : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_LE; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryLT : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_LT; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryMinus : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_MINUS; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryMod : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_MOD; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryMUL : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_MUL; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryNEQ : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_NEQ; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinaryOR : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_OR; }
   private:
    void _checkAndSetTypeOfNode() const { }
};
class ExprTreeNodeBinarySubscript : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_SUBSCRIPT; }
   private:
    void _checkAndSetTypeOfNode() const { }
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_BINARY_NODE_HPP
