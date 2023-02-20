#include "SCCParser.hpp"

#include <iostream>
#include <string>

#include "GlobalConfig.hpp"
#include "cassert"
#include "lexer.h"
#include "semantic-classes/SCCError.hpp"
#include "semantic-classes/SCCScope.hpp"
#include "semantic-classes/SCCSymbol.hpp"
#include "semantic-classes/SCCType.hpp"
#include "semantic-classes/SCCTypeChecker.hpp"
#include "tokens.h"

static SCCScope *globalScope = new SCCScope();
static SCCScope *currentScope = globalScope;

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
    lookahead = (Token)yylex();
#ifdef DEBUG_PRINT_MATCHING
    cout << "[DEBUG] lookahead: ";
    prettyPrintToken(lookahead);
    cout << endl;
#endif
    start();
    //! Cleanup
    delete globalScope;
}

/**
 * Match token and advance lookahead
 * @param token_type type of token, defined in tokens.h
 * @param caller where in the parse tree is this call from, used to give error
 * message
 * @remark when no argument are given, this simple advances the lookahead
 */
void match(Token token_type) {
    if (lookahead == token_type) {
        lookahead = (Token)yylex();
#ifdef DEBUG_PRINT_MATCHING
        cout << "[DEBUG] lookahead: ";
        prettyPrintToken(lookahead);
        cout << endl;
#endif
    } else {
        // error
        cout << "[ERROR] Parsing error at line " << yylineno << ", expecting ";
        prettyPrintToken(token_type);
        cout << " and found ";
        prettyPrintToken(lookahead);
        cout << endl;
        exit(0);
    }
}

string matchAndReturn(Token token_type) {
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
                                 size_t indirection, const string &id) {
    PRINT_FUNC_IF_ENABLED;
    //! Enter function scope
    SCCScope *lastScope = currentScope;  // Save current scope so that I can
                                         // store the func definition
    currentScope = currentScope->createScope();
    std::vector<SCCType> *params = parameters();
    SCCSymbol *func = new SCCSymbol(
        id,
        SCCType(currentSpecifier, SCCType::FUNCTION, indirection, 0, params));
    lastScope->addSymbol(*func);
    currentScope->setEnclosingFunc(func);
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
std::vector<SCCType> *parameters() {
    PRINT_FUNC_IF_ENABLED;
    std::vector<SCCType> *params = new std::vector<SCCType>();
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
        params->push_back(parameter());  // Parameter 0
    }
    while (lookahead == ',') {
        match();
        params->push_back(parameter());
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
#ifdef VERBOSE_ERROR_MSG
            cout << "[WARN] Attempting to Define an array with length " << num
                 << " <=0 on Line " << yylineno << endl;
#endif
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
        checkReturnType(currentScope, expression());
        match(OP_SC);
    } else if (lookahead == WHILE) {
        // | while ( expression ) statement
        match();
        match(OP_L_PARENT);
        checkTestExpr(expression());
        match(OP_R_PARENT);
        statement();
    } else if (lookahead == FOR) {
        // | for ( assignment ; expression ; assignment ) statement
        match(FOR);
        match(OP_L_PARENT);
        assignment();
        match(OP_SC);
        checkTestExpr(expression());
        match(OP_SC);
        assignment();
        match(OP_R_PARENT);
        statement();
    } else if (lookahead == IF) {
        // | if ( expression ) statement
        // | if ( expression ) statement else statement
        match(IF);
        match(OP_L_PARENT);
        checkTestExpr(expression());
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
    SCCType lhs = expression();
    if (lookahead == '=') {
        match();
        SCCType rhs = expression();
        checkAssign(lhs, rhs);
    }
}

// expression-list -> expression
//                 | expression , expression-list
std::vector<SCCType> *expression_list() {
    PRINT_FUNC_IF_ENABLED;
    std::vector<SCCType> *res = new std::vector<SCCType>();
    res->push_back(expression());
    while (lookahead == ',') {
        match();
        res->push_back(expression());
    }
    return res;
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
SCCType expression() {
    PRINT_FUNC_IF_ENABLED;
    return expression_level_1();
}

SCCType expression_level_1() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_2();
    while (lookahead == OP_OR) {
        match();
        op1 =
            typeOfExpression(SCCTypeChecker::OP_OR, op1, expression_level_2());
    }
    return op1;
}

SCCType expression_level_2() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_3();
    while (lookahead == OP_AND) {
        match();
        op1 =
            typeOfExpression(SCCTypeChecker::OP_AND, op1, expression_level_3());
    }
    return op1;
}

SCCType expression_level_3() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_4();
    while (lookahead == OP_EQ || lookahead == OP_NE) {
        SCCTypeChecker::SCCBinaryOperation op;
        switch (lookahead) {
            case OP_EQ:
                op = SCCTypeChecker::SCCBinaryOperation::OP_EQ;
                break;
            default: /*OP_NE*/
                op = SCCTypeChecker::SCCBinaryOperation::OP_NEQ;
                break;
        }
        match();
        op1 = typeOfExpression(op, op1, expression_level_4());
    }
    return op1;
}

SCCType expression_level_4() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_5();
    while (lookahead == OP_LT || lookahead == OP_GT || lookahead == OP_LE ||
           lookahead == OP_GE) {
        SCCTypeChecker::SCCBinaryOperation op;
        switch (lookahead) {
            case OP_LT:
                op = SCCTypeChecker::SCCBinaryOperation::OP_LT;
                break;
            case OP_GT:
                op = SCCTypeChecker::SCCBinaryOperation::OP_GT;
                break;
            case OP_LE:
                op = SCCTypeChecker::SCCBinaryOperation::OP_LE;
                break;
            default: /*OP_GE*/
                op = SCCTypeChecker::SCCBinaryOperation::OP_GE;
                break;
        }
        match();
        op1 = typeOfExpression(op, op1, expression_level_5());
    }
    return op1;
}

SCCType expression_level_5() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_6();
    while (lookahead == '+' || lookahead == '-') {
        SCCTypeChecker::SCCBinaryOperation op;
        if (lookahead == '+')
            op = SCCTypeChecker::SCCBinaryOperation::OP_ADD;
        else
            op = SCCTypeChecker::SCCBinaryOperation::OP_MINUS;
        match();
        op1 = typeOfExpression(op, op1, expression_level_6());
    }
    return op1;
}

SCCType expression_level_6() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_level_7();
    while (lookahead == '*' || lookahead == '/' || lookahead == '%') {
        SCCTypeChecker::SCCBinaryOperation op;
        switch (lookahead) {
            case '*':
                op = SCCTypeChecker::SCCBinaryOperation::OP_MUL;
                break;
            case '/':
                op = SCCTypeChecker::SCCBinaryOperation::OP_DIV;
                break;
            default:
                op = SCCTypeChecker::SCCBinaryOperation::OP_MOD;
                break;
        }
        match();
        op1 = typeOfExpression(op, op1, expression_level_7());
    }
    return op1;
}

SCCType expression_level_7() {
    PRINT_FUNC_IF_ENABLED;
    SCCTypeChecker::SCCUnaryOperation op;
    switch (lookahead) {
        case '&':
            op = SCCTypeChecker::SCCUnaryOperation::OP_ADDR_OF;
            break;
        case '*':
            op = SCCTypeChecker::SCCUnaryOperation::OP_DEREF;
            break;
        case '!':
            op = SCCTypeChecker::SCCUnaryOperation::OP_NOT;
            break;
        case '-':
            op = SCCTypeChecker::SCCUnaryOperation::OP_NEGATION;
            break;
        case SIZEOF:
            op = SCCTypeChecker::SCCUnaryOperation::OP_SIZEOF;
            break;
        default:
            return expression_level_8();
    }
    match();
    return typeOfExpression(op, expression_level_7());
}

SCCType expression_level_8() {
    PRINT_FUNC_IF_ENABLED;
    SCCType op1 = expression_term();
    while (lookahead == '[') {
        match();
        op1 = typeOfExpression(SCCTypeChecker::SCCBinaryOperation::OP_SUBSCRIPT,
                               op1, expression());
        match(OP_R_BRACKET);
    }
    return op1;
}

// | id ( expression-list )
// | id ( )
// | id
// | num
// | string
// | character
// | ( expression )
SCCType expression_term() {
    PRINT_FUNC_IF_ENABLED;
    if (lookahead == ID) {
        string id = matchAndReturn(ID);
        const SCCSymbol *idSymbol = currentScope->lookupSymbol(id);
        if (lookahead == '(') {
            match();
            if (lookahead == ')') {
                // id()
                match();
                return typeOfExpression(SCCType(idSymbol->type()));
            }
            std::vector<SCCType> *parameters = expression_list();
            // id(expr-list)
            match(OP_R_PARENT);
            SCCType returnType =
                typeOfExpression(SCCType(idSymbol->type()), parameters);
            delete parameters;
            return returnType;
        } else {
            // id
            return idSymbol->type();
        }
    } else if (lookahead == NUM) {
        //! Number literal, can be int or long
        signed long numVal = stol(matchAndReturn(NUM));
        if (numVal < INT_MAX && numVal > INT_MIN) {
            return SCCType(SCCType::INT, SCCType::SCALAR, 0, 0, nullptr, false);
        }
        return SCCType(SCCType::LONG, SCCType::SCALAR, 0, 0, nullptr, false);
    } else if (lookahead == STRING) {
        //! String literal value, unused for now
        //! will be converted to a `const static char array`
        __attribute__((unused)) string strVal = matchAndReturn(STRING);
        // This returns stuff like "str", thus strVal.length()-2
        return SCCType(SCCType::CHAR, SCCType::ARRAY, 0, strVal.length() - 2,
                       nullptr, false);
    } else if (lookahead == CHARACTER) {
        //! Character literal value
        __attribute__((unused)) string charStr = matchAndReturn(CHARACTER);
        // char charVal;
        // assert(charStr.at(0) == '\'');
        // size_t charStrLen = charStr.length();
        // assert(charStrLen == 3 || charStrLen == 4);
        // if (charStrLen == 3) {
        //     charVal = charStr.at(1);
        // } else {
        //     charVal = charStr.at(2);
        // }
        return SCCType(SCCType::CHAR, SCCType::SCALAR, 0, 0, nullptr, false);
    } else {  //! MUST be '('
        match(OP_L_PARENT);
        SCCType subExprType = expression();
        match(OP_R_PARENT);
        return subExprType;
    }
}
