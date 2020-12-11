#pragma once
#include <iostream>
#include <stack>
#include "parse.h"
using namespace std;
const int maxPriority = 2;
const char operat[10] = "+-/*^";
const char priority[maxPriority][10] = {"+-", "*/^"};


vector<string> getPostfix(vector<string> tokens);
bool isOperand(string token);
bool isOperator(char oper);
int getPriority(char oper);
