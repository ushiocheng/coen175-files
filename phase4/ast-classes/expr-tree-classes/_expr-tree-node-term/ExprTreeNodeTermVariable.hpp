#if !defined(EXPR_TREE_NODE_TERM_VAR_HPP)
#define EXPR_TREE_NODE_TERM_VAR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermVariable : ExprTreeTermNode {
   private:
    SCCSymbol* _symbol;
   public:
    ExprTreeNodeTermVariable(SCCSymbol* symbol) : _symbol(symbol) {}
    NodeType identify() const { return NodeType::T_VAR; }
private:
void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermVariable*>(this)->_typeOfNode = this->_symbol->type();
        const_cast<ExprTreeNodeTermVariable*>(this)->_typeOfNodeSet = true;
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_VAR_HPP
