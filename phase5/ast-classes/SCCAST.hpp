#if !defined(SCC_AST_HPP)
#define SCC_AST_HPP

#include <vector>
#include <ostream>

#include "../semantic-classes/SCCScope.hpp"

namespace SCCASTClasses {
    class Function;
}

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

    /**
     * Phase 5 - Generate Code
     * @param out output stream
    */
    void generateCode(std::ostream& out) const;
};

#endif  // SCC_AST_HPP
