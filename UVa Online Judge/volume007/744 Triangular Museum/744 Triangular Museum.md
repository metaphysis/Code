## 题目描述

$\texttt{Triangular Museum}$ 是一个由 $K^2$ 个全等三角形房间组成的博物馆，形状也是一个大的正三角形。每个房间内恰好有一名警卫，警卫的名字由不超过 $10$ 个字母组成。初始时所有警卫位于某个初始配置，目标是将他们移动到另一个事先约定的目标配置。移动规则是：每次只能交换两个相邻房间内警卫的位置。要求输出一个交换序列，使得从初始配置变换到目标配置，且交换次数不超过 $4K^3$。

## 输入格式

输入包含多个测试实例。每个实例的第一行是一个整数 $K$（$0 \le K \le 10$），表示大三角形的边长（即共有 $K^2$ 个房间）。第二行包含 $2K^2$ 个警卫名字：前 $K^2$ 个是初始配置（从上到下、从左到右排列），后 $K^2$ 个是目标配置（同样顺序）。名字之间至少有一个空格分隔。输入以单独的一行 `0` 结束。

## 输出格式

对于每个测试实例，首先输出一行整数 $N$，表示交换的次数（$N \le 4K^3$）。随后输出 $N$ 行，每行两个警卫名字，表示一次交换。两个实例的输出之间用一个空行隔开。

## 样例

输入
```
3
DD FF AA CC BB EE II GG HH AA BB CC DD EE FF GG HH II
2
D A B C A B C D
0
```

输出
```
6
GG II
HH II
EE BB
DD AA
BB FF
DD CC

3
A B
A D
C D
```

## 题目分析

本题的核心是将一个图上的标签置换问题转化为一系列相邻交换。博物馆的房间构成一个三角形网格，每个房间是一个顶点，相邻房间之间有边。初始时每个顶点有一个标签（警卫名），目标是将标签移动到指定顶点。允许的操作是交换一条边两端的标签。

由于图是连通的，且顶点数 $N = K^2 \le 100$，边数 $O(K^2)$，我们可以采用贪心策略：按目标顺序逐个确定每个顶点的标签。当处理到顶点 $v$ 时，若目标标签不在 $v$，则从该标签当前位置 $src$ 出发，在尚未确定（即未固定）的顶点子图上找到一条路径到 $v$，然后沿路径依次交换相邻标签，最终将目标标签移动至 $v$，然后将 $v$ 标记为固定，不再参与后续移动。

这种策略的可行性依赖于：在固定了若干顶点后，剩余的未固定顶点构成的子图仍然是连通的。事实上，对于三角形网格，固定任意顶点不会破坏剩余部分的连通性（除非固定了所有顶点），因此总能找到一条不经过固定顶点的路径。每次沿路径移动的长度不超过图直径 $O(K)$，总交换次数为 $O(K^3)$，满足题目限制 $4K^3$。

## 解题思路

### 图的构建

题目要求的三角形排列共有 $K$ 层（从上到下），第 $r$ 层（$0 \le r < K$）包含 $2r+1$ 个小三角形，总数为 $\sum_{r=0}^{K-1} (2r+1) = K^2$。每个小三角形用一个编号表示，编号顺序必须与输入顺序一致（从上到下，从左到右）。

为了正确建立相邻关系，需要确定每个小三角形在网格中的几何位置。一种简便方法是预先构建一个通用的三角形网格，适用于 $K=10$ 的最大情况，然后根据输入的 $K$ 截取前 $K^2$ 个房间并建立邻接表。在通过的代码中，使用了一个固定的区间划分：

```cpp
vector<pair<int, int>> interval = {{1, 1}, {2, 4}, {5, 9}, ..., {82, 100}};
```

每个区间 `{s, e}` 对应一层中的房间编号范围（从 `s` 到 `e`），层内房间从左到右编号。层与层之间的连接通过扫描每层内部的奇数位置（`link` 为 1 时）连接到上一层的对应房间。这样构建的图完全符合三角形网格的几何相邻关系，且编号顺序与输入一致。

### 移动策略

按目标顺序处理每个房间 $i$（从 $1$ 到 $N$）：
1. 读取目标配置中第 $i$ 个名字 `s`，它应最终位于房间 $i$。
2. 若该警卫已经在房间 $i$，则直接标记房间 $i$ 为固定（`disabled[i] = 1`），跳过。
3. 否则，在未固定的房间子图上执行 $\texttt{BFS}$，从该警卫当前位置 `room` 出发，找到到达 $i$ 的一条路径。由于未固定子图连通，$\texttt{BFS}$ 一定能找到路径。
4. 使用父指针数组 `parent` 还原路径，路径为从 `room` 到 $i$ 的顶点序列。
5. 沿路径依次交换相邻房间内的警卫，每次交换记录两个警卫名字，并更新房间内的警卫名字。
6. 将房间 $i$ 标记为固定（`disabled[i] = 1`）。

这样，每处理完一个房间，它的最终配置就确定了，并且后续移动不会进入该房间，从而保证已固定部分不会被破坏。

### 复杂度分析

每个房间最多触发一次 $\texttt{BFS}$，每次 $\texttt{BFS}$ 的时间复杂度为 $O(N + E)$，其中 $N = K^2$，$E = O(N)$。路径长度不超过 $N$，总交换次数不超过 $N \cdot$直径$(G) = O(K^3)$，满足题目给定的上界。对于 $K \le 10$，该算法非常高效。

## 代码实现

```cpp
// Triangular Museum
// UVa ID: 744
// Verdict: Accepted
// Submission Date: 2026-07-06
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> g[110];

void buildGraph() {
    vector<pair<int, int>> interval = {
        {1, 1}, {2, 4}, {5, 9}, {10, 16}, {17, 25}, {26, 36}, {37, 49}, {50, 64}, {65, 81}, {82, 100}
    };
    for (int i = 1; i < interval.size(); i++) {
        int s = interval[i].first, e = interval[i].second, up = interval[i - 1].first;
        for (int now = s, link = 0; now <= e; now++, link ^= 1) {
            if (now < e) {
                g[now].push_back(now + 1);
                g[now + 1].push_back(now);
            }
            if (link) {
                g[now].push_back(up);
                g[up].push_back(now);
                up += 2;
            }
        }
    }
}

int disabled[110], visited[110], parent[110];

void bfs(int s, int t) {
    memset(visited, 0, sizeof visited);
    memset(parent, -1, sizeof parent);
    queue<int> q;
    q.push(s);
    visited[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        if (u == t) break;
        q.pop();
        for (auto v : g[u]) {
            if (disabled[v] || visited[v]) continue;
            visited[v] = 1;
            parent[v] = u;
            q.push(v);
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    buildGraph();
    int K, cases = 0;
    while (cin >> K && K) {
        if (cases++) cout << '\n';
        int N = K * K;
        string s;
        vector<string> names;
        for (int i = 1; i <= N; i++) {
            cin >> s;
            names.push_back(s);
        }
        memset(disabled, 0, sizeof disabled);
        vector<pair<string, string>> swaps;
        for (int i = 1; i <= N; i++) {
            cin >> s;
            int room = 1 + (find(names.begin(), names.end(), s) - names.begin());
            if (room == i) { disabled[i] = 1; continue; }
            bfs(room, i);
            vector<int> path;
            int u = i;
            while (parent[u] != -1) {
                path.push_back(u);
                u = parent[u];
            }
            path.push_back(u);
            reverse(path.begin(), path.end());
            for (int j = 1; j < path.size(); j++) {
                swaps.push_back({names[path[j - 1] - 1], names[path[j] - 1]});
                swap(names[path[j - 1] - 1], names[path[j] - 1]);
            }
            disabled[i] = 1;
        }
        cout << swaps.size() << '\n';
        for (auto& p : swaps) cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
```

## 总结

本题的关键在于将抽象的房间置换问题转化为图上的路径交换问题。通过贪心策略逐个固定目标位置，并利用 $\texttt{BFS}$ 在剩余连通子图中寻找路径，保证了方案的可行性。图的构建需要准确反映三角形网格的几何相邻关系，而代码中预定义的区间方法简洁且正确。该算法的时间复杂度为 $O(K^3)$，完全满足 $K \le 10$ 的规模。主要技巧包括：**固定已处理节点**，**动态维护映射**，以及**路径还原与交换**，这些思想在图论相关的置换问题中具有通用性。
