
> **摘要**：本题给出两家公司对无线频谱信道的报价，要求选出互不冲突的报价使总金额最大。由于同一公司内部报价不冲突，冲突关系构成二分图，问题可转化为最大权独立集，进而由「总金额 − 最小权顶点覆盖」求得答案。最小权顶点覆盖通过最小割建模，并用 $\texttt{Dinic}$ 最大流算法求解，时间复杂度上界为 $O(V^2E)$。

 # 题目描述

某国将无线频谱划分为 $300000$ 个信道，并通过拍卖发放使用许可。参与竞拍的只有两家公司，每家公司可以对一组信道提交报价。每份报价包含一个价格，以及接受该报价时必须同时分配给它的全部信道。

同一个信道不能分配给不同的服务，因此，所需信道存在交集的两份报价不能同时被接受。另外，每家公司对任意一个信道至多提交一份报价，所以同一家公司内部的报价不会发生信道冲突。

政府需要选择若干份互不冲突的报价，使接受的报价总金额最大。求能够获得的最大收入。

# 输入格式

第一行给出测试数据组数 $T$，其中 $1\le T\le 10$。每组数据前有一个空行。

每组数据包含两家公司的报价信息，格式相同：

- 第一行给出报价数量 $N$，其中 $1\le N\le 3000$。
- 接下来 $N$ 行，每行描述一份报价。第一个整数为价格 $P$，满足 $1\le P\le 1000$；后面的整数为该报价需要的信道编号。

每份报价至少需要 $1$ 个信道，至多需要 $32$ 个信道。信道编号为不超过 $300000$ 的正整数。

# 输出格式

对于每组数据，先输出 `Case k:`，其中 $k$ 为从 $1$ 开始的数据编号，再在下一行输出最大收入。

相邻两组数据之间输出一个空行，最后一组数据之后不输出额外空行。

# 样例输入

```text
2

3
45 1
51 2
62 3
4
54 1
15 2
33 3
2 4 5

5
20 1
18 2
23 4
54 3 5 6
17 7
4
36 1 2 3
28 5
47 4 7
16 6
```

# 样例输出

```text
Case 1:
169

Case 2:
139
```

# 题目分析

如果两份报价需要同一个信道，它们就不能同时被接受。将每份报价视为一个顶点，报价金额作为顶点权值，在存在冲突的两份报价之间连边，那么问题就是选择一组互不相邻的顶点，使顶点权值之和最大，即求最大权独立集。

一般图上的最大权独立集较难求解，但本题有一个关键限制：同一家公司对一个信道至多提交一份报价。这意味着同一家公司内部的报价两两不冲突，所有冲突都发生在两家公司之间。因此，冲突图是一个二分图，两侧分别对应两家公司的报价。

设全部报价金额之和为 $S$。如果删除一些报价，使剩下的报价互不冲突，那么每条冲突边至少要有一个端点被删除。也就是说，被删除的顶点构成一个顶点覆盖。反过来，删除任意一个顶点覆盖后，剩余顶点之间都没有冲突边，可以全部接受。因此：

$$
\text{最大收入}=
S-\text{最小权顶点覆盖的权值}
$$

二分图的最小权顶点覆盖可以通过最小割求解，再利用最大流最小割定理，将问题转化为最大流。

# 解题思路

设第一家公司有 $N$ 份报价，第二家公司有 $M$ 份报价。建立源点 $s$、汇点 $t$，并为每份报价建立一个顶点。第一家公司的报价作为左侧顶点，第二家公司的报价作为右侧顶点。

对于第一家公司的每份报价 $u$，添加一条从源点到 $u$ 的有向边，容量为该报价的价格 $w_u$。对于第二家公司的每份报价 $v$，添加一条从 $v$ 到汇点的有向边，容量为该报价的价格 $w_v$。如果左侧报价 $u$ 与右侧报价 $v$ 存在信道冲突，则添加一条从 $u$ 到 $v$ 的有向边，容量为无穷大：

$$
s\xrightarrow{w_u}u,\qquad
u\xrightarrow{\mathrm{INF}}v,\qquad
v\xrightarrow{w_v}t.
$$

这里的无穷大只需严格大于全部报价金额之和。由于最多有 $6000$ 份报价，每份报价金额不超过 $1000$，总金额不超过 $6000000$，代码使用的 $\texttt{INF}$ 足够大。

考虑任意一个最小割，将包含源点的一侧记为 $X$，包含汇点的一侧记为 $Y$。一定存在容量不超过 $S$ 的割，因此最小割不会切断容量为无穷大的冲突边。对于每条冲突边 $u\to v$，不可能同时出现 $u\in X$ 且 $v\in Y$，于是至少满足下面一个条件：左侧顶点 $u$ 位于 $Y$，或者右侧顶点 $v$ 位于 $X$。

把位于 $Y$ 的左侧报价，以及位于 $X$ 的右侧报价视为删除的报价。每条冲突边至少有一个端点被删除，所以这些报价构成顶点覆盖。其价格之和恰好等于割容量：左侧被删除的报价对应被切断的边 $s\to u$，右侧被删除的报价对应被切断的边 $v\to t$。

反过来，对于任意一个顶点覆盖，可以将其中的左侧顶点放入 $Y$、右侧顶点放入 $X$，其余报价顶点放在另一侧。由于每条冲突边都被覆盖，不会有无穷大容量的边跨越割，割容量正好等于该顶点覆盖的总权值。因此，网络的最小割容量等于冲突图的最小权顶点覆盖权值。由最大流最小割定理，最终答案为：

$$
S-\operatorname{maxFlow}(s,t)
$$

构建冲突边时，无需两两比较报价中的信道。代码使用数组 $\texttt{used}$ 记录每个信道对应的第一家公司报价编号。读取第二家公司的报价时，逐个检查所需信道；若该信道已被第一家公司某份报价使用，就在两份报价之间添加冲突边。由于同一家公司内部不会重复使用信道，每个信道在第一家公司中至多对应一份报价，因此这种记录方式不会遗漏冲突。如果两份报价共享多个信道，代码会添加多条平行边，但不会影响最小割的含义。

最大流使用 $\texttt{Dinic}$ 算法计算。每轮先通过广度优先搜索构建层次图，再利用深度优先搜索和当前弧优化在层次图中增广，直到残量网络中不存在从源点到汇点的路径。

设 $V=N+M+2$，$E$ 为网络中添加的正向边数，$C$ 为两家公司报价中信道编号的出现总次数。使用长度为 $U=300000$ 量级的数组记录信道归属，初始化与建图需要 $O(U+C+N+M)$ 时间。一般容量网络上，$\texttt{Dinic}$ 算法的时间复杂度上界为 $O(V^2E)$。网络及信道记录数组所需空间为 $O(V+E+U)$。代码为顶点和边预先分配了固定大小的存储空间。

# 代码实现

代码在读取报价时累加总金额，并利用信道归属数组建立两家公司之间的冲突边。随后计算最大流，用总报价金额减去最大流得到最大收入。

```cpp
// Duopoly
// UVa ID: 1212
// Verdict: Accepted
// Submission Date: 2023-01-22
// UVa Run Time: 0.030s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

struct arc { int u, v, capacity, residual, next; };

class Dinic {
private:
    arc *arcs;
    int vertices, source, sink, idx, *head, *dist, *current;
    bool bfs() {
        memset(dist, -1, sizeof(int) * vertices);
        queue<int> q;
        q.push(source);
        dist[source] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (arcs[i].residual > 0 && dist[arcs[i].v] < 0) {
                    dist[arcs[i].v] = dist[u] + 1;
                    q.push(arcs[i].v);
                }
        }
        return dist[sink] > 0;
    }
    int dfs(int u, int flow) {
        if (u == sink) return flow;
        for (int &i = current[u]; ~i; i = arcs[i].next) {
            int v = arcs[i].v, r = arcs[i].residual;
            if (dist[v] == (dist[u] + 1) && r > 0) {
                int volume = dfs(v, min(r, flow));
                if (volume > 0) {
                    arcs[i].residual -= volume;
                    arcs[i ^ 1].residual += volume;
                    return volume;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int v, int e, int s, int t) {
        arcs = new arc[e];
        vertices = v;
        source = s, sink = t;
        idx = 0, head = new int[v], dist = new int[v], current = new int[v];
        memset(head, -1, sizeof(int) * v);
    }
    ~Dinic() { delete [] arcs, head, dist, current; }
    void addArc(int u, int v, int capacity) {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }
    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            for (int i = 0; i < vertices; i++) current[i] = head[i];
            while (int delta = dfs(source, INF))
                flow += delta;
        }
        return flow;
    }
};

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, N, M;
    string line;
    cin >> T;
    int used[300100];
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ":\n";
        memset(used, 0, sizeof used);
        Dinic dinic(6100, 1000010, 0, 6001);
        int s = 0, p, c;
        cin >> N;
        cin.ignore(256, '\n');
        for (int i = 1; i <= N; i++) {
            getline(cin, line);
            istringstream iss(line);
            iss >> p; s += p;
            dinic.addArc(0, i, p);
            while (iss >> c) used[c] = i;
        }
        cin >> M;
        cin.ignore(256, '\n');
        for (int i = 1; i <= M; i++) {
            getline(cin, line);
            istringstream iss(line);
            iss >> p; s += p;
            dinic.addArc(N + i, 6001, p);
            while (iss >> c) {
                if (used[c]) dinic.addArc(used[c], N + i, INF);
            }
        }
        cout << s - dinic.maxFlow() << '\n';
        if (cs < T) cout << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是利用“同一家公司内部的报价不冲突”这一限制，将报价冲突关系建模为二分图。最大化互不冲突报价的总金额，可以转化为最小化需要删除的报价金额，也就是求二分图的最小权顶点覆盖。通过源点、汇点和无穷大容量的冲突边建立网络后，使用最大流即可求出最小删除代价，进而得到最大收入。
