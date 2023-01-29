// #define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT_FUNC_TRACE
#define DEBUG_PRINT_MATCHING
#endif

#ifndef PARSER_HPP
#define PARSER_HPP

int lookahead;
void prettyPrint(int tmp);
void match(int token_type = lookahead);
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

#endif