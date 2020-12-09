//
// Created by Bogdan Zavadovschi on 06.12.2020.
//

//https://stackoverflow.com/questions/11708195/infix-to-postfix-with-function-support
#include "parse.h"

//reading from file for now.
string readFunction()
{
    string function;
    //debug


    ifstream f("../demoFunction.txt");
    getline(f, function);
    f.close();


    //end debug
    function = sanitizeString(function);
    return function;
}



vector<string> tokenizeString(string f)
{
    vector<string> tokens;
    int poz=0, lastPos=0;
    while(poz<f.length())
    {
        int value;
        //check for operator
        if(isOperator(f,poz))
        {
            if(DEBUG==true)
                cout << "Found the operator "<< f[poz] << " at position: " << poz << endl;
            tokens.push_back(f.substr(poz, 1));

        }
        //check for operand
        else if(isOperand(f, poz, value))
        {
            if(DEBUG==true)
                cout << "We found the operand " << f.substr(poz, value-poz) << " at position: " << poz << " for " << value << " length!\n";
            tokens.push_back(f.substr(poz,value-poz));
            poz+=(value-poz)-1;
        }
        poz++;
    }
    if(DEBUG==true)
    {
        cout << "This are the tokens before applying the rules: \n";
        for(auto i: tokens)
            cout << i << ", ";
        cout << endl;
    }
    return applyTokenizationRules(tokens);
}


vector<string> applyTokenizationRules(vector<string> tokens)
{
    bool vizitati[tokens.size()+10];
    memset(vizitati, 0, tokens.size()+10);
    vector<string> normalizedTokens;
    int dummyVariable=0,offset=0;
    for(int i=0;i<tokens.size();i++)
    {
        if(tokens[i][0]=='-' && isOperand(tokens[i+1].c_str(),0,dummyVariable) && !vizitati[i])
        {
            if(DEBUG==true)
                cout << "FOUND UNARY - OPERATOR at pos" << i << endl;
            normalizedTokens.push_back(tokens[i]+ tokens[i+1]);
            vizitati[i]=1;
            vizitati[i+1]=1;
            offset++;
        }
        else if(isMathematicalFunction(tokens[i]) && !vizitati[i])
        {
            normalizedTokens.push_back(tokens[i]);
            vizitati[i]=1;
            normalizedTokens.push_back("[");
            vizitati[i+1]=1;
            int closingOfMathFunction = getEndOfMathFunction(tokens, i+1);
            if(DEBUG==true)
            {
                cout << "Got math function: "<< tokens[i] << " found at the pozition in vector " << i;
                cout << " and it ends with: " << tokens[closingOfMathFunction] << " the position in vector being "<< closingOfMathFunction << endl;
            }
            tokens[13]=string("]");
            if(closingOfMathFunction<tokens.size() && tokens[closingOfMathFunction][0]==')')
                tokens[closingOfMathFunction]=string("]");
        }
        else if(!vizitati[i])
        {
            normalizedTokens.push_back(tokens[i]);
        }
    }
    return normalizedTokens;
}

//check for the operators.
bool isOperator(string function, int position)
{
    //check if we should even bother to look for special cases
    if(!strchr(operatii, function[position]))
        return false;
    //we have a valid 2 way merge
    return true;
}

//check for the variables or for numbers
bool isOperand(string function, int position, int &value)
{
    value=position;
    if(function[value] == '-') {
        char low = function[position - 1], high = function[position + 1];
        //check if at the lower place is an operator and at the higher positon we can find a digi, number or an open paranthesis
        if ((low >= 0 && strchr(operatii, low)) && (high < function.length() && (isalpha(high) || isdigit(high) || high == '(')))
            value++;
    }
    while(!strchr(operatii,function[value]) && value<function.length())
        value++;
    for(int i=position;i<value && i<function.length();i++)
        if(!isalpha(function[i]) && !isdigit(function[i]) && function[i]!='-' && function[i]!=',')
            return false;
    return true;
}

//check if it's mathematical function
bool isMathematicalFunction(string f)
{
    int i=0;
    for(i=0;i<mathFunctionsCounter;i++)
        if(!strcmp(mathematicalFunctions[i],f.c_str()))
            return true;
    return false;
}

//sanitize the string for spaces
string sanitizeString(string f)
{
    for(int i=0;i<f.length();i++)
        if(f[i]==' ')
        {
            f.erase(i,1);
            i--;
        }
    return f;
}

//If we are inside of a function check where it ends
int getEndOfMathFunction(vector<string> tokens, int poz)
{
    int openPars=0;
    for(int i=poz;i<tokens.size();i++)
    {
        if(tokens[i][0]=='(')
            openPars++;
        if(tokens[i][0]==')')
            openPars--;
        if (!openPars)
            return i;
    }
    return -1;
}