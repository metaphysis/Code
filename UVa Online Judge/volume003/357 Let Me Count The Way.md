[UVa 357 Let Me Count The Way](https://blog.csdn.net/metaphysis/article/details/161588949)

## 题目描述

$\texttt{Mel}$ 在大商场购物后收到 $17$ 美分找零：$1$ 枚 $10$ 美分、$1$ 枚 $5$ 美分和 $2$ 枚 $1$ 美分。当天晚些时候，他在便利店购物，又收到 $17$ 美分找零：$2$ 枚 $5$ 美分和 $7$ 枚 $1$ 美分。他开始思考：“有多少种不同的硬币组合可以组成 $17$ 美分？”经过一番思考，他得出答案是 $6$ 种。现在他要求你考虑一般情况。

编写程序，计算用美国硬币（$1$ 美分、$5$ 美分、$10$ 美分、$25$ 美分、$50$ 美分）组成给定金额的不同组合数。

### 输入格式

输入包含一组 $0$ 到 $30000$ 之间的整数，每行一个。

### 输出格式

对于每个输入值，输出相应语句：
- 如果有多种组合：`There are m ways to produce n cents change.`
- 如果只有 $1$ 种组合：`There is only 1 way to produce n cents change.`

### 样例输入

```
17
11
4
```

### 样例输出

```
There are 6 ways to produce 17 cents change.
There are 4 ways to produce 11 cents change.
There is only 1 way to produce 4 cents change.
```

---

## 题目分析

### 问题的本质

这是一个经典的**硬币找零问题**（$\texttt{coin change problem}$），属于完全背包问题：给定几种面额的硬币（每种无限供应），求组成特定金额的不同组合数。

### 硬币种类

- $\texttt{Penny}$（$1$ 美分）
- $\texttt{Nickel}$（$5$ 美分）
- $\texttt{Dime}$（$10$ 美分）
- $\texttt{Quarter}$（$25$ 美分）
- $\texttt{Half-dollar}$（$50$ 美分）

### 数据范围

金额最大为 $30000$，硬币种类为 $5$ 种。使用动态规划可以在 $O(5 \times 30000)$ 的时间内预处理所有结果。

### 组合与排列的区别

本题要求的是**组合数**（不考虑硬币顺序），而不是排列数。例如，用 $1$ 美分和 $5$ 美分组成 $6$ 美分：
- 组合：$1+5$（只有一种）
- 排列：$1+5$ 和 $5+1$（两种）

动态规划中的完全背包通常计算的是组合数（通过限制外层循环为硬币种类）。

---

## 解题思路

### 步骤一：动态规划状态定义

设 $dp[i][j]$ 表示使用前 $i$ 种硬币组成金额 $j$ 的组合数。

### 步骤二：状态转移方程

对于硬币种类 $i$，面额为 $c_i$：
- 不使用第 $i$ 种硬币：$dp[i-1][j]$
- 使用第 $i$ 种硬币（至少一枚）：$dp[i][j - c_i]$

因此：
$$
dp[i][j] = dp[i-1][j] + dp[i][j - c_i]
$$

### 步骤三：初始化

$dp[0][0] = 1$（用 $0$ 种硬币组成 $0$ 金额有 $1$ 种方式）

### 步骤四：空间优化

可以使用一维数组，但需要按硬币顺序正向遍历（完全背包）：
```cpp
for (int coin : cents)
    for (int j = coin; j <= MAX; j++)
        ways[j] += ways[j - coin];
```

但注意：一维正向遍历计算的是**组合数**（因为硬币按顺序添加，避免重复计算不同顺序）

### 步骤五：预处理

由于 $n \leq 30000$，可以预先计算所有金额的结果，然后直接查表输出。

---

## 参考代码

```cpp
// Let Me Count The Ways
// UVa ID: 357
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> cents = {1, 5, 10, 25, 50};
    
    // 二维 DP 数组：dp[i][j] 表示用前 i 种硬币组成金额 j 的组合数
    long long int ways[6][30010] = {0};
    ways[0][0] = 1;  // 边界条件
        
    // 动态规划预处理
    for (int i = 1; i <= 5; i++)           // 枚举硬币种类
        for (int j = 0; j <= 30000; j++) {
            // 不使用第 i 种硬币
            ways[i][j] = ways[i - 1][j];
            // 使用至少一枚第 i 种硬币
            if (j - cents[i - 1] >= 0)
                ways[i][j] += ways[i][j - cents[i - 1]];
        }
    
    int n;
    while (cin >> n) {    
        if (ways[5][n] == 1)
            cout << "There is only 1 way to produce " << n << " cents change." << endl;
        else
            cout << "There are " << ways[5][n] << " ways to produce " << n << " cents change." << endl;
    }
    
    return 0;
}
```
