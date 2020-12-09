//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#define DEBUG false
using namespace std;

const int mathFunctionsCounter = 23;
const char mathematicalFunctions[25][10] = {"abs","acos","asin","atan","cbrt","ceil","cos","cosh","exp","expm1","fabs","fdim","floor","hypot","fma","fmax","fmin","fmod","pow","sqrt","sin","sinh","tan","tanh"};
const char operatii[] = "+-/*^()";

/**
 * Main functions
 */
/**
  * Reads the function from file for now.
  * TODO: Implement it in the UI
  * @return string
  */
string readFunction();
/**
 * Get the function to be parsed as string
 * @param f
 * @return infix notation tree
 */

vector<string> tokenizeString(string f);
/**
 * Check for empy spaces
 * @param f
 * @return sanitized string
 */
string sanitizeString(string f);
/**
 * Applying the rules:
 * Operands X, Y etc
 * Left Paranthesis - (
 * Right Paranthesis - )
 * Operators - +, *
 * Function call starts - sin(
 * Function call ends - sin( x )
 * Comma - ,
 * @param tokens
 * @return
 */
vector<string> applyTokenizationRules(vector<string> tokens);



/**
 * Helper functions
 */
bool isOperator(string function, int position);
bool isOperand(string function, int position, int &value);
bool isMathematicalFunction(string f);
int getEndOfMathFunction(vector<string> tokens, int poz);