#include "postfixValidator.h"


//transformation from infix to postfix
vector<string> getPostfix(vector<string> tokens)
{
    vector<string> postfix;
    stack<string> s;
    int dummy=0;
    for(auto t: tokens)
    {
        //reusing the function declared in `tokenize`
        if(t[0]=='[' && t.length()==1)
            s.push(t);
        else if(isMathematicalFunction(t))
        {
            if(DEBUG==true)
                cout << "[POSTFIX] Found the math function `" << t << "` and added it to the stack!\n";
            s.push(t);
        }
        else if(isOperand(t,0,dummy))
        {
            int getBreakpoint = splitDigitFromAlpha(t);
            //handling the cases like 10.20x, 10x, x10, x10.20
            if(getBreakpoint<t.length() && getBreakpoint)
            {
                if(DEBUG==true)
                {
                    cout << "[POSTFIX] We have a two way split for " << t << " at position " << getBreakpoint << endl;
                    cout << "[POSTFIX] Found operand " << t.substr(0, getBreakpoint) << " and adding it to the vector\n";
                    cout << "[POSTFIX] Found operand " << t.substr(getBreakpoint, t.length()) << " and adding it to the vector\n";
                }
                postfix.push_back(t.substr(0, getBreakpoint));
                postfix.push_back(t.substr(getBreakpoint, t.length()));
                postfix.push_back("*");
            }
                //normal cases like 10,x,10.20
            else
            {
                if(DEBUG==true)
                    cout << "[POSTFIX] Found operand " << t << " and adding it to the vector\n";
                postfix.push_back(t);
            }
        }
        else if(t[0]=='(' && t.length()==1)
            s.push(t);
        //check for normal parenthesis
        else if(t[0]==')' && t.length()==1)
        {
            while(!s.empty() && s.top()[0]!='(')
            {
                postfix.push_back(s.top());
                s.pop();
            }
            if(!s.empty())
                s.pop();
        }
        //check for math function parenthesis
        else if(t[0]==']' && t.length()==1)
        {
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
        else if(isOperator(t, 0, dummy))
        {
            if(DEBUG==true)
                cout << "[POSTFIX] Found the operator " << t << " now removing from the stack all operators that have lower priority!\n";
            //we check for the priority, but also we need to make sure that we don't encounter a math function there.
            while(!s.empty() && s.top()[0]!='(' && s.top()[0]!='[' && getPriority(s.top())>=getPriority(t) && (getPriority(s.top())>=0 && getPriority(t)>=0))
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(t);
        }

    }
    while(!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}

//check if we need to handle a math function
bool isMathematicalFunction(string t)
{
    if(t[0]=='-')
        t=t.substr(1, t.length()-1);
    if(t.length()<=2)
        return false;
    for(int i=0;i<mathFunctionsCounter;i++)
        if(!strcmp(mathematicalFunctions[i], t.c_str()))
            return true;
    return false;
}

//check if we need to handle an operator
bool isOperator(string t)
{

    if(t.length()!=1)
        return 0;
    char op = t[0];
    if(op=='[' || op=='(')
        return false;
    return (strchr(operatorsPostfix, op)!=NULL);
}

//treat the cases like 10x, 10.20x, x10, x10.20
int splitDigitFromAlpha(string t)
{
    if(isalpha(t[0]))
        return 1;
    int i=0;
    if(t[i]=='-')
        i++;
    while(i<t.length() && (isdigit(t[i]) || t[i]=='.'))
        i++;
    if(t[0]=='-')
        i++;
    return i;
}
//decide in which order we put operators in the postfix vector
int getPriority(string t)
{
    if(t.length()!=1)
        return -1;
    char op = t[0];
    if(isalpha(op) || isdigit(op))
        return -2;
    for(int i=0;i<maxPriority;i++)
        if(strchr(priority[i], op))
            return i;
    return -2;
}
//get the arity of an operator or mathfunction
int getArity(string t)
{
    if(isMathematicalFunction(t))
    {
        for(int i=0;i<maxArity;i++)
            if(!strcmp(mathFunctionsWithArity2[i], t.c_str()))
                return 2;
        return 1;
    }
    return 2;
}

//check the validity of the function
bool validatePostix(vector<string> postfix)
{
    int counter=0,dummy=0;
    for(auto i: postfix)
    {
        if((isOperator(i) && i.length()==1 ) || isMathematicalFunction(i))
        {
            int arity = getArity(i);
            if(DEBUG==true) cout << "[VALIDATION] Found the operator " << i << " with arity " << arity << endl;
            if(arity==-1)
                return false;
            counter-=arity;
            counter++;
        }else if(isOperand(i,0,dummy))
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
