> **摘要**：本文讲解如何为 $\texttt{AND-OR}$ 有向无环图实现增量句子生成器。核心思路是把 $\texttt{OR}$ 节点的序列连接视为区间划分、把 $\texttt{AND}$ 节点的笛卡尔积视为混合进制编码，通过预计算节点长度、$\texttt{OR}$ 前缀和与 $\texttt{AND}$ 后缀乘积，在 $O(n \cdot d)$ 时间内生成任意索引对应的句子，并用 `__int128` 处理超过 $2^{63}$ 的句子总数，避免枚举组合爆炸。
## 题目描述

给定一个 $\texttt{AND-OR}$ 有向无环图，每个节点表示一个句子序列的生成规则。  
叶子节点生成一个单字符句子（即该节点的标号字符）。  
$\texttt{OR}$ 节点将其后继节点生成的句子序列按顺序连接（先第一个后继的全部句子，再第二个后继的全部句子，依此类推）。  
$\texttt{AND}$ 节点将其后继节点生成的句子按**字典序**（复合索引升序）进行笛卡尔积式连接：若有 $m$ 个后继，生成序列为所有可能组合 $(s_0, s_1, \ldots, s_{m-1})$ 的拼接，且组合按索引 $(i_0, i_1, \ldots, i_{m-1})$ 的字典序排列。  

根节点（编号 $0$）生成的句子序列即为该图所描述的语言。  
要求实现一个**增量生成器**：维护当前索引指针，每次给定整数 $k$（$|k| \le 1000$），若 $k>0$ 则输出接下来 $k$ 个句子（每行一个），若 $k<0$ 则仅向前推进 $|k|$ 个句子而不输出。当指针到达序列末尾时自动循环到开头。句子总数可能超过 $2^{63}$，但在 `__int128` 范围内。

## 输入格式

第一行为数据组数 $T$。  
每组数据：  
- 第一行一个正整数 $n$（$n \le 50$），表示图的节点数。  
- 接下来 $n$ 行描述节点 $0$ 到 $n-1$，每行格式：  
  - 叶子节点：`节点编号 字符`（字符不是 `*` 或 `|`）  
  - $\texttt{AND}$ 节点：`节点编号 * 后继个数 后继1 后继2 ...`  
  - $\texttt{OR}$ 节点：`节点编号 | 后继个数 后继1 后继2 ...`  
  （题目原文中 $\texttt{OR}$ 标记为 `'1'`，但实际输入使用 `'|'`，代码同时支持两者）。  
每个节点最多 $10$ 个后继，句子最大长度为 $80$ 字符。  
- 此后每行一个整数 $k$（$|k| \le 1000$），直到读入 $0$ 表示该组数据结束。每组数据总指令数不超过 $100$。

## 输出格式

对于每个 $k$：  
- 先输出一行 `k`（原样输出）。  
- 若 $k>0$，则继续输出接下来 $k$ 个句子，每行一个。  
- 若 $k<0$，则不输出句子。  
- 若 $k=0$，只输出 `0` 并结束该组数据。

## 样例

输入
```
1
4
0 * 2 1 3
1 | 2 2 3
2 a
3 b
-1
3
0
```
输出
```
-1
3
bb
ab
bb
0
```

## 题目分析

本题的核心是**根据图结构快速定位并生成任意索引对应的句子**，同时支持指针递增与循环。  
由于图的规模很小（$n \le 50$，出度 $\le 10$），但句子总数可能极大，不能枚举生成，必须利用规则直接映射。

- 对于 $\texttt{OR}$ 节点，其序列是多个后继序列的**首尾连接**，因此全局索引可通过检查落入哪个后继的区间来确定。  
- 对于 $\texttt{AND}$ 节点，其序列是多个后继序列的**笛卡尔积**，按复合索引字典序排列，这等价于一个**混合进制数**：若后继长度分别为 $L_0, L_1, \dots, L_{m-1}$，则索引 $i$ 可分解为 $i = i_0 \cdot (L_1 L_2 \cdots L_{m-1}) + i_1 \cdot (L_2 \cdots L_{m-1}) + \cdots + i_{m-1}$，即从高位到低位逐次带余除法。

因此，我们只需预计算每个节点的总长度及其辅助数组（$\texttt{OR}$ 的前缀和、$\texttt{AND}$ 的后缀乘积），即可在 $O(\text{深度} \times \text{出度})$ 时间内生成任意句子。

## 解题思路

### 1. 建图与长度计算

使用结构体存储节点类型、叶子字符、后继列表，以及辅助数组 `prefixSum`（$\texttt{OR}$ 专用）和 `suffixProd`（$\texttt{AND}$ 专用）。  
记忆化递归计算 `len[u]`：  
- 叶子：`len[u] = 1`  
- $\texttt{OR}$：`len[u] = sum(len[v])`  
- $\texttt{AND}$：`len[u] = prod(len[v])`  

由于题目保证结果在 `__int128` 范围内，直接使用内置 `__int128` 类型，避免手工实现大整数。

### 2. 预处理辅助数组

- 对于 $\texttt{OR}$ 节点，计算后继长度的前缀和 `prefixSum`，便于二分（或顺序）定位索引。  
- 对于 $\texttt{AND}$ 节点，计算从右向左的后缀乘积 `suffixProd`，其中 `suffixProd[i] = L_{i+1} * L_{i+2} * ... * L_{m-1}`。这样给定全局索引 `idx`，第 $i$ 个后继的局部索引为 `idx / suffixProd[i]`，然后 `idx %= suffixProd[i]` 继续处理下一位。

### 3. 递归生成句子

函数 `generate(u, idx)` 返回节点 `u` 序列中索引为 `idx`（$0$-based）的句子：

- 叶子：返回其字符。  
- $\texttt{OR}$：在 `prefixSum` 中查找第一个大于 `idx` 的元素，确定后继编号，偏移量 = `idx - 前一个前缀和`，递归调用。  
- $\texttt{AND}$：依次对每个后继使用带余除法得到局部索引，递归生成并拼接。

### 4. 增量控制

维护当前索引 `cur`（`__int128` 类型），总长度 `total = len[0]`。  
对于每个 $k$：  
- 输出 `k`。  
- 若 $k>0$，循环 $k$ 次：调用 `generate(0, cur)` 输出句子，然后 `cur = (cur + 1) % total`。  
- 若 $k<0$，仅将 `cur` 向前推进 `|k|` 次（即 `cur = (cur + |k|) % total`），不输出。

### 复杂度分析

- 长度计算与预处理：遍历所有节点及后继，$O(n \cdot d)$，$d \le 10$。  
- 单次生成：递归深度为最长路径（$\le n$），每层需遍历后继（$\le d$）或进行常数次除法，故 $O(n \cdot d)$。  
- 总生成次数：所有 $k>0$ 的 $|k|$ 之和不超过 $100 \times 1000 = 10^5$，完全可行。

## 代码实现

```cpp
// Sentence Generator
// UVa ID: 780
// Verdict: Accepted
// Submission Date: 2026-07-11
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using BigInt = __int128;

enum NodeType { LEAF, OR, AND };

struct Node {
    NodeType type;
    char leafChar;
    vector<int> succ;
    vector<BigInt> suffixProd;
    vector<BigInt> prefixSum;
};

vector<Node> nodes;
vector<BigInt> len;

BigInt getLength(int u) {
    if (len[u] != -1) return len[u];
    if (nodes[u].type == LEAF) return len[u] = 1;
    BigInt res = 0;
    if (nodes[u].type == OR) {
        for (int v : nodes[u].succ) res += getLength(v);
    } else {
        res = 1;
        for (int v : nodes[u].succ) res *= getLength(v);
    }
    return len[u] = res;
}

void preprocess(int u) {
    if (nodes[u].type == OR) {
        vector<BigInt>& ps = nodes[u].prefixSum;
        ps.clear();
        BigInt acc = 0;
        for (int v : nodes[u].succ) {
            acc += getLength(v);
            ps.push_back(acc);
        }
    } else if (nodes[u].type == AND) {
        vector<BigInt>& sp = nodes[u].suffixProd;
        int m = (int)nodes[u].succ.size();
        sp.resize(m);
        BigInt prod = 1;
        for (int i = m - 1; i >= 0; --i) {
            sp[i] = prod;
            prod *= getLength(nodes[u].succ[i]);
        }
    }
    for (int v : nodes[u].succ) preprocess(v);
}

string generate(int u, BigInt idx) {
    if (nodes[u].type == LEAF) return string(1, nodes[u].leafChar);
    if (nodes[u].type == OR) {
        const vector<BigInt>& ps = nodes[u].prefixSum;
        for (int i = 0; i < (int)ps.size(); ++i) {
            if (idx < ps[i]) {
                BigInt offset = (i == 0 ? idx : idx - ps[i - 1]);
                return generate(nodes[u].succ[i], offset);
            }
        }
    } else {
        string res;
        BigInt cur = idx;
        const vector<BigInt>& sp = nodes[u].suffixProd;
        for (int i = 0; i < (int)nodes[u].succ.size(); ++i) {
            BigInt idx_i = cur / sp[i];
            cur %= sp[i];
            res += generate(nodes[u].succ[i], idx_i);
        }
        return res;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        nodes.assign(n, Node());
        len.assign(n, -1);

        for (int i = 0; i < n; ++i) {
            int id;
            string mark;
            cin >> id >> mark;
            if (mark == "*" || mark == "|") {
                int numSucc;
                cin >> numSucc;
                nodes[id].succ.resize(numSucc);
                for (int j = 0; j < numSucc; ++j) cin >> nodes[id].succ[j];
                nodes[id].type = (mark == "*" ? AND : OR);
                nodes[id].leafChar = 0;
            } else {
                nodes[id].type = LEAF;
                nodes[id].leafChar = mark[0];
                nodes[id].succ.clear();
            }
        }

        for (int i = 0; i < n; ++i) getLength(i);
        preprocess(0);

        BigInt cur = 0;
        BigInt total = len[0];

        int k;
        while (cin >> k) {
            cout << k << "\n";
            if (k == 0) break;
            int cnt = abs(k);
            if (k > 0) {
                for (int i = 0; i < cnt; ++i) {
                    cout << generate(0, cur) << "\n";
                    BigInt nxt = cur + 1;
                    cur = (nxt == total ? 0 : nxt);
                }
            } else {
                for (int i = 0; i < cnt; ++i) {
                    BigInt nxt = cur + 1;
                    cur = (nxt == total ? 0 : nxt);
                }
            }
        }
    }
    return 0;
}
```

## 总结

本题通过**索引映射**将 $\texttt{AND-OR}$ 图的生成序列转化为混合进制编码，从而支持快速随机访问与增量遍历。  
关键技巧：  
- 利用 `__int128` 简化大整数运算，在数据范围内高效且简洁。  
- 预计算 $\texttt{OR}$ 前缀和与 $\texttt{AND}$ 后缀乘积，实现 $O(1)$ 索引分解。  
- 递归生成句子，深度可控。  

此方法避免了枚举所有组合，适用于句子总数巨大的场景，是处理组合爆炸问题的经典思路。
