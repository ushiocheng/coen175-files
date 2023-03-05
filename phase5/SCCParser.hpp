#if !defined(SCC_PARSER_HPP)
#define SCC_PARSER_HPP

#include <string>

#include "ast-classes/SCCASTExpression.hpp"
#include "ast-classes/SCCASTFunction.hpp"
#include "ast-classes/SCCASTStatement.hpp"
#include "ast-classes/expr-tree-classes/ExprTreeBinaryNode.hpp"
#include "semantic-classes/SCCSymbol.hpp"
#include "semantic-classes/SCCType.hpp"
#include "tokens.h"

Token lookahead;
void match(Token token_type = lookahead);
std::string matchAndReturn(Token token_type);
void start();
void translation_unit();
void rest_of_global_declarator_list(
    SCCType::SCCType_Specifier currentSpecifier);
void global_declarator(SCCType::SCCType_Specifier currentSpecifier);
size_t pointers();
SCCType::SCCType_Specifier specifier();
inline bool lh_is_specifier();
void rest_of_function_definition(SCCType::SCCType_Specifier currentSpecifier,
                                 size_t indirection, const std::string& id);
std::vector<SCCType>* parameters();
SCCType parameter();

void declarations();
void declarator_list(SCCType::SCCType_Specifier sp);
void declarator(SCCType::SCCType_Specifier sp);
void statements();
SCCASTClasses::Statement* statement();
SCCASTClasses::Statement* assignment();

SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_1();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_2();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_3();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_4();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_5();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_6();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_7();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_level_8();
SCCASTClasses::ExprTreeClasses::ExprTreeNode* expression_term();

#endif  // SCC_PARSER_HPP
