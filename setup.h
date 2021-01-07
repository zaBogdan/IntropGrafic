#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#define SDL_MAIN_HANDLED
#define DEBUG false
#include <graphics.h>
#ifndef __TYPES_H
#define __TYPES_H
typedef struct {
    int x=0,y=0;
} coord;
#endif
#include "evaluator/evaluator.h"
#include "draw/main.h"
using namespace std;
