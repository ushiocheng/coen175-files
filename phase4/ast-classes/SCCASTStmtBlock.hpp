#if !defined(SCC_AST_STMT_BLOCK_HPP)
#define SCC_AST_STMT_BLOCK_HPP

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTStatement.hpp"

namespace SCCASTClasses {
class StmtBlock : public Statement {
   private:
    SCCScope* _blockScope;
    std::vector<Statement*> _innerStatements;

   public:
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_STMT_BLOCK_HPP
