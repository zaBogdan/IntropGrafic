#pragma once
#include "../setup.h"
using namespace std;
const char operators[10] = "+-/*^(),";
const int mathFunctionsCounter = 24;
const char mathematicalFunctions[25][10] = {"abs","acos","log","asin","atan","cbrt","ceil","cos","cosh","exp","expm1","floor","pow","sqrt","sin","sinh","tan","tanh"};


vector<string> tokenizeFunction(string);
vector<string> applyTokenRules(vector<string>);
bool isOperator(string, int, int&);
bool isOperand(string, int, int&);
bool isMathFunction(string, int, int&);
int getClosingParenthesis(vector<string>, int);