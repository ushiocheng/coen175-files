#include "parser.hpp"

#include <iostream>

#include "lexer.h"
#include "tokens.h"

using namespace std;

int lookahead;

int main() {
    lookahead = yylex();
    start();
    // int token;
    // string label;
    // while ((token = yylex()) != 0) {
    // if (AUTO <= token && token <= WHILE)
    //     label = "keyword";
    // else if (token == STRING)
    //     label = "string";
    // else if (token == CHARACTER)
    //     label = "character";
    // else if (token == ID)
    //     label = "identifier";
    // else if (token == NUM)
    //     label = "integer";
    // else
    //     label = "operator";
    // cout << label << " " << yytext << endl;
    // }
}

/**
 * Match token and advance lookahead
 * @param token_type type of token, defined in tokens.h
 * @param caller where in the parse tree is this call from, used to give error
 * message
 * @remark when no argument are given, this simple advances the lookahead
 */
void match(int token_type = lookahead, string caller = "") {
    if (lookahead == token_type) {
        lookahead = yylex();
        // TODO: pass token content back to caller for sematics?
    } else {
        // error
        // TODO: fix this
        cerr << "[ERROR] Parsing error at line " << yylineno() << ", expecting "
             << token_type << " and found " << lookahead << endl;
        // report("[ERROR] Parsing error at line %d, expecting %d and found
        // %d",yylineno(),token_type,lookahead);
    }
}

void start() { translation_unit(); }

// translation-unit -> ε
//                  | global-declaration translation-unit
//                  | function-definition translation-unit
void translation_unit() {
    while (lookahead != Done) {
        // global declaration or function definition
        // take up 'specifier pointer id'
        specifier();
        pointers();
        match(ID);
        if (lookahead == '(') {
            match();
            if (lookahead == ')') {
                match();
                // This is a global-declaration
                rest_of_global_declarator_list();
            } else {
                // This is a function-definition
                rest_of_function_definition();
            }
        } else {
            // This is a global-declaration
            if (lookahead == '[') {
                match();
                match(NUM);
                match(']');
            }
            rest_of_global_declarator_list();
        }
    }
}

// global-declaration -> specifier global-declarator-list ;
// global-declarator-list -> global-declarator
//!                       | global-declarator **, global-declarator-list**

void rest_of_global_declarator_list() {
    while (lookahead == ',') {
        match();
        global_declarator();
    }
    match(';');
}

// global-declarator -> pointers id
//                    | pointers id ( )
//                    | pointers id [ num ]
void global_declarator() {
    pointers();
    match(ID);
    if (lookahead == '(') {
        match();
        match(')');
    } else if (lookahead == '[') {
        match();
        match(NUM);
        match(']');
    }
}

// pointers -> ε
// | * pointers
void pointers() {
    while (lookahead == '*') {
        match();
    }
}

// specifier -> int
// | char
// | long
// | void
void specifier() {
    if (lh_is_specifier()) {
        match();
        return;
    }
    match(VOID);
    //! would certainly fail, use void cause if user said nothing they probably
    //! meant void
}

/**
 * ! This is NOT part of the syntax tree
 * check to see if lookahead matches one of the specifiers
 */
inline bool lh_is_specifier() {
    return (lookahead == INT) || (lookahead == CHAR) || (lookahead == LONG) ||
           (lookahead == VOID);
}

// function-definition -> specifier pointers id (
//! parameters ) { declarations statements }
void rest_of_function_definition() {
    parameters();
    match(')');
    match('{');
    declarations();
    statements();
    match('}');
}

// parameters -> void
//      | parameter-list
// parameter-list -> parameter
//      | parameter , parameter-list
void parameters() {
    if (lookahead == VOID) {
        match();
    } else {
        parameter();
        while (lookahead == ',') {
            match();
            parameter();
        }
    }
}

// parameter -> specifier pointers id
void parameter() {
    specifier();
    pointers();
    match(ID);
}

// declarations -> ε
//      | declaration declarations
// declaration -> specifier declarator-list ;
void declarations() {
    //! declarations and statements are competing for tokens, but only
    //! declarations start with specifiers
    while (lh_is_specifier()) {
        specifier();
        declarator_list();
        match(';')
    }
}

// declarator-list -> declarator
//      | declarator , declarator-list
void declarator_list() {
    declarator();
    while (lookahead == ',') {
        match();
        declarator();
    }
}

// declarator -> pointers id
//      | pointers id [ num ]
void declarator() {
    pointers();
    match(ID);
    if (lookahead == '[') {
        match();
        match(NUM);
        match(']');
    }
}

// statements -> ε
// | statement statements
void statements() {
    while (lookahead != '}') {
        //! Statement cannot start with '}' and must be followed by '}'. So this
        //! determines if there is more statement
        statement();
    }
}

// statement -> { declarations statements }
// | return expression ;
// | while ( expression ) statement
// | for ( assignment ; expression ; assignment ) statement
// | if ( expression ) statement
// | if ( expression ) statement else statement
// | assignment ;
void statement() {
    if (lookahead == '{') {
        match();
        declarations();
        statements();
        match('}');
    } else if (lookahead == RETURN) {
        match();
        expression();
        match(';');
    } else if (lookahead == WHILE) {
        // | while ( expression ) statement
        match();
        match('(');
        expression();
        match(')');
        statement();
    } else if (lookahead == WHILE) {
        // | for ( assignment ; expression ; assignment ) statement
        
        // TODO: continue here
    } else if (lookahead == WHILE) {
        // | if ( expression ) statement
        // | if ( expression ) statement else statement
    } else {
        // | assignment ;
    }
}

// assignment -> expression = expression
// | expression
void assignment() {
    expression();
    if (lookahead == '=') {
        match();
        expression();
    }
}

// expression-list -> expression
// | expression , expression-list

// expression -> expression || expression
// | expression && expression
// | expression == expression
// | expression != expression
// | expression <= expression
// | expression >= expression
// | expression < expression
// | expression > expression
// | expression + expression
// | expression - expression
// | expression * expression
// | expression / expression
// | expression % expression
// | ! expression
// | - expression
// | & expression
// | * expression
// | sizeof expression
// | expression [ expression ]
// | id ( expression-list )
// | id ( )
// | id
// | num
// | string
// | character
// | ( expression )
