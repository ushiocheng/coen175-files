#if !defined(EXPR_TREE_NODE_UNARY_NEGATION_HPP)
#define EXPR_TREE_NODE_UNARY_NEGATION_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryNegation : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_NEGATION; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_NEGATION_HPP
