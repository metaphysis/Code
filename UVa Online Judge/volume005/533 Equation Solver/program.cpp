// Equation Solver
// UVa ID: 533
// Verdict: Accepted
// Submission Date: 2017-04-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int PLUS = 0, MINUS = 1, MULTIPLY = 2, X = 3, 
    LEFT_BRACE = 4, RIGHT_BRACE = 5, NUMBER = 6;

struct token
{
    int id, coefficient, constant;
};

map<int, int> priority = {{0, 1}, {1, 1}, {2, 2}, {4, 0}, {5, 0}};

bool lessPriority(token previous, token next)
{
    return priority[previous.id] <= priority[next.id];
}

vector<token> toPostfix(vector<token> infix)
{
    stack<token> operands, operators;

    for (auto t : infix)
    {
        if (t.id == NUMBER || t.id == X)
        {
            operands.push(t);
            continue;
        }

        if (t.id == LEFT_BRACE)
        {
            operators.push(t);
            continue;
        }

        if (t.id == RIGHT_BRACE)
        {
            while (!operators.empty() && operators.top().id != LEFT_BRACE)
            {
                operands.push(operators.top());
                operators.pop();
            }
            if (!operators.empty()) operators.pop();

            continue;
        }

        if (operators.empty() || operators.top().id == LEFT_BRACE || !lessPriority(t, operators.top()))
        {
            operators.push(t);
        }
        else
        {
            while (!operators.empty() && lessPriority(t, operators.top()))
            {
                operands.push(operators.top());
                operators.pop();
            }
            operators.push(t);
        }
    }

    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }

    vector<token> postfix;
    while (!operands.empty())
    {
        postfix.insert(postfix.begin(), operands.top());
        operands.pop();
    }

    return postfix;
}

void parse(string expression, int &x, int &constant)
{
    vector<token> infix;
    for (int i = 0; i < expression.length(); i++)
    {
        if (isblank(expression[i])) continue;

        if (expression[i] == '+') infix.push_back(token{PLUS, 0, 0});
        else if (expression[i] == '-') infix.push_back(token{MINUS, 0, 0});
        else if (expression[i] == '*') infix.push_back(token{MULTIPLY, 0, 0});
        else if (expression[i] == '(') infix.push_back(token{LEFT_BRACE, 0, 0});
        else if (expression[i] == ')') infix.push_back(token{RIGHT_BRACE, 0, 0});
        else if (expression[i] == 'x') infix.push_back(token{X, 1, 0});
        else
        {
            int number = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                number = number * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            infix.push_back(token{NUMBER, 0, number});
        }
    }

    vector<token> postfix = toPostfix(infix);

    stack<token> result;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i].id == NUMBER || postfix[i].id == X)
        {
            result.push(postfix[i]);
        }
        else
        {
            token b = result.top(); result.pop();
            token a = result.top(); result.pop();

            if (postfix[i].id == PLUS)
            {
                int v1 = a.coefficient + b.coefficient;
                int v2 = a.constant + b.constant;
                
                if (v1 == 0)
                    result.push(token{NUMBER, v1, v2});
                else
                    result.push(token{X, v1, v2});
            }
            else if (postfix[i].id == MINUS)
            {
                int v1 = a.coefficient - b.coefficient;
                int v2 = a.constant - b.constant;
                
                if (v1 == 0)
                    result.push(token{NUMBER, v1, v2});
                else
                    result.push(token{X, v1, v2});
            }
            else
            {
                if (a.id == NUMBER && b.id == NUMBER)
                {
                    int v1 = a.coefficient + b.coefficient;
                    int v2 = a.constant * b.constant;
                
                    result.push(token{NUMBER, 0, v2});
                }
                else
                {
                    int v1 = a.constant * b.coefficient + a.coefficient * b.constant;
                    int v2 = a.constant * b.constant;
                    
                    result.push(token{X, v1, v2});
                }
            }
        }
    }

    x = result.top().coefficient, constant = result.top().constant;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    int cases = 0;

    while (getline(cin, line))
    {
        int left_x = 0, left_constant = 0, right_x = 0, right_constant = 0;

        int equation = line.find('=');

        parse(line.substr(0, equation), left_x, left_constant);
        parse(line.substr(equation + 1), right_x, right_constant);

        left_x -= right_x, right_constant -= left_constant;

        if (cases++ > 0) cout << '\n';
        cout << "Equation #" << cases << '\n';

        if (left_x == 0) 
        {
            if (right_constant == 0)
                cout << "Infinitely many solutions.\n";
            else
                cout << "No solution.\n";
        }
        else
        {
            cout << "x = ";
            cout << fixed << setprecision(6);
            cout << (double)right_constant / (double)left_x << '\n';
        }
    }

    return 0;
}
