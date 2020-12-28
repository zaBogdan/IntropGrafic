#pragma once
#include "../setup.h"
using namespace std;
const int maxPriority = 3, maxArity=6;
const char priority[maxPriority][10] = {"+-", "*/","^"};
const char operatorsPostfix[10] = "+-/^*";
const char mathFunctionsWithArity2[10][10] = {"pow", "fmod","fdim","fmax","fmin","hypot"};

vector<string> getPostfix(vector<string>);
bool validatePostix(vector<string>);
bool isMathematicalFunction(string);
int splitDigitFromAlpha(string);
int getPriority(string);
bool isOperator(string);
int getArity(string t);