[UVa 363 Approximate Matches](https://blog.csdn.net/metaphysis/article/details/161611319)

## 题目描述

给定一个非空文本字符串 $S$、一个非空模式字符串 $P$ 和一个整数 $k \ge 0$，找出 $S$ 中所有与 $P$ 精确匹配或近似匹配（最多 $k$ 个不匹配）的非空子串。

**不匹配数的定义**：
- 如果要从 $S_1$ 中删除最少 $m$ 个字符使其与 $P$ 相同，则 $S_1$ 与 $P$ 有 $m$ 个不匹配
- 如果要从 $P$ 中删除最少 $n$ 个字符使其与 $S_1$ 相同，则 $S_1$ 与 $P$ 有 $n$ 个不匹配
- 如果要从 $S_1$ 中删除 $m$ 个字符且从 $P$ 中删除 $n$ 个字符使两者相同，则 $S_1$ 与 $P$ 有 $m+n$ 个不匹配（取最小值）

**注意**：大小写敏感。

### 输入格式

每个数据集包含三行：
- 第一行：整数 $k$
- 第二行：字符串 $S$（长度 $1 \sim 50$）
- 第三行：字符串 $P$（长度 $1 \sim 20$）

当 $k$ 为负数时停止处理。

### 输出格式

对于每个匹配（不匹配数 $i$ 满足 $0 \le i \le k$），输出一行：
- 如果 $i = 0$：`Q matches P`
- 如果 $i = 1$：`Q matches P with 1 mismatch`
- 如果 $i \ge 2$：`Q matches P with i mismatches`

其中 $Q$ 是 $S$ 的近似匹配子串。如果有多个匹配，按在 $S$ 中出现的顺序（从左到右）输出。从同一位置开始的子串，按长度从小到大输出。不输出重复的子串。

如果没有匹配，不输出任何内容。每个数据集输出后跟一个空行。

### 样例输入

```
1
He did not care about the carpet in the car.
car
2
ABC
BC
-1
```

### 样例输出

```
car matches car with 1 mismatch
ca matches car with 1 mismatch
car matches car
care matches car with 1 mismatch
ar matches car with 1 mismatch
carp matches car with 1 mismatch
car. matches car with 1 mismatch

AB matches BC with 2 mismatches
ABC matches BC with 1 mismatch
B matches BC with 1 mismatch
BC matches BC
C matches BC with 1 mismatch
```

---

## 题目分析

### 问题的本质

这是一个**近似字符串匹配**问题。给定一个文本字符串 $S$ 和一个模式 $P$，需要找出 $S$ 中所有与 $P$ 的**编辑距离**（仅允许删除操作）不超过 $k$ 的子串。

### 不匹配数的计算

定义 $Q$ 和 $P$ 之间的不匹配数为：
$$
\text{mismatches}(Q, P) = |Q| + |P| - 2 \times \text{LCS}(Q, P)
$$

其中 $\text{LCS}(Q, P)$ 是 $Q$ 和 $P$ 的**最长公共子序列**（$\texttt{longest common subsequence}$）的长度。

**原理**：
- 要从 $Q$ 和 $P$ 中删除字符使它们相同，剩下的公共部分长度最多为 $\text{LCS}(Q, P)$
- 需要从 $Q$ 中删除 $|Q| - \text{LCS}(Q, P)$ 个字符
- 需要从 $P$ 中删除 $|P| - \text{LCS}(Q, P)$ 个字符
- 总删除数 = $|Q| + |P| - 2 \times \text{LCS}(Q, P)$

### 示例验证

以 `scrapple` 和 `apples` 为例：
- $|Q| = 8$，$|P| = 6$
- $\text{LCS} = 5$（`apple`）
- 不匹配数 = $8 + 6 - 2 \times 5 = 14 - 10 = 4$

### 算法步骤

1. 枚举 $S$ 的所有非空子串 $Q$
2. 计算 $Q$ 和 $P$ 的 $\text{LCS}$ 长度
3. 计算不匹配数，如果 $\le k$，则输出
4. 去重（避免重复输出相同子串）

---
## 参考代码

```cpp
// Approximate Matches
// UVa ID: 363
// Verdict: Accepted
// Submission Date: 2016-07-11
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 计算字符串 s 和 t 的最长公共子序列长度
int lcs(string& s, string& t)
{
    int memo[s.length() + 1][t.length() + 1];
    memset(memo, 0, sizeof(memo));

    for (int i = 1; i <= s.length(); i++)
        for (int j = 1; j <= t.length(); j++)
            if (s[i - 1] == t[j - 1])
                memo[i][j] = memo[i - 1][j - 1] + 1;
            else
                memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);

    return memo[s.length()][t.length()];
}

// 生成所有近似匹配子串
void generate(string S, string P, int k)
{
    set<string> produced;  // 去重
    for (int i = 0; i < S.length(); i++)
        for (int j = 1; j <= S.length() - i; j++)
        {
            string Q = S.substr(i, j);
            // 避免重复输出
            if (produced.find(Q) != produced.end()) 
                continue;
            produced.insert(Q);
            
            int matches = lcs(Q, P);
            int mismatches = Q.length() + P.length() - 2 * matches;
            if (mismatches <= k)
            {
                if (mismatches == 0) 
                    cout << Q << " matches " << P << '\n';
                else if (mismatches == 1) 
                    cout << Q << " matches " << P << " with 1 mismatch\n";
                else 
                    cout << Q << " matches " << P << " with " << mismatches << " mismatches\n";
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int k;
    string S, P;
    while (cin >> k, k >= 0)
    {
        cin.ignore(1024, '\n');  // 忽略换行
        getline(cin, S);
        getline(cin, P);
        generate(S, P, k);
        cout << '\n';  // 数据集间空行
    }
    
    return 0;
}
```
