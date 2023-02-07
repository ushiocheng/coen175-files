#if !defined(PARSER_HPP)
#define PARSER_HPP

#include "semantic-classes/SCCSymbol.hpp"
#include "semantic-classes/SCCType.hpp"
#include <string>

int lookahead;
void prettyPrint(int tmp);
void match(int token_type = lookahead);
std::string matchAndReturn(int token_type);
void start();
void translation_unit();
void rest_of_global_declarator_list();
void global_declarator();
void pointers();
void specifier();
inline bool lh_is_specifier();
void rest_of_function_definition();
void parameters();
void parameter();
void declarations();
void declarator_list();
void declarator();
void statements();
void statement();
void assignment();
void expression_list();
void expression();
void expression_level_1();
void expression_level_2();
void expression_level_3();
void expression_level_4();
void expression_level_5();
void expression_level_6();
void expression_level_7();
void expression_level_8();
void expression_term();

#endif // PARSER_HPP
