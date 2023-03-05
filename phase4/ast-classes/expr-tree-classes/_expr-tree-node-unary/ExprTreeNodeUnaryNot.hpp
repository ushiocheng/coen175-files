#if !defined(EXPR_TREE_NODE_UNARY_NOT_HPP)
#define EXPR_TREE_NODE_UNARY_NOT_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryNot : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_NOT; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_NOT_HPP
