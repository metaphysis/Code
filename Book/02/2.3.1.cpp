#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;

map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
};

int calculate(string postfix)
{
    stack<int> operands;
    for (auto c : postfix)
    {
        if (isdigit(c)) operands.push(c - '0');
        else
        {
            int second = operands.top(); operands.pop();
            int first = operands.top(); operands.pop();

            if (c == '+') operands.push(first + second);
            if (c == '-') operands.push(first - second);
            if (c == '*') operands.push(first * second);
            if (c == '/') operands.push(first / second);
        }
    }
    return operands.top();
}

bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

string toPostfix(string infix)
{
    stack<char> operands, operators;

    for (auto c : infix)
    {
        if (isdigit(c))
        {
            operands.push(c);
            continue;
        }

        if (c == '(')
        {
            operators.push(c);
            continue;
        }

        if (c == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                operands.push(operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();

            continue;
        }

        if (operators.empty() || operators.top() == '(' ||
            !lessPriority(c, operators.top()))
        {
            operators.push(c);
        }
        else
        {
            while (!operators.empty() && lessPriority(c, operators.top()))
            {
                operands.push(operators.top());
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }

    string postfix;
    while (!operands.empty())
    {
        postfix = operands.top() + postfix;
        operands.pop();
    }

    return postfix;
}

int main(int argc, char *argv[])
{
    string infix;
    while (getline(cin, infix), infix.length() > 0)
        cout << calculate(toPostfix(infix)) << endl;

    return 0;
}
