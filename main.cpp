#include "setup.h"
int errorFlagDrawing=0;

int main() {

    if(DEBUG==true)
        cout << "[MAIN] Starting the graphic UI.\n";
    graphic();
    if(DEBUG==true)
        cout << "[MAIN] This was the end!\n";
    cout << endl;
    return 0;
}