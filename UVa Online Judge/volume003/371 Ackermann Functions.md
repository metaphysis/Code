[UVa 371 Ackermann Functions](https://blog.csdn.net/metaphysis/article/details/161642286)


## 题目描述

阿克曼函数的一个特性是：函数生成的数列长度无法直接从输入值计算得出。一种特定的整数阿克曼函数定义如下：

$$
f(n) = \begin{cases}
n/2 & \text{if } n \text{ is even} \\
3n + 1 & \text{if } n \text{ is odd}
\end{cases}
$$

该阿克曼函数的特性是它最终收敛到 $1$。示例（起始值在方括号中，后跟生成的数列，数列长度在大括号中）：

- $[10]\ 5\ 16\ 8\ 4\ 2\ 1\ \{6\}$
- $[13]\ 40\ 20\ 10\ 5\ 16\ 8\ 4\ 2\ 1\ \{9\}$
- $[14]\ 7\ 22\ 11\ 34\ 17\ 52\ 26\ 13\ 40\ 20\ 10\ 5\ 16\ 8\ 4\ 2\ 1\ \{17\}$
- $[19]\ 58\ 29\ 88\ 44\ 22\ \dots\ 2\ 1\ \{20\}$
- $[32]\ 16\ 8\ 4\ 2\ 1\ \{5\}$
- $[1]\ 4\ 2\ 1\ \{3\}$

### 输入格式

输入包含多行，每行两个整数，表示区间的起始和结束值。最后一行以 `0 0` 结束。

### 输出格式

对于每个区间，输出：

```
Between L and H, V generates the longest sequence of S values.
```

其中 $L$ 和 $H$ 是区间的边界（小的在前），$V$ 是生成最长序列的第一个值（如有并列取较小的），$S$ 是序列长度。

### 样例输入

```
1 20
35 55
0 0
```

### 样例输出

```
Between 1 and 20, 18 generates the longest sequence of 20 values.
Between 35 and 55, 54 generates the longest sequence of 112 values.
```

---

## 题目分析

### 问题的本质

这是经典的 $3n+1$ 问题（也称考拉兹猜想、冰雹猜想）。需要计算区间内每个数生成到 $1$ 的序列长度，并找出最长者。

### 序列长度定义

从起始数开始，按规则生成，直到到达 $1$ 为止。注意：起始数本身也算一个值。

例如：$[10] \to 5 \to 16 \to 8 \to 4 \to 2 \to 1$，长度为 $6$（$10$ 到 $1$ 共 $6$ 个数）。

### 数据范围

输入值在 $32$ 位整数范围内，但中间值可能超过 $32$ 位，需要使用 `long long`。

### 优化策略

使用**记忆化搜索**（$\texttt{memoization}$）缓存已计算的值。由于区间最大可能很大（如 $1 \sim 10^6$），直接计算每个数会重复大量计算。

---
## 参考代码

```cpp
// Ackermann Functions
// UVa ID: 371
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int cache[500010] = {0};  // 缓存序列长度
// 递归计算从 number 到 1 的序列长度
int counter(long long int number) {
    // 奇数：3n+1，偶数：n/2
    if (number & 1) number += (number << 1) + 1;
    else number >>= 1;
    if (number == 1) return 1;
    // 如果在缓存范围内且未计算过，递归计算
    if (number <= 500000) {
        if (!cache[number])
            cache[number] = counter(number);
        return 1 + cache[number];
    }
    // 超出缓存范围，继续递归
    return 1 + counter(number);
}

int main() {
    ios::sync_with_stdio(false);
    // 预处理所有 1..500000 的序列长度
    for (int i = 1; i <= 500000; i++)
        cache[i] = counter(i);
    int first, second, start, end;
    while (cin >> first >> second, first && second) {
        start = min(first, second);
        end = max(first, second);
        int result = 0, maxi = start;
        for (int i = start; i <= end; i++) {
            long long temp = i;
            int steps = 0;
            // 处理大于缓存范围的值，直到进入缓存范围
            while (temp > 500000) {
                if (temp & 1) temp += (temp << 1) + 1;  // 3*temp+1
                else temp >>= 1;               // temp/2
                steps++;
            }
            // 加上缓存中的长度
            steps += cache[temp];
            // 更新最大值
            if (steps > result) {
                result = steps;
                maxi = i;
            }
        }
        cout << "Between " << start << " and " << end;
        cout << ", " << maxi << " generates the longest sequence of " << result << " values." << endl;
    }
    return 0;
}
```
