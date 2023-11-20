#include "evaluate.h"

bool isOperator(const char c)
{
    return c == '+' || c == '-' || c == '&';
};

bool isOperator(const std::string &s)
{
    return s.length() == 1 && isOperator(s[0]);
};

int getPriority(const char c)
{
    if (c == '&')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
};

bool checkParentheses(const std::string &str)
{
    std::stack<char> parenthesesStack;

    for (char c : str)
    {
        if (c == '(')
        {
            parenthesesStack.push(c);
        }
        else if (c == ')')
        {
            if (parenthesesStack.empty() || parenthesesStack.top() != '(')
            {
                return false; // Unmatched right parenthesis
            }
            parenthesesStack.pop();
        }
    }

    return parenthesesStack.empty(); // If stack is empty, all parentheses are matched
}

std::vector<std::string> infixToPostfix(const std::string &infix)
{
    if (infix.empty())
    {
        throw "Error expression!!!";
    }

    if (isOperator(infix.front()) || isOperator(infix.back()))
    {
        throw "Error expression!!!";
    }

    if (!checkParentheses(infix))
    {
        throw "Error expression!!!";
    }

    std::vector<std::string> postfixExpression;
    std::stack<char> operatorStack;
    std::string operand;

    for (char c : infix)
    {
        if (c == ' ')
        {
            continue; // 跳过空格
        }
        else if (c == '(')
        {
            if (operand != "")
            {
                postfixExpression.push_back(operand);
                operand = "";
            }

            operatorStack.push(c);
        }
        else if (c == ')')
        {
            if (operand != "")
            {
                postfixExpression.push_back(operand);
                operand = "";
            }

            while (!operatorStack.empty() && operatorStack.top() != '(')
            {
                std::string op(1, operatorStack.top());
                postfixExpression.push_back(op);
                operatorStack.pop();
            }
            operatorStack.pop(); // 弹出左括号
        }
        else if (isOperator(c))
        {
            if (operand != "")
            {
                postfixExpression.push_back(operand);
                operand = "";
            }

            while (!operatorStack.empty() && getPriority(operatorStack.top()) >= getPriority(c))
            {
                std::string op(1, operatorStack.top());
                postfixExpression.push_back(op);
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
        else
        {
            operand += c;
        }
    }

    if (operand != "")
    {
        postfixExpression.push_back(operand);
    }

    while (!operatorStack.empty())
    {
        std::string op(1, operatorStack.top());
        postfixExpression.push_back(op);
        operatorStack.pop();
    }

    return postfixExpression;
}