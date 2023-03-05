#if !defined(EXPR_TREE_NODE_TERM_FUNC_CALL_HPP)
#define EXPR_TREE_NODE_TERM_FUNC_CALL_HPP

#include <vector>

#include "../../../exceptions/SCCError.hpp"
#include "../../SCCASTExpression.hpp"
#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermFuncCall : ExprTreeTermNode {
   public:
    const SCCSymbol* function;
    std::vector<SCCASTClasses::Expression*>* paramList;
    ExprTreeNodeTermFuncCall(SCCSymbol* func = nullptr) : this->function(func) {
        this->paramList = new std::vector<SCCASTClasses::Expression*>();
    }
    ~ExprTreeNodeTermFuncCall() {
        for (Expression* nodes : paramList) {
            delete nodes;
        }
        delete paramList;
    }
    NodeType identify() const { return NodeType::T_FUNC_CALL; }

   private:
    void _checkAndSetTypeOfNode() const {
        assert(!_typeOfNodeSet);
        assert(this->function);
        //! Evaluate Parameters
        std::vector<SCCType> typeOfParams;
        for (const SCCASTClasses::Expression* expr : *(this->paramList)) {
            // This also performs type checking for expr
            SCCType typeOfParam = expr->getType();
            if (typeOfParam.isError()) {
                //! If any param has error, stop evaluation for this subtree
                const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                    SCCType();
                const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet =
                    true;
                return;
            }
            typeOfParams.push_back(typeOfParam);
        }
        SCCType func = this->function->type();
        //! if func type is error, ignore checks and propergate error state
        if (func.isError()) {
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                SCCType();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
        //! Check func is FUNCTION
        if (!func.isFunc()) {
            throw new SCCError("Phase4: Callee not function.",
                               SCCSemanticError::EXP_NOT_FUNC);
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                SCCType();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
        //! check if func is defined/declared
        if (func.parameters() == nullptr) {
            //! Function is undefined in this scope, skip param checking
            // // return SCCType();
            func.promoteFunc();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
        //! Function is defined at this point
        //! Check parameter count matches
        size_t expectedArgCount = func.parameters()->size();
        size_t actualArgCount = typeOfParams.size();
        if (expectedArgCount != actualArgCount) {
            printAndReport(
                "Phase4: Calling function with mismatched param count.",
                SCCSemanticError::EXP_INV_ARG);
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                SCCType();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
            return;
        }
        //! Check param matches
        if (expectedArgCount > 0) {
            const std::vector<SCCType>* expectedParams = func.parameters();
            for (size_t i = 0; i < expectedParams->size(); i++) {
                if (typeOfParams.at(i).isCompatible(expectedParams->at(i)) &&
                    typeOfParams.at(i).isPredicate())
                    continue;
                // Mis match params
                printAndReport(
                    "Phase4: Calling function with mismatched params.",
                    SCCSemanticError::EXP_INV_ARG);
                const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode =
                    SCCType();
                const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet =
                    true;
                return;
            }
        }
        //! Promote Function to its return value
        func.promoteFunc();
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
        const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet = true;
        return;
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_FUNC_CALL_HPP
