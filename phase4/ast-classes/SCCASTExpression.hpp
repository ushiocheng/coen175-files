#if !defined(SCC_AST_EXPRESSION_HPP)
#define SCC_AST_EXPRESSION_HPP

#include "SCCASTStatement.hpp"

namespace SCCASTClasses {

class Expression : public Statement {
   private:
   public:
    ExprStmt();
    ~ExprStmt();
    bool performTypeCheck() const {
        return (this->typeOf().declaratorType() != SCCType::ERROR);
    }
    SCCType typeOf() const;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
