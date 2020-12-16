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
                cout << "[Tokenize] Found the operator "<< f[poz] << " at position: " << poz << endl;
            tokens.push_back(f.substr(poz, 1));

        }
        //check for operand
        else if(isOperand(f, poz, value))
        {
            if(DEBUG==true)
                cout << "[Tokenize] Found the operand " << f.substr(poz, value-poz) << " at position: " << poz << " for " << value << " length!\n";
            tokens.push_back(f.substr(poz,value-poz));
            poz+=(value-poz)-1;
        }
        poz++;
    }
    if(DEBUG==true)
    {
        cout << "[Tokenize] This are the tokens before applying the rules: \n";
        for(auto i: tokens)
            cout << i << ", ";
        cout << endl;
    }
    return applyTokenizationRules(tokens);
}

// sin(x) -> x sin
// x+y -> x y +
vector<string> applyTokenizationRules(vector<string> tokens)
{
    bool visited[tokens.size() + 10];
    memset(visited, 0, tokens.size() + 10);
    vector<string> normalizedTokens;
    int dummyVariable=0,dumVar=0,offset=0;
    for(int i=0;i<tokens.size();i++)
    {
        if(tokens[i][0]=='-' && isOperand(tokens[i+1].c_str(),0,dummyVariable) && !visited[i])
        {
            if(DEBUG==true)
                cout << "[Rules] Found unary minus at " << i << endl;
            normalizedTokens.push_back(tokens[i]+ tokens[i+1]);
            visited[i]=1;
            visited[i + 1]=1;
            offset++;
        }
        else if(isMathematicalFunction(tokens[i]))
        {
            if(!visited[i])
            {
                normalizedTokens.push_back(tokens[i]);
                visited[i]=1;
            }
            normalizedTokens.push_back("[");
            visited[i + 1]=1;
            int closingOfMathFunction = getEndOfMathFunction(tokens, i+1);
            if(DEBUG==true)
            {
                cout << "[Rules] Found math function `"<< tokens[i] << "` with the start position in vector " << i;
                cout << " ending at "<< closingOfMathFunction << endl;
            }
            if(closingOfMathFunction<tokens.size() && tokens[closingOfMathFunction][0]==')')
                tokens[closingOfMathFunction]=string("]");

        }
        else if(!visited[i])
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
    for(int i=0;i<mathFunctionsCounter;i++)
        if(!strcmp(mathematicalFunctions[i],f.c_str()))
            return true;
    return false;
}

//sanitize the string for spaces
string sanitizeString(string f)
{
    for(int i=0;i<f.length();i++)
    {
        if(isalpha(f[i]))
            f[i]=tolower(f[i]);
        else if(f[i]==' ')
        {
            f.erase(i,1);
            i--;
        }
        else if(f[i]==',')
            f[i]='.';
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