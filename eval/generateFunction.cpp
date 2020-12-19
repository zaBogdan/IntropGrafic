#include "generateFunction.h"


string postfixToCPP(vector<string> postfix)
{
    stack<string> s;
    string cppValue="";

    for(int i=0;i<postfix.size();i++) {
        if(isOperator(postfix[i][0]) && postfix[i].length()==1)
        {
            string rightSide = s.top();
            s.pop();
            string leftSide = s.top();
            s.pop();
            string buildString = "";
            if(postfix[i][0]=='^')
            {
                if(leftSide[0]=='e' && leftSide.length()==1)
                    buildString = "exp("+rightSide+")";
                else
                    buildString = "pow("+leftSide+","+rightSide+")";
            }
            else
            {
                buildString = leftSide+postfix[i]+rightSide;
            }
            s.push(buildString);
        }else if(isMathematicalFunction(postfix[i]))
        {
            string buildString = "";
            string value = s.top();
            s.pop();
            buildString = postfix[i]+"("+value+")";
            s.push(buildString);
        }else if(isOperand(postfix[i]))
        {
            s.push(postfix[i]);
        }
    }
    cout << s.top();
    cout << endl;
    return 0;
}