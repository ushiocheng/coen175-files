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
    StmtBlock(SCCScope* scope) : _scope(scope) {
        this->innerStatements = new std::vector<Statement*>();
    }
    ~StmtBlock() {
        for (Statement* stmt : innerStatements) delete stmt;
        delete innerStatements;
    }
    StmtType identify() const { return BLOCK; }
    void performTypeChecking() {
        bool noError = true;
        for (Statement* stmt : innerStatements) {
            if (!stmt->performTypeChecking()) noError = false;
        }
        return noError;
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_STMT_BLOCK_HPP
