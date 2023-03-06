/*
 * File:	tokens.h
 *
 * Description:	This file contains the token definitions for use by the
 *		lexical analyzer and parser for Simple C.  Single character
 *		tokens use their ASCII values, so we can refer to them
 *		either as character literals or as symbolic names.
 */

# ifndef TOKENS_H
# define TOKENS_H

enum Token {
    // single character operators
    OP_ASSIGN = '=',
    OP_MINUS = '-',
    OP_LT = '<',
    OP_GT = '>',
    OP_PLUS = '+',
    OP_AST = '*',
    OP_DIV = '/',
    OP_MOD = '%',
    OP_BIN_AND = '&',
    OP_BIN_OR = '|',
    OP_NOT = '!',
    OP_L_PARENT = '(',
    OP_R_PARENT = ')',
    OP_L_BRACKET = '[',
    OP_R_BRACKET = ']',
    OP_L_BRACE = '{',
    OP_R_BRACE = '}',
    OP_SC = ';',
    OP_COL = ':',
    OP_DOT = '.',
    OP_COMMA = ',',

    // keywords
    AUTO = 256, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE,
    ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER,
    RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF,
    UNION, UNSIGNED, VOID, VOLATILE, WHILE,

    // two character operators, ID, num, string, done
    OP_OR, OP_AND,
    OP_EQ, OP_NE,
    OP_LE, OP_GE,
    OP_INC, OP_DEC,
    OP_ARROW,
    STRING,
    CHARACTER,
    ID,
    NUM,
    
    Done = 0
};

#include <iostream>

void prettyPrintToken(Token tmp, std::ostream& out = std::cerr);

# endif /* TOKENS_H */
