#if !defined(SCC_AST_ASSIGN_HPP)
#define SCC_AST_ASSIGN_HPP

#include "SCCASTExpression.hpp"
#include "SCCASTStatement.hpp"
#include "expr-tree-classes/ExprTreeNode.hpp"

namespace SCCASTClasses {

class Assignment : public Statement {
   private:
   public:
    ExprTreeClasses::ExprTreeNode* lhs;
    ExprTreeClasses::ExprTreeNode* rhs;

    Assignment(ExprTreeClasses::ExprTreeNode* lhs, ExprTreeClasses::ExprTreeNode* rhs);
    ~Assignment();

    StmtType identify() const { return StmtType::ASSIGN; }
    bool performTypeChecking() const;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_ASSIGN_HPP
