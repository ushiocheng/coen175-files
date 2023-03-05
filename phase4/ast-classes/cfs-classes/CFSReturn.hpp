#if !defined(SCC_AST_CFS_RETURN_HPP)
#define SCC_AST_CFS_RETURN_HPP

#include "../SCCASTControlFlowStatement.hpp"
#include "../SCCASTExpression.hpp"
#include "../SCCASTStatement.hpp"
#include "../SCCASTStmtBlock.hpp"

namespace SCCASTClasses {
class CFSReturn : public CtrFlowStmt {
   public:
    Expression* expr1;
    StmtBlock* enclosingBlock;

    // return expr1
    CFSReturn(Expression* expr1, StmtBlock* enclosingBlock)
        : expr1(expr1), enclosingBlock(enclosingBlock) {}
    StmtType identify() const { return StmtType::RETURN; }
    
    bool performTypeChecking() const {
        SCCType returnType = expr1->getType();
        //! if expr have error type, skip check
        if (returnType.isError()) return false;
        //! get expected return type
        const SCCSymbol* enclosingFunc =
            this->enclosingBlock->scope()->getEnclosingFunc();
        assert(enclosingFunc);
        //! Check compatible
        SCCType expectedReturnType(enclosingFunc->type());
        //! If expected return type are error, skip check
        if (expectedReturnType.declaratorType() == SCCType::ERROR) return false;
        expectedReturnType.promoteFunc();
        if (!returnType.isCompatible(expectedReturnType)) {
            return false;
        }
        return true;
    }
};
}  // namespace SCCASTClasses

#endif  // SCC_AST_CFS_RETURN_HPP
