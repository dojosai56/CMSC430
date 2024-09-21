// Sairam Soundararajan
// 1-26-22
// Project 1
// Compiler Theory and Design
// Dr. Duane J. Jarc

// This file contains the bodies of the functions that produces the compilation
// listing

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

#include "listing.h"

static int lineNumber;
static string error = "";
static int totalErrors = 0;
static int lexicalErrors = 0;
static int syntaxErrors = 0;
static int semanticErrors = 0;
static queue<string> errorQ;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{
	printf("\r");
	displayErrors();
	printf("     \n");
	if(totalErrors > 0)
	{
	   cout << "Lexical Errors: " << lexicalErrors << endl;
	   cout << "Syntax Errors: " << syntaxErrors << endl;
	   cout << "Semantic Errors: " << semanticErrors << endl;
	}
	else
	{
	    cout << "Compiled Successfully" << endl;
	}
	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate Identifier: ",
		"Semantic Error, Undeclared " };

	error = messages[errorCategory] + message;
	errorQ.push(error);
	switch(errorCategory)
	{
	   case LEXICAL:
	      lexicalErrors++;
                      break;
	   case SYNTAX:
	      syntaxErrors++;
	      break;
	   default:
	      semanticErrors++;
                      break;
	}
	totalErrors++;
}

void displayErrors()
{
	while(!errorQ.empty()) {
	       cout << errorQ.front();
 	       errorQ.pop();
	}
}
