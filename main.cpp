#include "setup.h"
int errorFlagDrawing=0;
string readStringConsole()
{
    string str;
    ifstream f("../debug.txt");
    f >> str;
    return str;
}

int main() {
//    string s = readStringConsole();
//    cout << s << endl;
//    vector<string> post = buildAndValidatePostfix(s);



    cout << "[MAIN] Starting the graphic UI.\n";
    graphic();
    cout << "[MAIN] This was the end!\n";
    cout << endl;
    return 0;
}