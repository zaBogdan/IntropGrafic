//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

#include "readFunction.h"
//bool isValid=true;

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


void parseByOperators(string f)
{
    cout << "Initial function: " << f << endl;
    int poz=0, lastPos=0;
    while(poz < f.length())
    {
        if(checkForOperator(f, poz))
        {
            cout << "Found subfunction: " << f.substr(lastPos, poz-lastPos) << endl;
            lastPos=poz+1;
        }
        poz++;
    }
    cout << "Found subfunction: " << f.substr(lastPos, poz-lastPos) << endl;
}



//this function must be done properly.
bool checkForOperator(string function, int position, bool paraCheck)
{

    if(!strchr(operatii, function[position]))
        return false;
    if(function[position] == '-' && !paraCheck)
    {
        char nc= function[position + 1];
        if(position + 1 > function.length())
            return false;
        if(isdigit(nc) || isalpha(nc) || nc == '(')
            return false;
    }
    if(function[position] == '-' && paraCheck)
    {
        char bc = function[position - 1];
        if(strchr(operatii, bc) || isdigit(bc) || isdigit(bc) || strchr("()", bc))
            return true;
        return false;
    }
//    cout << "WAITING LAST CHECK AT: " << position << endl;
    for(int i=position; i >= 0; i--)
    {
        //must be checking if I am inside parantesis
        if(function[i]=='(' && checkForOperator(function,i-1, true))
            return false;
    }
//    cout << "VALID AT POSITION: " << position << endl;
    return true;
}


//bool isInsideParantesis(string func, int poz)
//{
//    int open=0,close=0;
//    while(poz!=0)
//    {
//        if(func[poz]=='(')
//            open++;
//        if(func[poz]==')')
//            close++;
//    }
//    return (open<close);
//}
//check if it is a mathematical function
bool isMathematicalFunction(string function, int &poz)
{
    if(!isalpha(function[poz-1]))
        return false;
    int leng = 0, intialPoz=poz;
    poz--;
    while(isalpha(function[poz]))
        poz--, leng++;
    string mathCheck = function.substr(poz+1, leng);
    //make them to a standard.
    transform(mathCheck.begin(), mathCheck.end(), mathCheck.begin(), ::tolower);
    //map alternatives ( ex: rad(x) = sqrt(x) )

    for(int i=0;i<mathFunctionsCounter;i++)
        if(mathCheck.find(mathematicalFunctions[i])!=string::npos)
        {
            //move the pointer
            poz = intialPoz;
            int openPar = 0;
            while(poz<function.length())
            {
                if(function[poz]=='(')
                    openPar++;
                if(function[poz]==')')
                    openPar--;
                if(!openPar)
                    break;
                poz++;
            }
            poz--;
            return true;
        }
    poz=intialPoz;
    return false;
}