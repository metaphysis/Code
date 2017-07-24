// Grammar Evaluation
// UVa ID: 622
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

using namespace std;

// 定义运算符的优先级顺序，值越高，优先级越高。在栈中，括号的优先级最小。
map<char, int> priority = {
    {'+', 1}, {'*', 2}, {'(', 0}, {')', 0}
};

const int OPERATOR = 0, NUMBER = 1;

struct symbol
{
    int token, category;
};

vector<symbol> symbols;

int calculate()
{
    stack<symbol> operands;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == NUMBER)
            operands.push(s);
        else
        {
            symbol a = operands.top(); operands.pop();
            symbol b = operands.top(); operands.pop();
                
            switch (s.token)
            {
                case '+':
                    operands.push((symbol){a.token + b.token, NUMBER});
                    break;
                case '*':
                    operands.push((symbol){a.token * b.token, NUMBER});
                    break;
            }
        }
    }
    
    return operands.top().token;
}

// 比较运算符在栈中的优先级顺序。
bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

void infixToPostfix()
{  
    stack<symbol> operands, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
            
        if (s.category == NUMBER)
            operands.push(s);
        else
        {
            if (s.token == '(')
                operators.push(s);
            else if (s.token == ')')
            {
                while (!operators.empty() && operators.top().token != '(')
                {
                    operands.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {                
                if (operators.empty() || operators.top().token == '(' || !lessPriority(s.token, operators.top().token))
                    operators.push(s);
                else
                {
                    while (!operators.empty() && lessPriority(s.token, operators.top().token))
                    {
                        operands.push(operators.top());
                        operators.pop();
                    }
                    operators.push(s);
                }
            }
        }
    }

    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }
    
    symbols.clear();
    while (!operands.empty())
    {
        symbols.insert(symbols.begin(), operands.top());
        operands.pop();
    }
}

bool validate(string &line)
{
    string next;
    int i = 0;
    
    while (i < line.length())
    {
        if (isdigit(line[i]))
        {
            next += 'd';
            while (i < line.length() && isdigit(line[i]))
                i++;
        }
        else if (line[i] == '(' || line[i] == ')' || line[i] == '+' || line[i] == '*')
        {
            next += line[i];
            i++;
        }
        else
            return false;
    }
    
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < next.length(); i++)
        {
            if (((next[i] == '+' || next[i] == '*') && i > 0 && next[i - 1] == 'd' && (i + 1) < next.length() && next[i + 1] == 'd') ||
                (next[i] == 'd' && i > 0 && next[i - 1] == '(' && (i + 1) < next.length() && next[i + 1] == ')'))
            {
                next[i - 1] = 'd';
                next.erase(next.begin() + i);
                next.erase(next.begin() + i);
                updated = true;
                break;
            }
        }
        
        if (!updated)
            break;
    }        
    
    return next.length() == 1;
}

void parse(string &line)
{
    symbols.clear();

    int index = 0;
    while (index < line.length())
    {
        if (line[index] >= '0' && line[index] <= '9')
        {
            int number = 0;
            while (index < line.length() && line[index] >= '0' && line[index] <= '9')
            {
                number = number * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){number, NUMBER});
        }
        else if (line[index] == '(' || line[index] == ')' || line[index] == '+' || line[index] == '*')
        {
            symbols.push_back((symbol){line[index], OPERATOR});
            index++;            
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);

        if (validate(line))
        {
            parse(line);
            infixToPostfix();
            cout << calculate() << '\n';
        }
        else
            cout << "ERROR\n";
    }
    
	return 0;
}
