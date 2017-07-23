// Playing With Fraction
// UVa ID: 10437
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

typedef unsigned long long ull;

const int OPERATOR = 0, NUMBER = 1;

ull gcd(ull a, ull b)
{
    return b == 0 ? a : gcd(b, a % b);
}

struct fraction
{
    ull numerator, denominator;
    
    void justify()
    {
        if (numerator != 0 && denominator != 0)
        {
            ull g = gcd(numerator, denominator);
            numerator /= g, denominator /= g;
        }
        
        if (numerator == 0 && denominator != 0)
        {
            denominator = 1;
        }
    }
    
    fraction operator+(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator + denominator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.justify();
        return r;
    }
    
    fraction operator-(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator - denominator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.justify();
        return r;
    }
    
    fraction operator*(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.numerator;
        r.denominator = denominator * f.denominator;
        r.justify();
        return r;
    }
    
    fraction operator/(const fraction f)
    {
        fraction r;
        r.numerator = numerator * f.denominator;
        r.denominator = denominator * f.numerator;
        r.justify();
        return r;
    }
};

struct symbol
{
    char character;
    fraction f;
    int category;
};

vector<symbol> symbols;

symbol calculate()
{
    symbol empty = (symbol){0, (fraction){0, 0}, NUMBER};
    
    stack<symbol> result;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.category == NUMBER)
            result.push(s);
        else
        {
            symbol a = result.top(); result.pop();
            symbol b = result.top(); result.pop();
            
            if (a.f.denominator == 0 || b.f.denominator == 0) return empty;
            if (s.character == '/' && a.f.numerator == 0) return empty;

            switch (s.character)
            {
                case '+':
                    result.push((symbol){0, a.f + b.f, NUMBER});
                    break;
                case '-':
                    result.push((symbol){0, b.f - a.f, NUMBER});
                    break;
                case '*':
                    result.push((symbol){0, a.f * b.f, NUMBER});
                    break;
                case '/':
                    result.push((symbol){0, b.f / a.f, NUMBER});
                    break;
            }
        }
    }

    return result.top();
}

// 比较运算符在栈中的优先级顺序。
bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

void infixToPostfix()
{  
    stack<symbol> number, operators;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
            
        if (s.category == NUMBER)
            number.push(s);
        else
        {
            if (s.character == '(')
                operators.push(s);
            else if (s.character == ')')
            {
                while (!operators.empty() && operators.top().character != '(')
                {
                    number.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {                
                if (operators.empty() || operators.top().character == '(' || !lessPriority(s.character, operators.top().character))
                    operators.push(s);
                else
                {
                    while (!operators.empty() && lessPriority(s.character, operators.top().character))
                    {
                        number.push(operators.top());
                        operators.pop();
                    }
                    operators.push(s);
                }
            }
        }
    }

    while (!operators.empty())
    {
        number.push(operators.top());
        operators.pop();
    }
    
    symbols.clear();
    while (!number.empty())
    {
        symbols.insert(symbols.begin(), number.top());
        number.pop();
    }
}

void parse(string line)
{
    symbols.clear();

    int index = 0;
    while (index < line.length())
    {
        if (line[index] >= '0' && line[index] <= '9')
        {
            ull numerator = 0, denominator = 1;
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

            symbols.push_back((symbol){0, (fraction){numerator, denominator}, NUMBER});
        }
        else
        {
            symbols.push_back((symbol){line[index], (fraction){0, 0}, OPERATOR});
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
        r.f.justify();
        
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
