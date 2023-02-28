#if !defined(EXPR_TREE_NODE_HPP)
#define EXPR_TREE_NODE_HPP

#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

#include "../../semantic-classes/SCCType.hpp"
#include "../SCCASTExpression.hpp"

class ExprTreeNode {
   protected:
    SCCType _typeOfNode;
    bool _typeOfNodeSet;

   public:
    /**
     * idenitfy API for RTTI
     */
    virtual NodeType identify() const = 0;

    /**
     * Phase 4 - Perform Static Type Checking
     * @remark also set typeOfNode
     * @remark should only be ran once from top down
     * @return true if no error is generated on type checking
     */
    virtual bool performTypeChecking(SCCASTClasses::Expression* expr) const = 0;

    SCCType typeOf(SCCASTClasses::Expression* expr) const {
        if (_typeOfNodeSet) return _typeOfNode;
        this->performTypeChecking(expr);
        return _typeOfNode;
    }
};

}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_HPP
