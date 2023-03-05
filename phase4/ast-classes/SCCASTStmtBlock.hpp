#if !defined(SCC_AST_STMT_BLOCK_HPP)
#define SCC_AST_STMT_BLOCK_HPP

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTStatement.hpp"

namespace SCCASTClasses {
class StmtBlock : public Statement {
   private:
    SCCScope* _scope;

   public:
    std::vector<Statement*>* innerStatements;
    StmtBlock(SCCScope* scope);
    ~StmtBlock();
    const SCCScope* scope() const;
    StmtType identify() const;
    bool performTypeChecking() const;
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_STMT_BLOCK_HPP
