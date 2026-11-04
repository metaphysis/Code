
> **摘要**：本题要求在 $(M+1)\times(N+1)$ 的棋盘上用 $K$ 种颜色染色，满足相邻格子异色且同色格子曼哈顿距离为偶数。通过奇偶性分析可将问题拆分为两个独立子问题，利用第二类斯特林数与排列数化简组合计数，预处理后单次查询仅需 $O(K)$，可高效处理 $T \le 50000$ 组数据。

## 题目描述

给定一个矩形棋盘，需要画 $M$ 条水平线和 $N$ 条垂直线，将其分成 $(M + 1) \times (N + 1)$ 个格子。第 $x$ 行第 $y$ 列的格子记为 $\textit{cell}(x, y)$。两个格子之间的距离定义为曼哈顿距离：

$$
\textit{dist}(\text{cell}(x_1, y_1), \textit{cell}(x_2, y_2)) = |x_1 - x_2| + |y_1 - y_2|。
$$

现用 $K$ 种颜色给所有格子染色，需要满足：

1. 任意两个相邻格子（距离为 $1$）的颜色不能相同。
2. 任意两个同色格子的距离不能是奇数。

颜色可以不全部使用，但每个格子必须被染色。求所有合法染色方案数，结果对 $10^9 + 7$ 取模。

## 输入格式

第一行包含一个整数 $T$（$T \le 50000$），表示测试用例数量。  
接下来 $T$ 行，每行三个整数 $M, N, K$（$0 \le M, N \le 19$，$1 \le K \le 50$）。

## 输出格式

对于每个测试用例，输出一行 `Case #: P`，其中 `#` 为用例编号（从 $1$ 开始），`P` 为方案数对 $10^9+7$ 取模的结果。

## 样例

输入

```
4
0 0 1
0 0 2
5 5 2
5 5 1
```

输出

```
Case 1: 1
Case 2: 2
Case 3: 2
Case 4: 0
```

## 题目分析

本题的关键在于约束条件的转化。第二个条件“同色格子距离不能为奇数”实际上限制了同一种颜色只能出现在棋盘上具有相同 $(x+y)$ 奇偶性的格子中。因为曼哈顿距离的奇偶性完全由 $(x+y)$ 的奇偶性是否一致决定：

- 若 $(x_1 + y_1)$ 与 $(x_2 + y_2)$ 同奇偶，则距离为偶数。
- 若奇偶性不同，则距离为奇数。

因此，若两种颜色的格子具有不同的 $(x+y)$ 奇偶性，它们之间距离必然为奇数，这与“同色不能有奇数距离”矛盾。所以每种颜色至多只能染一种奇偶性的格子集合。也就是说，整个染色过程可以分解为两个独立的子问题：用若干种颜色染所有 $(x+y)$ 为偶数的格子，用剩余颜色染 $(x+y)$ 为奇数的格子，且两者使用的颜色集合不能有交集。

第一个条件“相邻格子颜色不同”在满足第二个条件后自然成立吗？不完全是。相邻格子一定具有相反奇偶性，所以它们颜色必然来自不同的颜色集合，因此只要两个颜色集合不相交，就自动满足相邻不同色。所以第一个条件并不额外增加限制，它已由第二个条件保证。

于是问题转化为：设棋盘总格数为 $S = (M+1)(N+1)$，其中偶数格（$(x+y)$ 为偶数）的数量为 $A$，奇数格数量为 $B$。显然 $A = \lceil S/2 \rceil$，$B = \lfloor S/2 \rfloor$。我们用 $K$ 种颜色，从中选出 $e$ 种染偶数格集合，$o$ 种染奇数格集合，且 $e + o \le K$。对于大小为 $A$ 的集合，使用恰好 $e$ 种不同颜色（每种颜色至少使用一次）的染色方案数是多少？这是经典的“将 $A$ 个不同格子分给 $e$ 种不同颜色且每种颜色非空”的计数，等于 $e! \cdot S(A, e)$，其中 $S(n, k)$ 为第二类斯特林数。类似地，奇数格集合的方案数为 $o! \cdot S(B, o)$。

选择颜色的方式为：先从 $K$ 种中选 $e$ 种给偶数格，再从剩下的 $K-e$ 种中选 $o$ 种给奇数格，即 $\binom{K}{e} \binom{K-e}{o}$。因此总方案数为：

$$
\sum_{e, o \ge 0, \, e+o \le K} \binom{K}{e} \binom{K-e}{o} \cdot e! \cdot S(A, e) \cdot o! \cdot S(B, o)。
$$

化简组合系数：

$$
\binom{K}{e} \binom{K-e}{o} \cdot e! \cdot o! = \frac{K!}{e!(K-e)!} \cdot \frac{(K-e)!}{o!(K-e-o)!} \cdot e! \cdot o! = \frac{K!}{(K-e-o)!}。
$$

令 $t = e+o$，则上式对给定 $t$ 的和为：

$$
\sum_{t=0}^{K} \frac{K!}{(K-t)!} \cdot \sum_{e=0}^{t} S(A, e) \, S(B, t-e)。
$$

记排列数 $P(K, t) = \frac{K!}{(K-t)!}$，并定义 $g_{A,B}[t] = \sum_{e=0}^{t} S(A, e) S(B, t-e)$。则答案即为：

$$
\sum_{t=0}^{K} P(K, t) \cdot g_{A,B}[t]。
$$

由于 $M, N \le 19$，所以 $S \le 400$，$K \le 50$。我们完全可以预处理所有可能出现的 $A, B$ 对应的 $g_{A,B}[t]$，以及阶乘和排列数，从而每个测试用例只需 $O(K)$ 时间累加即可。

## 解题思路

### 预处理

1. **第二类斯特林数**：  
   $S(n, k)$ 表示将 $n$ 个不同元素划分成 $k$ 个非空无序集合的方案数。递推公式为：
   $$
   S(n, k) = S(n-1, k-1) + k \cdot S(n-1, k)。
   $$
   边界条件 $S(0,0)=1$，$S(n,0)=0$（$n>0$）。由于最大格子数为 $400$，我们只需计算到 $S(400, 400)$。

2. **阶乘与逆阶乘**：  
   需要计算 $0!$ 到 $K$ 的阶乘，以及其逆元，用于快速求排列数 $P(K, t)$。模数为 $10^9+7$，可用费马小定理求逆元。

3. **组合量 $g_{A,B}[t]$**：  
   对于每种可能的格子总数 $S$（$1 \le S \le 400$），计算 $A = (S+1)/2$，$B = S/2$。然后对 $t$ 从 $0$ 到 $K$（$K \le 50$）计算卷积：
   $$
   g_{A,B}[t] = \sum_{e=0}^{t} S(A, e) \cdot S(B, t-e)。
   $$
   这里 $S(A, e)$ 在 $e > A$ 时为 $0$，同理 $S(B, t-e)$ 在 $t-e > B$ 时为 $0$，因此求和范围可限制。由于 $A, B \le 400$，而 $t \le 50$，直接循环即可，无需优化。

### 查询

对于每个测试用例，给定 $M, N$，计算 $S = (M+1)(N+1)$，$A = (S+1)/2$，$B = S/2$。然后遍历 $t = 0$ 到 $K$，累加：

$$
\textit{ans} = \sum_{t=0}^{K} \left( \frac{K!}{(K-t)!} \bmod \text{MOD} \right) \cdot g_{A,B}[t] \bmod \text{MOD}。
$$

排列数可通过预处理的阶乘和逆阶乘得到：$P(K, t) = \text{fact}[K] \cdot \textit{invFact}[K-t] \bmod \text{MOD}$。

### 复杂度分析

- 预处理斯特林数：$O(400^2)$。
- 预处理阶乘及逆元：$O(50)$。
- 预处理所有 $g_{A,B}[t]$：对每个 $S$（$1$ 到 $400$）和 $t$（$0$ 到 $50$）内层求和至多 $t+1 \le 51$，总操作数约 $400 \times 50 \times 25 \approx 5 \times 10^5$，可忽略。
- 每个查询：$O(K) \le O(50)$。
- 总时间复杂度：预处理 $O(400^2)$，总查询 $O(T \cdot K)$，$T$ 最大 $50000$，最坏 $2.5 \times 10^6$ 次操作，完全可行。
- 空间复杂度：$O(400^2 + 400 \times 50)$，主要存储斯特林数和 $g$ 数组。

## 代码实现


```cpp
// Colorful Board (II)
// UVa ID: 11798
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_S = 400;
const int MAX_K = 50;
const long long MOD = 1000000007LL;

long long stirling[MAX_S + 1][MAX_S + 1];
long long ways[201][201][MAX_K + 1];
long long factorial[MAX_K + 1];
long long invFactorial[MAX_K + 1];

long long modPow(long long a, long long e) {
    long long res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

void precompute() {
    // 第二类斯特林数
    stirling[0][0] = 1;
    for (int n = 1; n <= MAX_S; ++n) {
        stirling[n][0] = 0;
        for (int k = 1; k <= n; ++k)
            stirling[n][k] = (stirling[n - 1][k - 1] + (long long)k * stirling[n - 1][k]) % MOD;
    }
    // 阶乘
    factorial[0] = 1;
    for (int i = 1; i <= MAX_K; ++i) factorial[i] = factorial[i - 1] * i % MOD;
    // 逆阶乘
    invFactorial[MAX_K] = modPow(factorial[MAX_K], MOD - 2);
    for (int i = MAX_K - 1; i >= 0; --i) invFactorial[i] = invFactorial[i + 1] * (i + 1) % MOD;
    // 预处理 g[A][B][t]
    for (int S = 1; S <= MAX_S; ++S) {
        int A = (S + 1) / 2;
        int B = S / 2;
        for (int t = 0; t <= MAX_K; ++t) {
            long long sum = 0;
            for (int e = 0; e <= t; ++e)
                sum = (sum + stirling[A][e] * stirling[B][t - e]) % MOD;
            ways[A][B][t] = sum;
        }
    }
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int M, N, K;
        scanf("%d %d %d", &M, &N, &K);
        int total = (M + 1) * (N + 1);
        int A = (total + 1) / 2;
        int B = total / 2;
        long long ans = 0;
        for (int t = 0; t <= K; ++t) {
            long long perm = factorial[K] * invFactorial[K - t] % MOD;
            ans = (ans + perm * ways[A][B][t]) % MOD;
        }
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
```

## 总结

本题将看似复杂的棋盘染色约束转化为奇偶性分类，从而将问题分解为两个独立的经典计数问题：将若干不同元素用指定颜色且每种颜色非空的染色方案数。核心技巧是利用第二类斯特林数和排列数化简组合计数，并预处理所有可能的状态以应对多组查询。关键点包括：

- 奇偶性分析简化条件。
- 组合恒等式化简双枚举为单重枚举。
- 预处理斯特林数和卷积数组，使单次查询达到 $O(K)$ 高效时间。

这种通过数学转化减少状态空间的方法，在棋盘染色、图着色等组合计数问题中具有普遍参考价值。
