#if !defined(EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP)
#define EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP

#include "../ExprTreeTermNode.hpp"

namespace SCCASTClasses::ExprTreeClasses {

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
}  // namespace SCCASTClasses::ExprTreeClasses

#endif  // EXPR_TREE_NODE_TERM_LITERAL_CHAR_HPP
