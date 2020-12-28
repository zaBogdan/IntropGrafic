#pragma once
#include <map>
#include <functional>
#include "../setup.h"
#include "tokenize.h"
#include "postfixValidator.h"
using namespace std;

/**
 * Getting the postfix version and validate it
 * @param function
 */
vector<string> buildAndValidatePostfix(string);
string getCPPNotation(vector<string>);
double getValueFromPostfix(vector<string>, double);
