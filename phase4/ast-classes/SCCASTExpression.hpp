#if !defined(SCC_AST_EXPRESSION_HPP)
#define SCC_AST_EXPRESSION_HPP

#include "SCCASTStatement.hpp"
#include "../semantic-classes/SCCType.hpp"
#include "expr-tree-classes/ExprTreeNode.hpp"

namespace SCCASTClasses {

class Expression : public Statement {
   private:
   public:
    ExprTreeClasses::ExprTreeNode* exprTreeRoot;

    Expression(ExprTreeClasses::ExprTreeNode* exprTreeRoot)
        : exprTreeRoot(exprTreeRoot) {}
    ~Expression() { delete exprTreeRoot; }

    StmtType identify() const { return StmtType::EXPR; }

    bool performTypeChecking() const {
        return exprTreeRoot->performTypeChecking();
    }

    SCCType getType() const { return exprTreeRoot->getType(); }
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
