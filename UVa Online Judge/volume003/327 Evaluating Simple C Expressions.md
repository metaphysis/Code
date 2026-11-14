[UVa 327 Evaluating Simple C Expressions](https://blog.csdn.net/metaphysis/article/details/161513771)

## 题目描述

本题要求计算一系列简单 `C` 表达式的值。每个表达式占一行，长度不超过 $110$ 个字符。表达式中只包含简单的整型变量和有限的操作符，没有常量。共有 $26$ 个变量 `a` 到 `z`（仅小写字母）。在每个表达式开始求值时，这 $26$ 个变量的初值分别为 $1$ 到 $26$（即 `a = 1`, `b = 2`, ..., `z = 26`）。每个变量在表达式中最多出现一次，许多变量可能根本不会出现。

表达式中可以出现的操作符包括：
- 二元操作符 `+` 和 `-`（加法与减法），具有通常的含义
- 一元操作符 `++` 和 `--`（自增和自减），可以出现在变量之前或之后

### 自增/自减运算符的语义

- **前缀形式**（如 `++a`）：在变量值被使用之前，先将其增加 $1$
- **后缀形式**（如 `a++`）：在变量值被使用之后，再将其增加 $1$
- 减号运算符 `-` 同理，为自减

### 求值算法（简化版）

1. 找出每个变量前面的 `++` 运算符，生成赋值语句递增这些变量，并从表达式中移除这些运算符
2. 找出每个变量后面的 `++` 运算符，生成赋值语句递增这些变量，并从表达式中移除这些运算符
3. 此时表达式只包含二元运算符，计算其值
4. 按顺序执行：第一步的赋值 → 第三步的计算 → 第二步的赋值

### 输入格式

输入包含多行，每行一个表达式，直到文件结束。

### 输出格式

对于每个表达式：
- 第一行输出 `Expression: ` 后跟原表达式
- 第二行输出 `    value = ` 后跟表达式的值
- 后续每行输出 `    变量 = 值`，按字母顺序输出，只输出表达式中使用过的变量

### 样例输入

```
a+b
b-z
a+b- - +c++
c+f- - +- - a
f- - +c- - +d- +e
```

### 样例输出

```
Expression: a+b
    value = 3
    a = 1
    b = 2

Expression: b-z
    value = -24
    b = 2
    z = 26

Expression: a+b- - +c++
    value = 6
    a = 1
    b = 1
    c = 4

Expression: c+f- - +- - a
    value = 9
    a = 0
    c = 3
    f = 5

Expression: f- - +c- - +d- +e
    value = 7
    c = 2
    d = 4
    e = 6
    f = 5
```

---

## 题目分析

### 问题的本质

这是一个**表达式求值**问题，但具有特殊的自增/自减运算符语义。由于表达式不包含括号，且变量最多出现一次，我们可以采用**线性扫描 + 状态机**的方式解析。

### 关键难点

自增/自减运算符的**前缀**与**后缀**区别需要正确处理：
- 前缀 `++a`：先自增，再使用值
- 后缀 `a++`：先使用值，再自增

由于变量在表达式中最多出现一次，我们不需要考虑复杂的副作用顺序问题。

### 解析策略

由于表达式中可能含有空格，需要先过滤掉空白字符。然后从左到右扫描，识别：
- 一元运算符（`+`、`-`、`++`、`--`）
- 二元运算符（`+`、`-`）
- 变量名（`a` ~ `z`）

### 表达式结构简化

观察表达式 `a+b- - +c++`：

去除空格后：`a+b--+c++`

根据自增/自减的语义，可以将其分解为：
- 前缀 `++` 或 `--` 紧跟在二元运算符之后
- 后缀 `++` 或 `--` 紧跟在变量之后

---

## 参考代码

```cpp
// Evaluating Simple C Expressions
// UVa ID: 327
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    char readed[1024];  // 存储过滤后的表达式字符
    string line;

    while (getline(cin, line))
    {
        // 初始化变量：-1 表示未使用，否则存储最终值
        int variable[26] = { };
        int used[26] = { };
        int position = 0;
        int value = 0;

        // 过滤空白字符，将有效字符存入 readed
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ' ' || line[i] == '\t')
                continue;
            if (line[i] == '+' || line[i] == '-' || isalpha(line[i]))
            {
                readed[position++] = line[i];
                
                // 模式1：后缀自增/自减 ... 变量 ++ 或 变量 --
                // 序列：变量、运算符、运算符
                if (position >= 3 && isalpha(readed[position - 3]))
                {
                    if ((readed[position - 1] == '+' && readed[position - 2] == '+') ||
                        (readed[position - 1] == '-' && readed[position - 2] == '-'))
                    {
                        int sign = 1;
                        int letter = readed[position - 3] - 'a';
                        // 检查前面的符号（决定正负）
                        if (position >= 4 && readed[position - 4] == '-')
                            sign = -1;
                        
                        // 后缀形式：使用原值，然后自增/自减
                        value += (letter + 1) * sign;
                        used[letter] = 1;
                        // 最终值：原值 +1 或 -1
                        variable[letter] = letter + (readed[position - 1] == '+' ? 2 : 0);
                        // 移除已处理的 3 或 4 个字符
                        position -= (position >= 4 ? 4 : 3);
                    }
                }
                // 模式2：前缀自增/自减 ++ 变量 或 -- 变量
                // 序列：运算符、运算符、变量
                else if (position >= 3 && isalpha(readed[position - 1]))
                {
                    if ((readed[position - 2] == '+' && readed[position - 3] == '+') ||
                        (readed[position - 2] == '-' && readed[position - 3] == '-'))
                    {
                        int sign = 1;
                        int letter = readed[position - 1] - 'a';
                        if (position >= 4 && readed[position - 4] == '-')
                            sign = -1;
                        
                        // 前缀形式：先自增/自减，再使用值
                        value += (letter + (readed[position - 2] == '+' ? 2 : 0)) * sign;
                        used[letter] = 1;
                        variable[letter] = letter + (readed[position - 2] == '+' ? 2 : 0);
                        position -= (position >= 4 ? 4 : 3);
                    }
                }
            }
        }

        // 处理剩余的二元表达式（只有变量和 + / - 运算符）
        for (int i = 0; i < position; i++)
            if (isalpha(readed[i]))
            {
                int letter = readed[i] - 'a';
                used[letter] = 1;
                // 如果变量尚未赋值（没有自增/自减），初始值为 letter+1
                if (variable[letter] == 0)
                    variable[letter] = letter + 1;
                
                int sign = 1;
                if (i > 0 && readed[i - 1] == '-')
                    sign = -1;
                value += sign * variable[letter];
            }

        // 输出结果
        cout << "Expression: " << line << "\n";
        cout << "    value = " << value << "\n";
        for (int i = 0; i < 26; i++)
            if (used[i])
                cout << "    " << (char)('a' + i) << " = " << variable[i] << "\n";
    }

    return 0;
}
```
