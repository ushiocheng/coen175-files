#if !defined(SCC_AST_EXPRESSION_HPP)
#define SCC_AST_EXPRESSION_HPP

#include "SCCASTStatement.hpp"
#include "expr-tree-classes/ExprTreeNode.hpp"
#include "../semantic-classes/SCCType.hpp"

namespace SCCASTClasses {

class Expression : public Statement {
   private:
   public:
    ExprTreeClasses::ExprTreeNode* exprTreeRoot;

    Expression(SCCScope* enclosingScope,
               ExprTreeClasses::ExprTreeNode* exprTreeRoot)
        : Statement(enclosingScope), exprTreeRoot(exprTreeRoot) {}
    ~Expression() { delete exprTreeRoot; }

    StmtType identify() const { return StmtType::EXPR; }

    bool performTypeChecking() const {
        return exprTreeRoot->performTypeChecking(this);
    }

    SCCType typeOf() const {
        return exprTreeRoot->typeOf(this);
    }
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
