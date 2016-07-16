// 
// UVa ID: 
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

// 定义运算符的优先级顺序，值越高，优先级越高。在栈中，括号的优先级最小。
map<char, int> priority = {
    {'!', 1}, {'&', 2}, {'|', 2}, {'+', 3}, {'-', 3},
    {'*', 4}, {'/', 4}, {'$', 5}
};

// 比较运算符在栈中的优先级顺序。
bool lessPriority(char previous, char next)
{
    return priority[previous] <= priority[next];
}

// 将中缀表达式转换为后缀表达式。
string toPostfix(string infix)
{
    for (int i = infix.length() - 1; i >= 0; i--)
        if (isblank(infix[i]))
            infix.erase(infix.begin() + i);
            
    stack<char> operands;         // 操作数栈
    stack<char> operators;      // 运算符栈

    for (auto c : infix) {
        // 如果是数字，直接压入操作数栈中。
        if (isalpha(c)) { operands.push(c); continue; }

        // 如果是非括号运算符，当运算符堆栈为空，或者运算符堆栈栈顶元素
        // 为左括号，或者比运算符堆栈栈顶运算符的优先级高，将当前运算符
        // 压入运算符堆栈。
        bool flag = operators.empty() || !lessPriority(c, operators.top());
        
        // 根据条件进行操作。
        if (flag) operators.push(c);
        else {
            // 当运算符的优先级比运算符堆栈栈顶元素的优先级低或相等时，
            // 弹出运算符堆栈栈顶元素，直到运算符堆栈为空，或者遇到比
            // 当前运算符优先级低的运算符。
            while (!operators.empty() && lessPriority(c, operators.top())) {
                operands.push(operators.top());
                operators.pop();
            }

            // 将当前运算符压入运算符堆栈。
            operators.push(c);
        }
    }

    // 当中缀表达式处理完毕，运算符堆栈不为空时，逐个弹出压入到操作数堆栈中。
    while (!operators.empty()) {
        operands.push(operators.top());
        operators.pop();
    }

    // 将操作数堆栈中保存的后缀表达式提取为一个字符串以利于后续值的计算。
    string postfix;
    while (!operands.empty()) {
        postfix = operands.top() + postfix;
        operands.pop();
    }

    return postfix;
}

int main(int argc, char *argv[])
{
    string infix, prefix, postfix;
    while (getline(cin, infix))
    {
        cout << setw(7) << left << "INFIX" << " => " << infix << endl;
        getline(cin, prefix);
        cout << setw(7) << left << "PREFIX" << " => " << prefix << endl;
        postfix = toPostfix(infix);
        cout << setw(7) << left << "POSTFIX" << " => " << postfix << endl;
    }

    return 0;
}
