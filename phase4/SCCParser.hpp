#if !defined(SCC_PARSER_HPP)
#define SCC_PARSER_HPP

#include <string>

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
void statement();
void assignment();
/**
 * @return dynamically allocated list of expr type
*/
std::vector<SCCType>* expression_list();
SCCType expression();
SCCType expression_level_1();
SCCType expression_level_2();
SCCType expression_level_3();
SCCType expression_level_4();
SCCType expression_level_5();
SCCType expression_level_6();
SCCType expression_level_7();
SCCType expression_level_8();
SCCType expression_term();

#endif  // SCC_PARSER_HPP
