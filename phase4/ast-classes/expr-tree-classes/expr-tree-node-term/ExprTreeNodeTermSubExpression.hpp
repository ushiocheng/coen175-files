#if !defined(EXPR_TREE_NODE_TERM_SUBEXPR_HPP)
#define EXPR_TREE_NODE_TERM_SUBEXPR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermSubExpr : ExprTreeTermNode {
   private:
   public:
    NodeType identify() const { return NodeType::T_Expr; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_SUBEXPR_HPP
