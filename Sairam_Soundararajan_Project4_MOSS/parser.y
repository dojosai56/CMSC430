/* Sairam Soundararajan */
/* 3-04-22 */
/* Project 4 */
/* Compiler Theory and Design
   Dr. Duane J. Jarc */

%{

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
void yyerror(const char* message);
Symbols<Types> symbols;
%}



%define parse.error verbose

%union
{
	CharPtr iden;
	Types type;
}

%token <iden> IDENTIFIER
%token <type> INT_LITERAL REAL_LITERAL BOOL_LITERAL

%token ADDOP MULOP RELOP ANDOP OROP NOTOP REMOP EXPOP

%token BEGIN_ BOOLEAN END ENDREDUCE FUNCTION INTEGER IS REDUCE RETURNS

%token IF THEN ELSE ENDIF ARROW CASE ENDCASE OTHERS REAL WHEN

%type <type> type statement statement_ reductions expression relation term
	factor primary and_expression power not_expression case function_header
	function_header_ body cases

%%

function:	
	function_header_ optional_variable body {checkAssignment($1, $3, "Function Return");} ;
	
function_header_:
	function_header ';' |
	error ';' {$$ = MISMATCH;} ;

function_header:	
	FUNCTION IDENTIFIER optional_parameters RETURNS type {$$ = $5;} ;

optional_variable:
	optional_variable variable |
	error ';' |
	;

variable:
	IDENTIFIER ':' type IS statement_ 										{checkAssignment($3, $5, "Variable Initialization");
		{ if (symbols.find($1, $3)) appendError(DUPLICATE_IDENTIFIER, $1);
		symbols.insert($1, $3);}} ;

optional_parameters:
  parameter |
  optional_parameters ',' parameter |
  ;


parameter:
	IDENTIFIER ':' type ;

type:
	INTEGER {$$ = INT_TYPE;}|
	BOOLEAN {$$ = BOOL_TYPE;}|
	REAL {$$ = REAL_TYPE;};

body:
	BEGIN_ statement_ END ';' {$$ = $2;} ;
    
statement_:
	statement ';' |
	error ';' {$$ = MISMATCH;};

statement:
	expression |
	REDUCE operator reductions ENDREDUCE {$$ = $3;}|
	IF expression THEN statement_ ELSE statement_ ENDIF {$$ = checkIf($2, $4, $6);} |
	CASE expression IS cases OTHERS ARROW statement_ ENDCASE 	{ checkCaseExpression($2); $$ = checkCase($4, $7);};

operator:
	ADDOP |
	MULOP ;

cases:
        cases case {$$ = checkCase($1, $2);} |
        { $$ = EMPTY; } ;

case:
       WHEN INT_LITERAL ARROW statement_ {$$ = $4;} |
        error ';' {$$ = MISMATCH;} ;



reductions:
	reductions statement_ {$$ = checkArithmetic($1, $2);} |
	{$$ = INT_TYPE;} ;
		    
expression:
	expression OROP and_expression {checkLogical($1, $3);} |
	and_expression ;

and_expression:
	and_expression ANDOP relation {checkLogical($1, $3);} |
     	relation ;

relation:
	relation RELOP term {$$ = checkRelational($1, $3);}|
	term;

term:
	term ADDOP factor {$$ = checkArithmetic($1, $3);} |
	factor ;
      
factor:
	factor MULOP power {$$ = checkArithmetic($1, $3);}|
	factor REMOP power {$$ = checkRemainder($1, $3);}|
	power ;

power:
	not_expression EXPOP power {$$ = checkArithmetic($1, $3);}|
	not_expression ;

not_expression:
	NOTOP not_expression {$$ = checkLogical(BOOL_TYPE, $2);}|
	primary ;

primary:
	'(' expression ')' {$$ = $2;}|
	INT_LITERAL |
	REAL_LITERAL |
	BOOL_LITERAL | 
	IDENTIFIER {if (!symbols.find($1, $$)) appendError(UNDECLARED, $1);} ;
    
%%

void yyerror(const char* message)
{
	appendError(SYNTAX, message);
}



int main(int argc, char *argv[])    
{
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
