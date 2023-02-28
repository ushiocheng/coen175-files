#if !defined(EXPR_TREE_NODE_BINARY_SUBSCRIPT_HPP)
#define EXPR_TREE_NODE_BINARY_SUBSCRIPT_HPP

#include "../ExprTreeBinaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeBinarySubscript : public ExprTreeBinaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_SUBSCRIPT; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_BINARY_SUBSCRIPT_HPP
