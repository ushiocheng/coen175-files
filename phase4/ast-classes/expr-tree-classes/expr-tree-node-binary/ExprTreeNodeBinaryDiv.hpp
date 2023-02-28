#if !defined(EXPR_TREE_NODE_BINARY_DIV_HPP)
#define EXPR_TREE_NODE_BINARY_DIV_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinaryDiv : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_DIV; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_DIV_HPP
