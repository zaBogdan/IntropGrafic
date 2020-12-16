#include "validate.h"


bool checkValidity(vector<string> postfix)
{
    int counter=0;
    for(auto i: postfix)
    {
        if((isOperator(i[0]) && i.length()==1 ) || isMathematicalFunction(i))
        {
            int arity = getArity(i);
            if(DEBUG==true) cout << "[VALIDATION] Found the operator " << i << " with arity " << arity << endl;
            if(arity==-1)
                return false;
            counter-=arity;
            counter++;
        }else if(isOperand(i))
        {
            if(DEBUG==true) cout << "[VALIDATION] Found the operand " << i << endl;
            counter++;
        }
        else
            return false;

        if(counter<0)
            return false;
    }
    if(counter==1)
        return true;
    return false;
}

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
            int poz = digitVal(token);
            if(poz==-1)
                postfix.push_back(token);
            else
            {
                postfix.push_back(token.substr(0, poz));
                postfix.push_back(token.substr(poz, token.length()-poz));
                postfix.push_back("*");
            }
        }
        else {
            //check for normal pharanthesis
            if(token[0]==')')
            {
                if(DEBUG==true) cout << "[POSTFIX] Found closing parathesis \n";
                while(!s.empty() && s.top()[0]!='(')
                {
                    postfix.push_back(s.top());
                    s.pop();
                }
                if(!s.empty())
                    s.pop();
            }
            //check for math functions
            else if(token[0]==']')
            {
                if(DEBUG==true) cout << "[POSTFIX] Found closing math function \n";
                while(!s.empty() && s.top()[0]!='[')
                {
                    postfix.push_back(s.top());
                    s.pop();
                }
                if(s.size()>=2)
                {
                    s.pop();
                    //get the math function associated.
                    postfix.push_back(s.top());
                    s.pop();
                }
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
int digitVal(string token)
{
    int poz = 0;
    if(token[poz]=='-')
        poz++;
    if(!isdigit(token[poz]))
        return -1;
    while(isdigit(token[poz]) && poz<token.length())
        poz++;
    if(poz==token.length())
        return -1;
    return poz;
}
int getArity(string i)
{
    if(strchr(operat,i[0]))
        return 2;
    for(auto stri: arity2Op)
        if(!i.compare(stri))
            return 2;
    if(strchr("[()]",i[0]))
        return -1;
    return 1;
}