#if !defined(SCC_AST_HPP)
#define SCC_AST_HPP

#include <vector>

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTFunction.hpp"

class SCCAST {
   public:
    // Global Declaration List
    SCCScope* globalScope;
    // Function Definition List
    std::vector<SCCASTClasses::Function*> functionDefinitions;
    SCCAST();
    ~SCCAST();

    /**
     * Phase 4 - Perform Static Type Checking
     * @return true if no error is generated on type checking
     */
    bool performTypeChecking();
};

#endif  // SCC_AST_HPP
