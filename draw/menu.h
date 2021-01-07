#pragma once
#include "../setup.h"
#include "elements.h"
#include "draw.h"
using namespace std;
//this must not be changed!!!
const int maxWidth = 1024;
const int maxHeigh = 768;
const int frames = 30;
struct coord{
    int x=0,y=0;
};
extern coord mouseC;
extern int activePage;
extern char input[];

void mainLoop(vector<string>);
void primaryPage();
void inputPage();
void quit();
void thirdPage();
void secondaryPage();
