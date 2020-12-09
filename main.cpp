#include <iostream>
#define SDL_MAIN_HANDLED
#include <graphics.h>
#include "eval/parse.h"

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
    cout << "[Final Output] The given function is: " << func << endl;
    vector<string> tokens = tokenizeString(func);
    cout << "[Final Output] The tokenized func is: ";
    for(auto i :tokens)
        cout << i;
    cout << endl;
    cout << "[Final Output] Checking the vector: \n";
    for(auto i :tokens)
        cout << i << " | ";
    cout << endl;
    return 0;

}