#if !defined(EXPR_TREE_NODE_HPP)
#define EXPR_TREE_NODE_HPP

#include "../../semantic-classes/SCCType.hpp"
#include "NodeType.hpp"
namespace SCCASTClasses {
namespace ExprTreeClasses {

class ExprTreeNode {
   protected:
    SCCType _typeOfNode;
    bool _typeOfNodeSet;
    void _setNodeType(SCCType type) const {
        const_cast<ExprTreeNode*>(this)->_typeOfNode = type;
        const_cast<ExprTreeNode*>(this)->_typeOfNodeSet = true;
    }

   public:
    ExprTreeNode() { this->_typeOfNodeSet = false; }
    virtual ~ExprTreeNode(){};

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
    bool performTypeChecking() const { return !(this->getType().isError()); }

    SCCType getType() const {
        if (_typeOfNodeSet) return _typeOfNode;
        this->_checkAndSetTypeOfNode();
        return _typeOfNode;
    }

   private:
    virtual void _checkAndSetTypeOfNode() const {};
};

};  // namespace ExprTreeClasses
};  // namespace SCCASTClasses

#endif  // EXPR_TREE_NODE_HPP
