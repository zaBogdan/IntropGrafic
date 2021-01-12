#include "setup.h"

/**
  * Reads the function from file for now.
  * TODO: Implement it in the UI
  * @return string
  */
string readFunction2()
{
    string function;
    //debug


    ifstream f("../demoFunction.txt");
    getline(f, function);
    f.close();


    //end debug
//    function = sanitizeString(function);
    return function;
}
//arguments for main?idk
//int argc, char* args[]
double f(double x)
{
    return cos(x+sin(exp(x)+-x)*10);
}

int main() {
//    string func = readFunction2();
//    postfix = buildAndValidatePostfix(func);
//    if(postfix.empty())
//        return 1;
//    cout << "[MAIN] The C/C++ notation of this function is: ";
//    cout << getCPPNotation(postfix) << endl;

    graphic();
    cout << "[MAIN] This was the end!";
    cout << endl;
    return 0;
}