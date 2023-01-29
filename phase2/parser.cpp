#include "parser.hpp"

#include <iostream>

#include "lexer.h"
#include "tokens.h"

using namespace std;

#include "parser_expression.hpp"
#include "parser_util_funcs.hpp"

int main() {
    lookahead = yylex();
#ifdef DEBUG_PRINT_MATCHING
    cout << "[DEBUG] lookahead: ";
    prettyPrint(lookahead);
    cout << endl;
#endif
    start();
}

void start() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    translation_unit();
    // expression();
}

// translation-unit -> ε
//                  | global-declaration translation-unit
//                  | function-definition translation-unit
void translation_unit() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
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
                match(OP_R_BRACKET);
            }
            rest_of_global_declarator_list();
        }
    }
}

// global-declaration -> specifier global-declarator-list ;
// global-declarator-list -> global-declarator
//!                       | global-declarator **, global-declarator-list**

void rest_of_global_declarator_list() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    while (lookahead == ',') {
        match();
        global_declarator();
    }
    match(OP_SC);
}

// global-declarator -> pointers id
//                    | pointers id ( )
//                    | pointers id [ num ]
void global_declarator() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    pointers();
    match(ID);
    if (lookahead == '(') {
        match();
        match(OP_R_PARENT);
    } else if (lookahead == '[') {
        match();
        match(NUM);
        match(OP_R_BRACKET);
    }
}

// pointers -> ε
// | * pointers
void pointers() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    while (lookahead == '*') {
        match();
    }
}

// specifier -> int
// | char
// | long
// | void
void specifier() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
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
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    return (lookahead == INT) || (lookahead == CHAR) || (lookahead == LONG) ||
           (lookahead == VOID);
}

// function-definition -> specifier pointers id (
//! parameters ) { declarations statements }
void rest_of_function_definition() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    parameters();
    match(OP_R_PARENT);
    match(OP_L_BRACE);
    declarations();
    statements();
    match(OP_R_BRACE);
}

// parameters -> void
//      | parameter-list
// parameter-list -> parameter
//      | parameter , parameter-list
void parameters() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
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
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    specifier();
    pointers();
    match(ID);
}

// declarations -> ε
//      | declaration declarations
// declaration -> specifier declarator-list ;
void declarations() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    //! declarations and statements are competing for tokens, but only
    //! declarations start with specifiers
    while (lh_is_specifier()) {
        specifier();
        declarator_list();
        match(OP_SC);
    }
}

// declarator-list -> declarator
//      | declarator , declarator-list
void declarator_list() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    declarator();
    while (lookahead == ',') {
        match();
        declarator();
    }
}

// declarator -> pointers id
//      | pointers id [ num ]
void declarator() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    pointers();
    match(ID);
    if (lookahead == '[') {
        match();
        match(NUM);
        match(OP_R_BRACKET);
    }
}

// statements -> ε
// | statement statements
void statements() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
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
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    if (lookahead == '{') {
        match();
        declarations();
        statements();
        match(OP_R_BRACE);
    } else if (lookahead == RETURN) {
        match();
        expression();
        match(OP_SC);
    } else if (lookahead == WHILE) {
        // | while ( expression ) statement
        match();
        match(OP_L_PARENT);
        expression();
        match(OP_R_PARENT);
        statement();
    } else if (lookahead == FOR) {
        // | for ( assignment ; expression ; assignment ) statement
        match(FOR);
        match(OP_L_PARENT);
        assignment();
        match(OP_SC);
        expression();
        match(OP_SC);
        assignment();
        match(OP_R_PARENT);
        statement();
    } else if (lookahead == IF) {
        // | if ( expression ) statement
        // | if ( expression ) statement else statement
        match(IF);
        match(OP_L_PARENT);
        expression();
        match(OP_R_PARENT);
        statement();
        if (lookahead == ELSE) {
            match();
            statement();
        }
    } else {
        // | assignment ;
        assignment();
        match(OP_SC);
    }
}

// assignment -> expression = expression
//            | expression
void assignment() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression();
    if (lookahead == '=') {
        match();
        expression();
    }
}

// expression-list -> expression
//                 | expression , expression-list
void expression_list() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression();
    while (lookahead == ',') {
        match();
        expression();
    }
}
