#if !defined(SCC_AST_FUNCTION_HPP)
#define SCC_AST_FUNCTION_HPP

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTStatement.hpp"
#include <vector>
namespace SCCASTClasses {

class Function {
   private:
    SCCScope* _functionScope;
    std::vector<Statement> _statements;
   public:
    
};

}  // namespace SCCASTClasses

#endif  // SCC_AST_FUNCTION_HPP
