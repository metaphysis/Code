[UVa 374 Big Mod](https://blog.csdn.net/metaphysis/article/details/161642342)

## 题目描述

计算：
$$
R = B^P \bmod M
$$

其中 $B$、$P$、$M$ 可能很大。需要使用高效的算法。

### 输入格式

输入包含多个测试用例，每个测试用例由三行组成（$B$、$P$、$M$），连续测试用例之间由一个空行分隔。

- $B$ 和 $P$：$0 \leq B, P \leq 2147483647$
- $M$：$1 \leq M \leq 46340$

### 输出格式

对于每个测试用例，输出一行，包含计算结果。

### 样例输入

```
3
18132
17

17
1765
3

2374859
3029382
36123
```

### 样例输出

```
13
2
13195
```

---

## 题目分析

### 问题的本质

这是一个**快速幂取模**问题。需要计算 $B^P \bmod M$，其中指数 $P$ 可能高达 $2^{31}-1$，直接循环计算不可行。

### 快速幂算法

利用指数的二进制分解：

$$
B^P = \begin{cases}
(B^{P/2})^2 & \text{if } P \text{ is even} \\
(B^{P/2})^2 \times B & \text{if } P \text{ is odd}
\end{cases}
$$

每次将指数减半，时间复杂度 $O(\log P)$。

### 取模性质

在乘法过程中取模：
$$
(a \times b) \bmod M = ((a \bmod M) \times (b \bmod M)) \bmod M
$$

因此可以在每一步都取模，避免溢出。

### 边界情况

- $P = 0$：$B^0 = 1$，结果为 $1 \bmod M$
- $B \bmod M = 0$：结果为 $0$

---
## 参考代码

```cpp
// Big Mod
// UVa ID: 374
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 递归快速幂取模
long long mod(long long B, long long P, long long M)
{
    if (P == 1)
        return B % M;
    
    if (P == 2)
        return (B * B) % M;
    
    long long m = mod(B, P / 2, M);
    m = (m * m) % M;
    
    if (P % 2 == 1)
        m = (m * (B % M)) % M;
    
    return m % M;
}

int main(int argc, char *argv[])
{
    long long B, P, M;
    
    while (cin >> B >> P >> M)
    {
        // 指数为 0 的特殊情况
        if (P == 0)
        {
            cout << 1 % M << endl;
            continue;
        }
        
        // 底数能被模数整除的情况
        if (B % M == 0)
        {
            cout << 0 << endl;
            continue;
        }
        
        cout << mod(B % M, P, M) << endl;
    }
    
    return 0;
}
```
