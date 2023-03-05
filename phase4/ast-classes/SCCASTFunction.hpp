#if !defined(SCC_AST_FUNCTION_HPP)
#define SCC_AST_FUNCTION_HPP

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTStatement.hpp"
#include "SCCASTStmtBlock.hpp"
namespace SCCASTClasses {

class Function {
   public:
    StmtBlock* innerBlock;

    Function(SCCScope* functionScope);
    ~Function();

    /**
     * Phase 4 - Perform Static Type Checking
     * @return true if no error is generated on type checking
     */
    bool performTypeChecking();
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_FUNCTION_HPP
