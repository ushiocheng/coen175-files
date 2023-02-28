#if !defined(SCC_AST_HPP)
#define SCC_AST_HPP

#include "../semantic-classes/SCCScope.hpp"
#include "SCCASTFunction.hpp"
#include <vector>

class SCCAST {
   public:
    // Global Declaration List
    SCCScope* globalScope;
    // Function Definition List
    std::vector<SCCASTClasses::Function>* functionDefinitions;
    SCCAST();
    ~SCCAST();
};

#endif  // SCC_AST_HPP
