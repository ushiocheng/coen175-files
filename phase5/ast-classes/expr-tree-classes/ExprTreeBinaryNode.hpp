#if !defined(EXPR_TREE_BINARY_NODE_HPP)
#define EXPR_TREE_BINARY_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"
#include "../../GlobalConfig.hpp"

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

    SCCDataLocation* generateCodeToEvaluateExprNode(
        std::ostream& out, const char* indentation = "") const {
        assert(false);
        return NULL;
    }
};

class ExprTreeNodeBinaryAdd : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryAdd(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_ADD; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryAnd : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryAnd(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_AND; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryDiv : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryDiv(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_DIV; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryEQ : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryEQ(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_EQ; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryGE : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryGE(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_GE; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryGT : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryGT(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_GT; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryLE : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryLE(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_LE; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryLT : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryLT(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_LT; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMinus : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMinus(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MINUS; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMod : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMod(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MOD; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryMUL : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryMUL(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_MUL; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryNEQ : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryNEQ(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_NEQ; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinaryOR : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinaryOR(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_OR; }

   private:
    void _checkAndSetTypeOfNode() const;
};
class ExprTreeNodeBinarySubscript : public ExprTreeBinaryNode {
   public:
    ExprTreeNodeBinarySubscript(ExprTreeNode* arg1, ExprTreeNode* arg2)
        : ExprTreeBinaryNode(arg1, arg2) {}
    NodeType identify() const { return OP_SUBSCRIPT; }

   private:
    void _checkAndSetTypeOfNode() const;
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_BINARY_NODE_HPP
