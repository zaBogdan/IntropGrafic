#pragma once
#include "../setup.h"
#include "tokenize.h"
#include "postfixValidator.h"
using namespace std;
extern unordered_map<double, double> values;

/**
 * Getting the postfix version and validate it
 * @param function
 */
vector<string> buildAndValidatePostfix(string);
string getCPPNotation(vector<string>);
double getValueFromPostfix(vector<string>,double,double,double);
bool isNumber(double);