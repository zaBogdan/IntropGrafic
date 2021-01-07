#pragma once
#include "../setup.h"
#define buttonFocusColor COLOR(104, 137, 255)
using namespace std;
const int defaultSizeX = 10, defaultSizeY = 10;
const int shiftKeys[] = {')', '!', '@','#','$','%', '^','&', '*', '(','+'};
const int maxLength = 50;


bool inFocus(coord center,coord mouseInput,int, int);
void drawButton(int, int,coord, char text[20],int);
void textInputBar(coord, coord);

void inputText(int, int,int maxLength=50);
void drawHugeText(coord, string);