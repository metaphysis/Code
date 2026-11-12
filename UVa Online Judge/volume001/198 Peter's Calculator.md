[UVa 198 Peter's Calculator](https://blog.csdn.net/metaphysis/article/details/160943552)

## 题目分析

$\texttt{Peter}$ 需要一个支持整数运算的计算器，功能包括：

- 变量赋值，变量名由字母开头，后跟至多 $49$ 个字母或数字
- 支持加法、减法、乘法运算
- 表达式可以引用尚未定义的变量
- $\texttt{PRINT}$ 指令输出变量的值，若变量未定义或存在循环依赖则输出 $\texttt{UNDEF}$
- $\texttt{RESET}$ 指令清空所有变量定义

变量是否 **未定义** 的判定条件：

1. 变量从未被赋值
2. 变量的定义中引用了未定义的变量
3. 变量的定义中存在循环依赖

## 解题思路

本题的核心是处理 **带依赖关系的表达式求值**。由于变量可以相互引用，且存在循环依赖的可能，需要在求值时检测循环。

### 整体框架

1. **解析输入**：每行可能是赋值、打印或重置指令
2. **表达式解析**：将中缀表达式转换为后缀表达式（逆波兰表示），方便后续计算
3. **循环检测**：在递归求值时，使用集合记录当前求值路径上的变量，若重复出现则检测到循环
4. **延迟求值**：变量被赋值时只存储其后缀表达式，实际求值在 $\texttt{PRINT}$ 时进行

### 关键实现细节

#### 1. 负数的处理

题目中的数字可以以负号开头（如 $-5$）。解析时，将负号特殊标记（代码中用 `_` 代替），与减法运算符区分开。

判断条件：当 `-` 的前一个是运算符、括号或行首时，表示负数而非减法。

#### 2. 中缀转后缀

使用调度场算法（$\texttt{Shunting-yard algorithm}$），定义优先级：

- `+`、`-`：优先级 $1$
- `*`：优先级 $2$
- `(`、`)`：优先级 $0$

#### 3. 后缀表达式求值与循环检测

递归求值时，维护一个全局集合 `undefined` 记录当前求值路径上的变量：

- 进入求值某个变量时，将其加入集合
- 若求值中再次遇到集合内的变量，说明存在循环依赖，返回失败
- 求值完成后从集合中移除

## 代码实现

```cpp
// Peter's Calculator
// UVa ID: 198
// Verdict: Accepted
// Submission Date: 2016-03-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int VARIABLE = 0, OPERATOR = 1, NUMBER = 2;

// 符号结构体：存储表达式中每个元素的信息
struct symbol {
    string token;      // 符号的字符串表示（变量名/运算符/数字字符串）
    int operand;       // 若为数字类型，存储其整数值
    int category;      // 类型：VARIABLE（变量）、OPERATOR（运算符）、NUMBER（数字）
};

set<string> undefined;                              // 用于循环检测，记录当前求值路径上的变量
map<string, vector<symbol>> formula;                // 存储每个变量对应的后缀表达式
map<string, int> priority;                          // 存储运算符的优先级

// 递归计算后缀表达式的值
// symbols: 后缀表达式序列
// value: 输出参数，用于存储计算结果
// 返回值: true表示计算成功，false表示变量未定义或存在循环依赖
bool calculate(vector < symbol > symbols, int &value) {
    stack<symbol> operands;  // 操作数栈
    for (int i = 0; i < symbols.size(); i++) {
        symbol s = symbols[i];
        // 变量或数字直接入栈
        if (s.category == VARIABLE || s.category == NUMBER)
            operands.push(s);
        else {
            // 遇到运算符，弹出两个操作数
            symbol b = operands.top(); operands.pop();
            symbol a = operands.top(); operands.pop();

            int aa, bb, cc;
            // 处理左操作数 a
            if (a.category == VARIABLE) {
                if (undefined.count(a.token) > 0) return false;
                if (formula.count(a.token) == 0) return false;

                undefined.insert(a.token);
                if (calculate(formula[a.token], aa) == false) return false;
                undefined.erase(a.token);
            } else aa = a.operand;

            // 处理右操作数 b
            if (b.category == VARIABLE) {
                if (undefined.count(b.token) > 0) return false;
                if (formula.count(b.token) == 0) return false;
                
                undefined.insert(b.token);    
                if (calculate(formula[b.token], bb) == false) return false;
                undefined.insert(b.token);
            } else bb = b.operand;

            // 执行运算
            if (s.token == "+") cc = aa + bb;
            else if (s.token == "-") cc = aa - bb;
            else if (s.token == "*") cc = aa * bb;

            // 将运算结果作为数字压入栈中
            operands.push((symbol){"", cc, NUMBER});
        }
    }

    // 栈顶即为最终结果
    if (operands.top().category == NUMBER) {
        value = operands.top().operand;
        return true;
    } else {
        // 栈顶为变量，需要继续递归求值
        string variable = operands.top().token;

        if (undefined.count(variable) > 0) return false;
        if (formula.count(variable) == 0) return false;

        undefined.insert(variable);
        if (calculate(formula[variable], value)) undefined.erase(variable);
        else return false;
    }
    return true;
}

// 判断运算符 a 的优先级是否不高于运算符 b
bool lessPriority(string a, string b) {
    return priority[a] <= priority[b];
}

// 中缀表达式转后缀表达式（逆波兰表达式）
vector<symbol> infixToPostfix(vector<symbol> symbols) {
    stack<symbol> operands, operators;  // operands: 输出栈, operators: 运算符栈
    for (int i = 0; i < symbols.size(); i++) {
        symbol s = symbols[i];

        // 数字或变量直接输出到 operands 栈
        if (s.category == NUMBER || s.category == VARIABLE) operands.push(s);
        else {
            // 左括号直接入运算符栈
            if (s.token == "(") operators.push(s);
            // 右括号：弹出运算符直到遇到左括号
            else if (s.token == ")") {
                while (!operators.empty() && operators.top().token != "(") {
                    operands.push(operators.top());
                    operators.pop();
                }
                // 弹出左括号
                if (!operators.empty()) operators.pop();
            } else {                
                // 当前运算符优先级高时直接入栈，否则弹出优先级较高的运算符
                if (operators.empty() || operators.top().token == "(" ||
                    !lessPriority(s.token, operators.top().token))
                    operators.push(s);
                else {
                    while (!operators.empty() && lessPriority(s.token, operators.top().token)) {
                        operands.push(operators.top());
                        operators.pop();
                    }
                    operators.push(s);
                }
            }
        }
    }

    // 弹出剩余运算符
    while (!operators.empty()) {
        operands.push(operators.top());
        operators.pop();
    }

    // 反转得到正确的后缀表达式顺序
    symbols.clear();
    while (!operands.empty()) {
        symbols.insert(symbols.begin(), operands.top());
        operands.pop();
    }

    return symbols;
}

// 解析赋值语句
void parse(string line) {
    // 删除所有空格
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);

    // 分离左值和右值表达式
    string left = line.substr(0, line.find(":="));
    line = line.substr(line.find(":=") + 2);

    // 将负数标记转换为特殊字符 '_'，以便与减法运算符区分
    int index = line.length() - 1;
    while (index >= 2) {
        if (isdigit(line[index]) && line[index - 1] == '-') {
            if (line[index - 2] == '+' ||
                line[index - 2] == '-' ||
                line[index - 2] == '(' ||
                line[index - 2] == '*') {
                line[index - 1] = '_';
                index -= 2;
            }
        }
        index--;
    }

    // 处理行首的负号
    if (line.front() == '-') line[0] = '_';

    // 词法分析：将字符串分割为 token
    index = 0;
    vector<symbol> symbols;
    while (index < line.length()) {
        // 处理数字（包括负数）
        if ((line[index] >= '0' && line[index] <= '9') || line[index] == '_') {
            int sign = line[index] == '_' ? -1 : 1;
            int operands = 0;

            if (line[index] == '_') index++;

            while (index < line.length() && (line[index] >= '0' && line[index] <= '9')) {
                operands = operands * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){"", operands * sign, NUMBER});
        }
        // 处理变量名
        else if (isalpha(line[index])) {
            string block;
            while (index < line.length()) {
                if (isalpha(line[index]) || isdigit(line[index])) {
                    block += line[index];
                    index++;
                }
                else break;
            }
            symbols.push_back((symbol){block, 0, VARIABLE});
        }
        // 处理运算符
        else {
            symbols.push_back((symbol){string(1, line[index]), 0, OPERATOR});
            index++;            
        }
    }

    // 将中缀表达式转换为后缀表达式并存储
    formula[left] = infixToPostfix(symbols);
}

int main() {
    // 初始化运算符优先级
    priority.insert(pair<string, int>("+", 1));
    priority.insert(pair<string, int>("-", 1));
    priority.insert(pair<string, int>("*", 2));
    priority.insert(pair<string, int>("(", 0));
    priority.insert(pair<string, int>(")", 0));

    string line;
    while (getline(cin, line)) {
        // 赋值语句
        if (line.find(":=") != line.npos)  parse(line);
        else {
            // PRINT 语句
            if (line.find("PRINT") != line.npos) {
                // 从行尾提取要打印的变量名
                int index = line.length() - 1;
                while (isblank(line[index])) index--;

                string block;
                while (!isblank(line[index])) {
                    block += line[index];
                    index--;
                }
                reverse(block.begin(), block.end());

                // 计算并输出结果
                undefined.clear();
                if (formula.count(block) > 0) {
                    undefined.insert(block);
                    int value;
                    if (calculate(formula[block], value))
                        cout << value << endl;
                    else
                        cout << "UNDEF" << endl;
                } else cout << "UNDEF" << endl;
            }
            // RESET 语句：清空所有变量定义
            else formula.clear();
        }
    }

    return 0;
}
```

## 总结

本题的核心难点在于：

1. **循环依赖检测**：通过在递归求值路径上标记变量，遇到重复即判定为循环
2. **负数解析**：需要区分负数符号与减法运算符
3. **表达式求值**：采用中缀转后缀 + 栈求值的经典方法

上述代码通过递归求值和循环检测，能够正确处理变量间的复杂依赖关系，并在遇到未定义变量或循环时输出 $\texttt{UNDEF}$。
