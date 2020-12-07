//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#define type string
using namespace std;

enum priorityOperators{
    plus = 0,
    subtraction = 0,
    multiply = 2,
    division = 2,
};

string readFunction();
bool writeFunction(string func);
bool evaluateFunction(string func);
bool checkSyntax(string func);
bool checkForOperator(string function, int pozition);