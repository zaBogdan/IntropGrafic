#pragma once
#include "../setup.h"
#define buttonFocusColor COLOR(104, 137, 255)
using namespace std;
const int defaultSizeX = 10, defaultSizeY = 10;
const int shiftKeys[] = {')', '!', '@','#','$','%', '^','&', '*', '(','+'};
const int maxLength = 50;
extern int isShiftUp;

bool inFocus(coord center,coord mouseInput,int, int);
void drawButton(int , int,coord, char text[20],int, int font_size=2, int active=0);
void textInputBar(coord, coord);

