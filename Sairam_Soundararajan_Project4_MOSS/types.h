/* Sairam Soundararajan */
/* 3-04-22 */
/* Project 4 */
/* Compiler Theory and Design
   Dr. Duane J. Jarc */

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, BOOL_TYPE, REAL_TYPE, EMPTY};

void checkAssignment(Types lValue, Types rValue, string message);
Types checkArithmetic(Types left, Types right);
Types checkCase(Types expression1, Types expression2);
Types checkCaseExpression(Types statement);
Types checkLogical(Types left, Types right);
Types checkRelational(Types left, Types right);
Types checkRemainder(Types left, Types right);
Types checkIf(Types expression, Types left, Types right);