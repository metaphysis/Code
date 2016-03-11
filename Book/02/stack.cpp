#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;

// 使用栈来计算后缀表达式的值。从左至右扫描后缀表达式，如果是数字，则压入结果栈，
// 如果是运算符，则取出结果栈栈顶的两个元素进行运算符所指定的运算，然后将运算结果
// 压入结果栈中，直到后缀表达式处理完毕，结果栈的栈顶元素即为表达式的值。
int calculate(string postfixNotation)
{
    stack<int> result;
    for (int i = 0; i < postfixNotation.length(); i++)
    {
        char c = postfixNotation.at(i);
        if (isdigit(c))
            result.push(c - '0');
        else
        {
            int b = result.top();
            result.pop();
            int a = result.top();
            result.pop();

            switch (c)
            {
                case '+':
                    result.push(a + b);
                    break;
                case '-':
                    result.push(a - b);
                    break;
                case '*':
                    result.push(a * b);
                    break;
                case '/':
                    result.push(a / b);
                    break;
                default:
                    break;
            }
        }
    }
    
    return result.top();
}

// 比较运算符在栈中的优先级顺序。在栈中，括号的优先级最小。
bool lessPriority(char a, char b)
{
    map<char, int> priority;
    priority.insert(pair<char, int>('+', 1));
    priority.insert(pair<char, int>('-', 1));
    priority.insert(pair<char, int>('*', 2));
    priority.insert(pair<char, int>('/', 2));
    priority.insert(pair<char, int>('(', 0));
    priority.insert(pair<char, int>(')', 0));

    return priority[a] <= priority[b];
}

// 将中缀表达式转换为后缀表达式。
string parseToReversePolishNotation(string infixNotation)
{
    stack<char> number;     // 操作数栈。
    stack<char> operators;  // 运算符栈。

    for (int i = 0; i < infixNotation.length(); i++)
    {
        char c = infixNotation.at(i);
        // 如果是数字，直接压入操作数栈中。
        if (isdigit(c))
            number.push(c);
        else
        {
            // 如果是左括号，直接压入运算符栈中。
            if (c == '(')
                operators.push(c);
            // 如果是右括号，则弹出运算符栈顶元素，直到遇到左括号。
            else if (c == ')')
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    number.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {
                // 如果是非括号运算符，当运算符堆栈为空，或者运算符堆栈栈顶元素
                // 为左括号，或者比运算符堆栈栈顶运算符的优先级高，将当前运算符
                // 压入运算符堆栈。
                if (operators.empty() || operators.top() == '('
                    || !lessPriority(c, operators.top()))
                    operators.push(c);
                else
                {
                    // 当运算符的优先级比运算符堆栈栈顶元素的优先级低或相等时，
                    // 弹出运算符堆栈栈顶元素，直到运算符堆栈为空，或者遇到比
                    // 当前运算符优先级低的运算符。
                    while (!operators.empty()
                        && lessPriority(c, operators.top()))
                    {
                        number.push(operators.top());
                        operators.pop();
                    }

                    // 将当前运算符压入运算符堆栈。
                    operators.push(c);
                }
            }
        }
    }

    // 当中缀表达式处理完毕，运算符堆栈不为空时，逐个弹出压入到操作数堆栈中。
    while (!operators.empty())
    {
        number.push(operators.top());
        operators.pop();
    }

    // 将操作数堆栈中保存的后缀表达式转换为一个字符串以利于后续值的计算。
    string postfixNotation;
    while (!number.empty())
    {
        postfixNotation = number.top() + postfixNotation;
        number.pop();
    }

    return postfixNotation;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line), line.length() > 0)
        cout << calculate(parseToReversePolishNotation(line)) << endl;

    return 0;
}
