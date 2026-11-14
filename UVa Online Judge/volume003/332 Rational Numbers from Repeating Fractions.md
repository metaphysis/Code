[UVa 332 Rational Numbers from Repeating Fractions](https://blog.csdn.net/metaphysis/article/details/161533385)

## 题目描述

有理数是可以写成 $p/q$ 形式（$p$ 和 $q$ 为整数）的任何数。所有小于 $1$ 的有理数（即 $p < q$）都可以展开为十进制小数，但这种展开可能需要重复某几位尾数。例如，有理数 $7/22$ 的十进制展开是 $0.3181818\ldots$（注意数字对 $18$ 无限重复）。这种具有重复小数展开的数字通常用重复数字上方的横线表示，如 $0.3\overline{18}$。

如果我们给定一个有理分数的十进制展开（并指明哪些数字重复，如果需要），我们可以使用以下算法确定有理分数（即 $p/q$ 中的整数值 $p$ 和 $q$）。

假设小数点后有 $k$ 位数字不重复，随后有 $j$ 位数字重复。例如对于 $7/22$，$k = 1$（数字 $3$），$j = 2$（数字 $1$ 和 $8$）。设 $X$ 为原数（$7/22$），我们可以计算以下表达式的分子和分母：

$$
\frac{10^{k+j} \times X - 10^k \times X}{10^{k+j} - 10^k}
$$

对于 $0.3\overline{18}$，分子计算如下：

$$
10^3 \times 0.3\overline{18} - 10^1 \times 0.3\overline{18} = 318.\overline{18} - 3.\overline{18} = 315
$$

分母为 $1000 - 10 = 990$。该表达式的分子和分母总是整数，代表有理数的分子和分母。因此循环小数 $0.3\overline{18}$ 是有理数 $315/990$ 的小数展开。约简后得到 $7/22$。

### 输入格式

输入数据由一系列测试用例组成，每个测试用例单独一行，后跟一个 $-1$。每个测试用例以一个整数 $j$ 开头（表示重复位数），后跟一个或多个空格，然后是形如 `0.ddddd` 的小数展开。小数展开最多有 $9$ 位数字（即 $k+j \leq 9$）。

### 输出格式

对于每个测试用例，输出用例编号（从 $1$ 开始）和约简后的有理数，格式为 `p/q`。

### 样例输入

```
2 0.318
1 0.3
2 0.09
6 0.714285
-1
```

### 样例输出

```
Case 1: 7/22
Case 2: 1/3
Case 3: 1/11
Case 4: 5/7
```

---

## 题目分析

### 问题的本质

这是一个**循环小数化分数**问题。给定一个小数部分和循环节长度 $j$，需要将其转换为最简分数形式。

### 数学原理

设小数部分为 $0.\underbrace{d_1 d_2 \dots d_k}_{k\text{ 位非循环}}\underbrace{d_{k+1} \dots d_{k+j}}_{j\text{ 位循环}}$。

记：
- $A$ 为 $k$ 位非循环部分组成的整数
- $B$ 为 $j$ 位循环部分组成的整数

则原数 $X$ 可以表示为：
$$
X = 0.\overline{d_1 d_2 \dots d_k d_{k+1} \dots d_{k+j}}
$$

根据题目给出的公式：
$$
\frac{10^{k+j}X - 10^k X}{10^{k+j} - 10^k} = \frac{\text{整数部分}}{10^{k+j} - 10^k}
$$

其中：
- $10^{k+j}X$ 将小数点向右移动 $k+j$ 位
- $10^k X$ 将小数点向右移动 $k$ 位
- 两者相减得到整数

具体地：
$$
10^{k+j}X = \text{(由整数部分和小数部分组成的数)}
$$
但 $X < 1$，所以 $10^{k+j}X$ 的整数部分就是由 $A$ 和 $B$ 组成的整数，小数部分为 $0.\overline{B}$。

同理，$10^k X$ 的整数部分为 $A$，小数部分为 $0.\overline{B}$。

因此：
$$
10^{k+j}X - 10^k X = \text{(整数部分)} - \text{(整数部分)} = (A \times 10^j + B) - A
$$

所以：
$$
X = \frac{(A \times 10^j + B) - A}{10^{k+j} - 10^k}
$$

### 特殊情况

- 当 $j = 0$（没有循环节）时，分数为 $\frac{\text{整数部分}}{10^k}$，即纯有限小数
- 当 $k = 0$（没有非循环部分）时，$A = 0$
## 参考代码

```cpp
// Rational Numbers From Repeating Fractions
// UVa ID: 332
// Verdict: Accepted
// Submission Date: 2017-07-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 欧几里得算法求最大公约数
long long gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

// 将循环小数转换为最简分数
// fraction: 小数部分字符串（不含整数部分）
// j: 循环节长度
pair<long long, long long> getFraction(string fraction, int j)
{
    long long numerator, denominator;

    // 去掉开头的 "0."
    size_t dot = fraction.find('.');
    if (dot != fraction.npos) 
        fraction = fraction.substr(dot + 1);
    
    // 情况1：没有循环节（有限小数）
    if (j == 0)
    {
        numerator = stoll(fraction);
        denominator = pow(10, fraction.length());
    }
    // 情况2：有循环节
    else
    {
        int k = fraction.length() - j;                    // 非循环节位数
        string preRepeated = fraction.substr(0, k);       // 非循环部分
        if (preRepeated.length() == 0) preRepeated = "0"; // 空串时补0
        
        numerator = stoll(fraction) - stoll(preRepeated); // 分子 = 全体 - 非循环部分
        denominator = pow(10, k + j) - pow(10, k);         // 分母 = 10^(k+j) - 10^k
    }
    
    // 约分
    long long g = gcd(numerator, denominator);
    return make_pair(numerator / g, denominator / g);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int j, cases = 0;
    string fraction;
    
    while (cin >> j, j >= 0)
    {
        cin >> fraction;

        pair<long long, long long> r = getFraction(fraction, j);

        cout << "Case " << ++cases << ": " << r.first << "/" << r.second << '\n';
    }
    
    return 0;
}
```
