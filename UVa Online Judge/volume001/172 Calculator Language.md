[UVa 172 Calculator Language](https://blog.csdn.net/metaphysis/article/details/160662329)

## 题目分析

本题要求实现一个简单的计算器语言（$\texttt{Calculator Language}$，简称 $\texttt{CL}$）的解释器。该语言支持变量（`A-Z`）、整数、四则运算（加、减、乘、整除）和赋值操作，运算符优先级相同且为**右结合**，括号可以任意嵌套。

### 语言规则回顾

1. **变量**：`A-Z` 共 26 个，初始值为 $0$，在整个程序运行期间保持值，直到被显式修改。
2. **运算符**：`+` `-` `*` `/` `=`，所有运算符优先级相同，右结合。
3. **括号**：`(` 和 `)`，强制先计算括号内的表达式。
4. **负号**：仅出现在数字前（如 `_2` 表示 $-2$），不会出现在变量前。
5. **空格**：可随意插入，但负号与数字之间不能有空格。
6. **输入**：每行一个正确的 $\texttt{CL}$ 表达式，行长度不超过 $100$ 个字符，以 `#` 单独一行结束。
7. **输出**：对于每行表达式，输出**值发生改变**的变量（按字母顺序），格式为 `变量 = 新值`，多个变量用 `, ` 分隔。若没有变量改变，输出 `No Change`。

### 关键点

- **变量初值与保留**：每个变量在程序开始为 $0$，且上一次计算的结果会影响下一次。
- **赋值**：`=` 也是运算符，具有与 `+` 等相同的优先级和右结合性，因此 `A = B = 4` 等价于 `A = (B = 4)`。
- **负号处理**：输入中用 `_` 表示负号，例如 `_2` 表示 $-2$。
- **多次赋值**：同一变量在一行中可能被多次赋值，只输出最终值。
- **没有变化的变量不输出**：比较执行前后的值，只有变化了的才打印。

## 解题思路

本题的核心是**表达式求值**，但由于运算符优先级相同且为右结合，加上括号的支持，最稳妥的方式是采用**中缀转后缀（逆波兰表示法）**再求值。

### 整体流程

1. **读取一行**，去掉所有空格（负号与数字之间本来无空格，去除空格不影响负数解析）。
2. **词法分析**：将字符串分解为 $\texttt{token}$（变量、数字、运算符、括号）。
   - 数字可能带负号（用 `_` 表示）。
3. **中缀转后缀**：考虑右结合和括号。
4. **后缀表达式求值**：使用栈，遇到变量时获取当前值，遇到运算符则弹出两个操作数计算，遇到 `=` 则执行赋值并压入结果。
5. **记录变化**：求值前后比较变量值，收集变化的变量，按字母序输出。

### 关键细节处理

#### 1. 负数的处理

题目保证负号只出现在数字前，且用 `_` 表示。在词法分析时，当遇到 `_`，标记为负号，然后继续读取数字，组合成一个负的整数字面量，作为一个 $\texttt{NUMBER token}$。

#### 2. 中缀转后缀的调整

由于题目中运算符是右结合的，且优先级相同，我们可以在转换时采用如下策略：

- 遇到操作数（变量或数字）直接输出到后缀队列。
- 遇到左括号 `(` 入栈。
- 遇到右括号 `)` 将栈顶直到左括号的运算符弹出。
- 遇到运算符时：
  - 因为优先级相同且右结合，新来的运算符应该**先于**栈顶已有的相同优先级运算符被处理（即栈顶的相同优先级运算符不应先弹出），所以应直接将当前运算符入栈。
  - 但为了满足右结合，实际实现中更简单的方式是：**反转表达式**，将 `(` 与 `)` 互换，然后按左结合的常规方式处理，最后再反转回来。这是很多 AC 代码采用的方法。

本题的参考代码使用了这种“反转变换”技巧：

- 先将整个 $\texttt{token}$ 序列反转。
- 同时将 `(` 和 `)` 互换。
- 然后进行标准的左结合中缀转后缀（遇到运算符时，弹出栈中优先级**大于等于**当前运算符的运算符）。
- 最后将得到的后缀序列反转回来。

这样巧妙地将右结合转换成了左结合问题。

#### 3. 赋值运算符的处理

`=` 在求值时，弹出右操作数（值或变量）和左操作数（必须是变量），将右操作数的值赋给左变量，同时压入该值作为结果，以便参与外层运算。

例如 `A = B = 4`：
- 后缀形式为 `A B 4 = =`。
- 先计算 `B = 4`：将 `4` 赋给 `B`，压入 `4`。
- 再计算 `A = 4`：将 `4` 赋给 `A`，压入 `4`。

#### 4. 变量初始值和不变化判断

用两个数组 `original[26]` 和 `now[26]`：
- 每行开始前，将 `now` 复制到 `original` 保存旧值。
- 执行完该行后，比较 `now[i]` 与 `original[i]`，不同则记录。
- 全局变量保留值，因此下一行的旧值就是上一行的 `now`。

#### 5. 输出格式

严格按题目要求：
- 变量按字母顺序。
- 等号两边空格：`A = 4`。
- 逗号后跟一个空格。
- 无变化输出 `No Change`。

## 代码实现

```cpp
// Calculator Language
// UVa ID: 172
// Verdict: Accepted
// Submission Date: 2016-02-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int VARIABLE = 0, OPERATOR = 1, NUMBER = 2;

struct symbol { int token, category; };

int original[26] = { 0 };
int now[26] = { 0 };

vector<symbol> symbols;

void calculate() {
    stack<symbol> operands;
    for (int i = 0; i < symbols.size(); i++) {
        symbol s = symbols[i];
        if (s.category == VARIABLE || s.category == NUMBER) operands.push(s);
        else {
            symbol a = operands.top(); operands.pop();
            symbol b = operands.top(); operands.pop();
            int aa, bb, cc;
            if (a.category == VARIABLE) aa = now[a.token - 'A'];
            else aa = a.token;
            if (b.category == VARIABLE) bb = now[b.token - 'A'];
            else bb = b.token;
            switch (s.token) {
                case '+': cc = aa + bb; break;
                case '-': cc = aa - bb; break;
                case '*': cc = aa * bb; break;
                case '/': cc = aa / bb; break;
                case '=': cc = bb; now[a.token - 'A'] = bb; break;
                default: break;
            }
            operands.push((symbol){cc, NUMBER});
        }
    }
}

void infixToPostfix() {
    reverse(symbols.begin(), symbols.end());
    for (int i = 0; i < symbols.size(); i++)
        if (symbols[i].category == OPERATOR) {
            if (symbols[i].token == ')') symbols[i].token = '(';
            else if (symbols[i].token == '(') symbols[i].token = ')';
        }
    stack<symbol> operands, operators;
    for (int i = 0; i < symbols.size(); i++) {
        symbol s = symbols[i];
        if (s.category == NUMBER || s.category == VARIABLE) operands.push(s);
        else {
            if (s.token == '(') operators.push(s);
            else if (s.token == ')') {
                while (!operators.empty() && operators.top().token != '(') {
                    operands.push(operators.top());
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();
            } else {                
                if (operators.empty() || operators.top().token == '(') operators.push(s);
                else {
                    while (!operators.empty() && operators.top().token != '(') {
                        operands.push(operators.top());
                        operators.pop();
                    }
                    operators.push(s);
                }
            }
        }
    }
    while (!operators.empty()) {
        operands.push(operators.top());
        operators.pop();
    }
    symbols.clear();
    while (!operands.empty()) {
        symbols.insert(symbols.begin(), operands.top());
        operands.pop();
    }
}

void parse(string line) {
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    symbols.clear();
    int index = 0;
    while (index < line.length()) {
        if ((line[index] >= '0' && line[index] <= '9') || line[index] == '_') {
            int sign = line[index] == '_' ? -1 : 1;
            int operands = 0;
            if (line[index] == '_') index++;
            while (index < line.length() && (line[index] >= '0' && line[index] <= '9')) {
                operands = operands * 10 + line[index] - '0';
                index++;
            }
            symbols.push_back((symbol){operands * sign, NUMBER});
        } else if (line[index] >= 'A' && line[index] <= 'Z') {
            symbols.push_back((symbol){line[index], VARIABLE});
            index++;
        } else {
            symbols.push_back((symbol){line[index], OPERATOR});
            index++;            
        }
    }
    infixToPostfix();
    calculate();
    vector < int > operands;
    for (int i = 0; i < 26; i++)
        if (now[i] != original[i])
            operands.push_back(i);
    if (operands.size() > 0) {
        for (int i = 0; i < operands.size(); i++) {
            cout << (char)('A' + operands[i]) << " = " << now[operands[i]];
            if (i < operands.size() - 1)
                cout << ", ";
        }
        cout << '\n';
    } else cout << "No Change" << '\n';
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    string line;
    while (getline(cin, line), line != "#") {
        copy(now, now + 26, original);
        parse(line);
    }
    return 0;
}
```

## 总结

本题考察的核心是**带右结合运算符和赋值操作的表达式求值**。通过中缀转后缀并利用栈进行求值，可以清晰且正确地处理优先级、括号和右结合性。同时需要注意负数的表示（`_` 符号）和变量值的持久化。代码实现采用反转括号的手法简化了右结合的中缀转换，是一个值得借鉴的技巧。
