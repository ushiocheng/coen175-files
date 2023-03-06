#if !defined(SCC_AST_FUNCTION_HPP)
#define SCC_AST_FUNCTION_HPP

#include "SCCASTStmtBlock.hpp"
namespace SCCASTClasses {

class Function {
   public:
    StmtBlock* innerBlock;
    bool haveFunctionCall;

    Function(SCCScope* functionScope);
    ~Function();

    /**
     * Phase 4 - Perform Static Type Checking
     * @return true if no error is generated on type checking
     */
    bool performTypeChecking();

    /**
     * Phase 5 - Generate Code
     * @param out output stream
    */
    void generateCode(std::ostream& out) const;
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_FUNCTION_HPP
