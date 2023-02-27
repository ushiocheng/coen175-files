#if !defined(SCC_AST_EXPRESSION_HPP)
#define SCC_AST_EXPRESSION_HPP

#include "SCCASTStatement.hpp"

namespace SCCASTClasses {

    class Expression : public Statement {
    private:
    public:
        ExprStmt();
        ~ExprStmt();
        bool performTypeCheck() const {
            return (this->typeOf().declaratorType() != SCCType::ERROR);
        }
        SCCType typeOf() const;
    };

    namespace ExprTreeClasses {
        enum NodeType {
            // OP UNARY
            OP_NOT = 0,
            OP_NEGATION,
            OP_ADDR_OF,
            OP_DEREF,
            OP_SIZEOF,
            // OP BINARY
            OP_OR,
            OP_AND,
            OP_EQ,
            OP_NEQ,
            OP_LT,
            OP_GT,
            OP_LE,
            OP_GE,
            OP_ADD,
            OP_MINUS,
            OP_MUL,
            OP_DIV,
            OP_MOD,
            OP_SUBSCRIPT,
            // Term
            T_FUNC_CALL,
            T_VAR,
            T_LITERAL_NUM,
            T_LITERAL_STR,
            T_LITERAL_CHAR,
            T_Expr
        };
        class ExpTreeNode {
        public:
            virtual static NodeType identify() = 0;
        };

        class ExpTreeUnaryNode : public ExpTreeNode {
        protected:
            ExpTreeNode* op1;
        };

        class ExpTreeBinaryNode : public ExpTreeNode {
        protected:
            ExpTreeNode* op1;
            ExpTreeNode* op2;
        };

        class ExpTerm : ExpTreeNode {};
    }
}  // namespace SCCASTClasses

#endif  // SCC_AST_EXPRESSION_HPP
