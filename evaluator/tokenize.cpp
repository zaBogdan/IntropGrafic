#include "tokenize.h"

//get the tokenizedFunction
vector<string> tokenizeFunction(string function)
{
    vector<string> tokens;
    int i=0, len = function.length();
    while(i<len)
    {
        bool found = false;
        int substringLength = 0;
        if(isOperator(function, i, substringLength))
        {
            if(DEBUG==true) cout << "[Tokenize] Found operator "<< function.substr(i, substringLength) << " at position: " << i;
            found = true;
            tokens.push_back(function.substr(i, substringLength));
        }
        else if(isMathFunction(function, i, substringLength))
        {
            if(DEBUG==true) cout << "[Tokenize] Found math function "<< function.substr(i, substringLength) << " at position: " << i;
            found = true;
            //added | to recognize a math function
            tokens.push_back("|"+function.substr(i, substringLength));
        }
        else if(isOperand(function, i, substringLength))
        {
            if(DEBUG==true) cout << "[Tokenize] Found operand "<< function.substr(i, substringLength) << " at position: " << i;
            found = true;
            tokens.push_back(function.substr(i, substringLength));
        }
        if(found)
        {
            i+=substringLength-1;
            if(DEBUG==true)
                cout << '\n';
        }
        else
        {
            cout << "Failed at: " << i << endl;
            return vector<string>();
        }

        i++;
    }
    return applyTokenRules(tokens);
}

vector<string> applyTokenRules(vector<string> tokens)
{
    bool visited[tokens.size() + 10];
    memset(visited, 0, tokens.size() + 10);
    vector<string> nTokens;
    int dummyLen=0;
    for(int i=0;i<tokens.size();i++) {
        string workingValue = tokens[i];

        if (workingValue[0] == '-' && workingValue.length() == 1
            && (isOperand(tokens[i + 1].c_str(), 0, dummyLen) || isMathFunction(tokens[i+1],0,dummyLen))
            && ((i-1>=0 && !(isOperand(tokens[i-1],0,dummyLen) || isMathFunction(tokens[i-1],1,dummyLen))) || i-1<0)
            && (i-1>=0 && tokens[i-1][tokens[i-1].length()-1]!=')' && tokens[i-1][tokens[i-1].length()-1]!=']' )
            && !visited[i])
        {
            if (DEBUG == true)
                cout << "[TokenizeRules] Found unary minus at " << i << endl;
            if(isMathFunction(tokens[i+1],1,dummyLen))
                nTokens.push_back(tokens[i]+tokens[i+1].substr(1, tokens[i+1].length()-1));
            else
                nTokens.push_back(tokens[i] + tokens[i + 1]);
            visited[i] = 1;
            visited[i + 1] = 1;
        } else if (workingValue[0] == '|' && workingValue.length() != 1)
        {
            if (DEBUG == true)
                cout << "[TokenizeRules] Found math function: " << workingValue << endl;
            if(!visited[i])
            {
                nTokens.push_back(workingValue.substr(1, workingValue.length()-1));
                visited[i]=1;
            }
            nTokens.push_back("[");
            visited[i+1]=1;
            //going to the end of the function
            int endMathFunc = getClosingParenthesis(tokens, i+1);
            if(endMathFunc<tokens.size() && tokens[endMathFunc][0]==')')
                tokens[endMathFunc]=string("]");
            if(endMathFunc>=tokens.size())
                return vector<string>();
        }
        else if(workingValue[0]==',' && workingValue.length()==1)
        {
            if (DEBUG == true)
                cout << "[TokenizeRules] Found a function with arity 2 or greater" << endl;
            nTokens.push_back("|");
            visited[1]=1;
        }
        else if(!visited[i])
        {
            nTokens.push_back(workingValue);
            visited[i]=1;
        }

    }
    return nTokens;
}


/*
 * Helper functions
 */
bool isOperator(string f, int i, int& len)
{
    if(!strchr(operators, f[i]))
        return false;
    len=1;
    return true;
}
bool isOperand(string f, int i, int& len)
{
    //get the length first
    int dummyLen=0,start=i;
    while(i<f.length() && !isOperator(f,i, dummyLen))
        i++;
    int finish=i;
    // The are only digits: 10.20, 10, 20131
    // There is something like: 10x which can be translated to 10*x
    // There is x10 which can be translated to x*10
    //From this we get the following allowed symbols: DIGITS, 1 ALPHA and .
    bool foundComma=false, foundAlpha=false;
    // Treat the case in which we have -something
    if(f[start]=='-' && f.length()!=1)
        start++;
    for(int i=start;i<finish;i++)
    {
        if(f[i]=='.')
        {
            // We can't allow something like 10..x
            if(foundComma)
                return false;
            // We also can't allow .01
            if(i==start)
                return false;
            if(isalpha(f[i-1]))
                return false;

            foundComma=true;
        }
        if(isalpha(f[i]))
        {
            // There is only a variable: x
            if(foundAlpha)
                return false;
            if(foundComma)
            {
                // We can't allow 10.x but we can allow 10.2x because it is 10.2*x
                if(f[i-1]=='.')
                    return false;
            }
            foundAlpha=true;
        }
        if(!isalpha(f[i]) && !isdigit(f[i]) && f[i]!='.')
            return false;
    }
    len = finish-start;
    if(len==0)
        return false;
    return true;
}

bool isMathFunction(string f, int i, int& len)
{
    int start = i;
    if(f[i]=='|')
        start++;
    while(i<f.length() && f[i]!='(')
        i++;
    int finish = i;
    len = finish-start;
    string probableMathFunction = f.substr(start, len);
    for(int i=0;i<mathFunctionsCounter;i++)
        if(!strcmp(mathematicalFunctions[i],probableMathFunction.c_str()))
            return true;
    return false;
}
//If we are inside of a function check where it ends
int getClosingParenthesis(vector<string> tokens, int poz)
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