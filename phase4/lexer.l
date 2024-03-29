%{
/*
 * File:	lexer.l
 *
 * Description:	This file contains the flex description for the lexical
 *		analyzer for Simple C.
 *
 *		Extra functionality:
 *		- checking for out of range integer literals
 *		- checking for invalid string literals
 */

# include <cerrno>
# include <cstdio>
# include <cstdlib>
# include <iostream>
# include "string.h"
# include "lexer.h"
# include "tokens.h"

/* This used to be a function, but students wouldn't remove the definition
   when they moved to the next phase, even though the function wasn't used
   anymore and they'd get a warning telling them that.  It annoyed me. */

# define printToken(s)	(cout << s << " " << yytext << endl)


using namespace std;

int numerrors = 0;
static void checkInt();
static void checkStr();
static void checkChar();
static void ignoreComment();
%}

%option nounput noyywrap yylineno
%%

(\/\*([^*]|\*+[^/\*])*\*+\/|\/\/[^\n]*)     { /* ignored - comment */   }

"/*"					{ignoreComment();}

"auto"					{return AUTO;}
"break"					{return BREAK;}
"case"					{return CASE;}
"char"					{return CHAR;}
"const"					{return CONST;}
"continue"				{return CONTINUE;}
"default"				{return DEFAULT;}
"do"					{return DO;}
"double"				{return DOUBLE;}
"else"					{return ELSE;}
"enum"					{return ENUM;}
"extern"				{return EXTERN;}
"float"					{return FLOAT;}
"for"					{return FOR;}
"goto"					{return GOTO;}
"if"					{return IF;}
"int"					{return INT;}
"long"					{return LONG;}
"register"				{return REGISTER;}
"return"				{return RETURN;}
"short"					{return SHORT;}
"signed"				{return SIGNED;}
"sizeof"				{return SIZEOF;}
"static"				{return STATIC;}
"struct"				{return STRUCT;}
"switch"				{return SWITCH;}
"typedef"				{return TYPEDEF;}
"union"					{return UNION;}
"unsigned"				{return UNSIGNED;}
"void"					{return VOID;}
"volatile"				{return VOLATILE;}
"while"					{return WHILE;}

"||"					{return OP_OR;}
"&&"					{return OP_AND;}
"=="					{return OP_EQ;}
"!="					{return OP_NE;}
"<="					{return OP_LE;}
">="					{return OP_GE;}
"++"					{return OP_INC;}
"--"					{return OP_DEC;}
"->"					{return OP_ARROW;}
"="                                     {return OP_ASSIGN;}
"|"                                     {return OP_BIN_OR;} 
"&"                                     {return OP_BIN_AND;} 
"!"                                     {return OP_NOT;} 
"<"                                     {return OP_LT;} 
">"                                     {return OP_GT;} 
"+"                                     {return OP_PLUS;} 
"-"                                     {return OP_MINUS;} 
"*"                                     {return OP_AST;} 
"/"                                     {return OP_DIV;} 
"%"                                     {return OP_MOD;} 
"("                                     {return OP_L_PARENT;} 
")"                                     {return OP_R_PARENT;} 
"["                                     {return OP_L_BRACKET;} 
"]"                                     {return OP_R_BRACKET;} 
"{"                                     {return OP_L_BRACE;} 
"}"                                     {return OP_R_BRACE;} 
";"                                     {return OP_SC;} 
":"                                     {return OP_COL;} 
"."                                     {return OP_DOT;} 
","                                     {return OP_COMMA;} 


[a-zA-Z_][a-zA-Z_0-9]*			{return ID;}

[0-9]+					{checkInt(); return NUM;}
\"(\\.|[^\\\n"])*\"			{checkStr(); return STRING;}
\'(\\.|[^\\\n'])+\'			{checkChar(); return CHARACTER;}

[ \f\n\r\t\v]+				{/* ignored */}
.					{cerr << "oops: " << yytext << endl; /* ignored */}

%%

/*
 * Function:	ignoreComment
 *
 * Description:	Ignore a comment after recognizing its beginning.
 */

static void ignoreComment()
{
    int c1, c2;


    while ((c1 = yyinput()) != 0) {
	while (c1 == '*') {
	    if ((c2 = yyinput()) == '/' || c2 == 0)
		return;

	    c1 = c2;
	}
    }

    if (c1 == 0)
	report("unterminated comment");
}


/*
 * Function:	checkInt
 *
 * Description:	Check if an integer constant is valid.
 */

static void checkInt()
{
    errno = 0;
    strtol(yytext, NULL, 0);

    if (errno != 0)
	report("integer constant too large");
}


/*
 * Function:	checkStr
 *
 * Description:	Check if a string literal is valid.
 */

static void checkStr()
{
    bool invalid, overflow;
    string s(yytext + 1, yyleng - 2);


    parseString(s, invalid, overflow);

    if (invalid)
	report("unknown escape sequence in string constant");
    else if (overflow)
	report("escape sequence out of range in string constant");
}


/*
 * Function:	checkChar
 *
 * Description:	Check if a character literal is valid.
 */

static void checkChar()
{
    bool invalid, overflow;
    string s(yytext + 1, yyleng - 2);


    parseString(s, invalid, overflow);

    if (invalid)
	report("unknown escape sequence in character constant");
    else if (overflow)
	report("escape sequence out of range in character constant");
}


/*
 * Function:	report
 *
 * Description:	Report an error to the standard error prefixed with the
 *		line number.  We'll be using this a lot later with an
 *		optional string argument, but C++'s stupid streams don't do
 *		positional arguments, so we actually resort to snprintf.
 *		You just can't beat C for doing things down and dirty.
 */

void report(const string &str, const string &arg)
{
    char buf[1000];


    snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
    cerr << "line " << yylineno << ": " << buf << endl;
    numerrors ++;
}
