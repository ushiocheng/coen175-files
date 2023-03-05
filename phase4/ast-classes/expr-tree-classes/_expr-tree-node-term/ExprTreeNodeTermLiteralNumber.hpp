#if !defined(EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralNumber : ExprTreeTermNode {
   private:
    long _value;

   public:
    ExprTreeNodeTermLiteralNumber(long value) : _value(value) {
        this->_checkAndSetTypeOfNode();
    }
    NodeType identify() const { return NodeType::T_LITERAL_NUM; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNode = SCCType(
            (this->_value < INT_MIN || this->_value > INT_MAX) ? SCCType::LONG
                                                               : SCCType::INT,
            SCCType::SCALAR, 0, 0, nullptr, false);
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNodeSet = true;
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_NUM_HPP
