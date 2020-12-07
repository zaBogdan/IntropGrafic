//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

#include "readFunction.h"

//reading from file for now.
string readFunction()
{
    string function;
    //debug
    ifstream f("../demoFunction.txt");
    f >> function;
    cout << function << '\n';
    f.close();
    //end debug
    return function;
}
bool checkSyntax(string func)
{
    cout << func.length() << endl;
    int lastPos=0, poz=0;

    priorityOperators last, actual;

    while(poz<func.length())
    {
        if(checkForOperator(func, poz))
        {
            cout << "Pozitia: " << poz << " output: " << func[poz] << " lastPos: " << lastPos << " ec: ";
            cout << func.substr(lastPos, poz-lastPos) << endl;
            lastPos=poz+1;
        }
        poz++;
    }
    cout << "Pozitia: " << poz << " output: " << func[poz-1] << " lastPos: " << lastPos << " ec: ";
    cout << func.substr(lastPos, poz-lastPos) << endl;
    return true;
}

//this function must be done properly.
bool checkForOperator(string function, int pozition)
{
    char operatii[] = "+-/*";
    return strchr(operatii, function[pozition]);
}