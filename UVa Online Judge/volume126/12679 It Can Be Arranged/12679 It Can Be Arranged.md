
> **摘要**：本题要求在给定 $N$ 门课程的时间区间、注册人数与教室容量 $M$ 的前提下，求出最少需要的教室数量。由于单门课程人数可能超过容量，需将其拆分为 $\lceil S_i / M \rceil$ 个并行副本；课程之间还需满足清理时间约束 $B_i + \textit{clean}_{ij} < A_j$ 才能在同一教室衔接。文章将问题转化为 $\texttt{DAG}$ 最小路径覆盖，并用带容量限制的二分图最大流（$\texttt{Dinic}$）压缩建模，最终答案为总副本数减去最大匹配数，时间复杂度 $O(N^3)$。

## 题目描述

每年有多所大学联合举办校际编程竞赛，$\texttt{MMR}$（$\texttt{Mission Maker Rahman}$）计划开办一所编程学校，教授 $N$ 门课程。每门课程每天上课，给出课程 $i$ 的开始时间 $A_i$ 与结束时间 $B_i$（包含端点）以及注册学生数 $S_i$，保证没有学生同时注册两门不同课程。  
学校租用“$\texttt{Sentinel Tower}$”中的若干教室，每个教室容量为 $M$ 名学生。课程结束后需要清理教室才能安排下一门课程，清理时间矩阵为 $\textit{clean}_{ij}$，表示课程 $i$ 结束后打扫至适合课程 $j$ 开始所需的时间。  
目标是求出最少需要的教室数量。

## 输入格式

输入第一行为整数 $T$（$T \le 100$），表示测试用例数。  
每个测试用例第一行为两个整数 $N$（$1 \le N \le 100$）和 $M$（$1 \le M \le 10000$），分别表示课程数和教室容量。  
接下来 $N$ 行，每行三个整数 $A_i, B_i, S_i$（$0 \le A_i \le B_i \le 10^6$，$1 \le S_i \le 10^4$）。  
接下来 $N$ 行，每行 $N$ 个整数，构成清理时间矩阵，满足 $0 \le \textit{clean}_{ij} \le 10^6$，且 $\textit{clean}_{ii} = 0$。

## 输出格式

对于每个测试用例，输出一行 `Case X: Y`，其中 $X$ 为用例编号（从 $1$ 开始），$Y$ 为最少教室数。

## 样例

输入：
```
3
1 5
1 60 12
0
4 1
1 100 10
50 130 3
150 200 15
80 170 7
0 2 3 4
5 0 7 8
9 10 0 12
13 14 15 0
2 1
1 10 1
12 20 1
0 2
5 0
```

输出：
```
Case 1: 3
Case 2: 22
Case 3: 2
```

## 题目分析

本题的核心是在时间维度上为课程安排教室，每个教室同一时刻只能上一门课，且课程之间存在必要的清理时间。由于同一门课的学生数量可能超过教室容量，必须将该课程拆分为多个并行的“副本”，每个副本占用一个教室同时进行。

若一个教室先后安排课程 $i$ 和课程 $j$（$i \ne j$），则必须满足 $B_i + \textit{clean}_{ij} < A_j$（严格小于，因为时间区间包含端点，打扫完成时刻必须早于下一课程的开始时刻）。满足该条件的课程对可以形成“衔接”关系。

将所有课程副本视为节点，若两副本所属课程可衔接，则在该两节点之间连一条有向边。一个教室对应的课程序列就是一条有向路径，且所有路径需要覆盖所有节点。问题转化为：在有向无环图（因时间严格递增）中，用最少路径覆盖所有节点，即最小路径覆盖问题。对于 $\texttt{DAG}$，最小路径覆盖数等于节点总数减去最大匹配数。

由于课程副本数量可能很大（$N \le 100$，$S_i \le 10000$，$M \ge 1$，总副本数可达 $10^6$），不能直接对每个副本建点。但同一课程的所有副本之间完全等价：它们的时间区间相同，与其它课程的衔接关系也完全相同。因此可以使用带容量限制的二分图来压缩建模。

## 解题思路

步骤 $\texttt{1}$. 计算每门课程需要的副本数 $k_i = \left\lceil \frac{S_i}{M} \right\rceil$，并令总副本数 $P = \sum_{i=1}^N k_i$。

步骤 $\texttt{2}$. 构建二分图网络流模型：
- 左部节点代表课程 $i$（作为“前驱”角色），右部节点也代表课程 $j$（作为“后继”角色）。
- 源点 $s$ 向左部节点 $i$ 连边，容量为 $k_i$，表示该课程最多有 $k_i$ 个副本可以作为某个教室中已结束的课程去匹配后面的课程。
- 右部节点 $j$ 向汇点 $t$ 连边，容量为 $k_j$，表示该课程最多有 $k_j$ 个副本可以作为某个教室中即将开始的课程去匹配前面的课程。
- 若课程 $i$ 可衔接课程 $j$（即 $i \ne j$ 且 $B_i + \textit{clean}_{ij} < A_j$），则从左部 $i$ 向右部 $j$ 连一条容量为 $+\infty$ 的边，表示任意一个课程 $i$ 的副本都可以衔接任意一个课程 $j$ 的副本。

步骤 $\texttt{3}$. 在该网络中求最大流 $F$。最大流的物理意义是能够形成的“前后衔接”关系最大数量，即最大匹配数。因为每单位流量代表一个左部副本匹配一个右部副本，且由于容量限制，同一个左部副本最多匹配一次（流出流量受 $k_i$ 限制），同一个右部副本也最多被匹配一次（流入流量受 $k_j$ 限制）。

步骤 $\texttt{4}$. 最少教室数即为 $P - F$。因为每条教室路径包含若干节点，若有 $x$ 条路径，则路径内边数为 $P - x$，而最大流 $F$ 正是所有路径内部边数的最大值，因此 $x_{\min} = P - F_{\max}$。

算法使用 $\texttt{Dinic}$ 实现最大流，节点数仅为 $2N+2 \le 202$，边数 $O(N^2)$，运行效率极高。

## 代码实现

```cpp
// It Can Be Arranged
// UVa ID: 12679
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Dinic {
    struct Edge {
        int to, rev, cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : n(n), g(n), level(n), it(n) {}
    void addEdge(int v, int to, int cap) {
        Edge a{to, (int)g[to].size(), cap};
        Edge b{v, (int)g[v].size(), 0};
        g[v].push_back(a);
        g[to].push_back(b);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        scanf("%d %d", &N, &M);
        vector<int> A(N), B(N), S(N);
        for (int i = 0; i < N; ++i) scanf("%d %d %d", &A[i], &B[i], &S[i]);
        vector<vector<int>> clean(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf("%d", &clean[i][j]);

        vector<int> k(N);
        int totalNodes = 0;
        for (int i = 0; i < N; ++i) {
            k[i] = (S[i] + M - 1) / M;   // 向上取整
            totalNodes += k[i];
        }

        int SRC = 0, SNK = 2 * N + 1;
        Dinic dinic(SNK + 1);
        // 源点 -> 左部
        for (int i = 0; i < N; ++i) dinic.addEdge(SRC, 1 + i, k[i]);
        // 右部 -> 汇点
        for (int j = 0; j < N; ++j) dinic.addEdge(1 + N + j, SNK, k[j]);
        // 转移边（严格小于）
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (B[i] + clean[i][j] < A[j])   // 注意严格小于
                    dinic.addEdge(1 + i, 1 + N + j, totalNodes);
            }

        int maxMatch = dinic.maxFlow(SRC, SNK);
        printf("Case %d: %d\n", tc, totalNodes - maxMatch);
    }
    return 0;
}
```

## 总结

本题的巧妙之处在于将“教室数量”转化为“路径覆盖”问题，并利用容量压缩处理大量重复副本。关键点包括：

- 将学生数量上取整得到副本数，从而将课程抽象为带容量的节点。
- 衔接条件的严格小于判断，避免端点时刻冲突。
- 使用最大流求解 $\texttt{DAG}$ 最小路径覆盖，算法复杂度为 $O(N^3)$（实际运行很快），足以应对 $N \le 100$ 的数据范围。

空间复杂度 $O(N^2)$，时间复杂度主要由 $\texttt{Dinic}$ 决定，对于本题规模完全满足要求。该方法具有普适性，可推广至类似的时间表调度与资源复用问题。
