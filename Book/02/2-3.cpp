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
    stack<int> result;
    for (auto c : postfix)
    {
        if (isdigit(c))
        {
            result.push(c - '0');
        }
        else
        {

            int second = result.top(); result.pop();
            int first = result.top(); result.pop();

            if (c == '+') result.push(first + second);
            if (c == '-') result.push(first - second);
            if (c == '*') result.push(first * second);
            if (c == '/') result.push(first / second);
        }
    }
    return result.top();
}

bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

string toPostfix(string infix)
{
    stack<char> operands;
    stack<char> operators;

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
