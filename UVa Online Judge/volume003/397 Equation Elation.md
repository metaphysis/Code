[UVa 397 Equation Elation](https://blog.csdn.net/metaphysis/article/details/161705487)

## 题目描述

小学代数教科书的作者希望你编写一个程序来求解简单的代数方程。所有问题都将采用代数等式的形式，包含整数常量、四个基本算术运算符、等号和一个变量。

例如：
```
12 - 4*3 = x
```

输出应逐步显示求解过程：
```
12 - 4*3 = x
12 - 12 = x
0 = x
```

运算遵循标准优先级：先乘除（从左到右），后加减（从左到右）。所有除法结果均为整数。

### 输入格式

输入文件包含多个待求解的方程。每个方程包含 $1$ 到 $20$ 个运算符，$2$ 到 $21$ 个整数操作数。整数可以带有前导符号（即一元运算符）。输入行中的空格是可选的。变量名由 $1$ 到 $8$ 个字母组成。

### 输出格式

每个问题的输出以原问题开始，然后每执行一次操作输出一行。每个问题的输出之间用一个空行分隔。

### 样例输入

```
3*4+4-1/1=xyzzy
12+2*12/2-1=y
2*-3+-6-+4=r
```

### 样例输出

```
3 * 4 + 4 - 1 / 1 = xyzzy
3 * 4 + 4 - 1 = xyzzy
12 + 4 - 1 = xyzzy
16 - 1 = xyzzy
15 = xyzzy

12 + 2 * 12 / 2 - 1 = y
12 + 24 / 2 - 1 = y
12 + 12 - 1 = y
24 - 1 = y
23 = y

2 * -3 + -6 - 4 = r
-6 + -6 - 4 = r
-12 - 4 = r
-16 = r
```

---

## 题目分析

### 问题的本质

这是一个**算术表达式逐步求值**问题。需要：
1. 解析表达式（处理一元运算符）
2. 按优先级逐步化简表达式
3. 每次化简后输出当前表达式
4. 最终得到变量值

### 表达式结构

表达式包含：
- 整数（可能带有前导 `+` 或 `-`）
- 运算符 `*`、`/`、`+`、`-`
- 等号 `=`
- 变量名（由字母组成）

### 求值策略

1. 先处理所有乘除运算（从左到右）
2. 再处理所有加减运算（从左到右）
3. 每次只执行一个运算，然后输出

---
## 参考代码

```cpp
// Equation Elation
// UVa ID: 397
// Verdict: Accepted
// Submission Date: 2016-07-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int cases = 0;
    string line;
    
    while (getline(cin, line))
    {
        // 去除空格
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);

        vector<string> equation;
        
        // 解析表达式
        int position = 0;
        while (position < line.length())
        {
            if (line[position] == '*' || line[position] == '/')
            {
                equation.push_back(string(1, line[position++]));
                
                // 读取数字（可能带符号）
                string value;
                value += line[position++];
                while (position < line.length() && isdigit(line[position]))
                    value += line[position++];
                equation.push_back(to_string(stoi(value)));
            }
            else if (line[position] == '+' || line[position] == '-')
            {
                // 判断是一元还是二元运算符
                if (position == 0 || 
                    (line[position - 1] == '*' || line[position - 1] == '/' || 
                     line[position - 1] == '+' || line[position - 1] == '-'))
                {
                    // 一元运算符，属于数字的一部分
                    string value;
                    value += line[position++];
                    while (position < line.length() && isdigit(line[position]))
                        value += line[position++];
                    equation.push_back(to_string(stoi(value)));
                }
                else
                {
                    // 二元运算符
                    equation.push_back(string(1, line[position++]));
                    
                    string value;
                    value += line[position++];
                    while (position < line.length() && isdigit(line[position]))
                        value += line[position++];
                    equation.push_back(to_string(stoi(value)));
                }
            }
            else if (line[position] == '=')
            {
                equation.push_back("=");
                string variable;
                position++;
                while (position < line.length())
                    variable += line[position++];
                equation.push_back(variable);
            }
            else if (isdigit(line[position]))
            {
                string value;
                while (position < line.length() && isdigit(line[position]))
                    value += line[position++];
                equation.push_back(to_string(stoi(value)));
            }
        }
        
        // 测试用例间空行
        if (cases++ > 0)
            cout << endl;
        
        // 逐步化简
        while (equation.size() > 3)
        {
            // 输出当前状态
            for (int i = 0; i < equation.size(); i++)
            {
                if (i > 0) cout << " ";
                cout << equation[i];
            }
            cout << "\n";
            
            // 优先处理乘除
            bool updated = false;
            for (int i = 0; i < equation.size(); i++)
                if (equation[i] == "*" || equation[i] == "/")
                {
                    updated = true;
                    int a = stoi(equation[i - 1]);
                    int b = stoi(equation[i + 1]);
                    int result = (equation[i] == "*") ? a * b : a / b;
                    equation[i - 1] = to_string(result);
                    equation.erase(equation.begin() + i);
                    equation.erase(equation.begin() + i);
                    break;
                }
            
            // 没有乘除，处理加减
            if (!updated)
            {
                for (int i = 0; i < equation.size(); i++)
                    if (equation[i] == "+" || equation[i] == "-")
                    {
                        int a = stoi(equation[i - 1]);
                        int b = stoi(equation[i + 1]);
                        int result = (equation[i] == "+") ? a + b : a - b;
                        equation[i - 1] = to_string(result);
                        equation.erase(equation.begin() + i);
                        equation.erase(equation.begin() + i);
                        break;
                    }
            }
        }
        
        // 输出最终结果
        for (int i = 0; i < equation.size(); i++)
        {
            if (i > 0) cout << " ";
            cout << equation[i];
        }
        cout << "\n";
    }
    
    return 0;
}
```
