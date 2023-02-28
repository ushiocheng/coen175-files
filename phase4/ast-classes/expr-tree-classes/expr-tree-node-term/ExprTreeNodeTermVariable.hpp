#if !defined(EXPR_TREE_NODE_TERM_VAR_HPP)
#define EXPR_TREE_NODE_TERM_VAR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermVariable : ExprTreeTermNode {
   private:
   public:
    NodeType identify() const { return NodeType::T_VAR; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_VAR_HPP
