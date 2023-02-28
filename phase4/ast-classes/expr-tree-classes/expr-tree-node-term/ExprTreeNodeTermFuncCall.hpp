#if !defined(EXPR_TREE_NODE_TERM_FUNC_CALL_HPP)
#define EXPR_TREE_NODE_TERM_FUNC_CALL_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermFuncCall : ExprTreeTermNode {
   private:
   public:
    NodeType identify() { return NodeType::T_FUNC_CALL; }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_FUNC_CALL_HPP
