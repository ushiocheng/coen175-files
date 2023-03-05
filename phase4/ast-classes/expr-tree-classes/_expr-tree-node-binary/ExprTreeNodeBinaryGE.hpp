#if !defined(EXPR_TREE_NODE_BINARY_GE_HPP)
#define EXPR_TREE_NODE_BINARY_GE_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryGE : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_GE; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_GE_HPP
