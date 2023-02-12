#include "parser.hpp"

#include <iostream>
#include <string>

#include "GlobalConfig.hpp"
#include "cassert"
#include "lexer.h"
#include "semantic-classes/SCCScope.hpp"
#include "semantic-classes/SCCSymbol.hpp"
#include "semantic-classes/SCCType.hpp"
#include "tokens.h"

static SCCScope* globalScope = new SCCScope();
static SCCScope* currentScope = globalScope;

#ifdef DEBUG
// #define DEBUG_PRINT_FUNC_TRACE_FLG
// #define DEBUG_PRINT_MATCHING
#define PRINT_IF_DEBUG(sth) cout << sth << endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED \
    cout << "[DEBUG] Running " << __func__ << " on line " << __LINE__ << endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

using namespace std;

int main() {
    lookahead = yylex();
#ifdef DEBUG_PRINT_MATCHING
    cout << "[DEBUG] lookahead: ";
    prettyPrint(lookahead);
    cout << endl;
#endif
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

void prettyPrint(int tmp) {
    if (tmp == 0) {
        cout << "Done";
        return;
    }
    if (tmp < 256) {
        cout << (char)tmp;
    } else {
        switch (tmp) {
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
void match(int token_type) {
    if (lookahead == token_type) {
        lookahead = yylex();
#ifdef DEBUG_PRINT_MATCHING
        cout << "[DEBUG] lookahead: ";
        prettyPrint(lookahead);
        cout << endl;
#endif
        // TODO: pass token content back to caller for sematics?
    } else {
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

string matchAndReturn(int token_type) {
    string s = yytext;
    match(token_type);
    return s;
}

void start() {
    PRINT_FUNC_IF_ENABLED;
    translation_unit();
    // expression();
}

// translation-unit -> ε
//                  | global-declaration translation-unit
//                  | function-definition translation-unit
void translation_unit() {
    PRINT_FUNC_IF_ENABLED;
    while (lookahead != Done) {
        assert(currentScope == globalScope);
        // global declaration or function definition
        // take up 'specifier pointer id'

        // Specifier for declaration/func definition
        SCCType::SCCType_Specifier sp = specifier();
        // Indirection for declaration/func definition
        size_t idr = pointers();
        string firstID = matchAndReturn(ID);
        if (lookahead == '(') {
            match();
            if (lookahead == ')') {
                match();
                //! A function with return type sp-idr is declared, save it
                currentScope->addSymbol(
                    SCCSymbol(firstID, SCCType(sp, SCCType::FUNCTION, idr)));
                // This is a global-declaration
                rest_of_global_declarator_list(sp);
            } else {
                // This is a function-definition
                rest_of_function_definition(sp, idr, firstID);
            }
        } else {
            // This is a global-declaration
            if (lookahead == '[') {
                match();
                signed long num = stol(matchAndReturn(NUM));
                match(OP_R_BRACKET);
                if (num <= 0) {
                    //! Cannot declare array with size <= 0
                    cout << "[WARN] Attempting to Define an array with length "
                         << num << " <=0 on Line " << yylineno << endl;
                    num = 0;
                }
                //! 1st item is an array
                currentScope->addSymbol(
                    SCCSymbol(firstID, SCCType(sp, SCCType::ARRAY, idr, num)));
            } else {
                //! 1st item is a scalar
                currentScope->addSymbol(
                    SCCSymbol(firstID, SCCType(sp, SCCType::SCALAR, idr)));
            }
            rest_of_global_declarator_list(sp);
        }
    }
}

// global-declaration -> specifier global-declarator-list ;
// global-declarator-list -> global-declarator
//!                       | global-declarator **, global-declarator-list**

void rest_of_global_declarator_list(
    SCCType::SCCType_Specifier currentSpecifier) {
    PRINT_FUNC_IF_ENABLED;
    while (lookahead == ',') {
        match();
        global_declarator(currentSpecifier);
    }
    match(OP_SC);
}

// global-declarator -> pointers id
//                    | pointers id ( )
//                    | pointers id [ num ]
void global_declarator(SCCType::SCCType_Specifier currentSpecifier) {
    PRINT_FUNC_IF_ENABLED;
    size_t idr = pointers();
    string id = matchAndReturn(ID);
    if (lookahead == '(') {
        //! is FUNC declaration
        match();
        match(OP_R_PARENT);
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(currentSpecifier, SCCType::FUNCTION, idr)));
    } else if (lookahead == '[') {
        //! is ARRAY declaration
        match();
        signed long num = stol(matchAndReturn(NUM));
        match(OP_R_BRACKET);
        if (num <= 0) {
            //! Cannot declare array with size <= 0
            cout << "[WARN] Attempting to Define an array with length " << num
                 << " <=0 on Line " << yylineno << endl;
            num = 0;
        }
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(currentSpecifier, SCCType::ARRAY, idr, num)));
    } else {
        //! is SCALAR declaration
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(currentSpecifier, SCCType::SCALAR, idr)));
    }
}

// pointers -> ε
// | * pointers
size_t pointers() {
    PRINT_FUNC_IF_ENABLED;
    size_t count = 0;
    while (lookahead == '*') {
        match();
        count++;
    }
    return count;
}

// specifier -> int
// | char
// | long
// | void
SCCType::SCCType_Specifier specifier() {
    PRINT_FUNC_IF_ENABLED;
    if (lh_is_specifier()) {
        int tmp = lookahead;
        match();
        switch (tmp) {
            case INT:
                return SCCType::INT;
            case CHAR:
                return SCCType::CHAR;
            case LONG:
                return SCCType::LONG;
            default:
                return SCCType::VOID;
        }
    }
    match(VOID);
    //! would certainly fail, use void cause if user said nothing they probably
    //! meant void
    return SCCType::VOID;  // More or less just to suppress no return warning.
}

/**
 * ! This is NOT part of the syntax tree
 * check to see if lookahead matches one of the specifiers
 */
inline bool lh_is_specifier() {
    PRINT_FUNC_IF_ENABLED;
    return (lookahead == INT) || (lookahead == CHAR) || (lookahead == LONG) ||
           (lookahead == VOID);
}

// function-definition -> specifier pointers id (
//! parameters ) { declarations statements }
void rest_of_function_definition(SCCType::SCCType_Specifier currentSpecifier,
                                 size_t indirection, const string& id) {
    PRINT_FUNC_IF_ENABLED;
    //! Enter function scope
    SCCScope* lastScope = currentScope;  // Save current scope so that I can
                                         // store the func definition
    currentScope = currentScope->createScope();
    std::vector<SCCType>* params = parameters();
    lastScope->addSymbol(SCCSymbol(
        id,
        SCCType(currentSpecifier, SCCType::FUNCTION, indirection, 0, params)));
    match(OP_R_PARENT);
    match(OP_L_BRACE);
    declarations();
    statements();
    match(OP_R_BRACE);
    //! Exit function scope
    currentScope = currentScope->exitScope();
}

// parameters -> void
//      | parameter-list
// parameter-list -> parameter
//      | parameter , parameter-list
std::vector<SCCType>* parameters() {
    PRINT_FUNC_IF_ENABLED;
    std::vector<SCCType>* params = new std::vector<SCCType>();
    // Special case when it start with void
    // since void can be its own thing or as part of a param
    if (lookahead == VOID) {
        match();
        if (lookahead == OP_R_PARENT) {
            // NO param
            return params;
        } else {
            // a param start with void
            // Parameter 0
            size_t idr = pointers();
            string id = matchAndReturn(ID);
            SCCType type = SCCType(SCCType::VOID, SCCType::SCALAR, idr);
            params->push_back(SCCType(type));
            currentScope->addSymbol(SCCSymbol(id, type));
        }
    } else {
        params->push_back(SCCType(parameter()));  // Parameter 0
    }
    while (lookahead == ',') {
        match();
        params->push_back(SCCType(parameter()));
    }
    return params;
}

// parameter -> specifier pointers id
SCCType parameter() {
    PRINT_FUNC_IF_ENABLED;
    SCCType::SCCType_Specifier sp = specifier();
    size_t idr = pointers();
    string id = matchAndReturn(ID);
    SCCType type = SCCType(sp, SCCType::SCALAR, idr);
    currentScope->addSymbol(SCCSymbol(id, type));
    return type;
}

// declarations -> ε
//      | declaration declarations
// declaration -> specifier declarator-list ;
void declarations() {
    PRINT_FUNC_IF_ENABLED;
    //! declarations and statements are competing for tokens, but only
    //! declarations start with specifiers
    while (lh_is_specifier()) {
        SCCType::SCCType_Specifier sp = specifier();
        declarator_list(sp);
        match(OP_SC);
    }
}

// declarator-list -> declarator
//      | declarator , declarator-list
void declarator_list(SCCType::SCCType_Specifier sp) {
    PRINT_FUNC_IF_ENABLED;
    declarator(sp);
    while (lookahead == ',') {
        match();
        declarator(sp);
    }
}

// declarator -> pointers id
//      | pointers id [ num ]
void declarator(SCCType::SCCType_Specifier sp) {
    PRINT_FUNC_IF_ENABLED;
    size_t idr = pointers();
    string id = matchAndReturn(ID);
    if (lookahead == '[') {
        //! array
        match();
        signed long num = stol(matchAndReturn(NUM));
        match(OP_R_BRACKET);
        if (num <= 0) {
            //! Cannot declare array with size <= 0
            cout << "[WARN] Attempting to Define an array with length " << num
                 << " <=0 on Line " << yylineno << endl;
            num = 0;
        }
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(sp, SCCType::ARRAY, idr, num)));
    } else {
        //! scalar
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(sp, SCCType::SCALAR, idr)));
    }
}

// statements -> ε
// | statement statements
void statements() {
    PRINT_FUNC_IF_ENABLED;
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
    PRINT_FUNC_IF_ENABLED;
    if (lookahead == '{') {
        currentScope = currentScope->createScope();
        match();
        declarations();
        statements();
        currentScope = currentScope->exitScope();
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
    PRINT_FUNC_IF_ENABLED;
    expression();
    if (lookahead == '=') {
        match();
        expression();
    }
}

// expression-list -> expression
//                 | expression , expression-list
void expression_list() {
    PRINT_FUNC_IF_ENABLED;
    expression();
    while (lookahead == ',') {
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
void expression() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_1();
}

void expression_level_1() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_2();
    while (lookahead == OP_OR) {
        match();
        expression_level_2();
        // cout << "or" << endl;
    }
}

void expression_level_2() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_3();
    while (lookahead == OP_AND) {
        match();
        expression_level_3();
        // cout << "and" << endl;
    }
}

void expression_level_3() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_4();
    while (lookahead == OP_EQ || lookahead == OP_NE) {
        int tmp = lookahead;
        match();
        expression_level_4();
        switch (tmp) {
            case OP_EQ:
                // cout << "eql" << endl;
                break;

            default:  // OP_NE
                // cout << "neq" << endl;
                break;
        }
    }
}

void expression_level_4() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_5();
    while (lookahead == OP_LT || lookahead == OP_GT || lookahead == OP_LE ||
           lookahead == OP_GE) {
        // int tmp = lookahead;
        match();
        expression_level_5();
        // switch (tmp) {
        //     case OP_LT:
        //         cout << "ltn" << endl;
        //         break;
        //     case OP_GT:
        //         cout << "gtn" << endl;
        //         break;
        //     case OP_LE:
        //         cout << "leq" << endl;
        //         break;

        //     default:  // OP_GE
        //         cout << "geq" << endl;
        //         break;
        // }
    }
}

void expression_level_5() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_6();
    while (lookahead == '+' || lookahead == '-') {
        // int tmp = lookahead;
        match();
        expression_level_6();
        // switch (tmp) {
        //     case '+':
        //         cout << "add" << endl;
        //         break;

        //     default:
        //         cout << "sub" << endl;
        //         break;
        // }
    }
}

void expression_level_6() {
    PRINT_FUNC_IF_ENABLED;
    expression_level_7();
    while (lookahead == '*' || lookahead == '/' || lookahead == '%') {
        // int tmp = lookahead;
        match();
        expression_level_7();
        // switch (tmp) {
        //     case '*':
        //         cout << "mul" << endl;
        //         break;
        //     case '/':
        //         cout << "div" << endl;
        //         break;
        //     default:
        //         cout << "rem" << endl;
        //         break;
        // }
    }
}

void expression_level_7() {
    PRINT_FUNC_IF_ENABLED;
    // int tmp = -1;
    if (lookahead == '&' || lookahead == '*' || lookahead == '!' ||
        lookahead == '-' || lookahead == SIZEOF) {
        // tmp = lookahead;
        match();
        expression_level_7();
    } else {
        expression_level_8();
    }
    // switch (tmp) {
    //     case '&':
    //         cout << "addr" << endl;
    //         break;
    //     case '*':
    //         cout << "deref" << endl;
    //         break;
    //     case '!':
    //         cout << "not" << endl;
    //         break;
    //     case '-':
    //         cout << "neg" << endl;
    //         break;
    //     case SIZEOF:
    //         cout << "sizeof" << endl;
    //         break;
    //     default:
    //         break;
    // }
}

void expression_level_8() {
    PRINT_FUNC_IF_ENABLED;
    expression_term();
    while (lookahead == '[') {
        match();
        expression();
        match(OP_R_BRACKET);
        // cout << "index" << endl;
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
    PRINT_FUNC_IF_ENABLED;
    if (lookahead == ID) {
        string id = matchAndReturn(ID);
        //! currently ignored, just make sure the id is declared
        // TODO: use this
        __attribute__((unused)) const SCCSymbol* ignored =
            currentScope->lookupSymbol(id);
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
