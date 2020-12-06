#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <graphics.h>

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
    example3();
    return 0;
}