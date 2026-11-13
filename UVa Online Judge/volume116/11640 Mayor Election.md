
> **摘要**：本题要求统计用 $N$ 位候选人的海报完整覆盖长度为 $L$ 的道路的方案数。每位候选人的海报排列相互独立，可先用有限状态动态规划求出单个候选人在各长度下的合法排列数，再将其视为多项式系数，通过 NTT 快速卷积合并所有候选人的多项式，最后用优先队列优化合并顺序并截断到最大查询长度，从而在 $O\left(\sum U_iP_i^2C_i + M\log M\log N\right)$ 时间内回答全部查询。

# 题目描述

$\texttt{Shohor}$ 市有 $N$ 位市长候选人，长度为 $L$ 的道路需要被海报完全覆盖。每位候选人占据道路上的一个连续区间，候选人的区间按照编号从前到后依次排列，且所有区间首尾相接并恰好覆盖整条道路。

第 $i$ 位候选人拥有 $P_i$ 种不同的海报，第 $j$ 种海报最多连续出现 $c_j$ 次。该候选人需要放置的海报数量位于 $[l_i,u_i]$ 范围内。不同候选人之间不存在相同海报，因此每位候选人的海报排列相互独立。

对于每次给定的道路长度 $L$，求完整覆盖道路的海报序列数量，答案对 $786433$ 取模。

# 输入格式

第一行输入测试组数 $T$。

每组测试数据首先输入候选人数 $N$。

接下来输入 $N$ 行，每行描述一位候选人。第 $i$ 行首先输入 $P_i$、$l_i$、$u_i$，分别表示海报种类数、允许放置海报数量的最小值和最大值；随后输入 $P_i$ 个整数，表示每种海报的最大连续出现次数。

之后输入查询数量 $Q$。

接下来输入 $Q$ 行，每行输入一个整数 $L$，表示道路长度。

# 输出格式

对于每组测试数据，首先输出：

```text
Case #x:
```

其中 $x$ 表示测试组编号，从 $1$ 开始。

对于每个查询，输出：

```text
Query y: ans
```

其中 $y$ 表示查询编号，从 $1$ 开始，$ans$ 表示对应的方案数。

每组测试数据输出结束后额外输出一个空行。

# 样例输入

```text
1
2
2 1 4 2 2
1 1 5 3
9
1
2
3
4
5
6
7
8
9
```

# 样例输出

```text
Case #1:
Query 1: 0
Query 2: 2
Query 3: 6
Query 4: 12
Query 5: 20
Query 6: 16
Query 7: 10
Query 8: 0
Query 9: 0
```

# 题目分析

整条道路上的海报序列由 $N$ 段连续部分组成。第 $i$ 段只允许使用第 $i$ 位候选人的海报，并且长度必须满足 $l_i \le len_i \le u_i$。由于不同候选人的海报完全不同，候选人之间不会发生相同海报连续出现的情况，因此每一段内部的排列方案可以独立计算。

设第 $i$ 位候选人在放置 $k$ 张海报时的合法排列数量为 $f_i(k)$。当每位候选人分别选择长度 $len_i$ 时，完整道路长度满足：

$$
len_1 + len_2 + \cdots + len_N = L
$$

此时总方案数为：

$$
\sum_{len_1 + len_2 + \cdots + len_N = L}f_1(len_1)f_2(len_2)\cdots f_N(len_N)
$$

该形式正是多项式卷积。为第 $i$ 位候选人构造多项式：

$$
F_i(x) = \sum_{k=l_i}^{u_i}f_i(k)x^k
$$

所有候选人的总方案多项式为：

$$
F(x) = F_1(x)F_2(x)\cdots F_N(x)
$$

道路长度为 $L$ 的答案就是 $F(x)$ 中 $x^L$ 的系数。

查询数量 $Q$ 最大为 $100000$，道路长度也最大为 $100000$。若逐个查询重新计算，或者使用普通多项式乘法，时间复杂度无法满足要求。因此需要先计算所有长度对应的答案，再通过数组直接回答每次查询。

# 解题思路

首先计算单个候选人在每种长度下的合法排列数。设该候选人拥有 $P$ 种海报，第 $j$ 种海报最多连续出现 $c_j$ 次。

定义状态：

$$
\textit{dp}[j][r]
$$

表示当前已构造某个固定长度的海报序列，序列最后一张海报是第 $j$ 种，并且该海报已经连续出现 $r$ 次时的方案数。其中：

$$
1 \le r \le c_j
$$

构造长度为 $1$ 的序列时，每种海报都可以单独出现一次：

$$
\textit{dp}[j][1] = 1
$$

从当前状态扩展一张海报时存在两类转移。

规则 $\texttt{1}$. 继续使用第 $j$ 种海报。若当前连续出现次数为 $r$，且 $r < c_j$，则可以转移到：

$$
\textit{dp}[j][r+1]
$$

规则 $\texttt{2}$. 更换为第 $t$ 种海报，其中 $t \ne j$。更换后第 $t$ 种海报的连续出现次数变为 $1$，转移到：

$$
\textit{dp}[t][1]
$$

长度为 $k$ 的总合法方案数为所有状态之和：

$$
f(k) = \sum_{j=1}^{P}\sum_{r=1}^{c_j}\textit{dp}[j][r]
$$

若 $k$ 不在 $[l_i,u_i]$ 范围内，则第 $i$ 位候选人不能选择该长度，因此对应多项式系数置为 $0$。当 $l_i=0$ 时，长度为 $0$ 的空序列存在唯一方案，其方案数为 $1$。

得到每位候选人的多项式后，需要计算它们的乘积。模数为：

$$
786433 = 3 \times 2^{18} + 1
$$

该模数是适合 $\texttt{NTT}$ 的质数，代码使用原根 $10$ 完成快速多项式卷积。

为了降低多项式合并的总开销，使用优先队列维护所有候选人的多项式，每次取出当前长度最小的两个多项式相乘，再将乘积放回优先队列。该过程与最优合并思想一致，可以减少大规模多项式卷积的次数。

设所有查询中的最大道路长度为 $M$。任何次数大于 $M$ 的项都不会影响查询答案，因此每次卷积后只保留次数不超过 $M$ 的部分。

单个候选人的状态数量不超过：

$$
\sum_{j=1}^{P}c_j
$$

由于 $P \le 10$ 且 $c_j \le 10$，单个候选人的动态规划规模较小。设第 $i$ 位候选人的有效最大长度为 $U_i=\min(u_i,M)$，单个候选人的计算复杂度为：

$$
O(U_iP_i^2C_i)
$$

其中 $C_i$ 表示该候选人的最大连续次数限制。

所有候选人的动态规划总时间复杂度为：

$$
O\left(\sum_{i=1}^{N}U_iP_i^2C_i\right)
$$

多项式合并使用 $\texttt{NTT}$，时间复杂度为：

$$
O(M\log M\log N)
$$

空间复杂度为：

$$
O(M)
$$

# 代码实现

```cpp
// Mayor Election
// UVa ID: 11640
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.310s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int mod = 786433;
const int primitiveRoot = 10;

int powerMod(int a, int b) {
    long long result = 1, base = a;
    while (b > 0) {
        if (b & 1) result = result * base % mod;
        base = base * base % mod;
        b >>= 1;
    }
    return (int)result;
}

void ntt(vector<int> &a, bool invert) {
    int n = (int)a.size(), i, j, len;
    for (i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (len = 2; len <= n; len <<= 1) {
        int root = powerMod(primitiveRoot, (mod - 1) / len);
        if (invert) root = powerMod(root, mod - 2);
        for (i = 0; i < n; i += len) {
            long long currentRoot = 1;
            for (j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(a[i + j + len / 2] * currentRoot % mod);
                a[i + j] = u + v;
                if (a[i + j] >= mod) a[i + j] -= mod;
                a[i + j + len / 2] = u - v;
                if (a[i + j + len / 2] < 0) a[i + j + len / 2] += mod;
                currentRoot = currentRoot * root % mod;
            }
        }
    }
    if (invert) {
        int inverseN = powerMod(n, mod - 2);
        for (i = 0; i < n; i++) a[i] = (int)((long long)a[i] * inverseN % mod);
    }
}

vector<int> multiplyPoly(const vector<int> &a, const vector<int> &b, int maxLen) {
    if (a.empty() || b.empty()) return {};
    int fullSize = (int)a.size() + (int)b.size() - 1, needSize = min(maxLen + 1, fullSize), n = 1;
    while (n < fullSize) n <<= 1;
    vector<int> fa = a, fb = b;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] = (int)((long long)fa[i] * fb[i] % mod);
    ntt(fa, true);
    fa.resize(needSize);
    return fa;
}

vector<int> buildCandidatePoly(int posterCount, int lowerBound, int upperBound, const vector<int> &caps, int maxLen) {
    int upper = min(upperBound, maxLen);
    vector<int> result(upper + 1, 0);
    result[0] = 1;
    if (upper == 0 || posterCount == 0) return result;
    vector<vector<int>> current(posterCount);
    for (int i = 0; i < posterCount; i++) {
        current[i].assign(caps[i] + 1, 0);
        current[i][1] = 1;
    }
    for (int length = 1; length <= upper; length++) {
        long long total = 0;
        for (int i = 0; i < posterCount; i++)
            for (int run = 1; run <= caps[i]; run++)
                total += current[i][run];
        result[length] = (int)(total % mod);
        if (length == upper) break;
        vector<vector<int>> next(posterCount);
        for (int i = 0; i < posterCount; i++) next[i].assign(caps[i] + 1, 0);
        for (int i = 0; i < posterCount; i++) {
            for (int run = 1; run <= caps[i]; run++) {
                int value = current[i][run];
                if (value == 0) continue;
                if (run < caps[i]) {
                    next[i][run + 1] += value;
                    if (next[i][run + 1] >= mod) next[i][run + 1] -= mod;
                }
                for (int j = 0; j < posterCount; j++) {
                    if (i == j) continue;
                    next[j][1] += value;
                    if (next[j][1] >= mod) next[j][1] -= mod;
                }
            }
        }
        current.swap(next);
    }
    for (int i = 0; i < min(lowerBound, maxLen + 1); i++) result[i] = 0;
    if (lowerBound > maxLen) fill(result.begin(), result.end(), 0);
    return result;
}

struct PolyCompare {
    bool operator()(const vector<int> &a, const vector<int> &b) const {
        return a.size() > b.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testCase = 1; testCase <= testCount; testCase++) {
        int candidateCount;
        cin >> candidateCount;
        vector<int> posterCounts(candidateCount), lowerBounds(candidateCount), upperBounds(candidateCount);
        vector<vector<int>> allCaps(candidateCount);
        for (int i = 0; i < candidateCount; i++) {
            cin >> posterCounts[i] >> lowerBounds[i] >> upperBounds[i];
            allCaps[i].resize(posterCounts[i]);
            for (int j = 0; j < posterCounts[i]; j++) cin >> allCaps[i][j];
        }
        int queryCount;
        cin >> queryCount;
        vector<int> queries(queryCount);
        int maxQuery = 0;
        for (int i = 0; i < queryCount; i++) {
            cin >> queries[i];
            maxQuery = max(maxQuery, queries[i]);
        }
        priority_queue<vector<int>, vector<vector<int>>, PolyCompare> polyQueue;
        for (int i = 0; i < candidateCount; i++)
            polyQueue.push(buildCandidatePoly(posterCounts[i], lowerBounds[i], upperBounds[i], allCaps[i], maxQuery));
        while (polyQueue.size() > 1) {
            vector<int> first = polyQueue.top();
            polyQueue.pop();
            vector<int> second = polyQueue.top();
            polyQueue.pop();
            polyQueue.push(multiplyPoly(first, second, maxQuery));
        }
        vector<int> answer = polyQueue.top();
        cout << "Case #" << testCase << ":\n";
        for (int i = 0; i < queryCount; i++) {
            int value = queries[i] < (int)answer.size() ? answer[queries[i]] : 0;
            cout << "Query " << i + 1 << ": " << value << "\n";
        }
        cout << "\n";
    }
    return 0;
}
```

# 总结

本题的核心是将每位候选人的海报排列问题转换为独立的有限状态动态规划，再将候选人的长度选择转换为多项式系数问题。

- 使用 $\texttt{DP}$ 统计单个候选人在每种长度下的合法海报排列数。
- 使用多项式的次数表示海报数量，使用系数表示对应方案数。
- 使用 $\texttt{NTT}$ 快速完成多项式卷积。
- 使用优先队列优先合并较短多项式，降低整体卷积开销。
- 每次卷积后截断到最大查询长度 $M$，避免无效计算。
