%option noyywrap

%{

#include "parser.tab.hpp"

#include <stdlib.h>

#include <string>

#include <iostream>


extern "C" int fileno(FILE *stream);

unsigned int line_number = 1;

%}

/*Digit declarations (decimal, Hex, Octal, Bin)*/
D [0-9]
H [a-fA-F0-9]
O [0-7]

/*suffixes (integer suffixes, float suffixes)*/
IntS ([uU][lL]?)|([lL]+[uU]?)
FloatS ([fF][lL]?)|([lL][fF]?)

/*eponential*/
Exp [Ee][+-]?{D}+

/*Integer Constants */
DEC_CONSTANT [0-9]{D}*{IntS}?
HEX_CONSTANT 0[xX]{H}+{IntS}?
OCT_CONSTANT 0{O}+{IntS}?
BIN_CONSTANT 0[bB][0-1]+{IntS}?

/*Escape Characters (shouldn't matter on individual commands) */
ESCAPE_CHAR [abfnrtv\'\"\?\\]

/*Other Constants*/
FLOAT_CONSTANT ({D}+{Exp}{FloatS}?|{D}*"."{D}+({Exp})?{FloatS}?|{D}+"."{D}*({Exp})?{FloatS}?)
CHAR_CONSTANT [L]?\'(?:\\({ESCAPE_CHAR}|{O}{1,3}|x{H}+)|[^\\'])+\'
STRING_CONSTANT [L]?\"(?:\\({ESCAPE_CHAR}|[0-7]{1,3}|x[0-9A-Fa-f]+)|[^\\"])*\"

/*Other Commands*/
NEW_LINE [\n\r]
WHITESPACE [ \t\v]
COMMENT_LINE [/][/][.]*
COMMENT_MULTI ([/]\*(.|{NEW_LINE})*\*[/])

C_IDENTIFIER ([_]|[a-zA-Z])([a-zA-Z0-9]|[_])*

%%

"auto"			{ return(AUTO); }
"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"const"			{ return(CONST); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"extern"		{ return(EXTERN); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"register"		{ return(REGISTER); }
"return"		{ return(RETURN); }
"short"			{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"union"			{ return(UNION); }
"unsigned"		{  return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }


"..."			 { return ELLIPSIS; }
">>="			 { return RIGHT_ASSIGN; }
"<<="			 { return LEFT_ASSIGN; }
"+="			 { return ADD_ASSIGN; }
"-="			 { return SUB_ASSIGN; }
"*="			 { return MUL_ASSIGN; }
"/="			 { return DIV_ASSIGN; }
"%="			 { return MOD_ASSIGN; }
"&="			 { return AND_ASSIGN; }
"^="			 { return XOR_ASSIGN; }
"|="			 { return OR_ASSIGN; }
">>"			 { return RIGHT_OP; }
"<<"			 { return LEFT_OP; }
"++"			 { return INC_OP; }
"--"			 { return DEC_OP; }
"->"			 { return PTR_OP; }
"&&"			 { return AND_OP; }
"||"			 { return OR_OP; }
"<="			 { return LE_OP; }
">="			 { return GE_OP; }
"=="			 { return EQ_OP; }
"!="			 { return NE_OP; }
";"			   { return ';'; }
("{"|"<%") { return '{'; }
("}"|"%>") { return '}'; }
","			   { return ','; }
":"			   { return ':'; }
"="			   { return '='; }
"("			   { return '('; }
")"			   { return ')'; }
("["|"<:") { return '['; }
("]"|":>") { return ']'; }
"."			   { return '.'; }
"&"			   { return '&'; }
"!"			   { return '!'; }
"~"			   { return '~'; }
"-"			   { return '-'; }
"+"			   { return '+'; }
"*"			   { return '*'; }
"/"			   { return '/'; }
"%"			   { return '%'; }
"<"			   { return '<'; }
">"			   { return '>'; }
"^"			   { return '^'; }
"|"			   { return '|'; }
"?"			   { return '?'; }
"_"        { return '_'; }


{DEC_CONSTANT} {
  yylval.int_constant = strtol(yytext, NULL, 10);
  return INT_CONSTANT;
}

{HEX_CONSTANT} {
  yylval.int_constant = strtol(yytext, NULL, 16);
  return INT_CONSTANT;
}

{OCT_CONSTANT} {
  yylval.int_constant = strtol(yytext, NULL, 8);
  return INT_CONSTANT;
}

{BIN_CONSTANT} {
  yylval.int_constant = strtol(yytext, NULL, 2);
  return INT_CONSTANT;
}

{FLOAT_CONSTANT} {
  yylval.float_constant = atof(yytext);
  return FLOAT_CONST;
}

{CHAR_CONSTANT} {
  yylval.char_constant = yytext;
  return CHAR_CONST;
}

{STRING_CONSTANT} {
  yylval.str = new std::string(yytext);
  return CHAR_CONST;
}

{WHITESPACE}|{COMMENT_LINE}|{COMMENT_MULTI} { ; }

{C_IDENTIFIER} {
  yylval.str = new std::string(yytext);
  return C_IDENTIFIER;
}

{NEW_LINE} {
  line_number++;
}

. {
  std::cerr << "\nLexer ERROR: INVALID COMMAND" << std::endl;
  std::cerr << "LINE: " << line_number << std::endl;
  std::cerr << "COMMAND: " << yytext << std::endl;
  exit(1);
}


%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  std::cerr << "LINE: " << line_number << std::endl;
  exit(1);
}
