/* config/lexer.l */
%{
#include "tok.h"
#include <cstdlib>
char * readString();
%}

delim	[ \n\t]
ws		{delim}+
letter	[A-Za-z]
digit	[0-9]
/* identifier */
id		{letter}({letter}|{digit})*
/* Integer */
number	{digit}+

%%
{ws}		{/* No actions */}

"while"		{return(WHILE);}
"const"		{return(CONST);}
"int"		{return(INT);}
"void"		{return(VOID);}
"return"	{return(RETURN);}
"else"		{return(ELSE);}
"if"		{return(IF);}

{number}	{var_val = readString(); return(NUMBER);}
{id}		{var_val = readString(); return(ID);}

"=="		{yylval = EQUAL; return(RELOP); }
"!=" 		{yylval = UNEQUAL; return(RELOP); }
"<"			{yylval = LT; return(RELOP);}
">" 		{yylval = GT; return(RELOP);}
"<=" 		{yylval = LE; return(RELOP);}
">="		{yylval = GE; return(RELOP);}

"="			{return(ASSIGN);}

";"			{yylval = ';'; return(PUNCTUATION);}
"("			{yylval = '('; return(PUNCTUATION);}
")"			{yylval = ')'; return(PUNCTUATION);}
"["			{yylval = '['; return(PUNCTUATION);}
"]"			{yylval = ']'; return(PUNCTUATION);}
"."			{yylval = '.'; return(PUNCTUATION);}
"-"			{yylval = '-'; return(BINOP_UNARYOP);}
"+"			{yylval = '+'; return(BINOP_UNARYOP);}
"*"			{yylval = '*'; return(BINOP);}
"/"			{yylval = '/'; return(BINOP);}
"%"			{yylval = '%'; return(BINOP);}
.			{ /* discard bad characters */ }

%%

int yywrap()
{
	return 1;
}

char * readString()
{
	char * string;
	int i;
	string = (char *)malloc((yyleng + 1) * sizeof(char));
	for(i = 0; i < yyleng; i++)
	{
		string[i] = yytext[i];
	}
	string[i] = '\0';
	return string;
}