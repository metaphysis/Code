
> **摘要**：本题给定一张 $N$ 个点的无向好友关系图（$N \le 20$），$\texttt{Bob}$ 为节点 $1$，$\texttt{Alice}$ 为节点 $N$。只有当 $\texttt{Bob}$ 当前好友集合中与某人至少有 $K$ 个共同好友时，才能添加该人为好友。求最少需要额外添加多少个朋友才能成功添加 $\texttt{Alice}$，若不可能则输出 $-1$。由于 $N$ 很小，可将 $\texttt{Bob}$ 已添加的朋友集合压缩为位掩码，用 $\texttt{BFS}$ 在状态空间上求最短步数，配合预处理的邻居掩码以 $O(1)$ 判断共同好友数，总复杂度约 $O(T \cdot 2^{N} \cdot N)$。

## 题目描述

$\texttt{Bob}$ 喜欢学校里的女孩 $\texttt{Alice}$。他梦想着与她约会、亲吻她并一起玩奇怪的游戏。但他太害羞了，不敢和 $\texttt{Alice}$ 说话，因此决定先通过网络接近她。他打算在 $\texttt{LifeInvader}$（一个很流行的社交网络）上把她加为好友。但是，人们通常不愿意接受陌生人的好友请求，除非你与他们至少有 $K$ 个共同好友。所以 $\texttt{Bob}$ 必须先添加 $\texttt{Alice}$ 的一些朋友。为了添加他们，他又必须先添加他们的朋友，如此递推。

$\texttt{Bob}$ 认为拥有并不真正认识的朋友毫无意义，所以他希望添加**最少数量**的额外朋友。请帮他计算出为了能够添加 $\texttt{Alice}$，最少需要添加多少个朋友。也有可能 $\texttt{Bob}$ 在 $\texttt{LifeInvader}$ 上已经是 $\texttt{Alice}$ 的好友了，这种情况输出 $0$。

## 输入格式

第一行包含整数 $T$（$T \le 200$），表示测试用例数。接下来 $T$ 个测试用例。

每个测试用例以三个整数 $N, M, K$ 开头：

- $2 \le N \le 20$：总人数（包括 $\texttt{Bob}$ 和 $\texttt{Alice}$）；
- $0 \le M \le \frac{N(N-1)}{2}$：当前好友关系的数量；
- $0 \le K \le N$：添加某人所需要的最少共同好友数。

每个人用唯一编号 $1$ 到 $N$ 标识，$\texttt{Bob}$ 的编号为 $1$，$\texttt{Alice}$ 的编号为 $N$。

接下来 $M$ 行，每行两个整数 $A, B$（$1 \le A, B \le N, A \ne B$），表示 $A$ 和 $B$ 当前是好友。

## 输出格式

对于每个测试用例，输出一行 `Case #X: Y`，其中 $X$ 是测试用例编号（从 $1$ 开始），$Y$ 是最少需要添加的朋友数；若不可能则输出 `-1`。

## 样例

输入

```
3
3 3 2
1 2
2 3
1 3
7 6 1
1 2
2 3
3 4
4 5
5 6
6 7
4 3 2
1 2
2 4
3 4
```

输出

```
Case #1: 0
Case #2: 4
Case #3: -1
```

## 题目分析

$\texttt{Bob}$ 初始已经拥有一些朋友（与节点 $1$ 直接相连的节点）。每次他可以“添加”一个新朋友 $v$，前提是当前 $\texttt{Bob}$ 的朋友集合中，与 $v$ 有直接好友关系的人数不少于 $K$。添加 $\texttt{Alice}$（节点 $N$）本身不计入额外朋友数，但要能够添加她，同样需要满足共同好友数 $\ge K$。

由于 $N \le 20$，人数很少，可以使用状态压缩表示 $\texttt{Bob}$ 当前已经添加了哪些节点（不含 $\texttt{Alice}$ 和 $\texttt{Bob}$ 自己）。状态数最多为 $2^{N-2} \le 2^{18}$，非常小，因此可以采用广度优先搜索（$\texttt{BFS}$）求最短步数。

我们需要处理的关键是：

- 如何快速判断当前状态能否添加某个节点 $v$？  
  只需统计当前状态掩码中与 $v$ 相邻的节点个数，若 $\ge K$ 则可添加。
- 如何判断能否添加 $\texttt{Alice}$？  
  同样统计当前状态掩码中与 $\texttt{Alice}$ 相邻的节点个数，若 $\ge K$ 则可添加。

图中当前已有的好友关系是静态的，不会因为 $\texttt{Bob}$ 添加朋友而改变。因此每个节点的“邻居掩码”可以预处理。

## 解题思路

### 状态定义

用整数 $\textit{mask}$ 表示 $\texttt{Bob}$ 已经添加的朋友集合（不包括 $\texttt{Bob}$ 自身和 $\texttt{Alice}$）。其中第 $i$ 位（$i$ 从 $0$ 开始）表示节点 $i+1$ 是否已被 $\texttt{Bob}$ 添加。由于 $\texttt{Bob}$ 和 $\texttt{Alice}$ 的编号固定为 $1$ 和 $N$，我们只关心编号 $2$ 到 $N-1$ 的节点，共 $N-2$ 个。

### 预处理

对于每个节点 $v$（$1 \le v \le N$），预先计算其邻居掩码 $\textit{neighborMask}[v]$，其中位 $j$ 表示节点 $j+1$ 是否与 $v$ 相邻。这样，判断某状态 $\textit{mask}$ 中与 $v$ 的共同好友数时，只需计算 `__builtin_popcount(mask & neighborMask[v])`。

### 初始状态

$\texttt{Bob}$ 初始已有的朋友是节点 $1$ 的直接邻居（不包括 $\texttt{Alice}$），将这些节点对应位设为 $1$，得到初始掩码 $\textit{startMask}$。

### 特殊情况

- 如果 $\texttt{Bob}$ 已经与 $\texttt{Alice}$ 是好友（即 $\textit{adj}[1][N]$ 为真），则答案为 $0$。
- 如果初始状态已经满足添加 $\texttt{Alice}$ 的条件（共同好友数 $\ge K$），则答案也为 $0$。

### $\texttt{BFS}$ 过程

使用队列存储状态和当前步数。每一步尝试添加一个尚未添加的非 $\texttt{Alice}$ 节点 $v$（$2 \le v \le N-1$），若满足共同好友数 $\ge K$，则生成新状态 $\textit{newMask} = \textit{mask} \mid (1 << (v-1))$。若该新状态未被访问过，则入队，步数加 $1$。

每生成一个新状态后，立即检查是否能添加 $\texttt{Alice}$。若可以，则当前步数（即已经添加的朋友数）就是答案，因为 $\texttt{Alice}$ 本身不计入额外朋友数。由于 $\texttt{BFS}$ 按层扩展，第一次找到的步数一定是最小值。

若 $\texttt{BFS}$ 结束仍未找到，则输出 $-1$。

### 正确性说明

- $\texttt{BFS}$ 保证了首次遇到可添加 $\texttt{Alice}$ 的状态时，所经过的边数（即添加的朋友数）最少。
- 状态的转移只依赖于当前 $\texttt{Bob}$ 的朋友集合，满足无后效性。
- 所有可能的状态都在有限的搜索空间内，因此算法必然会终止。

### 复杂度分析

- 状态数 $S = 2^{N-2} \le 2^{18} \approx 2.6 \times 10^5$。
- 每个状态扩展时，枚举 $O(N)$ 个未添加节点，每次检查共同好友数为 $O(1)$（利用 `__builtin_popcount`）。
- 总时间复杂度 $O(T \cdot 2^{N} \cdot N)$，其中 $T \le 200$，最坏情况下 $2^{18} \times 20 \approx 5 \times 10^6$ 次操作，可以接受。
- 空间复杂度 $O(2^{N})$。

## 代码实现

```cpp
// One Friend at a Time
// UVa ID: 12726
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, M, K;
        cin >> N >> M >> K;
        vector<vector<bool>> adj(N + 1, vector<bool>(N + 1, false));
        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
            adj[A][B] = adj[B][A] = true;
        }
        // 如果已经是好友
        if (adj[1][N]) {
            cout << "Case #" << tc << ": 0\n";
            continue;
        }
        // 预处理每个节点的邻居掩码（位 i-1 表示节点 i）
        vector<int> neighborMask(N + 1, 0);
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (adj[i][j])
                    neighborMask[i] |= (1 << (j - 1));
        // 初始状态：$\texttt{Bob}$ 已有的朋友（不含 Alice）
        int startMask = 0;
        for (int v = 2; v <= N - 1; ++v)
            if (adj[1][v])
                startMask |= (1 << (v - 1));
        // 检查初始状态是否能直接添加 Alice
        auto canAdd$\texttt{Alice}$ = [&](int mask) -> bool {
            int common = __builtin_popcount(mask & neighborMask[N]);
            return common >= K;
        };
        if (canAdd$\texttt{Alice}$(startMask)) {
            cout << "Case #" << tc << ": 0\n";
            continue;
        }
        // BFS
        int totalStates = 1 << N; // N <= 20，1<<20 可接受
        vector<bool> visited(totalStates, false);
        queue<pair<int, int>> q; // {mask, steps}
        visited[startMask] = true;
        q.push({startMask, 0});
        int answer = -1;
        while (!q.empty()) {
            auto [mask, steps] = q.front();
            q.pop();
            // 尝试添加一个非 Alice 的新朋友
            for (int v = 2; v <= N - 1; ++v) {
                int bit = 1 << (v - 1);
                if (mask & bit) continue; // 已经是朋友
                int common = __builtin_popcount(mask & neighborMask[v]);
                if (common < K) continue;
                int newMask = mask | bit;
                if (visited[newMask]) continue;
                visited[newMask] = true;
                // 检查添加 v 后是否能添加 Alice
                if (canAdd$\texttt{Alice}$(newMask)) {
                    answer = steps + 1; // 只额外添加了 v（Alice 不计）
                    goto found;
                }
                q.push({newMask, steps + 1});
            }
        }
        found:
        cout << "Case #" << tc << ": " << answer << "\n";
    }
    return 0;
}
```

## 总结

本题的核心是将社交网络上的朋友添加过程建模为状态空间搜索。由于 $N$ 很小（$\le 20$），状态压缩与 $\texttt{BFS}$ 是自然且高效的选择。关键技巧包括：

- 使用位掩码表示集合，利用内置函数快速计算共同好友数。
- 预处理邻居掩码，将判断条件优化为 $O(1)$ 操作。
- $\texttt{BFS}$ 保证最短路，且 $\texttt{Alice}$ 不计入步数，因此在扩展过程中检测答案。

本题展示了状态压缩在有限规模图问题上的强大力量，同时也提醒我们注意边界条件（如 $\texttt{Bob}$ 初始已与 $\texttt{Alice}$ 为好友，或初始即满足条件）。掌握此类解法有助于应对更多类似的集合覆盖或可达性搜索问题。
