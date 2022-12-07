#include "BigInt.h"
#include <stack>
#include <string>

// Convert an expression from infix format to postfix format
std::string infixToPostfix(const std::string &infix){
    std::stack<char> opStack;
    std::string postFixString = "";
    // Loop through the vector (one character at a time).
    for (unsigned int i = 0; i < infix.length(); i++) {
        if(isdigit(infix[i]) || isspace(infix[i])) 
            postFixString += infix[i]; //append it to our postfix string.
        else if(infix[i]=='+' ||infix[i]=='*' ||infix[i]=='-') 
        {
            char curOp = infix[i]; //this is current operator
            while((!opStack.empty() && opStack.top() != '(' && ((curOp ==  opStack.top()) || (curOp == '+' && opStack.top() == '-') || (curOp == '-' && opStack.top() == '+')|| ( curOp > opStack.top()))))
            {
                postFixString += opStack.top(); // append the top operator from stack to postFixString
                opStack.pop();
            }
            opStack.push(infix[i]);//Push current operator to the opStack
        } else if (infix[i]=='(') 
            opStack.push(infix[i]); // Push open parenthesis onto our stack.
        else if(infix[i]==')') 
        {
            // When we reach a closing one, start popping off operators
            // until we run into an opening parenthesis.
            while (!opStack.empty()) {
                if (opStack.top() == '(') {
                    opStack.pop();
                    break;
                } else {
                    postFixString += opStack.top();
                    opStack.pop(); 
                }
            }
        }
    }
    // If there is any remaining operators left on the stack
    // Pop them off and append them onto the postFixString one by one.
    while (!opStack.empty())
    {
        postFixString += opStack.top();
        opStack.pop();
    }
    return postFixString;
}

ds::BigInt evaluatePostfix(const std::string &postfix){
std::stack<ds::BigInt> stk;
ds::BigInt substring("");
for(unsigned int i=0; i<postfix.length();i++)
{
// If the char is a white space of any kind (' ', '\t', '\n'), skip to the next char.
    if(isspace(postfix[i]))
        continue;
// If the char is a digit, continue reading the rest of the number and push that substring onto stack.
    if(isdigit(postfix[i]))
    {
        while(isdigit(postfix[i]))
        {
            substring.digits.push_back(postfix[i]-'0');
            i++;
        }
        stk.push(substring);
        substring.digits.clear();
    }
// If the char is an operation symbol ('+', '-', '*'), pop two elements from the stack and apply the operation on the two elements.
// Push the result onto the stack.
    if(postfix[i]=='+' || postfix[i]=='-' || postfix[i]=='*')
    {
        ds::BigInt This("");
        ds::BigInt Other("");
        ds::BigInt Res("");
        This=stk.top();
        stk.pop();
        Other=stk.top();
        stk.pop();
        switch(postfix[i])
        {
            case '+':
                Res=This+Other;
                stk.push(Res);
                Res.digits.clear();
                This.digits.clear();
                break;
            case '*':
                Res=This*Other;
                stk.push(Res);
                Res.digits.clear();
                This.digits.clear();
                break;
            case '-':
                Res=This-Other;
                stk.push(Res);
                Res.digits.clear();
                This.digits.clear();
                break;
        }
    }
// When reaching the end of the expression, there should be only one value in the stack.
//Return this value.
}
//Clear all unwanted zeros. 
while (stk.top().digits.at(0)==0 && stk.top().digits.size()>1)
{
    stk.top().digits.erase(stk.top().digits.begin());
}

return stk.top();
}