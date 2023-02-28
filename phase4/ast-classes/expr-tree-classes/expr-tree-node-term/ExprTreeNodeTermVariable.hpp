#if !defined(EXPR_TREE_NODE_TERM_VAR_HPP)
#define EXPR_TREE_NODE_TERM_VAR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermVariable : ExprTreeTermNode {
   private:
   public:
    NodeType identify() { return NodeType::T_VAR; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_VAR_HPP
