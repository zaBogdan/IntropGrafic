#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <map>
#include <functional>
#include <cfloat>
#include <unordered_map>
#define SDL_MAIN_HANDLED
#define DEBUG false
#include <graphics.h>
#ifndef __TYPES_H
#define __TYPES_H
typedef struct {
    int x=0,y=0;
} coord;
typedef struct{
    bool initialized=false;
    bool isModified=false;
    bool axis_arrows;
    bool axis_numbers;
    bool minor_gridlines;
    std::string language;
    std::string measure;
} settings;
typedef std::map<std::string, std::string> langCore;
#endif
#include "evaluator/evaluator.h"
#include "draw/main.h"
using namespace std;
extern int errorFlagDrawing;