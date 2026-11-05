## 题目描述

$\texttt{Jolly}$ 和 $\texttt{Emily}$ 在纸上画了一棵有根树，结点编号为 $0$ 到 $n - 1$，$0$ 为根。每条边带有权值 $w$，表示该边有 $w$ 个相同的单位。初始时所有边均未涂色。  
游戏规则如下：

1. $\texttt{Emily}$ 先手，双方轮流操作。
2. 每轮玩家可以选择一条边，该边至少有一个单位尚未涂色，并且从根结点出发仅通过**空闲边**（即尚未被完全涂色的边）可以到达该边。
3. $\texttt{Emily}$ 用红色涂一个单位，$\texttt{Jolly}$ 用绿色涂一个单位。
4. 无法找到可涂边的玩家输掉游戏。

给定树的结构和边权，双方均采取最优策略，求获胜者。

## 输入格式

第一行一个整数 $T$（$T \le 500$），表示测试用例数。  
每个测试用例第一行一个整数 $n$（$2 \le n \le 1000$）。  
接下来 $n - 1$ 行，每行三个整数 $u$、$v$、$w$（$0 \le u, v < n$，$u \ne v$，$1 \le w \le 10^9$），表示一条无向边及其权值。输入保证构成一棵有效的树。  
数据量较大，建议使用快速 $\texttt{I/O}$。

## 输出格式

对于每个测试用例，输出 `Case x: Emily` 或 `Case x: Jolly`，其中 $x$ 为从 $1$ 开始的测试用例编号。

## 样例

输入

```
4
4
0 1 1
1 2 1
0 3 2
5
0 1 1
1 2 2
0 3 3
0 4 7
3
0 1 1
0 2 1
4
0 1 1
1 2 1
1 3 1
```

输出

```
Case 1: Emily
Case 2: Emily
Case 3: Jolly
Case 4: Emily
```

## 题目分析

本题是一个双人完全信息博弈，且游戏状态可以用树的结构和每条边的剩余涂色单位数描述。直接模拟状态空间不可行（边权可达 $10^9$）。需要利用博弈论中的 $\texttt{Sprague-Grundy}$（$\texttt{SG}$）定理来化简。

观察游戏规则：玩家只能涂那些从根出发、路径上的边都未被完全涂满的边。这等价于：若某条边被完全涂满，则其子树中的边（位于该边下方的边）将永远无法再被涂色，因为从根到它们必须经过这条已被封闭的边。因此，游戏过程可以看作是在树上从根向下逐步“封锁”边的过程。每条边一旦被完全涂满，就切断其下方所有边与根的联系。

这种结构非常适合用递归的 $\texttt{SG}$ 值来描述。对于一棵子树，其博弈状态仅取决于该子树根结点与其父结点之间的那条边（即“入口边”）的剩余单位数以及该子树内所有子结点的 $\texttt{SG}$ 值。由于每条边的权值可能很大，但 $\texttt{SG}$ 值的计算只涉及奇偶性和 $1$ 的特殊情况，因此可以高效求解。

## 解题思路

我们定义 $g(u)$ 为以结点 $u$ 为根的子树（包含从 $u$ 到其子结点的所有边）的 $\texttt{SG}$ 值。考虑结点 $u$ 与其父结点 $p$ 之间的边 $e$，其权值为 $w$。我们关心的游戏是：从根 $0$ 出发，只有经过 $e$ 才能进入 $u$ 的子树。在 $e$ 被完全涂满之前，玩家可以选择在 $e$ 上涂色，也可以选择进入 $u$ 的子结点对应的边进行涂色。一旦 $e$ 被涂满，$u$ 子树的所有边都被隔绝，游戏结束。

设 $C$ 为 $u$ 的所有子结点 $v$ 的 $\texttt{SG}$ 值 $g(v)$ 的异或和，即 $C = \bigoplus_{v \in \textit{children}(u)} g(v)$。那么整个以 $u$ 为根、入口边权为 $w$ 的子博弈可以看作一个组合游戏，其 $\texttt{SG}$ 值 $g(u)$ 由 $w$ 和 $C$ 共同决定。

通过归纳分析可得如下结论：

- 若 $w = 1$，则该边只有一个单位，必须等所有子博弈结束后才能涂这最后一个单位，相当于在子博弈的 $\text{SG}$ 值 $C$ 基础上再增加一步，因此 $g(u) = C + 1$。
- 若 $w$ 为偶数，则该边的涂色操作不会改变子博弈的奇偶性，整体 $\texttt{SG}$ 值不变，即 $g(u) = C$。
- 若 $w$ 为奇数且 $w > 1$，则每次在该边上涂色都会翻转子博弈 $\texttt{SG}$ 值的最低位，最终效果等价于将 $C$ 异或上 $1$，即 $g(u) = C \oplus 1$。

这一定理的严格证明可以通过对 $w$ 的归纳和 $\texttt{SG}$ 函数的定义完成，此处不再赘述。

因此，我们只需从叶子结点向上递归计算每个结点的 $g$ 值。对于根结点 $0$，它没有父边，整个游戏的 $\texttt{SG}$ 值即为所有子结点 $g(v)$ 的异或和（即 $C$ 的值）。若该异或和非零，则先手 $\texttt{Emily}$ 必胜，否则 $\texttt{Jolly}$ 必胜。

算法步骤：

1. 以 $0$ 为根，通过 $\texttt{DFS}$ 遍历树，建立父子关系。
2. 对于每个结点 $u$，递归计算其所有子结点 $v$ 的 $g(v)$，并求异或和 $C$。
3. 若 $u$ 不是根，则根据父边权值 $w$ 计算 $g(u)$；若 $u$ 是根，则直接将 $C$ 作为整棵树的 $\texttt{SG}$ 值。
4. 若整棵树的 $\texttt{SG}$ 值为 $0$，则后手 $\texttt{Jolly}$ 获胜，否则先手 $\texttt{Emily}$ 获胜。

时间复杂度：每个结点访问一次，$\texttt{DFS}$ 复杂度 $O(n)$，满足 $n \le 1000$ 的要求。空间复杂度 $O(n)$。

## 代码实现

```cpp
// Game of CS 
// UVa ID: 12033
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll sgFunc(ll w, ll c) {
    if (w == 1) return c + 1;
    if (w % 2 == 0) return c;
    return c ^ 1;
}

void dfs(int u, int parent, ll parentWeight,
         vector<vector<pair<int, ll>>>& adj,
         vector<ll>& sg, ll& totalXor) {
    ll childXor = 0;
    for (auto &e : adj[u]) {
        int v = e.first;
        ll w = e.second;
        if (v == parent) continue;
        dfs(v, u, w, adj, sg, totalXor);
        childXor ^= sg[v];
    }
    if (u == 0) {
        totalXor = childXor;
        sg[0] = childXor;
    } else {
        sg[u] = sgFunc(parentWeight, childXor);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n;
        scanf("%d", &n);
        vector<vector<pair<int, ll>>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            ll w;
            scanf("%d %d %lld", &u, &v, &w);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        vector<ll> sg(n, 0);
        ll totalXor = 0;
        dfs(0, -1, 0, adj, sg, totalXor);
        printf("Case %d: %s\n", caseNo, totalXor ? "Emily" : "Jolly");
    }
    return 0;
}
```

## 总结

本题的关键在于将复杂的博弈过程转化为可递归计算的 $\texttt{SG}$ 值，并利用奇偶性简化边权的影响。主要技巧：

- 识别游戏的有向树结构，利用 $\texttt{SG}$ 定理分解子游戏。
- 对边权进行分类（$1$、偶数、奇数 $>1$）并推导出对应的 $\texttt{SG}$ 值公式。
- 使用深度优先遍历自底向上计算，避免指数级状态。

该解法简洁高效，时间复杂度仅为 $O(n)$，适用于 $n \le 1000$ 且 $T \le 500$ 的输入规模。掌握此类树上组合游戏的 $\texttt{SG}$ 分析法，对解决类似问题有重要参考价值。
