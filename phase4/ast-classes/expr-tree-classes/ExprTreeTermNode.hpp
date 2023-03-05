#if !defined(EXPR_TREE_TERM_NODE_HPP)
#define EXPR_TREE_TERM_NODE_HPP

#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

namespace SCCASTClasses {
namespace ExprTreeClasses {

class ExprTreeTermNode : public ExprTreeNode {
   protected:
   public:
};

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

/**
 * Literal Character
 * Supports single chars and
 * - \0~\255
 * - \t, \n, \\
 * - \x00~\xFF
 */
class ExprTreeNodeTermLiteralChar : ExprTreeTermNode {
   private:
    char _valueOfLiteral;

   public:
    /**
     * @remark This does not emit error for invalid literals, it uses value[1]
     * or 0
     */
    ExprTreeNodeTermLiteralChar(const std::string& value) {
        if (value.length() < 3) {
            // Invalid literal
            this->_valueOfLiteral = 0;
        } else if (value.at(1) == '\\') {
            //! literal with escape chars
            if ((value.at(2) >= '0') && (value.at(2) <= '9')) {
                unsigned char d1 = value.at(2) - '0';
                unsigned char d2 = value.at(3) - '0';
                unsigned char d3 =
                    (value.length() >= 5) ? value.at(4) - '0' : 10;
                this->_valueOfLiteral = 0;
                // next char is num, i.e. '\0'
                if (d2 < 10) {
                    if (d3 < 10) {
                        // 3 digit
                        this->_valueOfLiteral += d3 * 100;
                        this->_valueOfLiteral += d2 * 10;
                        this->_valueOfLiteral += d1;
                    } else {
                        // 2 digit
                        this->_valueOfLiteral += d2 * 10;
                        this->_valueOfLiteral += d1;
                    }
                } else {
                    // 1 digit
                    this->_valueOfLiteral += d1;
                }
            } else if (value.at(2) == 't') {
                this->_valueOfLiteral = '\t';
            } else if (value.at(2) == 'n') {
                this->_valueOfLiteral = '\n';
            } else if (value.at(2) == '\\') {
                this->_valueOfLiteral = '\\';
            } else {
                this->_valueOfLiteral = 0;
            }
        } else {
            //! simple literals
            // ex. 'a'
            this->_valueOfLiteral = value.at(1);
        }
    }
    NodeType identify() const { return NodeType::T_LITERAL_CHAR; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralChar*>(this)->_typeOfNode =
            SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        const_cast<ExprTreeNodeTermLiteralChar*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermLiteralNumber : ExprTreeTermNode {
   private:
    long _value;

   public:
    ExprTreeNodeTermLiteralNumber(long value) : _value(value) {
        this->_checkAndSetTypeOfNode();
    }
    NodeType identify() const { return NodeType::T_LITERAL_NUM; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNode = SCCType(
            (this->_value < INT_MIN || this->_value > INT_MAX) ? SCCType::LONG
                                                               : SCCType::INT,
            SCCType::SCALAR, 0, 0, nullptr, false);
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermLiteralString : ExprTreeTermNode {
   private:
    std::string _value;

   public:
    ExprTreeNodeTermLiteralString(const std::string& value) : _value(value) {}
    NodeType identify() const { return NodeType::T_LITERAL_STR; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNode =
            SCCType(SCCType::CHAR, SCCType::ARRAY, 0, this->_value.length() - 2,
                    nullptr, false);
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermVariable : ExprTreeTermNode {
   private:
    SCCSymbol* _symbol;

   public:
    ExprTreeNodeTermVariable(SCCSymbol* symbol) : _symbol(symbol) {}
    NodeType identify() const { return NodeType::T_VAR; }

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermVariable*>(this)->_typeOfNode =
            this->_symbol->type();
        const_cast<ExprTreeNodeTermVariable*>(this)->_typeOfNodeSet = true;
    }
};

}  // namespace ExprTreeClasses
}  // namespace SCCASTClasses

#endif  // EXPR_TREE_TERM_NODE_HPP
