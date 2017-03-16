// Equation
// UVa ID: 727
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

// 定义运算符的优先级顺序，值越高，优先级越高。在栈中，括号的优先级最小。
map<char, int> priority = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}
};

// 比较运算符在栈中的优先级顺序。
bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

// 将中缀表达式转换为后缀表达式。
string toPostfix(string infix)
{
    stack<char> operands;     // 操作数栈
    stack<char> operators;    // 运算符栈

    for (auto c : infix)
    {
        // 如果是数字，直接压入操作数栈中。
        if (isdigit(c))
        {
            operands.push(c);
            continue;
        }

        // 如果是左括号，直接压入运算符栈中。
        if (c == '(')
        {
            operators.push(c);
            continue;
        }

        // 如果是右括号。
        if (c == ')')
        {
            // 弹出运算符栈顶元素，直到遇到左括号。
            while (!operators.empty() && operators.top() != '(')
            {
                operands.push(operators.top());
                operators.pop();
            }
            // 操作符堆栈不为空，继续弹出匹配的左括号。
            if (!operators.empty()) operators.pop();

            continue;
        }

        // 如果是非括号运算符，当运算符堆栈为空，或者运算符堆栈栈顶元素
        // 为左括号，或者比运算符堆栈栈顶运算符的优先级高，将当前运算符
        // 压入运算符堆栈。
        if (operators.empty() || operators.top() == '(' ||
            !lessPriority(c, operators.top()))
        {
            operators.push(c);
        }
        else
        {
            // 当运算符的优先级比运算符堆栈栈顶元素的优先级低或相等时，
            // 弹出运算符堆栈栈顶元素，直到运算符堆栈为空，或者遇到比
            // 当前运算符优先级低的运算符时结束。
            while (!operators.empty() && lessPriority(c, operators.top()))
            {
                operands.push(operators.top());
                operators.pop();
            }

            // 将当前运算符压入运算符堆栈。
            operators.push(c);
        }
    }

    // 当中缀表达式处理完毕，运算符堆栈不为空时，逐个弹出压入到操作数堆栈中。
    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }

    // 获取操作数堆栈中保存的后缀表达式，注意栈中保存的是从左至右的顺序，但
    // 从栈中弹出时是从右至左的顺序，需要适当调整。
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
    int cases = 0;

    cin >> cases;
    cin.ignore(1024, '\n');
    
    string line;
    getline(cin, line);
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        string infix;
        while (getline(cin, line), line.length() > 0) infix += line;

        cout << toPostfix(infix) << '\n';
    }
    
	return 0;
}
