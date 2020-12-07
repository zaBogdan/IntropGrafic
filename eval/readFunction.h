//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#define type string
using namespace std;

const int mathFunctionsCounter = 23;
const char mathematicalFunctions[25][10] = {"abs","acos","asin","atan","cbrt","ceil","cos","cosh","exp","expm1","fabs","fdim","floor","hypot","fma","fmax","fmin","fmod","pow","sqrt","sin","sinh","tan","tanh"};
const char operatii[] = "+-/*^";

string readFunction();
void parseByOperators(string f);
bool checkForOperator(string function, int position, bool paraCheck=false);
bool isInsideParantesis(string func, int poz);
//string checkMissingMultiplication(string f,char variable);
//bool isMathematicalFunction(string function, int &poz);
//bool writeFunction(string func);
//bool evaluateFunction(string func);
//bool checkSyntax(string func);
