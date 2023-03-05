#if !defined(EXPR_TREE_NODE_TERM_LITERAL_STR_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_STR_HPP

#include <string>

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermLiteralString : ExprTreeTermNode {
   private:
    std::string _value;

   public:
    ExprTreeNodeTermLiteralString(const std::string& value) : _value(value) {}
    NodeType identify() const { return NodeType::T_LITERAL_STR; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNode =
            SCCType(SCCType::CHAR, SCCType::ARRAY, 0, this->_value.length() - 2,
                    nullptr, false);
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNodeSet = true;
    }
};
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_STR_HPP
