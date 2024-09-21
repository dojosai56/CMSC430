/* Sairam Soundararajan */
/* 3-04-22 */
/* Project 4 */
/* Compiler Theory and Design
   Dr. Duane J. Jarc */

// This file contains the bodies of the type checking functions

#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"

void checkAssignment(Types lValue, Types rValue, string message)
{
        if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
        {
                if (lValue == INT_TYPE && rValue == REAL_TYPE)
                {
                        if (message == "Variable Initialization")
                        {
                                appendError(GENERAL_SEMANTIC,
                                        "Illegal Narrowing Variable Initialization");
                        }
                        if (message == "Function Return")
                        {
                                appendError(GENERAL_SEMANTIC,
                                        "Illegal Narrowing Function Return");
                        }
                } 
                else
                {
                        appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
                }
        }
}


Types checkArithmetic(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == BOOL_TYPE || right == BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Integer Type Required");
		return MISMATCH;
	}
	if ((left == REAL_TYPE && right == INT_TYPE) || (left == INT_TYPE && right == REAL_TYPE))
	{
		return REAL_TYPE;
	}	
	return INT_TYPE;
}

Types checkCaseExpression(Types statement)
{
        if(statement != INT_TYPE)
        {
                appendError(GENERAL_SEMANTIC, "Case Expression must be Integer Type");
                return MISMATCH;
        }
        return INT_TYPE;
 
}


Types checkCase(Types expression1, Types expression2)
{
        if (expression1 == MISMATCH || expression2 == MISMATCH)
                return MISMATCH;

        if (expression1 != EMPTY && expression2 != EMPTY && expression1 != expression2)
        {
                appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
                return MISMATCH;
        }
        return expression2;
}

Types checkIf(Types expression, Types left, Types right)
{
	if (expression != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required for If Expression");
		return MISMATCH;
	}
	{
		if (left != right)
		{
			appendError(GENERAL_SEMANTIC, "Left and Right statements must be of same type");
			return MISMATCH;
		}
		return left;
	}
	return BOOL_TYPE;
}
Types checkLogical(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
	
		return MISMATCH;
	if (left != BOOL_TYPE || right != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required");
		return MISMATCH;
	}	
		return BOOL_TYPE;
	return MISMATCH;
}

Types checkRelational(Types left, Types right)
{
	if (checkArithmetic(left, right) == MISMATCH)
	
		return MISMATCH;
	return BOOL_TYPE;
}

Types checkRemainder(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
	{
		return MISMATCH;
	}
	if (left != INT_TYPE || right != INT_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Integer Type Required");
		return MISMATCH;
	}	
		return INT_TYPE;
}
