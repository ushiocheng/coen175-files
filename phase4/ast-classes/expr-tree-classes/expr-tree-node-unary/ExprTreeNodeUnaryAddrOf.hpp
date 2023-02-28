#if !defined(EXPR_TREE_NODE_UNARY_ADDR_OF_HPP)
#define EXPR_TREE_NODE_UNARY_ADDR_OF_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnaryAddrOf : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_ADDR_OF; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_ADDR_OF_HPP
