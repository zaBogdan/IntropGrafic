#include <iostream>
#define SDL_MAIN_HANDLED
#include <graphics.h>
#include "eval/readFunction.h"

int example3()
{
    initwindow(800,600); int x = 400, y = 300, r;
    for (r = 25; r <= 125; r += 20)
        circle(x, y, r);
    getch(); closegraph(); return 0;
}

//arguments for main?idk
//int argc, char* args[]

int main() {
//    example3();
    string func = readFunction();
    checkSyntax(func);
    return 0;
}