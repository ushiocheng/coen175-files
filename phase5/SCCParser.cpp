#include "SCCParser.hpp"

#include <iostream>
#include <string>

#include "GlobalConfig.hpp"
#include "ast-classes/SCCAST.hpp"
#include "ast-classes/SCCASTAssign.hpp"
#include "ast-classes/SCCASTExpression.hpp"
#include "ast-classes/SCCASTFunction.hpp"
#include "ast-classes/SCCASTStatement.hpp"
#include "ast-classes/SCCASTStmtBlock.hpp"
#include "ast-classes/cfs-classes/CFSFor.hpp"
#include "ast-classes/cfs-classes/CFSIf.hpp"
#include "ast-classes/cfs-classes/CFSReturn.hpp"
#include "ast-classes/cfs-classes/CFSWhile.hpp"
#include "ast-classes/expr-tree-classes/ExprTreeBinaryNode.hpp"
#include "ast-classes/expr-tree-classes/ExprTreeTermNode.hpp"
#include "ast-classes/expr-tree-classes/ExprTreeUnaryNode.hpp"
#include "exceptions/SCCError.hpp"
#include "lexer.h"
#include "semantic-classes/SCCScope.hpp"
#include "semantic-classes/SCCSymbol.hpp"
#include "semantic-classes/SCCType.hpp"
#include "semantic-classes/SCCTypeChecker.hpp"
#include "tokens.h"

static SCCAST *astRoot = new SCCAST();
static SCCScope *globalScope = new SCCScope();
static SCCScope *currentScope = globalScope;
static SCCASTClasses::StmtBlock *currentBlock = NULL;

#ifdef DEBUG
// #define DEBUG_PRINT_FUNC_TRACE_FLG
// #define DEBUG_PRINT_MATCHING
// #define DUMP_SYMBOL_TABLE
#define PRINT_IF_DEBUG(sth) cerr << sth << endl;
#else
#define PRINT_IF_DEBUG(sth) /* debug print: sth */
#endif

#ifdef DEBUG_PRINT_FUNC_TRACE_FLG
#define PRINT_FUNC_IF_ENABLED                                         \
    cerr << "[DEBUG] Running " << __func__ << " on line " << __LINE__ \
         << " on source line " << yylineno << endl
#else
#define PRINT_FUNC_IF_ENABLED ;
#endif

using namespace std;

int main() {
    astRoot->globalScope = globalScope;
    lookahead = (Token)yylex();
#ifdef DEBUG_PRINT_MATCHING
    cerr << "[DEBUG] lookahead: ";
    prettyPrintToken(lookahead);
    cerr << endl;
#endif
    start();
    bool typeCheckingPass = astRoot->performTypeChecking();
    assert (typeCheckingPass ); // Change this to if
    astRoot->generateCode(cout);
    //! Cleanup
    //! DEBUG - Dump global scope
#ifdef DUMP_SYMBOL_TABLE
    globalScope->_dump();
#endif
    delete astRoot;
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
        cerr << "[DEBUG] lookahead: ";
        prettyPrintToken(lookahead);
        cerr << endl;
#endif
    } else {
        // error
        cerr << "[ERROR] Parsing error at line " << yylineno << ", expecting ";
        prettyPrintToken(token_type);
        cerr << " and found ";
        prettyPrintToken(lookahead);
        cerr << endl;
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
                currentScope->addSymbol(SCCSymbol(
                    firstID,
                    SCCType(sp, SCCType::FUNCTION, idr, 0, NULL, false)));
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
                    cerr << "[WARN] Attempting to Define an array with length "
                         << num << " <=0 on Line " << yylineno << endl;
                    num = 0;
                }
                //! 1st item is an array
                currentScope->addSymbol(SCCSymbol(
                    firstID,
                    SCCType(sp, SCCType::ARRAY, idr, num, NULL, false)));
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
            SCCSymbol(id, SCCType(currentSpecifier, SCCType::FUNCTION, idr, 0,
                                  NULL, false)));
    } else if (lookahead == '[') {
        //! is ARRAY declaration
        match();
        signed long num = stol(matchAndReturn(NUM));
        match(OP_R_BRACKET);
        if (num <= 0) {
            //! Cannot declare array with size <= 0
            cerr << "[WARN] Attempting to Define an array with length " << num
                 << " <=0 on Line " << yylineno << endl;
            num = 0;
        }
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(currentSpecifier, SCCType::ARRAY, idr, num,
                                  NULL, false)));
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
    SCCSymbol *func =
        new SCCSymbol(id, SCCType(currentSpecifier, SCCType::FUNCTION,
                                  indirection, 0, params, false));
    lastScope->addSymbol(*func);
    SCCASTClasses::Function *currentFunc =
        new SCCASTClasses::Function(currentScope);
    astRoot->functionDefinitions.push_back(currentFunc);
    currentBlock = currentFunc->innerBlock;
    currentScope->setEnclosingFunc(func);
    match(OP_R_PARENT);
    match(OP_L_BRACE);
    declarations();
    statements();
    match(OP_R_BRACE);
    //! Exit function scope
    currentScope = currentScope->exitScope();
    currentBlock = NULL;
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
            SCCType type =
                SCCType(SCCType::VOID, SCCType::SCALAR, idr, 0, NULL, true);
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
    SCCType type = SCCType(sp, SCCType::SCALAR, idr, 0, NULL, true);
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
            cerr << "[WARN] Attempting to Define an array with length " << num
                 << " <=0 on Line " << yylineno << endl;
#endif
            num = 0;
        }
        currentScope->addSymbol(SCCSymbol(
            id, SCCType(sp, SCCType::ARRAY, idr, num, NULL, false)));
    } else {
        //! scalar
        currentScope->addSymbol(
            SCCSymbol(id, SCCType(sp, SCCType::SCALAR, idr, 0, NULL, true)));
    }
}

// statements -> ε
// | statement statements
void statements() {
    PRINT_FUNC_IF_ENABLED;
    while (lookahead != '}') {
        //! Statement cannot start with '}' and must be followed by '}'. So this
        //! determines if there is more statement
        currentBlock->innerStatements->push_back(statement());
    }
}

// statement -> { declarations statements }
// | return expression ;
// | while ( expression ) statement
// | for ( assignment ; expression ; assignment ) statement
// | if ( expression ) statement
// | if ( expression ) statement else statement
// | assignment ;
SCCASTClasses::Statement *statement() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::Statement *astStmt;
    if (lookahead == '{') {
        //* { decls stmts }
        currentScope = currentScope->createScope();
        astStmt = new SCCASTClasses::StmtBlock(currentScope);
        SCCASTClasses::StmtBlock *enclosingBlock = currentBlock;
        currentBlock = (SCCASTClasses::StmtBlock *)astStmt;
        match();
        declarations();
        statements();
        currentScope = currentScope->exitScope();
        currentBlock = enclosingBlock;
        match(OP_R_BRACE);
    } else if (lookahead == RETURN) {
        //* return expr
        match();
        SCCASTClasses::Expression *expr1 =
            new SCCASTClasses::Expression(expression());
        astStmt = new SCCASTClasses::CFSReturn(expr1, currentBlock);
        checkReturnType(currentScope, expr1->getType());
        match(OP_SC);
    } else if (lookahead == WHILE) {
        //* while ( expression ) statement
        match();
        match(OP_L_PARENT);
        SCCASTClasses::Expression *expr1 =
            new SCCASTClasses::Expression(expression());
        checkTestExpr(expr1->getType());
        match(OP_R_PARENT);
        SCCASTClasses::Statement *body = statement();
        astStmt = new SCCASTClasses::CFSWhile(expr1, body);
    } else if (lookahead == FOR) {
        //* for ( assignment ; expression ; assignment ) statement
        match(FOR);
        match(OP_L_PARENT);
        SCCASTClasses::Statement *assign1 = assignment();
        match(OP_SC);
        SCCASTClasses::Expression *expr1 =
            new SCCASTClasses::Expression(expression());
        checkTestExpr(expr1->getType());
        match(OP_SC);
        SCCASTClasses::Statement *assign2 = assignment();
        match(OP_R_PARENT);
        SCCASTClasses::Statement *body = statement();
        astStmt = new SCCASTClasses::CFSFor(assign1, expr1, assign2, body);
    } else if (lookahead == IF) {
        //* if ( expression ) statement
        //* if ( expression ) statement else statement
        match(IF);
        match(OP_L_PARENT);
        SCCASTClasses::Expression *expr1 =
            new SCCASTClasses::Expression(expression());
        checkTestExpr(expr1->getType());
        match(OP_R_PARENT);
        SCCASTClasses::Statement *stmt1 = statement();
        astStmt = new SCCASTClasses::CFSIf(expr1, stmt1, NULL);
        if (lookahead == ELSE) {
            match();
            ((SCCASTClasses::CFSIf *)astStmt)->stmt2 = statement();
        }
    } else {
        // | assignment ;
        astStmt = assignment();  // type checking handled in assignment
        match(OP_SC);
    }
    return astStmt;
}

// assignment -> expression = expression
//            | expression
SCCASTClasses::Statement *assignment() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *expr1 = expression();
    if (lookahead == '=') {
        match();
        SCCASTClasses::ExprTreeClasses::ExprTreeNode *rhs = expression();
        checkAssign(expr1->getType(), rhs->getType());
        SCCASTClasses::Assignment *res =
            new SCCASTClasses::Assignment(expr1, rhs);
        return res;
    }
    SCCASTClasses::Expression *res = new SCCASTClasses::Expression(expr1);
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
SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression() {
    PRINT_FUNC_IF_ENABLED;
    return expression_level_1();
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_1() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_2();
    while (lookahead == OP_OR) {
        match();
        op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryOR(
            op1, expression_level_2());
    }
    op1->performTypeChecking();
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_2() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_3();
    while (lookahead == OP_AND) {
        match();
        op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAnd(
            op1, expression_level_3());
    }
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_3() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_4();
    while (lookahead == OP_EQ || lookahead == OP_NE) {
        if (lookahead == OP_EQ) {
            match();
            op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryEQ(
                op1, expression_level_4());
        } else {
            match();
            op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryNEQ(
                op1, expression_level_4());
        }
    }
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_4() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_5();
    while (lookahead == OP_LT || lookahead == OP_GT || lookahead == OP_LE ||
           lookahead == OP_GE) {
        Token op = lookahead;
        match();
        switch (op) {
            case OP_LT:
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLT(
                    op1, expression_level_5());
                break;
            case OP_GT:
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGT(
                    op1, expression_level_5());
                break;
            case OP_LE:
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryLE(
                    op1, expression_level_5());
                break;
            default: /*OP_GE*/
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryGE(
                    op1, expression_level_5());
                break;
        }
    }
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_5() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_6();
    while (lookahead == '+' || lookahead == '-') {
        Token op = lookahead;
        match();
        if (op == '+') {
            op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryAdd(
                op1, expression_level_6());
        } else {
            op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMinus(
                op1, expression_level_6());
        }
    }
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_6() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_level_7();
    while (lookahead == '*' || lookahead == '/' || lookahead == '%') {
        Token op = lookahead;
        match();
        switch (op) {
            case '*':
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMUL(
                    op1, expression_level_7());
                break;
            case '/':
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryDiv(
                    op1, expression_level_7());
                break;
            default:
                op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinaryMod(
                    op1, expression_level_7());
                break;
        }
    }
    return op1;
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_7() {
    PRINT_FUNC_IF_ENABLED;
    switch (lookahead) {
        case '&':
            match();
            return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryAddrOf(
                expression_level_7());
        case '*':
            match();
            return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryDeref(
                expression_level_7());
        case '!':
            match();
            return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnaryNot(
                expression_level_7());
        case '-':
            match();
            return new SCCASTClasses::ExprTreeClasses::
                ExprTreeNodeUnaryNegation(expression_level_7());
        case SIZEOF:
            match();
            return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeUnarySizeof(
                expression_level_7());
        default:
            return expression_level_8();
    }
}

SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_level_8() {
    PRINT_FUNC_IF_ENABLED;
    SCCASTClasses::ExprTreeClasses::ExprTreeNode *op1 = expression_term();
    while (lookahead == '[') {
        match();
        op1 = new SCCASTClasses::ExprTreeClasses::ExprTreeNodeBinarySubscript(
            op1, expression());
        match(OP_R_BRACKET);
    }
    return op1;
}

// expression-list -> expression
//                 | expression , expression-list
std::vector<SCCASTClasses::Expression *> *expression_list() {
    PRINT_FUNC_IF_ENABLED;
    std::vector<SCCASTClasses::Expression *> *res =
        new std::vector<SCCASTClasses::Expression *>();
    res->push_back(new SCCASTClasses::Expression(expression()));
    while (lookahead == ',') {
        match();
        res->push_back(new SCCASTClasses::Expression(expression()));
    }
    return res;
}

// | id ( expression-list )
// | id ( )
// | id
// | num
// | string
// | character
// | ( expression )
SCCASTClasses::ExprTreeClasses::ExprTreeNode *expression_term() {
    PRINT_FUNC_IF_ENABLED;
    if (lookahead == ID) {
        string id = matchAndReturn(ID);
        const SCCSymbol *idSymbol = currentScope->lookupSymbol(id);
        if (lookahead == '(') {
            match();
            
            //! Bodge: Find enclosing Function, this behavior is dependent on the fact that the latest Function Definition is the current one.
            astRoot->functionDefinitions.back()->haveFunctionCall = true;

            SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall *res =
                new SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermFuncCall(
                    idSymbol);
            if (lookahead == ')') {
                // id()
                match();
                res->performTypeChecking();
                return res;
            }
            std::vector<SCCASTClasses::Expression *> *parameters =
                expression_list();
            for (SCCASTClasses::Expression *param : *parameters) {
                res->paramList->push_back(param);
            }
            // id(expr-list)
            match(OP_R_PARENT);
            res->performTypeChecking();
            return res;
        } else {
            // id
            return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermVariable(
                idSymbol);
        }
    } else if (lookahead == NUM) {
        //! Number literal, can be int or long
        signed long numVal = stol(matchAndReturn(NUM));
        return new SCCASTClasses::ExprTreeClasses::
            ExprTreeNodeTermLiteralNumber(numVal);
    } else if (lookahead == STRING) {
        //! String literal value
        string strVal = matchAndReturn(STRING);
        // This returns stuff like "str", thus strVal.length()-2
        return new SCCASTClasses::ExprTreeClasses::
            ExprTreeNodeTermLiteralString(strVal);
    } else if (lookahead == CHARACTER) {
        //! Character literal value
        string charStr = matchAndReturn(CHARACTER);
        return new SCCASTClasses::ExprTreeClasses::ExprTreeNodeTermLiteralChar(
            charStr);
    } else {  //! MUST be '('
        match(OP_L_PARENT);
        SCCASTClasses::ExprTreeClasses::ExprTreeNode *res = expression();
        match(OP_R_PARENT);
        res->performTypeChecking();
        return res;
    }
}
