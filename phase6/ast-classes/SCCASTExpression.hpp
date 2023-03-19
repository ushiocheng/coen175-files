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

    Expression(ExprTreeClasses::ExprTreeNode* exprTreeRoot);
    virtual ~Expression();
    void deleteInnerNode();

    StmtType identify() const;

    bool performTypeChecking() const;

    SCCType getType() const;

    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const;
    void generateCode(std::ostream& out) const;
    SCCData* generateCodeAndReturnValue(std::ostream& out) const;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
