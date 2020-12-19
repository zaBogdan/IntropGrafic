#include <iostream>
#define SDL_MAIN_HANDLED
#include <graphics.h>
#include "eval/parse.h"
#include "eval/validate.h"
#include "eval/generateFunction.h"
#include "draw/draw.h"

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
    cout << "[RESULT] The given function is: " << func << endl;
    vector<string> tokens = tokenizeString(func);
    cout << "[RESULT] The tokenized func is: ";
    for(auto i :tokens)
        cout << i;
    cout << endl;
    vector<string> postfix = getPostfix(tokens);
    cout << "[RESULT] The postfix form is: ";
    for(auto i: postfix)
        cout << i << ", ";
    cout << endl;
    cout << "[RESULT] The formula `" << func;
    cout << ((checkValidity(postfix) == true) ? "` is valid!" : " is INVALID!");
    cout << endl;

    cout << "[MergeFunction] THe output is: \n";
    cout << postfixToCPP(postfix);
    cout << endl;
    return 0;

}