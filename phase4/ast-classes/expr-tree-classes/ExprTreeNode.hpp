#if !defined(EXPR_TREE_NODE_HPP)
#define EXPR_TREE_NODE_HPP

#include "NodeType.hpp"

namespace SCCASTClasses::ExprTreeClasses {

#include "../../semantic-classes/SCCType.hpp"
#include "../SCCASTExpression.hpp"

class ExprTreeNode {
   protected:
    SCCType _typeOfNode;
    bool _typeOfNodeSet = false;

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
    bool performTypeChecking() const {
        return !(this->getType().isError());
    }

    SCCType getType() const {
        if (_typeOfNodeSet) return _typeOfNode;
        this->_checkAndSetTypeOfNode();
        return _typeOfNode;
    }

   private:
    virtual void _checkAndSetTypeOfNode() const = 0;
};

}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_HPP
