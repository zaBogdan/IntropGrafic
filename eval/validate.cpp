#include "validate.h"

vector<string> getPostfix(vector<string> tokens)
{
    vector<string> postfix;
    stack<string> s;
    for(auto token: tokens)
    {
        if(isMathematicalFunction(token))
        {
            if(DEBUG==true) cout << "[POSTFIX] Adding math function " << token << " to the STACK \n";
            s.push(token);
        }
        else if(isOperand(token))
        {
            if(DEBUG==true) cout << "[POSTFIX] Adding the operand " << token << " to the VECTOR \n";
            postfix.push_back(token);
        }
        else {
            //check for normal pharanthesis
            if(token[0]==')')
            {
                if(DEBUG==true) cout << "[POSTFIX] Found closing parathesis \n";
                while(s.top()[0]!='(' && !s.empty())
                {
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.pop();
            }
            //check for math functions
            else if(token[0]==']')
            {
                if(DEBUG==true) cout << "[POSTFIX] Found closing math function \n";
                while(s.top()[0]!='[' && !s.empty())
                {
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.pop();
                //get the math function associated.
                postfix.push_back(s.top());
                s.pop();
            }
            //now we are 100% dealing with operands
            else if(isOperator(token[0])){
                if(DEBUG==true) cout << "[POSTFIX] Adding operator " << token << " to the stack \n";
                while(!s.empty() && s.top()[0]!='(' && getPriority(s.top()[0])>=getPriority(token[0]) &&(getPriority(s.top()[0])>=0 && getPriority(token[0])>=0))
                {
                    postfix.push_back(s.top());
                    s.pop();
                }
                s.push(token);
            }
        }
    }
    while(!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }
    if(DEBUG==true)
    {
        cout << "[POSTFIX] Transformation from tokens to : \n";
        for(auto i:postfix)
            cout << i << ", ";
        cout << endl;
    }

    return postfix;
}

bool isOperand(string f)
{
    int startPos=0;
    int foundComma = false;
    if(f[startPos]=='-')
        startPos++;
    for(int i=startPos;i<f.length();i++)
    {
        if(!isalpha(f[i]) && !isdigit(f[i]))
        {
            if(f[i]==',' && foundComma)
                return false;
            else if(f[i]==',' && !foundComma)
                foundComma=true;
            else
                return false;
        }
    }
    return true;
}
bool isOperator(char oper)
{
    if(oper=='[' || oper=='(')
        return true;
    return (strchr(operat, oper)!=NULL);
}

int getPriority(char oper)
{
    if(isalpha(oper) || isdigit(oper))
        return -2;
    for(int i=0;i<maxPriority;i++)
        if(strchr(priority[i], oper))
            return i;
    return -1;
}