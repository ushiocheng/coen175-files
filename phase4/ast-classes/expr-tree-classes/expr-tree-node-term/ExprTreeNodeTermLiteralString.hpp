#if !defined(EXPR_TREE_NODE_TERM_LITERAL_STR_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_STR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralString : ExprTreeTermNode {
   private:
   public:
    NodeType identify() const { return NodeType::T_LITERAL_STR; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_STR_HPP
