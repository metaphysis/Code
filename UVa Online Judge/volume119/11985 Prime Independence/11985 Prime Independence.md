
> **摘要**：本题要求从给定整数集合中选出最大的「素数独立」子集，即任意两元素之间不存在素数倍关系。核心思路是把每个数字视作顶点、素数倍关系视作边，利用质因数个数 $\Omega(x)$ 的奇偶性证明该图是二分图，再由 $\texttt{König}$ 定理把最大独立集转化为「总顶点数 − 最大匹配数」，最后用 $\texttt{Hopcroft–Karp}$ 算法在 $O(E\sqrt{V})$ 时间内求解。文中给出完整推导、复杂度分析与可提交的 $\texttt{C++}$ 实现。

## 题目描述

一个整数集合被称为素数独立的，如果其中没有任何一个成员是另一个成员的素数倍数。整数 $a$ 被称为 $b$ 的素数倍数，如果 $a = b \times k$，其中 $k$ 是素数。例如，$6$ 是 $2$ 的素数倍数，但 $8$ 不是。集合 $\{2, 8, 17\}$ 是素数独立的，但 $\{2, 8, 16\}$ 或 $\{3, 6\}$ 不是。

给定一个由互不相同的正整数组成的集合，计算最大的素数独立子集的大小。

## 输入格式

第一行包含一个整数 $T$（$T \le 25$），表示测试用例的数量。

每个测试用例以一行包含一个整数 $N$（$1 \le N \le 40000$）开始，表示集合的大小。下一行包含 $N$ 个互不相同的整数，每个整数在 $1$ 到 $500000$ 之间（含）。

## 输出格式

对于每个测试用例，输出一行，格式为 `Case x: y`，其中 $x$ 是测试用例编号（从 $1$ 开始），$y$ 是最大素数独立子集的大小。

## 样例

输入：

```
3
5
2 4 8 16 32
5
2 3 4 6 9
3
1 2 3
```

输出：

```
Case 1: 3
Case 2: 3
Case 3: 2
```

## 题目分析

将每个给定数字视作图的一个顶点。若两个数字 $a$ 和 $b$ 满足 $a = b \times p$ 或 $b = a \times p$（$p$ 为素数），则在它们之间连一条无向边。此时，素数独立子集等价于图中不存在任何边的顶点子集，即图的最大独立集。

问题的关键在于该图具有二分性。设 $\Omega(x)$ 表示 $x$ 的质因数个数（按重数计）。若 $a = b \times p$（$p$ 为素数），则 $\Omega(a) = \Omega(b) + 1$，因此 $\Omega(a)$ 与 $\Omega(b)$ 的奇偶性相反。所以图中的每条边都连接一个 $\Omega$ 值为奇数的顶点和一个 $\Omega$ 值为偶数的顶点，图是一个二分图。

对于二分图，最大独立集的大小等于总顶点数减去最大匹配数（由 König 定理保证）。因此，问题转化为构建上述二分图并求其最大匹配。

## 解题思路

### 步骤 $\texttt{1}$. 分组与索引

预处理每个数字 $x$ 的质因数个数 $\Omega(x)$（按重数计）。将 $\Omega(x)$ 为奇数的数字归入左部，为偶数的数字归入右部。注意 $1$ 的 $\Omega(1) = 0$ 为偶数，故 $1$ 属于右部。

使用两个数组（或哈希表）分别记录每个值在左部和右部的位置索引，便于快速查询某个数字是否在集合中及其所在部的位置。

### 步骤 $\texttt{2}$. 建边

枚举集合中的每个数字 $x$，枚举 $x$ 的所有不同质因子 $p$。若 $x$ 能被 $p$ 整除，令 $y = x / p$。如果 $y$ 也在输入集合中，则 $x$ 与 $y$ 之间存在冲突边。为了构造二分图的有向邻接表，仅添加从左部到右部的边。具体而言：

- 如果 $\Omega(x)$ 为奇数（$x$ 在左部），则 $y$ 必在右部，添加边 $x \to y$。
- 如果 $\Omega(x)$ 为偶数（$x$ 在右部），则 $y$ 必在左部，添加边 $y \to x$。

这样每条无向边恰好被添加一次，不会重复。

由于每个数的不同质因子个数最多为 $7$（因为 $2 \times 3 \times 5 \times 7 \times 11 \times 13 \times 17 = 510510 > 500000$），建边的总时间复杂度为 $O(N \times \omega(x))$，其中 $\omega(x)$ 为不同质因子个数，实际常数很小。

### 步骤 $\texttt{3}$. 求最大匹配

使用 $\texttt{Hopcroft–Karp}$ 算法求二分图的最大匹配。该算法的时间复杂度为 $O(E \sqrt{V})$，其中 $V$ 为顶点数（不超过 $N$），$E$ 为边数（不超过 $N \times \omega(x)$），对于 $N \le 40000$ 完全可行。

### 步骤 $\texttt{4}$. 计算答案

最大独立集大小 = 总顶点数 $N$ − 最大匹配数。直接输出即可。

### 复杂度分析

- **时间复杂度**：预处理线性筛 $O(500000)$；每个测试用例建边 $O(N \times \omega(x))$，其中 $\omega(x) \le 7$；$\texttt{Hopcroft–Karp}$ 算法 $O(E \sqrt{V})$，其中 $E \le N \times \omega(x) \le 2.8 \times 10^5$，$V \le 4 \times 10^4$。总运行时间在题目限制内。
- **空间复杂度**：$O(V + E)$，用于存储邻接表和索引数组。

## 代码实现

```cpp
// Prime Independence
// UVa ID: 11985
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 500000;

vector<int> spf(MAXV + 1), omega(MAXV + 1);

// 线性筛：最小质因子 + 质因子总数（带重数）
void preprocess() {
    vector<int> primes;
    for (int i = 2; i <= MAXV; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
            omega[i] = 1;
        }
        for (int p : primes) {
            if (p > spf[i] || i * p > MAXV) break;
            spf[i * p] = p;
            omega[i * p] = omega[i] + 1;
        }
    }
}

// 获取 x 的所有不同质因子
vector<int> getDistinctPrimes(int x) {
    vector<int> res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) x /= p;
    }
    return res;
}

// Hopcroft–Karp 二分图最大匹配
class HopcroftKarp {
public:
    int L, R;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;

    HopcroftKarp(int L_, int R_) : L(L_), R(R_), adj(L_), pairU(L_, -1), pairV(R_, -1), dist(L_) {}

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < L; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else dist[u] = -1;
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = pairV[v];
                if (u2 == -1) found = true;
                else if (dist[u2] == -1) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = pairV[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < L; ++u)
                if (pairU[u] == -1 && dfs(u)) ++matching;
        }
        return matching;
    }
};

int main() {
    preprocess();
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        scanf("%d", &N);
        vector<int> arr(N);
        vector<int> leftIdx(MAXV + 1, -1), rightIdx(MAXV + 1, -1);
        vector<int> leftNodes, rightNodes;

        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
            int x = arr[i];
            if (omega[x] & 1) {
                leftIdx[x] = (int)leftNodes.size();
                leftNodes.push_back(x);
            } else {
                rightIdx[x] = (int)rightNodes.size();
                rightNodes.push_back(x);
            }
        }

        int L = leftNodes.size(), R = rightNodes.size();
        HopcroftKarp hk(L, R);

        for (int x : arr) {
            vector<int> primes = getDistinctPrimes(x);
            for (int p : primes) {
                if (x % p != 0) continue;
                int y = x / p;
                if (y < 1) continue;
                if (omega[x] & 1) {
                    if (rightIdx[y] != -1) hk.addEdge(leftIdx[x], rightIdx[y]);
                } else {
                    if (leftIdx[y] != -1) hk.addEdge(leftIdx[y], rightIdx[x]);
                }
            }
        }

        int match = hk.maxMatching();
        printf("Case %d: %d\n", tc, N - match);
    }
    return 0;
}
```

## 总结

本题的核心是将“素数独立”条件转化为图论中的最大独立集问题，并利用质因数个数的奇偶性证明图的二分性。通过 $\texttt{König}$ 定理将最大独立集转化为最大匹配，从而使用高效的 $\texttt{Hopcroft–Karp}$ 算法求解。  
关键技巧包括：预处理最小质因子和质因数个数，利用除法（$x / p$）而非乘法枚举边，避免遗漏包含 $1$ 的边（因为 $p / p = 1$）。该思路同样适用于其他“倍乘素数”关系的独立集问题，具有通用性。
