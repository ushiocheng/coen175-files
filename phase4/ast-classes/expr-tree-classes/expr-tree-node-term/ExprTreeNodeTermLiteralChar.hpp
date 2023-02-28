#if !defined(EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralChar : ExprTreeTermNode {
   private:
   public:
    NodeType identify() const { return NodeType::T_LITERAL_CHAR; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP
