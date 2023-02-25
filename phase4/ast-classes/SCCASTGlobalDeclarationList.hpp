#if !defined(SCC_AST_GLOBAL_DECLARATION_LIST_HPP)
#define SCC_AST_GLOBAL_DECLARATION_LIST_HPP

#include "../semantic-classes/SCCScope.hpp"

namespace SCCASTClasses {

/**
 * Global Declaration List
 */
typedef struct _GDL {
    SCCScope globalScope;
} GDL;
}  // namespace SCCASTClasses

#endif  // SCC_AST_GLOBAL_DECLARATION_LIST_HPP
