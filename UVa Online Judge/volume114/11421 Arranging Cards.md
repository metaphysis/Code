
> **摘要**：本题要求在 $n$（$n \le 50$）张互不相同的扑克牌的所有排列中，找出满足“相邻两张牌点数不同”且字典序第 $k$（$k \le 10^{18}$）小的序列。解法将问题拆分为点数序列计数与花色内部排列两部分：先用容斥原理配合动态规划计算“有重复元素且相邻不同”的排列数，再用高精度整数（`cpp_int`）逐位构造出第 $k$ 个字典序排列，整体复杂度为 $O(n^3)$。

## 题目描述

给定 $n$（$n \le 50$）张互不相同的扑克牌，要求将它们排成一个序列，使得任意相邻的两张牌**点数不同**。

每张牌用两个字符表示：点数（`2` ~ `9`，`T` 代表 `10`，`J`，`Q`，`K`，`A`）和花色（`S`，`C`，`H`，`D`）。整个序列由所有牌的字符串拼接而成。例如 `6H7DJDKC` 是合法的，但 `6H7D7SKC` 不合法，因为 `7D` 和 `7S` 点数相同。

给定正整数 $k$（$1 \le k \le 10^{18}$），请求出所有合法序列中**字典序第 $k$ 小**的序列。

## 输入格式

输入最多包含 $1000$ 组测试数据。每组数据第一行为两个整数 $n$ 和 $k$，第二行包含 $n$ 张牌，用空格分隔。当 $n = 0$ 时输入结束，该组不需处理。

## 输出格式

对于每组数据，输出 `Case x:` 和对应的答案。若不存在第 $k$ 小的序列，则输出 `Not found`。输出时相邻两张牌之间用一个空格隔开。

## 样例

输入

```text
6 1
2S 3S 3C 4S 4C 4D
6 120
2S 3S 3C 4S 4C 4D
6 121
2S 3S 3C 4S 4C 4D
16 654321234567
2S 3S 4S 5S 2C 3C 4C 5C 2D 3D 4D 5D 2H 3H 4H 5H
0 0
```

输出

```text
Case 1: 2S 4C 3C 4D 3S 4S
Case 2: 4S 3S 4D 3C 4C 2S
Case 3: Not found
Case 4: 5D 4S 2D 5H 3S 4H 5S 2H 3D 2C 5C 4D 2S 3C 4C 3H
```

## 题目分析

本题要求在所有满足“相邻点数不同”的排列中，按字典序找出第 $k$ 个排列。

直接枚举所有排列显然不可行，$n \le 50$ 且 $k$ 可达 $10^{18}$，必须使用计数 + 构造的方法。

核心难点在于**快速计算**：给定当前已经确定的前缀（以及剩余牌），有多少种合法的方式可以完成整个序列。只有得到这个计数值，才能像字典序枚举一样逐位确定答案。

由于限制条件仅与点数有关，不同花色的同点数牌在相邻限制上是等价的。因此可以先将牌按点数分组，统计每个点数出现的次数 $c_i$（$i = 0 \dots 12$，对应 `2` ~ `A`）。任意一个合法的排列，其点数序列（忽略花色）必须满足相邻点数不同，而同一点数内的不同花色可以任意排列。

因此，总合法排列数为：

- 先计算点数序列的合法排列数（仅考虑点数，相同点数的牌视为相同）。
- 再乘以 $\prod_i c_i!$（每个点数内部花色的全排列）。

这样，计数问题就转化成了计算“有重复元素的排列，且相邻元素不同的排列数”的问题。

## 解题思路

### 1. 点数排列的计数（容斥原理）

设共有 $m$ 种点数，每种点数的个数为 $c_i$，总牌数为 $n = \sum c_i$。

将所有相同点数的牌视为不可区分的元素，要求相邻元素不同。这是一个经典的“有重复元素的错排”问题，可以用容斥原理解决。

具体做法是：对于每一种点数 $i$，其内部有 $c_i$ 个元素，它们之间共有 $c_i - 1$ 个相邻位置。如果我们强制某几个相邻位置上的元素相同（即将它们“捆绑”在一起），就可以用容斥来计算没有相邻相等的方案数。

更形式化地，对于每种点数 $i$，我们选择 $j_i$ 个相邻位置进行“合并”，使得该点数的元素被分成 $c_i - j_i$ 个块。此时，所有块（包括不同点数的块）的排列数就是 $\frac{(\sum (c_i - j_i))!}{\prod_i (c_i - j_i)!}$。根据容斥，最终的合法点数排列数为：

$$
\sum_{j_1=0}^{c_1-1} \cdots \sum_{j_m=0}^{c_m-1} (-1)^{\sum j_i}
\prod_i \binom{c_i - 1}{j_i}
\cdot \frac{(\sum (c_i - j_i))!}{\prod_i (c_i - j_i)!}
$$

上式即为代码中 `rankWays` 函数的核心计算。由于 $n \le 50$，枚举所有 $j_i$ 的组合在组合数上仍可能过大，但通过动态规划（$\texttt{DP}$）可以高效计算：按点数逐个加入，维护当前总块数 $b$，并利用组合数转移。

### 2. 字典序第 $k$ 小的构造

将全部 $n$ 张牌按字典序排序（即先按点数，再按花色）。然后按顺序逐位确定序列：

- 对于当前待确定的位置，依次尝试每个尚未使用的牌。
- 如果该牌的点数与上一张牌相同，则跳过（违反相邻限制）。
- 否则，**假设**这一位放这张牌，计算剩余牌（包括当前点数的剩余牌）在**首项已固定为该点数**的前提下，能构成多少种完整的合法排列。
- 若该数量小于 $k$，则从 $k$ 中减去这个数量，继续尝试下一张牌。
- 若数量不小于 $k$，则选择这张牌，固定它，进入下一位。

这样，每一步都保证跳过所有以更小字典序牌开头的排列，最终得到第 $k$ 个排列。

为了计算“首项固定为某点数 $r$”时的合法排列数，我们需要一个变体计数：在原来的点数计数中，强制第一个位置必须放点数 $r$。这可以通过先计算总合法数，再减去首项非 $r$ 的合法数，或者直接修改容斥 DP 的约束条件。代码中 `rankWays(cnt, forbidden)` 实现了这个功能：当 `forbidden` 为某个点数时，返回所有合法排列中首项**不是**该点数的数量；若 `forbidden = -1` 则返回所有合法排列数。因此，若要计算首项必须是 $r$ 的数量，只需计算 `totalWays(cnt) - rankWays(cnt, r)`，其中 `totalWays` 是总合法数（但注意还要乘以花色阶乘，不过花色阶乘在构造过程中保持不变，因为每步只是减少当前点数的数量，整体乘积因子会动态变化，代码中直接利用 `rankWays` 和 `productFact` 的乘积来计算实际计数）。

### 3. 大整数支持

由于 $k \le 10^{18}$，而合法排列数可能极大（$50! \approx 3 \times 10^{64}$），超出 $64$ 位整数范围。因此必须使用高精度整数。代码中采用了 `boost::multiprecision::cpp_int`，它支持任意大整数且运算高效。

### 4. 复杂度分析

- 预处理组合数和阶乘：$O(50^2)$。
- 每次 `rankWays` 计算使用 $\texttt{DP}$：点数最多 $13$ 种，每种点数最多 $50$ 个，状态转移复杂度 $O(13 \cdot n^2)$，但在 $n=50$ 时非常小。
- 构造答案时，每位最多尝试 $n$ 张牌，每尝试一次调用一次 `rankWays`，故总复杂度 $O(n \cdot 13 \cdot n^2) = O(n^3)$，完全可以接受。

## 代码实现

```cpp
// Arranging Cards
// UVa ID: 11421
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

typedef cpp_int bigint;

bigint C[55][55], fact[55];

void init() {
    for (int i = 0; i <= 50; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    fact[0] = 1;
    for (int i = 1; i <= 50; ++i) fact[i] = fact[i - 1] * i;
}

bigint productFact(const vector<int>& cnt) {
    bigint res = 1;
    for (int x : cnt) res *= fact[x];
    return res;
}

// 返回只考虑 rank 的合法排列数，若 forbidden 为 -1 表示无首项限制，
// 否则要求首项不能是 forbidden 这个 rank。
bigint rankWays(const vector<int>& cnt, int forbidden) {
    int N = 0;
    for (int x : cnt) N += x;
    // 常规 DP，计算所有合法 rank 序列数
    vector<bigint> dp(N + 1, 0);
    dp[0] = 1;
    int curMax = 0;
    for (int i = 0; i < 13; ++i) {
        if (cnt[i] == 0) continue;
        vector<bigint> ndp(N + 1, 0);
        for (int j = 0; j < cnt[i]; ++j) {
            int k = cnt[i] - j;
            bigint coeff = C[cnt[i] - 1][j];
            if (j & 1) coeff = -coeff;
            for (int b = 0; b <= curMax; ++b) {
                if (dp[b] == 0) continue;
                ndp[b + k] += dp[b] * C[b + k][k] * coeff;
            }
        }
        dp.swap(ndp);
        curMax += cnt[i];
    }
    bigint F = 0;
    for (int b = 0; b <= N; ++b) F += dp[b];
    if (forbidden == -1) return F;
    if (cnt[forbidden] == 0) return F;
    // 计算首项为 forbidden 的合法排列数 H
    // 先计算除 forbidden 以外的 rank 的 DP
    vector<bigint> dpOther(N + 1, 0);
    dpOther[0] = 1;
    curMax = 0;
    for (int i = 0; i < 13; ++i) {
        if (i == forbidden || cnt[i] == 0) continue;
        vector<bigint> ndp(N + 1, 0);
        for (int j = 0; j < cnt[i]; ++j) {
            int k = cnt[i] - j;
            bigint coeff = C[cnt[i] - 1][j];
            if (j & 1) coeff = -coeff;
            for (int b = 0; b <= curMax; ++b) {
                if (dpOther[b] == 0) continue;
                ndp[b + k] += dpOther[b] * C[b + k][k] * coeff;
            }
        }
        dpOther.swap(ndp);
        curMax += cnt[i];
    }
    int f = forbidden;
    bigint H = 0;
    for (int j = 0; j < cnt[f]; ++j) {
        int kf = cnt[f] - j;
        bigint coeff = C[cnt[f] - 1][j];
        if (j & 1) coeff = -coeff;
        bigint sum = 0;
        for (int b = 0; b <= N; ++b) {
            if (dpOther[b] == 0) continue;
            // 将 kf - 1 个剩余的 f 块插入到 b 个非 f 块中
            sum += dpOther[b] * C[b + kf - 1][b];
        }
        H += coeff * sum;
    }
    return F - H;
}

bigint totalWays(const vector<int>& cnt) {
    return rankWays(cnt, -1) * productFact(cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    unordered_map<char, int> rankMap = {
        {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4},
        {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9},
        {'Q', 10}, {'K', 11}, {'A', 12}
    };
    int n, caseNo = 0;
    long long kLL;
    while (cin >> n >> kLL && n != 0) {
        ++caseNo;
        vector<string> cards(n);
        for (int i = 0; i < n; ++i) cin >> cards[i];
        sort(cards.begin(), cards.end());
        vector<int> cnt(13, 0);
        for (const string& s : cards) cnt[rankMap[s[0]]]++;
        bigint K = kLL;
        if (totalWays(cnt) < K) {
            cout << "Case " << caseNo << ": Not found\n";
            continue;
        }
        vector<bool> used(n, false);
        vector<string> seq;
        int lastRank = -1;
        bool ok = true;
        for (int pos = 0; pos < n; ++pos) {
            bool chosen = false;
            for (int idx = 0; idx < n; ++idx) {
                if (used[idx]) continue;
                int r = rankMap[cards[idx][0]];
                if (r == lastRank) continue;
                // 尝试选择这张牌
                cnt[r]--;
                bigint ways = rankWays(cnt, r) * productFact(cnt);
                if (ways < K) {
                    K -= ways;
                    cnt[r]++;   // 恢复
                } else {
                    // 选中
                    used[idx] = true;
                    seq.push_back(cards[idx]);
                    lastRank = r;
                    chosen = true;
                    break;
                }
            }
            if (!chosen) {
                ok = false;
                break;
            }
        }
        if (!ok) cout << "Case " << caseNo << ": Not found\n";
        else {
            cout << "Case " << caseNo << ": ";
            for (int i = 0; i < (int)seq.size(); ++i) {
                if (i) cout << ' ';
                cout << seq[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
```

## 总结

本题是经典“字典序第 $k$ 小排列”与“相邻不同排列计数”的组合问题。关键技巧包括：

- 将问题拆分为点数序列的计数和花色内部的排列，利用容斥原理高效计算满足相邻不同条件的排列数。
- 使用高精度整数（$\texttt{cpp\_int}$）处理超大的排列数，避免溢出。
- 采用逐位构造法，每一步通过计数判断当前位置应该放置哪张牌，从而得到第 $k$ 个字典序排列。
- 在构造时，通过动态调整计数函数（固定首项点数）来适应前缀约束。

该解法的时间复杂度为 $O(n^3)$，在 $n \le 50$ 时运行迅速，足以应对最多 $1000$ 组测试数据。代码中对容斥 $\texttt{DP}$ 的实现展示了如何处理带有排列限制的计数问题，这种思路可推广至其他类似“相邻不同”的排列统计中。
