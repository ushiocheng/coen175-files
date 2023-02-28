#if !defined(EXPR_TREE_NODE_HPP)
#define EXPR_TREE_NODE_HPP

#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

class ExprTreeNode {
   public:
    virtual NodeType identify() = 0;
};

}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_HPP
