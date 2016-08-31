// Grammar Evaluation
// UVa ID: 622
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
    char character;
    int number, category;
};

string line;
int index;

vector<symbol> symbols;

int calculate()
{
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
                
            switch (s.character)
            {
                case '+':
                    result.push((symbol){0, a.number + b.number, NUMBER});
                    break;
                case '*':
                    result.push((symbol){0, a.number * b.number, NUMBER});
                    break;
            }
        }
    }
    
    return result.top().number;
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

bool validate()
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

void parse()
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
            symbols.push_back((symbol){0, number, NUMBER});
        }
        else if (line[index] == '(' || line[index] == ')' || line[index] == '+' || line[index] == '*')
        {
            symbols.push_back((symbol){line[index], 0, OPERATOR});
            index++;            
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    getline(cin, line);
    int cases = stoi(line);

    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);

        if (validate())
        {
            parse();
            infixToPostfix();
            cout << calculate() << '\n';
        }
        else
            cout << "ERROR\n";
    }
    
	return 0;
}
