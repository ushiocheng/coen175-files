#include "parser.hpp"

#include <iostream>

#include "lexer.h"
#include "tokens.h"

using namespace std;

int main()
{
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

void prettyPrint(int tmp)
{
    if (tmp < 256)
    {
        cout << (char)tmp;
    }
    else
    {
        switch (tmp)
        {
        case AUTO:
            cout << "AUTO";
            break;
        case BREAK:
            cout << "BREAK";
            break;
        case CASE:
            cout << "CASE";
            break;
        case CHAR:
            cout << "CHAR";
            break;
        case CONST:
            cout << "CONST";
            break;
        case CONTINUE:
            cout << "CONTINUE";
            break;
        case DEFAULT:
            cout << "DEFAULT";
            break;
        case DO:
            cout << "DO";
            break;
        case DOUBLE:
            cout << "DOUBLE";
            break;
        case ELSE:
            cout << "ELSE";
            break;
        case ENUM:
            cout << "ENUM";
            break;
        case EXTERN:
            cout << "EXTERN";
            break;
        case FLOAT:
            cout << "FLOAT";
            break;
        case FOR:
            cout << "FOR";
            break;
        case GOTO:
            cout << "GOTO";
            break;
        case IF:
            cout << "IF";
            break;
        case INT:
            cout << "INT";
            break;
        case LONG:
            cout << "LONG";
            break;
        case REGISTER:
            cout << "REGISTER";
            break;
        case RETURN:
            cout << "RETURN";
            break;
        case SHORT:
            cout << "SHORT";
            break;
        case SIGNED:
            cout << "SIGNED";
            break;
        case SIZEOF:
            cout << "SIZEOF";
            break;
        case STATIC:
            cout << "STATIC";
            break;
        case STRUCT:
            cout << "STRUCT";
            break;
        case SWITCH:
            cout << "SWITCH";
            break;
        case TYPEDEF:
            cout << "TYPEDEF";
            break;
        case UNION:
            cout << "UNION";
            break;
        case UNSIGNED:
            cout << "UNSIGNED";
            break;
        case VOID:
            cout << "VOID";
            break;
        case VOLATILE:
            cout << "VOLATILE";
            break;
        case WHILE:
            cout << "WHILE";
            break;
        case OP_OR:
            cout << "OP_OR";
            break;
        case OP_AND:
            cout << "OP_AND";
            break;
        case OP_EQ:
            cout << "OP_EQ";
            break;
        case OP_NE:
            cout << "OP_NE";
            break;
        case OP_LE:
            cout << "OP_LE";
            break;
        case OP_GE:
            cout << "OP_GE";
            break;
        case OP_INC:
            cout << "OP_INC";
            break;
        case OP_DEC:
            cout << "OP_DEC";
            break;
        case OP_ARROW:
            cout << "OP_ARROW";
            break;
        case STRING:
            cout << "STRING";
            break;
        case CHARACTER:
            cout << "CHARACTER";
            break;
        case ID:
            cout << "ID";
            break;
        case NUM:
            cout << "NUM";
            break;
        case Done:
            cout << "Done";
            break;
        default:
            cout << "????";
            break;
        }
    }
}

/**
 * Match token and advance lookahead
 * @param token_type type of token, defined in tokens.h
 * @param caller where in the parse tree is this call from, used to give error
 * message
 * @remark when no argument are given, this simple advances the lookahead
 */
void match(int token_type)
{
    if (lookahead == token_type)
    {
        lookahead = yylex();
        // TODO: pass token content back to caller for sematics?
    }
    else
    {
        // error
        // TODO: fix this
        cout << "[ERROR] Parsing error at line " << yylineno << ", expecting ";
        prettyPrint(token_type);
        cout << " and found ";
        prettyPrint(lookahead);
        cout << endl;
        exit(0);
        // report("[ERROR] Parsing error at line %d, expecting %d and found
        // %d",yylineno(),token_type,lookahead);
    }
}

void start()
{
    // translation_unit();
    // TODO: remove debug stuff
    expression();
}

// translation-unit -> ε
//                  | global-declaration translation-unit
//                  | function-definition translation-unit
void translation_unit()
{
    while (lookahead != Done)
    {
        // global declaration or function definition
        // take up 'specifier pointer id'
        specifier();
        pointers();
        match(ID);
        if (lookahead == '(')
        {
            match();
            if (lookahead == ')')
            {
                match();
                // This is a global-declaration
                rest_of_global_declarator_list();
            }
            else
            {
                // This is a function-definition
                rest_of_function_definition();
            }
        }
        else
        {
            // This is a global-declaration
            if (lookahead == '[')
            {
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

void rest_of_global_declarator_list()
{
    while (lookahead == ',')
    {
        match();
        global_declarator();
    }
    match(OP_SC);
}

// global-declarator -> pointers id
//                    | pointers id ( )
//                    | pointers id [ num ]
void global_declarator()
{
    pointers();
    match(ID);
    if (lookahead == '(')
    {
        match();
        match(OP_R_PARENT);
    }
    else if (lookahead == '[')
    {
        match();
        match(NUM);
        match(OP_R_BRACKET);
    }
}

// pointers -> ε
// | * pointers
void pointers()
{
    while (lookahead == '*')
    {
        match();
    }
}

// specifier -> int
// | char
// | long
// | void
void specifier()
{
    if (lh_is_specifier())
    {
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
inline bool lh_is_specifier()
{
    return (lookahead == INT) || (lookahead == CHAR) || (lookahead == LONG) ||
           (lookahead == VOID);
}

// function-definition -> specifier pointers id (
//! parameters ) { declarations statements }
void rest_of_function_definition()
{
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
void parameters()
{
    if (lookahead == VOID)
    {
        match();
    }
    else
    {
        parameter();
        while (lookahead == ',')
        {
            match();
            parameter();
        }
    }
}

// parameter -> specifier pointers id
void parameter()
{
    specifier();
    pointers();
    match(ID);
}

// declarations -> ε
//      | declaration declarations
// declaration -> specifier declarator-list ;
void declarations()
{
    //! declarations and statements are competing for tokens, but only
    //! declarations start with specifiers
    while (lh_is_specifier())
    {
        specifier();
        declarator_list();
        match(OP_SC);
    }
}

// declarator-list -> declarator
//      | declarator , declarator-list
void declarator_list()
{
    declarator();
    while (lookahead == ',')
    {
        match();
        declarator();
    }
}

// declarator -> pointers id
//      | pointers id [ num ]
void declarator()
{
    pointers();
    match(ID);
    if (lookahead == '[')
    {
        match();
        match(NUM);
        match(OP_R_BRACKET);
    }
}

// statements -> ε
// | statement statements
void statements()
{
    while (lookahead != '}')
    {
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
void statement()
{
    if (lookahead == '{')
    {
        match();
        declarations();
        statements();
        match(OP_R_BRACE);
    }
    else if (lookahead == RETURN)
    {
        match();
        expression();
        match(OP_SC);
    }
    else if (lookahead == WHILE)
    {
        // | while ( expression ) statement
        match();
        match(OP_L_PARENT);
        expression();
        match(OP_R_PARENT);
        statement();
    }
    else if (lookahead == WHILE)
    {
        // | for ( assignment ; expression ; assignment ) statement

        // TODO: continue here
    }
    else if (lookahead == WHILE)
    {
        // | if ( expression ) statement
        // | if ( expression ) statement else statement
    }
    else
    {
        // | assignment ;
    }
}

// assignment -> expression = expression
//            | expression
void assignment()
{
    expression();
    if (lookahead == '=')
    {
        match();
        expression();
    }
}

// expression-list -> expression
//                 | expression , expression-list
void expression_list()
{
    expression();
    while (lookahead == ',')
    {
        match();
        expression();
    }
}

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
void expression()
{
    expression_level_1();
}

void expression_level_1()
{
    expression_level_2();
    while (lookahead == OP_OR)
    {
        match();
        expression_level_2();
        cout << "or" << endl;
    }
}

void expression_level_2()
{
    expression_level_3();
    while (lookahead == OP_AND)
    {
        match();
        expression_level_3();
        cout << "and" << endl;
    }
}

void expression_level_3()
{
    expression_level_4();
    while (lookahead == OP_EQ || lookahead == OP_NE)
    {
        int tmp = lookahead;
        match();
        expression_level_4();
        switch (tmp)
        {
        case OP_EQ:
            cout << "eql" << endl;
            break;

        default: // OP_NE
            cout << "neq" << endl;
            break;
        }
    }
}

void expression_level_4()
{
    expression_level_5();
    while (
        lookahead == OP_LT ||
        lookahead == OP_GT ||
        lookahead == OP_LE ||
        lookahead == OP_GE)
    {
        int tmp = lookahead;
        match();
        expression_level_5();
        switch (tmp)
        {
        case OP_LT:
            cout << "ltn" << endl;
            break;
        case OP_GT:
            cout << "gtn" << endl;
            break;
        case OP_LE:
            cout << "leq" << endl;
            break;

        default: // OP_GE
            cout << "geq" << endl;
            break;
        }
    }
}

void expression_level_5()
{
    expression_level_6();
    while (
        lookahead == '+' ||
        lookahead == '-')
    {
        int tmp = lookahead;
        match();
        expression_level_6();
        switch (tmp)
        {
        case '+':
            cout << "add" << endl;
            break;

        default:
            cout << "sub" << endl;
            break;
        }
    }
}

void expression_level_6()
{
    expression_level_7();
    while (
        lookahead == '*' ||
        lookahead == '/' ||
        lookahead == '%')
    {
        int tmp = lookahead;
        match();
        expression_level_7();
        switch (tmp)
        {
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

void expression_level_7()
{
    int tmp = -1;
    if (
        lookahead == '&' ||
        lookahead == '*' ||
        lookahead == '!' ||
        lookahead == '-' ||
        lookahead == SIZEOF)
    {
        tmp = lookahead;
        match();
        expression_level_7();
    }
    expression_level_8();
    switch (tmp)
    {
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

void expression_level_8()
{
    expression_term();
    while (lookahead == '[')
    {
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
void expression_term()
{
    if (lookahead == ID)
    {
        match();
        if (lookahead == '(')
        {
            match();
            if (lookahead == ')')
            {
                match();
                return;
            }
            expression_list();
            match(OP_R_PARENT);
        }
    }
    else if (lookahead == NUM)
    {
        match();
    }
    else if (lookahead == STRING)
    {
        match();
    }
    else if (lookahead == CHARACTER)
    {
        match();
    }
    else
    { //! MUST be '('
        match(OP_L_PARENT);
        expression();
        match(OP_R_PARENT);
    }
}
