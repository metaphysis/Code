
> **摘要**：本题给定正整数 $N$（$1 \le N \le 10^{14}$），要求计算 $S = \sum_{i \mid N} \sum_{j \mid N} \gcd(i, j)$。直接枚举因子对复杂度为 $O(d(N)^2)$，无法接受。本文利用恒等式 $\gcd(a,b) = \sum_{d \mid \gcd(a,b)} \varphi(d)$ 并交换求和次序，将 $S$ 化简为 $S = \sum_{d \mid N} \varphi(d) \cdot \tau^2(N/d)$，再结合质因数分解与 DFS 枚举指数组合，把复杂度降至 $O(d(N))$，并给出线性筛预处理质数的实现。

## 题目描述

给定一个正整数 $N$（$1 \le N \le 10^{14}$），定义函数 $S$ 为：

$$
S = \sum_{i \mid N} \sum_{j \mid N} \gcd(i, j)
$$

即枚举 $N$ 的所有正因子 $i$ 和 $j$（有序数对），将所有 $\gcd(i, j)$ 累加。要求对于每个给定的 $N$，计算 $S$ 的值。

## 输入格式

第一行一个整数 $T$（$T \le 100$），表示测试用例数。  
接下来 $T$ 行，每行一个整数 $N$（$1 \le N \le 10^{14}$）。

## 输出格式

对于每个测试用例，输出一行 `Case I: S`，其中 $I$ 为用例编号（从 $1$ 开始），$S$ 为对应的计算结果。保证答案在 64 位有符号整数范围内。

## 样例

输入

```
12
1
2
3
4
5
6
7
8
9
10
1000
10000
```

输出

```
Case 1: 1
Case 2: 5
Case 3: 6
Case 4: 15
Case 5: 8
Case 6: 30
Case 7: 10
Case 8: 37
Case 9: 23
Case 10: 40
Case 11: 8584
Case 12: 97027
```

## 题目分析

直接按照定义，先枚举 $N$ 的所有因子，再两两枚举计算最大公约数，时间复杂度为 $O(d(N)^2)$，其中 $d(N)$ 表示因子个数。$N$ 最大可到 $10^{14}$，其因子个数最多约为 $10^5$ 级别（例如 $N = 963460800$ 等高度合数），平方后达到 $10^{10}$，无法接受。因此需要利用数论公式对 $S$ 进行化简。

注意到 $\gcd(i, j)$ 可以表示为 $\sum_{d \mid \gcd(i, j)} \varphi(d)$，其中 $\varphi$ 为欧拉函数。交换求和次序后，可将 $S$ 转化为仅关于 $N$ 的因子及其欧拉函数和因子个数的形式，从而避免双重枚举。

## 解题思路

### 公式推导

利用恒等式：

$$
\gcd(a, b) = \sum_{d \mid a, \; d \mid b} \varphi(d)
$$

代入 $S$ 的定义：

$$
S = \sum_{i \mid N} \sum_{j \mid N} \sum_{d \mid i, \; d \mid j} \varphi(d)
$$

交换求和顺序，先枚举 $d$，则 $d$ 必须同时整除 $i$ 和 $j$，因此 $d$ 必须整除 $N$。于是：

$$
S = \sum_{d \mid N} \varphi(d) \cdot \left( \#\{ i : i \mid N, \; d \mid i \} \right)^2
$$

对于固定的 $d \mid N$，满足条件的 $i$ 可以写成 $i = d \cdot x$，其中 $x \mid (N/d)$。因此这样的 $i$ 的个数等于 $(N/d)$ 的因子个数，记作 $\tau(N/d)$。于是得到：

$$
S = \sum_{d \mid N} \varphi(d) \cdot \tau^2\left(\frac{N}{d}\right) \tag{1}
$$

### 基于质因数分解的计算

设 $N$ 的质因数分解为：

$$
N = \prod_{t=1}^{k} p_t^{a_t}
$$

则任一因子 $d$ 可以表示为 $d = \prod_{t=1}^{k} p_t^{b_t}$，其中 $0 \le b_t \le a_t$。

- 欧拉函数值：  
  $$
  \varphi(d) = \prod_{t=1}^{k} \varphi(p_t^{b_t})
  $$
  其中
  $$
  \varphi(p_t^{b_t}) = 
  \begin{cases}
  1 & \text{若 } b_t = 0 \\
  p_t^{b_t - 1} (p_t - 1) & \text{若 } b_t \ge 1
  \end{cases}
  $$

- 因子个数：  
  $$
  \tau\left(\frac{N}{d}\right) = \prod_{t=1}^{k} (a_t - b_t + 1)
  $$

因此，我们只需枚举所有可能的指数组合 $(b_1, b_2, \dots, b_k)$，累计 $\varphi(d) \cdot \tau^2(N/d)$ 即可。总枚举量为 $\prod_{t=1}^{k} (a_t + 1)$，即 $N$ 的因子个数。对于 $10^{14}$ 范围内的数，因子个数最多约为 $10^5$，完全可行。

### 算法步骤

1. 预处理 $10^7$ 以内的所有质数（因为 $\sqrt{10^{14}} = 10^7$），使用线性筛。
2. 对于每个 $N$：
   - 分解质因数，得到质数列表和对应指数。
   - 使用深度优先搜索（$\texttt{DFS}$）枚举所有因子 $d$ 的指数组合，同时维护当前 $d$ 的欧拉函数值 $\varphi(d)$ 和 $\tau(N/d)$ 的乘积部分。
   - 每到达一个完整组合，累加 $\varphi(d) \cdot \tau^2(N/d)$ 到答案。
3. 输出答案。

### 复杂度分析

- 预处理质数：$O(10^7)$。
- 每个 $N$ 的质因数分解：试除所有不超过 $\sqrt{N}$ 的质数，最多约 $6.6 \times 10^5$ 个质数，$T = 100$ 时总除法次数约 $6.6 \times 10^7$，可接受。
- 枚举因子组合：总枚举次数等于 $d(N)$，最坏约 $10^5$，对每个测试用例均可快速完成。
- 总体时间复杂度：$O(10^7 + T \cdot \pi(10^7) + T \cdot d(N))$，空间复杂度 $O(10^7)$。

## 代码实现

```cpp
// Yet another GCDSUM
// UVa ID: 13083
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 线性筛法求 1e7 以内的所有质数
const int MAXP = 10000000;
vector<int> primes;
vector<int> lp(MAXP + 1, 0);

void sieve() {
    for (int i = 2; i <= MAXP; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lp[i] || 1LL * i * p > MAXP) break;
            lp[i * p] = p;
        }
    }
}

// 分解质因数，返回 vector<pair<质数, 指数>>
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> fac;
    for (int p : primes) {
        if (1LL * p * p > n) break;
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                ++cnt;
            }
            fac.push_back({p, cnt});
        }
    }
    if (n > 1) fac.push_back({n, 1});
    return fac;
}

vector<pair<long long, int>> factors; // 当前 N 的质因数分解
int k;                                // 质因数个数
__int128 ans;                         // 累加答案（防止中间溢出）

// DFS 枚举所有因子指数组合
// idx    : 当前处理的质因数下标
// phi    : 当前因子 d 的欧拉函数值
// tau    : 当前已选指数对应的 (N/d) 因子个数部分乘积
void dfs(int idx, long long phi, long long tau) {
    if (idx == k) {
        ans += (__int128)phi * tau * tau;
        return;
    }
    long long p = factors[idx].first;
    int a = factors[idx].second;
    long long curPow = 1; // p^b，b 从 0 开始
    for (int b = 0; b <= a; ++b) {
        long long newPhi = phi;
        if (b > 0) {
            // 计算 phi(p^b) = p^{b-1} * (p-1)
            long long pPowBminus1 = curPow / p; // curPow == p^b
            newPhi = (long long)((__int128)phi * (p - 1) * pPowBminus1);
        }
        long long newTau = tau * (a - b + 1);
        dfs(idx + 1, newPhi, newTau);
        curPow *= p; // 准备下一个指数
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        long long N;
        cin >> N;
        factors = factorize(N);
        k = (int)factors.size();
        ans = 0;
        dfs(0, 1, 1); // 初始 d=1, phi(1)=1, tau=1
        cout << "Case " << caseNo << ": " << (long long)ans << '\n';
    }
    return 0;
}
```

## 总结

本题的核心在于利用数论恒等式将双重因子求和转化为单重因子求和，从而将复杂度从 $O(d(N)^2)$ 降为 $O(d(N))$。关键技巧包括：

1. **欧拉函数与最大公约数的恒等式**：$\gcd(a,b) = \sum_{d \mid \gcd(a,b)} \varphi(d)$，这是化简的基础。
2. **交换求和顺序**：将内层求和转化为因子个数的平方，避免两两枚举。
3. **质因数分解与 $\texttt{DFS}$ 枚举因子**：利用指数的组合来遍历所有因子，同时维护所需的 $\varphi$ 和 $\tau$ 值，无需显式构造因子列表。

通过上述方法，可以在严格的时间限制内处理 $10^{14}$ 级别的输入，且代码实现简洁高效。对于类似的双重求和问题，若可转化为因子求和形式，应优先考虑数论公式优化。
