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
        : arg1(arg1), arg2(arg2) {
        this->performTypeChecking();
    }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const {
        arg1->generateStringLiterals(out);
        arg2->generateStringLiterals(out);
    }
};

class ExprTreeNodeBinaryAdd : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryAdd(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_ADD; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryAnd : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryAnd(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_AND; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryDiv : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryDiv(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_DIV; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryEQ : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryEQ(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_EQ; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryGE : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryGE(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_GE; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryGT : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryGT(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_GT; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryLE : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryLE(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_LE; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryLT : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryLT(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_LT; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMinus : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMinus(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MINUS; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMod : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMod(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MOD; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMUL : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMUL(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MUL; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryNEQ : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryNEQ(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_NEQ; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryOR : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryOR(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_OR; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinarySubscript : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinarySubscript(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_SUBSCRIPT; }
    // Code generation Interfaces
    SCCData* generateCode(std::ostream& out) const;
    SCCData* generateCode(std::ostream& out, bool retLValue) const;

   private:
    void _checkAndSetTypeOfNode() const;
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_BINARY_NODE_HPP
