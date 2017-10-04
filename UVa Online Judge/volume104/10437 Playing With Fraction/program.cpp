// Playing With Fraction
// UVa ID: 10437
// Verdict: Accepted
// Submission Date: 2017-07-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// 定义运算符的优先级顺序，值越高，优先级越高。在栈中，括号的优先级最小。
map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
};

#undef DEBUG

const int OPERATOR = 0, NUMBER = 1;

long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

struct fraction
{
    long long numerator, denominator;
    
    void reduce()
    {
        if (numerator != 0 && denominator != 0)
        {
            long long g = gcd(abs(numerator), abs(denominator));
            numerator /= g, denominator /= g;
        }

        if (numerator == 0 && denominator != 0) denominator = 1;
    }
    
    fraction operator+(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator + denominator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.reduce();
        return r;
    }
    
    fraction operator-(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator - denominator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.reduce();
        return r;
    }
    
    fraction operator*(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.reduce();
        return r;
    }
    
    fraction operator/(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator;
        r.denominator = denominator * f.numerator;
        r.reduce();
        return r;
    }
};

struct symbol
{
    int token, category;
    fraction f;
};

vector<symbol> symbols;

symbol calculate()
{
    symbol empty = (symbol){0, NUMBER, (fraction){0, 0}};

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
            
            if (a.f.denominator == 0 || b.f.denominator == 0) return empty;
            if (s.token == '/' && a.f.numerator == 0) return empty;

            switch (s.token)
            {
                case '+':
                    operands.push((symbol){0, NUMBER, b.f + a.f});
                    break;
                case '-':
                    operands.push((symbol){0, NUMBER, b.f - a.f});
                    break;
                case '*':
                    operands.push((symbol){0, NUMBER, b.f * a.f});
                    break;
                case '/':
                    operands.push((symbol){0, NUMBER, b.f / a.f});
                    break;
            }
            
            #ifdef DEBUG
            s = operands.top();
            cout << s.f.numerator << '|' << s.f.denominator << '\n';
            #endif
        }
    }

    return operands.top();
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

        if (s.category == NUMBER) operands.push(s);
        else
        {
            if (s.token == '(') operators.push(s);
            else if (s.token == ')')
            {
                while (!operators.empty() && operators.top().token != '(')
                {
                    operands.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty()) operators.pop();
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
    
    #ifdef DEBUG
    for (auto s : symbols)
    {
        if (s.category == OPERATOR) cout << s.token << ' ';
        else cout << s.f.numerator << '|' << s.f.denominator << ' ';
    }
    cout << '\n';
    #endif
}

void parse(string line)
{
    symbols.clear();

    int index = 0;
    while (index < line.length())
    {
        if (line[index] >= '0' && line[index] <= '9')
        {
            long long numerator = 0, denominator = 1;
            while (index < line.length() && line[index] >= '0' && line[index] <= '9')
            {
                numerator = numerator * 10 + line[index] - '0';
                index++;
            }
            
            if (index < line.length() && line[index] == '|')
            {
                denominator = 0;
                index++;
                while (index < line.length() && line[index] >= '0' && line[index] <= '9')
                {
                    denominator = denominator * 10 + line[index] - '0';
                    index++;
                }
            }

            symbols.push_back((symbol){0, NUMBER, (fraction){numerator, denominator}});
        }
        else
        {
            symbols.push_back((symbol){line[index], OPERATOR, (fraction){0, 0}});
            index++;            
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        string expression;
        for (int i = 0; i < line.length(); i++)
            if (!isblank(line[i]))
                expression += line[i];

        parse(expression);
        infixToPostfix();

        symbol r = calculate();
        r.f.reduce();
        
        if (r.f.denominator == 0) cout << "INVALID\n";
        else
        {
            cout << r.f.numerator;
            if (r.f.denominator > 1) cout << '|' << r.f.denominator;
            cout << '\n';
        }
    }
    
	return 0;
}
