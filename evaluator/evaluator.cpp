#include "evaluator.h"
unordered_map<double, double> values;

vector<string> buildAndValidatePostfix(string func)
{
    cout << "[EVAL] The function is: " << func << endl;
    vector<string> tokenizedFunction = tokenizeFunction(func);
    if(tokenizedFunction.empty())
    {
        cout << "[EVAL] The function can't be tokenized!";
        return vector<string>();
    }
    cout << "[EVAL] Tokenized function is: ";
    for(auto i: tokenizedFunction)
        cout << i << ", ";
    cout << endl;
    vector<string> postfix = getPostfix(tokenizedFunction);
    if(postfix.empty())
    {
        cout << "[EVAL] The function can't be transformed into postfix!";
        return vector<string>();
    }
    cout << "[EVAL] The postfix version of this function is: ";
    for(auto i: postfix)
        cout << i << ", ";
    cout << endl;

    bool valid = validatePostix(postfix);

    if(!valid)
    {
        cout << "[EVAL] This function isn't valid! Please try again!\n";
        return vector<string>();
    }
    cout << "[EVAL] The postfix notation is valid and ready to be evaluated!\n";
    return postfix;
}

string getCPPNotation(vector<string> postfix)
{
    stack<string> s;
    int dummy=0;

    for(int i=0;i<postfix.size();i++) {
        if(isOperator(postfix[i],0,dummy) && postfix[i].length()==1)
        {
            string rightSide = s.top();
            s.pop();
            string leftSide = s.top();
            s.pop();
            string buildString = "";
            char op = postfix[i][0];
            if(op=='^')
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
            int arity = getArity(postfix[i]);
            if(arity==1)
            {
                string value = s.top();
                s.pop();
                buildString = postfix[i]+"("+value+")";
                s.push(buildString);
            }else
            {
                string right = s.top();
                s.pop();
                string left = s.top();
                s.pop();
                buildString = postfix[i]+"("+left+","+right+")";
                s.push(buildString);
            }
        }else if(isOperand(postfix[i],0,dummy))
        {
            s.push(postfix[i]);
        }
    }
    return s.top();
}

double getValueFromPostfix(vector<string> postfix, double x)
{
    if(values[x])
    {
        if(DEBUG==true)
            cout << "[Caching] Already calculed value for " << x << " returning.\n";
        return values[x];
    }

    map<string, function<double(double,double)>> funcs2 = {
            {"pow", [](double x, double y){return pow(x,y);}},
            {"fmod", [](double x,double y){return fmod(x,y);}},
            {"fdim", [](double x,double y){return fdim(x,y);}},
            {"fmax", [](double x,double y){return fmax(x,y);}},
            {"fmin", [](double x,double y){return fmin(x,y);}},
            {"hypot", [](double x,double y){return hypot(x,y);}},
            {"+", [](double x,double y){return (x+y);}},
            {"-", [](double x,double y){return (x-y);}},
            {"/", [](double x,double y){if(y==0) return 0.0; return (x/y);}},
            {"*", [](double x,double y){return (x*y);}},
            {"^", [](double x,double y){return pow(x,y);}},
    };
    map<string, function<double(double)>> funcs = {
            {"expm1", [](double x){return expm1(x);}},
            {"cos", [](double x){return cos(x);}},
            {"asin", [](double x){return asin(x);}},
            {"sinh", [](double x){return sinh(x);}},
            {"tan", [](double x){return tan(x);}},
            {"acos", [](double x){return acos(x);}},
            {"exp", [](double x){return exp(x);}},
            {"sin", [](double x){return sin(x);}},
            {"fabs", [](double x){return fabs(x);}},
            {"sqrt", [](double x){return sqrt(x);}},
            {"ceil", [](double x){return ceil(x);}},
            {"cosh", [](double x){return cosh(x);}},
            {"atan", [](double x){return atan(x);}},
            {"cbrt", [](double x){return cbrt(x);}},
            {"abs", [](double x){return abs(x);}},
            {"tanh", [](double x){return tanh(x);}},
            {"log", [](double x){if(x>0) return log(x); return 0.0;}},
            {"floor", [](double x){return floor(x);}}
    };
    int dummyVal=0;
    stack <double> s;
    for(int i=0;i<postfix.size();i++)
    {
        string val = postfix[i];
        if(val.find("x")!=string::npos)
        {

            double aval = x;
            if(val[0]=='-')
                aval = -aval;
            s.push(aval);
        }else if((isOperator(val,0, dummyVal) && postfix[i].length()==1) || isMathematicalFunction(val))
        {
            int arity = getArity(val);
            if(arity==1)
            {
                double aval = s.top();
                s.pop();
                s.push(funcs[val](aval));
            }
            if(arity==2)
            {
                double right = s.top();
                s.pop();
                double left = s.top();
                s.pop();
                if(val=="^" && left==M_E)
                    s.push(funcs["exp"](right));
                if(val=="^" && left==M_E && right<0)
                    s.push(funcs["expm1"](right));
                else
                    s.push(funcs2[val](left,right));
            }
        }
        else
        {
            double aval = atof(val.c_str());
            if(val[0]=='e' && val.length()==1)
                aval = M_E;
            if(val.length()==1 && aval==0)
                aval=1;
            s.push(aval);
        }
    }
    if(DEBUG==true)
        cout << "[Caching] New value added for " << x << " to the vector!\n";
    values[x] = s.top();
    return s.top();
}