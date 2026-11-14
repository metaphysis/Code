
## 题目描述

在 $\texttt{ACM}$ 行星的东南部，存在多种使用非标准运算符符号的方言。这些方言中，加、减、乘、整数除法这四种运算分别使用不同的本地符号，且它们的优先级（数字越大优先级越高）和结合性（`L` 左结合，`R` 右结合）也各不相同。

给定一个方言描述（包含四个标准运算符对应的本地符号、优先级和结合性），以及若干条使用该方言书写的表达式，要求计算每个表达式的值，并将表达式中的本地运算符替换为标准运算符（`+`、`-`、`*`、`/`）后输出。

本地符号可以是任意可见字符（包括 `(` 和 `)`），这些字符不具分组功能，仅作为普通二元运算符参与运算。表达式中不会出现除已映射本地符号以外的圆括号。

## 输入格式

输入文件第一行为一个整数 $T$，表示测试数据组数。  
随后为一个空行。  
接下来是 $T$ 组数据，每组数据格式如下：

- 第一行为一个空行（仅在组间存在，第一组前也有一个空行）。
- 接下来 $4$ 行，每行是一个长度为 $4$ 的字符串 $c_1c_2c_3c_4$，描述一个标准运算符的本地映射：
  - $c_1$：标准运算符（`+`、`-`、`*`、`/` 之一）；
  - $c_2$：该运算符对应的本地符号（一个可见字符，不含数字、空白，可以为 `(` 或 `)`）；
  - $c_3$：一个数字字符（`0` ~ `9`），表示该运算符的优先级；
  - $c_4$：一个字母，`L` 表示左结合，`R` 表示右结合。
- 之后若干行，每行一个使用本地符号书写的表达式（不含空白字符），表达式可包含数字、括号（作为运算符）以及其他本地符号。表达式以空行结束（即下一行为空行），表示该组数据结束。

输入以 $\texttt{EOF}$ 结束。

> 注意：题目原始描述中未提及第一行的 $T$，但在线测试数据实际采用此格式。

## 输出格式

对于每个输入表达式，输出一行，内容为：**将本地运算符替换为标准运算符后的表达式**，后跟一个空格、一个等号、一个空格，以及该表达式的计算结果。每组内的表达式连续输出，组间由一个空行分隔。

## 样例

输入

```
3

+(9R
-)9R
**9L
//0L
2(3(3)9

++9R
--9R
**9L
//0L
3+2-1
3-2-1
2-1+3-2+9-0
2/2+3/3+4/4+5/5
10000/2/3/4/5
100*30/2+2-5/4*10-1+99*100

++0L
--0L
**9L
//8L
5*4*3*2*1/3*2*1*2*1
1+3+10/2*800-400/2*200+6-7*3/1
```

输出

```
2+3+3-9 = -1

3+2-1 = 4
3-2-1 = 2
2-1+3-2+9-0 = 11
2/2+3/3+4/4+5/5 = 0
10000/2/3/4/5 = 83
100*30/2+2-5/4*10-1+99*100 = 0

5*4*3*2*1/3*2*1*2*1 = 10
1+3+10/2*800-400/2*200+6-7*3/1 = -12

```

> 注意：样例输出中等号前后各有一个空格，与题目原始描述略有差异，实际评测以该格式为准。

## 题目分析

本题的核心是实现一个能够处理**自定义优先级和结合性**的表达式求值器。运算符的优先级（数字 $0 \sim 9$）和结合性（左/右）由输入动态指定，且必须严格遵循：

- **相同运算符连续出现**时，按该运算符自身的结合性（左或右）进行结合。
- **不同运算符**（即使优先级相同）一律按从左到右的顺序执行（即强制左结合）。

这是一个易错点。例如，若 `-` 为右结合，`+` 为左结合，且二者优先级相同，则表达式 `a - b + c` 应解释为 `(a - b) + c`，因为 `-` 与 `+` 不同，强制左结合；而表达式 `a - b - c` 因连续两个 `-`，按右结合解释为 `a - (b - c)`。

因此，解析器不能简单地将同优先级运算符统一左结合或右结合，必须区分“相同运算符”与“不同运算符”。

## 解题思路

### 调度场算法（$\texttt{Shunting-yard}$）模拟

采用基于栈的调度场算法进行表达式求值，同时维护三个栈：

- 操作数栈 `val`：存储整数值。
- 表达式字符串栈 `exp`：存储对应的标准运算符表达式。
- 运算符栈 `op`：存储本地运算符符号。

遍历表达式时：

1. 遇到数字，读取完整整数，压入 `val` 和 `exp`。
2. 遇到运算符 `cur` 时，与栈顶运算符 `top` 比较：
   - 若 `cur` 的优先级小于 `top` 的优先级，则弹出 `top` 并计算。
   - 若优先级相等：
     - 若 `cur == top`（相同运算符连续），则按 `top` 的结合性决定是否弹出（左结合弹出，右结合不弹）。
     - 若 `cur != top`（不同运算符），则强制左结合，弹出 `top`。
   - 若 `cur` 优先级大于 `top`，则不弹出。
   - 重复上述比较，直至不满足弹出条件，然后将 `cur` 压栈。
3. 扫描结束后，依次弹出栈中剩余运算符并计算。

此过程完全符合题目规则，且无需处理括号的特殊性，因为括号若作为运算符，它们也会出现在映射表中，以相同逻辑参与优先级比较。

### 运算符优先级比较

比较规则可归纳为：

```cpp
bool shouldPop = false;
if (prec[cur] < prec[top]) shouldPop = true;
else if (prec[cur] == prec[top]) {
    if (cur == top) shouldPop = (assoc[top] == 'L');
    else shouldPop = true;
}
```

该规则精准实现了“相同运算符按自身结合性，不同运算符强制左结合”。

### 输出生成

每次计算时，从 `exp` 栈弹出左右表达式字符串，拼接当前运算符对应的标准符号，得到新的表达式字符串。最终栈顶字符串即为转换后的标准表达式。

### 复杂度分析

设单条表达式长度为 $L$。每个字符（数字或运算符）至多入栈、出栈一次，因此单次求值时间复杂度为 $O(L)$。空间复杂度为 $O(L)$。总时间复杂度为 $O(\sum L)$，其中 $\sum L$ 为所有表达式长度之和，完全满足题目要求。

## 代码实现

```cpp
// Crazy Calculator
// UVa ID: 354
// Verdict: Accepted
// Submission Date: 2026-06-30
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, char> toStd;
unordered_map<char, int> prec;
unordered_map<char, char> assoc;

int calc(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b ? a / b : 0;
    }
    return 0;
}

void apply(stack<int>& val, stack<string>& exp, stack<char>& op) {
    char o = op.top(); op.pop();
    string r = exp.top(); exp.pop();
    string l = exp.top(); exp.pop();
    int rb = val.top(); val.pop();
    int lb = val.top(); val.pop();
    val.push(calc(lb, rb, toStd[o]));
    exp.push(l + toStd[o] + r);
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    getline(cin, line);
    int T = stoi(line);
    getline(cin, line);
    for (int cs = 0; cs < T; ++cs) {
        if (cs) cout << '\n';
        toStd.clear(); prec.clear(); assoc.clear();
        for (int i = 0; i < 4; ++i) {
            getline(cin, line);
            toStd[line[1]] = line[0];
            prec[line[1]] = line[2] - '0';
            assoc[line[1]] = line[3];
        }
        while (getline(cin, line) && !line.empty()) {
            stack<int> val;
            stack<string> exp;
            stack<char> op;
            for (int i = 0; i < (int)line.size(); ) {
                if (isdigit(line[i])) {
                    int num = 0;
                    while (i < (int)line.size() && isdigit(line[i]))
                        num = num * 10 + (line[i++] - '0');
                    val.push(num);
                    exp.push(to_string(num));
                } else {
                    char cur = line[i++];
                    while (!op.empty()) {
                        char top = op.top();
                        bool pop = false;
                        if (prec[cur] < prec[top]) pop = true;
                        else if (prec[cur] == prec[top]) {
                            if (cur == top) pop = (assoc[top] == 'L');
                            else pop = true;
                        }
                        if (!pop) break;
                        apply(val, exp, op);
                    }
                    op.push(cur);
                }
            }
            while (!op.empty()) apply(val, exp, op);
            cout << exp.top() << " = " << val.top() << '\n';
        }
    }
    return 0;
}
```

## 总结

本题的关键在于正确理解结合性的适用范围：**仅当相同运算符连续出现时，结合性才起作用；不同运算符之间始终保持左结合**。利用调度场算法，通过精确的优先级比较规则，可以简洁地实现这一逻辑。同时，将括号视为普通运算符，避免了额外处理分组符号的复杂性，使代码更加通用。该解法时间复杂度为 $O(L)$，空间复杂度为 $O(L)$，能够高效处理所有合法输入。
