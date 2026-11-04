
> **摘要**：给定一棵有根树，用 $1 \sim n$ 为顶点标号并满足父结点标号大于子结点标号的堆条件，求方案数对任意模数 $m$ 取模的结果。文章从偏序线性扩展的角度推导出闭式公式 $\dfrac{n!}{\prod \textit{size}(u)}$，并针对模数非素数无法求逆元的情况，采用线性筛预处理最小质因子 + 质因数分解的方式精确计算，整体复杂度 $O(n \log n)$。

## 题目描述

给定一棵包含 $n$ 个顶点的有根树。需要用数字 $1, 2, \ldots , n$ 给每个顶点标号，使得每个标号唯一，并且满足堆条件：任意顶点的标号都小于其父顶点的标号。求满足条件的标号方案总数，结果对给定整数 $m$ 取模。

## 输入格式

输入包含多棵树。第一行一个整数 $t$（$t \le 250$），表示树的个数。  
接下来每棵树描述：第一行包含两个整数 $n$（$1 \le n \le 500000$）和 $m$（$2 \le m \le 10^9$）。随后 $n-1$ 行，第 $i$ 行给出 $p(i+1)$，即第 $i+1$ 个顶点的父结点编号（$1 \le p(i+1) \le i$）。顶点 $1$ 是根，不给出其父结点。  
所有输入的总大小不超过 $50$ $\texttt{MB}$。

## 输出格式

对于每棵树，输出其有效标号方案数对 $m$ 取模的结果。

## 样例

**样例输入**
```
4
3 1000000
1
1
4 1000000
1
1
1
5 1000000
1
2
3
4
5 1000000
1
1
3
3
```

**样例输出**
```
2
6
1
8
```

## 题目分析

本题要求计算在固定形态的树结构上，满足“父结点标号大于子结点标号”的标号方案数。由于标号是 $1$ 到 $n$ 的全排列，且条件只限制相对大小关系，因此问题等价于：在树的偏序关系下（根为最小，叶子为最大），求线性扩展（拓扑排序）的个数。

对于一棵树，若已知所有子树的大小，则标号方案数可由递推公式得到。设 $f(u)$ 表示以 $u$ 为根的子树中，用该子树大小个连续标号（不关心具体数值）进行合法标号的方案数。则根结点必须取得该子树中的最小值（即最小标号），剩余标号分配给各个子结点对应的子树，且各子树之间可以任意交错。因此：

$$
f(u) = \binom{\textit{size}(u)-1}{\textit{size}(v_1), \textit{size}(v_2), \ldots, \textit{size}(v_k)} \cdot \prod_{v \in \textit{children}(u)} f(v)
$$

其中 $\textit{size}(u)$ 表示以 $u$ 为根的子树大小，$v_1, \ldots, v_k$ 为 $u$ 的所有子结点。

通过数学归纳，可以得到全局公式：

$$
\text{答案} = \frac{n!}{\prod_{u=1}^{n} \textit{size}(u)}
$$

该公式的直观理解：所有 $n!$ 种标号中，对于每个结点 $u$，其子树内 $u$ 必须是最小值，概率为 $1 / \textit{size}(u)$，且这些事件相互独立，因此总方案数为 $n! / \prod \textit{size}(u)$。

因此，核心任务变为：给定树，计算所有子树的结点数（即子树大小），然后计算上述分数值对 $m$ 取模的结果。由于 $m$ 不一定是素数，无法直接使用模逆元，需要采用质因数分解的方法，精确计算整数结果后再取模。

## 解题思路

### 1. 计算子树大小

使用从叶子向根方向的递推。初始时每个结点子树大小为 $1$，从 $n$ 到 $2$ 逆序遍历（因父结点编号一定小于子结点编号），将子结点的大小累加到父结点上。

### 2. 质因数分解计算组合数

公式中的分子 $n!$ 和分母 $\prod \textit{size}(u)$ 都是整数，最终结果也是整数。我们通过质因数分解来精确计算：

- 对每个质数 $p$，计算其在 $n!$ 中的指数（使用勒让德公式）：  
  $\displaystyle e_n(p) = \sum_{k \ge 1} \left\lfloor \frac{n}{p^k} \right\rfloor$。
- 对每个 $\textit{size}(u)$，分解质因数，并从 $e_n(p)$ 中减去对应的指数。
- 最终每个质数 $p$ 的剩余指数 $e(p) \ge 0$。
- 答案即为 $\prod p^{e(p)} \bmod m$。

由于 $n \le 500000$，我们可以预处理所有数的最小质因子，从而在 $O(\log n)$ 时间内分解任意数。使用线性筛一次性得到所有最小质因子，同时记录所有质数列表。

### 3. 细节处理

- 清空质数指数数组时，只需处理小于等于 $n$ 的质数。
- 快速幂计算时注意底数对 $m$ 取模，指数为长整型（实际不会超过 $n \log n$，但用 `long long` 安全）。
- 若 $m = 1$（虽题目给定 $m \ge 2$，但为稳健仍可处理），答案直接为 $0$。

### 4. 复杂度分析

- 线性筛时间复杂度 $O(n)$。
- 对每个子树大小分解质因数，总分解次数为 $n$，每次分解 $O(\log n)$，总复杂度 $O(n \log n)$。
- 计算 $n!$ 的质因数指数：遍历所有质数 $p \le n$，每个计算复杂度 $O(\log_p n)$，总复杂度约 $O(n)$。
- 最终快速幂：质数个数约为 $O(n / \log n)$，每个 $O(\log \text{指数})$，可视为 $O(n)$。
- 整体时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

## 代码实现

```cpp
// Counting Heaps
// UVa ID: 1436
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;
vector<int> primes;
vector<int> spf(MAXN + 1);
vector<long long> primeExp(MAXN + 1);

// 线性筛，求最小质因子
void sieve() {
    for (int i = 2; i <= MAXN; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > MAXN) break;
            spf[i * p] = p;
        }
    }
}

// 快速幂取模
long long modPow(long long base, long long exp, long long mod) {
    base %= mod;
    long long res = 1 % mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long m;
        cin >> n >> m;
        vector<int> parent(n + 1);
        parent[1] = 0;
        for (int i = 2; i <= n; ++i) cin >> parent[i];
        // 计算子树大小
        vector<int> subSize(n + 1, 1);
        for (int i = n; i >= 2; --i) subSize[parent[i]] += subSize[i];
        // 清空本次需要用到的质数指数（只清空 ≤ n 的质数）
        for (int p : primes) {
            if (p > n) break;
            primeExp[p] = 0;
        }
        // 减去每个子树大小的质因子指数（分母部分）
        for (int i = 1; i <= n; ++i) {
            int x = subSize[i];
            while (x > 1) {
                int p = spf[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    ++cnt;
                }
                primeExp[p] -= cnt;
            }
        }
        // 加上 n! 的质因子指数
        for (int p : primes) {
            if (p > n) break;
            long long exp = 0;
            long long power = p;
            while (power <= n) {
                exp += n / power;
                if (power > n / p) break;
                power *= p;
            }
            primeExp[p] += exp;
        }
        // 计算结果
        long long ans = 1 % m;
        for (int p : primes) {
            if (p > n) break;
            if (primeExp[p] > 0) ans = ans * modPow(p, primeExp[p], m) % m;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

## 总结

本题的关键在于将标号计数问题转化为组合数学中的树形排列计数，并推导出简洁的闭式公式 $\displaystyle \frac{n!}{\prod \textit{size}(u)}$。由于模数不保证为素数，采用质因数分解法避免了求逆元，利用线性筛预处理最小质因子，实现了高效的分解和指数运算。该方法的通用性较强，适用于任何需要计算大组合数且模数任意的场景。

核心技巧：
- 树形结构上的计数往往可以通过子树大小递推。
- 当模数非质数时，质因数分解是准确计算整数结果的有力工具。
- 预计算最小质因子可显著加速多次分解操作。
