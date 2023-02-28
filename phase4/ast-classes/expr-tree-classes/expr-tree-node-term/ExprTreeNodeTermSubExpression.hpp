#if !defined(EXPR_TREE_NODE_TERM_SUBEXPR_HPP)
#define EXPR_TREE_NODE_TERM_SUBEXPR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermSubExpr : ExprTreeTermNode {
   private:
   public:
    NodeType identify() { return NodeType::T_Expr; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_SUBEXPR_HPP
