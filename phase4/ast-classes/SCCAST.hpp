#if !defined(SCC_AST_HPP)
#define SCC_AST_HPP

#include "SCCASTFunctionDefinitionList.hpp"
#include "SCCASTGlobalDeclarationList.hpp"

class SCCAST {
   public:
    // Global Declaration List
    SCCASTClasses::GDL gdl;
    // Function Definition List
    SCCASTClasses::FDL fdl;
    SCCAST(){};
    ~SCCAST();
};

#endif  // SCC_AST_HPP
