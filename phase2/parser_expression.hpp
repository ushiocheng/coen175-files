#ifndef PARSER_EXPR_HPP
#define PARSER_EXPR_HPP

#include "parser.hpp"

// Function in this file
// void expression();
// void expression_level_1();
// void expression_level_2();
// void expression_level_3();
// void expression_level_4();
// void expression_level_5();
// void expression_level_6();
// void expression_level_7();
// void expression_level_8();
// void expression_term();

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
void expression() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_1();
}

void expression_level_1() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_2();
    while (lookahead == OP_OR) {
        match();
        expression_level_2();
        cout << "or" << endl;
    }
}

void expression_level_2() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_3();
    while (lookahead == OP_AND) {
        match();
        expression_level_3();
        cout << "and" << endl;
    }
}

void expression_level_3() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_4();
    while (lookahead == OP_EQ || lookahead == OP_NE) {
        int tmp = lookahead;
        match();
        expression_level_4();
        switch (tmp) {
            case OP_EQ:
                cout << "eql" << endl;
                break;

            default:  // OP_NE
                cout << "neq" << endl;
                break;
        }
    }
}

void expression_level_4() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_5();
    while (lookahead == OP_LT || lookahead == OP_GT || lookahead == OP_LE ||
           lookahead == OP_GE) {
        int tmp = lookahead;
        match();
        expression_level_5();
        switch (tmp) {
            case OP_LT:
                cout << "ltn" << endl;
                break;
            case OP_GT:
                cout << "gtn" << endl;
                break;
            case OP_LE:
                cout << "leq" << endl;
                break;

            default:  // OP_GE
                cout << "geq" << endl;
                break;
        }
    }
}

void expression_level_5() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_6();
    while (lookahead == '+' || lookahead == '-') {
        int tmp = lookahead;
        match();
        expression_level_6();
        switch (tmp) {
            case '+':
                cout << "add" << endl;
                break;

            default:
                cout << "sub" << endl;
                break;
        }
    }
}

void expression_level_6() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_level_7();
    while (lookahead == '*' || lookahead == '/' || lookahead == '%') {
        int tmp = lookahead;
        match();
        expression_level_7();
        switch (tmp) {
            case '*':
                cout << "mul" << endl;
                break;
            case '/':
                cout << "div" << endl;
                break;
            default:
                cout << "rem" << endl;
                break;
        }
    }
}

void expression_level_7() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    int tmp = -1;
    if (lookahead == '&' || lookahead == '*' || lookahead == '!' ||
        lookahead == '-' || lookahead == SIZEOF) {
        tmp = lookahead;
        match();
        expression_level_7();
    } else {
        expression_level_8();
    }
    switch (tmp) {
        case '&':
            cout << "addr" << endl;
            break;
        case '*':
            cout << "deref" << endl;
            break;
        case '!':
            cout << "not" << endl;
            break;
        case '-':
            cout << "neg" << endl;
            break;
        case SIZEOF:
            cout << "sizeof" << endl;
            break;
        default:
            break;
    }
}

void expression_level_8() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    expression_term();
    while (lookahead == '[') {
        match();
        expression();
        match(OP_R_BRACKET);
        cout << "index" << endl;
    }
}

// | id ( expression-list )
// | id ( )
// | id
// | num
// | string
// | character
// | ( expression )
void expression_term() {
#ifdef DEBUG_PRINT_FUNC_TRACE
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl;
#endif
    if (lookahead == ID) {
        match();
        if (lookahead == '(') {
            match();
            if (lookahead == ')') {
                match();
                return;
            }
            expression_list();
            match(OP_R_PARENT);
        }
    } else if (lookahead == NUM) {
        match();
    } else if (lookahead == STRING) {
        match();
    } else if (lookahead == CHARACTER) {
        match();
    } else {  //! MUST be '('
        match(OP_L_PARENT);
        expression();
        match(OP_R_PARENT);
    }
}

#endif
