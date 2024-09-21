%{
#include <stdio.h>
#include <ctype.h>

void toTitle(char* yytext, int yyleng);
%}

%option noyywrap

ws			[ \t\r\n]+
quoted		\".*\"
line		[\n]
letter		[A-Za-z]
digit		[0-9]
word		{letter}+(\-{letter}+)?
number		{digit}+
punc		[,:;]

%%

{ws}		{ ECHO; }
{quoted}	{ ECHO; }
{word}		{ toTitle(yytext, yyleng); }
{number}	{ ECHO; }
{punc}		{ ECHO; }
.			{}

%%

void toTitle(char* yytext, int yyleng)
{
	putchar(toupper(yytext[0]));
	int i;
	for (i = 1; i < yyleng; i++)
		putchar(tolower(yytext[i]));
}

int main()
{
	while (yylex());
	return 0;
}