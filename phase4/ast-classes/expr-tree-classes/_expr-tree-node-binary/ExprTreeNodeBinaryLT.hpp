#if !defined(EXPR_TREE_NODE_BINARY_LT_HPP)
#define EXPR_TREE_NODE_BINARY_LT_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryLT : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_LT; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_LT_HPP
