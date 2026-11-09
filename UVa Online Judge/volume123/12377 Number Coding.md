
> **摘要**：本题给定一个编码串，首位数字表示整数所含不同质因数的个数，其余部分需划分为若干个非递减且无前导零的频率。要求统计所有合法划分下，从 9 个质数中选取并分配频率所能产生的不同整数总数。解法通过深度优先搜索枚举所有合法分割，结合阶乘预处理与频率统计，用排列组合公式 $9!/((9-k)!\cdot\prod \text{cnt}(v)!)$ 计算每种分割的贡献并累加。算法复杂度约为 $O(\text{分割数}\cdot k\log k)$，分割数不超过 $\binom{18}{8}=43758$，可高效通过。

## 题目描述

给定一个编码串 $C$ ，其首位数字 $k$（$1 \le k \le 9$）表示一个整数所含的不同质因数个数，剩余部分需要被划分为 $k$ 个正整数（频率），这些频率按非递减顺序排列，且每个频率不能有前导零。仅考虑前 $9$ 个质数 $\{2, 3, 5, 7, 11, 13, 17, 19, 23\}$。

对于一种合法的频率划分，可产生的不同整数个数为：从 $9$ 个质数中选出 $k$ 个并分配这些频率，相同频率互换不产生新整数，方案数为

$$
\frac{9!}{(9-k)! \cdot \prod_{v} \text{cnt}(v)!}
$$

其中 $\text{cnt}(v)$ 是频率值 $v$ 在序列中出现的次数。所有合法划分的方案数之和即为答案。

## 输入格式

第一行一个整数 $T$ ，表示测试用例数量。  
接下来 $T$ 行，每行一个编码串 $C$ ，长度不超过 $20$ 个字符。

## 输出格式

对每个测试用例，输出一行一个整数，表示具有该编码的不同整数个数。

## 样例

输入
```
4
123
213
31312
311111
```
输出
```
9
72
504
504
```

## 题目分析

编码串的第一个字符直接给出质因数个数 $k$ ，余下部分是一串数字，需要将其分割成 $k$ 段，每段表示一个频率。由于编码时频率按递增顺序排列，所以分割得到的 $k$ 个数字必须满足非递减关系，并且每个数字不能有前导零（即不能以 `0` 开头，长度大于 $1$ 时首位不能为 `0`；单个 `0` 也不允许，因为频率至少为 $1$）。

例如 `31312` ：首位为 $3$ ，剩余 `1312` ，合法分割有 `1|3|12` ？频率为 1,3,12 递增，但 `12` 中的 `1` 和 `3` 等，我们需要枚举所有可能。

由于剩余长度最多为 $19$ ，$k \le 9$ ，可行的分割方式数量是有限的，可以用深度优先搜索枚举所有拆分方式。每次枚举当前段的长度，保证剩余部分至少能分成所需的段数，并且每段至少一位，同时满足非递减条件。

对于每种合法分割，计算其对答案的贡献：从 $9$ 个质数中选出 $k$ 个不同的质数，并将 $k$ 个频率分配下去，重复频率的分配顺序不增加新整数，因此贡献为排列数除以各频率出现次数的阶乘。将所有合法分割的贡献累加即为最终答案。

## 解题思路

1. **预处理阶乘**：计算 $0!$ 到 $9!$ 用于组合数计算。
2. **分割枚举**：定义递归函数 `dfs(pos, parts, last, cur)` ，其中 `pos` 是当前处理位置（从剩余串开头算起），`parts` 是已分割出的段数，`last` 是上一段的字符串形式（用于比较大小），`cur` 是当前已分割的段集合。
   - 当 `parts == k-1` 时，最后一段即为从 `pos` 到末尾的剩余串，检查其是否合法（非空、无前导零、且不小于 `last` ），若合法则统计频率并计算贡献。
   - 否则，枚举当前段的长度 `len` ，从 `1` 到 `maxLen`（保证后面每段至少一位），取出子串，若子串无前导零且不小于 `last` ，则递归进入下一段。
3. **统计与计算**：在递归到完整分割时，用 `map<string, int>` 统计各频率出现次数，然后利用阶乘计算贡献。
4. **输出结果**：对每个测试用例输出累加和。

该算法的时间复杂度为 $O(\text{分割数} \cdot k \cdot \log k)$ ，分割数不超过 $\binom{18}{8}=43758$ ，完全可接受。

## 代码实现

```cpp
// Number Coding
// UVa ID: 12377
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long fact[10]; // 阶乘表，fact[i] = i!

// 比较两个字符串表示的整数（无前导零），返回 a <= b
bool isLessOrEqual(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a <= b;
}

int k;          // 当前测试用例的质因数个数
string S;       // 编码串去掉首字符后的剩余部分
long long ans;  // 当前测试用例的答案

// 深度优先搜索枚举所有分割
// idx: 当前处理的起始位置，parts: 已分割出的段数
// last: 上一段的字符串表示，cur: 当前已分割出的所有段
void dfs(int idx, int parts, const string& last, vector<string>& cur) {
    if (parts == k - 1) { // 最后一段直接取剩余部分
        string rem = S.substr(idx);
        if (rem.empty() || rem[0] == '0') return;          // 空串或前导零非法
        if (!last.empty() && !isLessOrEqual(last, rem)) return; // 不满足非递减
        cur.push_back(rem);
        // 统计各频率出现的次数
        map<string, int> mp;
        for (const auto& s : cur) mp[s]++;
        // 计算方案数：P(9, k) / prod(cnt(v)!)
        long long ways = fact[9] / fact[9 - k];
        for (const auto& p : mp) ways /= fact[p.second];
        ans += ways;
        cur.pop_back();
        return;
    }
    int remainParts = k - parts - 1; // 还需要分的段数（不包括当前段）
    int maxLen = (int)S.length() - idx - remainParts; // 当前段最大长度，保证后面每段至少1位
    for (int len = 1; len <= maxLen; ++len) {
        string sub = S.substr(idx, len);
        if (sub[0] == '0') continue;                     // 前导零非法
        if (!last.empty() && !isLessOrEqual(last, sub)) continue; // 不递增
        cur.push_back(sub);
        dfs(idx + len, parts + 1, sub, cur);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 预计算阶乘
    fact[0] = 1;
    for (int i = 1; i <= 9; ++i) fact[i] = fact[i - 1] * i;
    int T;
    cin >> T;
    while (T--) {
        string C;
        cin >> C;
        k = C[0] - '0';          // 取首位作为质因数个数
        S = C.substr(1);         // 剩余部分
        ans = 0;
        if (k >= 1 && k <= 9 && (int)S.length() >= k) {
            vector<string> cur;
            dfs(0, 0, "", cur);
        }
        cout << ans << '\n';
    }
    return 0;
}
```

## 总结

本题核心在于枚举编码串的所有合法分割方式，并利用排列组合公式快速计算每种分割对应的整数个数。关键技巧包括：
- 将字符串分割问题转化为递归枚举，并利用非递减条件剪枝；
- 通过阶乘预处理和频率统计高效计算组合数；
- 注意前导零的排除和段数边界控制。

本题的难点在于理解编码规则并正确枚举所有可能性，而计算部分只需基础的组合数学知识。对于长度限制较小的情况，直接枚举即可通过。
