#if !defined(EXPR_TREE_NODE_TERM_FUNC_CALL_HPP)
#define EXPR_TREE_NODE_TERM_FUNC_CALL_HPP

#include <string>
#include <vector>

#include "../../../exceptions/SCCError.hpp"
#include "../../SCCASTExpression.hpp"
#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {
class ExprTreeNodeTermFuncCall : ExprTreeTermNode {
   private:
    const std::string& _id;
    std::vector<ExprTreeNode*>* paramList;

   public:
    ExprTreeNodeTermFuncCall(const std::string& id) : _id(id) {
        this->paramList = new std::vector<ExprTreeNode*>();
    }
    ~ExprTreeNodeTermFuncCall() {
        for (ExprTreeNode* nodes : paramList) {
            delete nodes;
        }
        delete paramList;
    }
    NodeType identify() const { return NodeType::T_FUNC_CALL; }
    bool performTypeChecking(SCCASTClasses::Expression* expr) const {
        SCCType func = expr->enclosingScope->lookupSymbol(_id)->type();
        //! Check func is FUNCTION
        if (!func.isFunc()) {
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet =
                true;
            throw new SCCError("Phase4: Callee not function.",
                               SCCSemanticError::EXP_NOT_FUNC);
        }
        //! check if func is defined/declared
        if (func.parameters() == nullptr) {
            //! Function is undefined in this scope, skip param checking
            // // return SCCType();
            func.promoteFunc();
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNode = func;
            const_cast<ExprTreeNodeTermFuncCall*>(this)->_typeOfNodeSet =
                true;
            return true;
        }
        //! Function is defined at this point
        //! Check parameter count matches
        size_t expectedArgCount = func.parameters()->size();
        size_t actualArgCount = (this->paramList) ? this->paramList->size() : 0;
        if (expectedArgCount != actualArgCount) {
            printAndReport(
                "Phase4: Calling function with mismatched param count.",
                SCCSemanticError::EXP_INV_ARG);
            return SCCType();
        }
        //! Check param matches
        if (expectedArgCount > 0) {
            const std::vector<SCCType>* expectedParams = func.parameters();
            for (size_t i = 0; i < expectedParams->size(); i++) {
                if (parameters->at(i).isCompatible(expectedParams->at(i)) &&
                    parameters->at(i).isPredicate())
                    continue;
                // Mis match params
                printAndReport(
                    "Phase4: Calling function with mismatched params.",
                    SCCSemanticError::EXP_INV_ARG);
#ifdef VERBOSE_ERROR_MSG
                PRINT_IF_DEBUG("Func: " << func << "Parameter: " << parameters);
#endif
                return SCCType();
            }
        }
        //! Promote Function to its return value
        func.promoteFunc();
        return func;
    }
};
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_FUNC_CALL_HPP
