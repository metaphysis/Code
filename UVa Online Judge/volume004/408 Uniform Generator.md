[UVa 408 Uniform Generator](https://blog.csdn.net/metaphysis/article/details/161737147)

## 题目描述

题目涉及一种伪随机数生成器，其递推公式为：

$$
\textit{seed}(x + 1) = [\textit{seed}(x) + \textit{STEP}] \% \textit{MOD}
$$

其中 $\%$ 为取模运算符。该生成器会产生 $0$ 到 $\textit{MOD} - 1$ 之间的伪随机数序列。如果 $\textit{STEP}$ 和 $\textit{MOD}$ 选择得当，该序列可以在 $\textit{MOD}$ 次迭代内生成 $0$ 到 $\textit{MOD} - 1$ 之间的所有整数，从而实现均匀分布。

例如，$\textit{STEP} = 3$，$\textit{MOD} = 5$ 时，序列为 $0, 3, 1, 4, 2$，覆盖了 $0$ 到 $4$ 的所有数字。而 $\textit{STEP} = 15$，$\textit{MOD} = 20$ 时，序列为 $0, 15, 10, 5, \ldots$，无法覆盖所有数字。

本题要求判断给定的 $\textit{STEP}$ 和 $\textit{MOD}$ 是否能生成均匀分布的伪随机数序列。

## 输入格式

输入包含多行，每行两个整数 $\textit{STEP}$ 和 $\textit{MOD}$（$1 \le \textit{STEP}, \textit{MOD} \le 100000$）。

## 输出格式

对于每行输入，输出三部分：
- $\textit{STEP}$ 值，右对齐占第 $1$ 到 $10$ 列。
- $\textit{MOD}$ 值，右对齐占第 $11$ 到 $20$ 列。
- 从第 $25$ 列开始，左对齐输出 $\texttt{Good Choice}$ 或 $\texttt{Bad Choice}$。

每组输出后跟一个空行。

## 样例

输入

```
3 5
15 20
63923 99999
```

输出

```
         3         5    Good Choice

        15        20    Bad Choice

     63923     99999    Good Choice
```

## 题目分析

本题的核心是判断线性同余生成器 $x_{n+1} = (x_n + \textit{STEP}) \bmod \textit{MOD}$ 是否具有最大周期 $\textit{MOD}$，即能否在 $\textit{MOD}$ 次迭代内生成 $0$ 到 $\textit{MOD} - 1$ 的所有整数。

### 周期条件

从初始值 $0$ 开始，序列为：
$$
0,\ \textit{STEP} \bmod \textit{MOD},\ 2 \times \textit{STEP} \bmod \textit{MOD},\ 3 \times \textit{STEP} \bmod \textit{MOD},\ \ldots
$$

一般项为 $k \times \textit{STEP} \bmod \textit{MOD}$。该序列的周期等于满足 $k \times \textit{STEP} \equiv 0 \pmod{\textit{MOD}}$ 的最小正整数 $k$，即 $\textit{MOD} / \gcd(\textit{STEP}, \textit{MOD})$。

因此，序列能生成所有 $\textit{MOD}$ 个不同余数的充要条件是：
$$
\frac{\textit{MOD}}{\gcd(\textit{STEP}, \textit{MOD})} = \textit{MOD} \quad \Longleftrightarrow \quad \gcd(\textit{STEP}, \textit{MOD}) = 1
$$

也就是说，$\textit{STEP}$ 与 $\textit{MOD}$ 互质时，生成器是均匀的；否则不是。

### 数学解释

线性同余生成器 $x_{n+1} = (x_n + a) \bmod m$ 的周期等于 $m / \gcd(a, m)$。这是因为每次增加 $a$，相当于在模 $m$ 的加法群中移动。群中由 $a$ 生成的子群的大小为 $m / \gcd(a, m)$。只有当 $\gcd(a, m) = 1$ 时，该子群才是整个群，周期达到最大值 $m$。

### 算法实现

对于每组 $\textit{STEP}$ 和 $\textit{MOD}$，使用欧几里得算法计算最大公约数：
- 若 $\gcd(\textit{STEP}, \textit{MOD}) = 1$，输出 $\texttt{Good Choice}$。
- 否则，输出 $\texttt{Bad Choice}$。

注意输出格式：$\textit{STEP}$ 和 $\textit{MOD}$ 各占 $10$ 列宽度，右对齐；然后输出 $4$ 个空格；最后输出判断结果。每组输出后需打印一个空行。

### 复杂度分析

每组数据使用欧几里得算法求最大公约数，时间复杂度 $O(\log \min(\textit{STEP}, \textit{MOD}))$，完全可接受。

## 代码实现

```cpp
// Uniform Generator
// UVa ID: 408
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int STEP, MOD;
    
    while (cin >> STEP >> MOD)
    {
        cout << setw(10) << right << STEP;
        cout << setw(10) << right << MOD;
        cout << string(4, ' ');
        
        int temp, a = STEP, b = MOD;
        while (a % b) temp = a, a = b, b = temp % b;
        
        if (b == 1) cout << "Good Choice\n\n";
        else cout << "Bad Choice\n\n";
    }
    
    return 0;
}
```