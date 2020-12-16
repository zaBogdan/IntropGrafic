#pragma once
#include <iostream>
#include <stack>
#include "parse.h"
using namespace std;
const int maxPriority = 2;
const char operat[10] = "+-/*^";
const char priority[maxPriority][10] = {"+-", "*/^"};
const char arity2Op[6][10] = {"pow", "fdim", "fmax", "fmin", "fmod"};


bool checkValidity(vector<string> postfix);
vector<string> getPostfix(vector<string> tokens);
bool isOperand(string token);
bool isOperator(char oper);
int getPriority(char oper);
int digitVal(string token);
int getArity(string i);
