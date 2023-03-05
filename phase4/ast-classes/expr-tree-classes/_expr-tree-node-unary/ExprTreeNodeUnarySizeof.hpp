#if !defined(EXPR_TREE_NODE_UNARY_SIZEOF_HPP)
#define EXPR_TREE_NODE_UNARY_SIZEOF_HPP

#include "../ExprTreeUnaryNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeUnarySizeof : public ExprTreeUnaryNode {
   private:
   public:
    NodeType identify() const { return NodeType::OP_SIZEOF; }
   private:
    void _checkAndSetTypeOfNode() const {
        // TODO
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_UNARY_SIZEOF_HPP