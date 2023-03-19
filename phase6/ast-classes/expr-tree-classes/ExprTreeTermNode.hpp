#if !defined(EXPR_TREE_TERM_NODE_HPP)
#define EXPR_TREE_TERM_NODE_HPP

#include <cassert>
#include <vector>

#include "../../GlobalConfig.hpp"
#include "../SCCASTExpression.hpp"
#include "ExprTreeNode.hpp"
#include "NodeType.hpp"

class SCCSymbol;

namespace SCCASTClasses {
namespace ExprTreeClasses {

class ExprTreeTermNode : public ExprTreeNode {
   protected:
   public:
};

class ExprTreeNodeTermFuncCall : public ExprTreeTermNode {
   public:
    const SCCSymbol* function;
    std::vector<SCCASTClasses::Expression*>* paramList;
    ExprTreeNodeTermFuncCall(const SCCSymbol* func = nullptr);
    ~ExprTreeNodeTermFuncCall();

    NodeType identify() const { return T_FUNC_CALL; }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const;
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const;
};

/**
 * Literal Character
 * Supports single chars and
 * - \0~\255
 * - \t, \n, \\
 * - \x00~\xFF
 */
class ExprTreeNodeTermLiteralChar : public ExprTreeTermNode {
   private:
    char _valueOfLiteral;

   public:
    /**
     * @remark This does not emit error for invalid literals, it uses value[1]
     * or 0
     */
    ExprTreeNodeTermLiteralChar(const std::string& value);
    NodeType identify() const { return T_LITERAL_CHAR; }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const {}
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralChar*>(this)->_typeOfNode =
            SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        const_cast<ExprTreeNodeTermLiteralChar*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermLiteralNumber : public ExprTreeTermNode {
   private:
    long _value;

   public:
    ExprTreeNodeTermLiteralNumber(long value) : _value(value) {
        this->_checkAndSetTypeOfNode();
    }
    NodeType identify() const { return T_LITERAL_NUM; }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const {}
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNode = SCCType(
            (this->_value < INT_MIN || this->_value > INT_MAX) ? SCCType::LONG
                                                               : SCCType::INT,
            SCCType::SCALAR, 0, 0, nullptr, false);
        const_cast<ExprTreeNodeTermLiteralNumber*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermLiteralString : public ExprTreeTermNode {
   private:
    std::string _value;
    std::string _label;

   public:
    ExprTreeNodeTermLiteralString(const std::string& value) {
        this->_value = std::string(value);
    }
    NodeType identify() const { return T_LITERAL_STR; }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const;
    SCCData* generateCode(std::ostream& out) const;

   private:
    void _checkAndSetTypeOfNode() const {
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNode =
            SCCType(SCCType::CHAR, SCCType::ARRAY, 0, this->_value.length() - 2,
                    nullptr, false);
        const_cast<ExprTreeNodeTermLiteralString*>(this)->_typeOfNodeSet = true;
    }
};

class ExprTreeNodeTermVariable : public ExprTreeTermNode {
   private:
    const SCCSymbol* _symbol;

   public:
    ExprTreeNodeTermVariable(const SCCSymbol* symbol) : _symbol(symbol) {}
    NodeType identify() const { return T_VAR; }
    // Code generation Interfaces
    void generateStringLiterals(std::ostream& out) const {}
    SCCData* generateCode(std::ostream& out) const;
    SCCData* generateCode(std::ostream& out, bool retLValue) const;

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
