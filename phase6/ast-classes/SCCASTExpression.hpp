#if !defined(SCC_AST_EXPRESSION_HPP)
#define SCC_AST_EXPRESSION_HPP

#include "../semantic-classes/SCCType.hpp"
#include "SCCASTStatement.hpp"
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

    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const {
        exprTreeRoot->generateStringLiterals(out);
    }
    void generateCode(std::ostream& out) const {
        exprTreeRoot->generateCode(out);
    }
    SCCData* generateCodeAndReturnValue(std::ostream& out) const {
        exprTreeRoot->generateCode(out);
    }
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
