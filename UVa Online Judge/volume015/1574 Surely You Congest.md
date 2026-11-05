
> **摘要**：本题要求为智能交通系统计算最多有多少通勤者能在无拥堵的前提下同时到达市中心。核心洞察是：只有到市中心最短距离相同的通勤者才可能在同一时刻争夺同一条道路，因此可按最短距离分组，每组转化为一个边容量为 $1$ 的最大流问题，各组答案之和即为最终结果。算法综合运用 $\texttt{Dijkstra}$ 最短路、最短路径 $\texttt{DAG}$ 构建与 $\texttt{Dinic}$ 最大流，是图论建模的典型例题。

## 题目描述

您负责为智能汽车设计一套高级集中式交通管理系统。目标是利用全局信息，指导早晨从郊区驾车前往市中心的通勤者，在避免交通拥堵的前提下，以最优方式到达市中心。

但通勤者熟悉城市且自私，您无法简单地命令他们走比正常时间更长的路线，否则他们会忽略您的指示。您只能说服他们改走同样快捷的替代路线。

城市道路网络由若干交叉口和连接它们的双向道路组成，每条道路有固定的行驶时间。每个通勤者的起点可能不同，但所有通勤者的终点均为市中心交叉口 $1$。如果两个通勤者同时试图沿同一方向进入同一条道路，则会发生拥堵，必须避免这种情况。允许两个通勤者同时通过同一交叉口，或在不同时间进入同一道路。

确定在满足以下条件时，最多有多少通勤者可以无拥堵地到达市中心：
- 所有通勤者同时出发；
- 没有任何通勤者选择非最优路线（即所有通勤者走的路线必须是从其起点到 $1$ 的最短路径）。

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含三个整数 $n$、$m$、$c$，分别表示交叉口数量（$1 \le n \le 25000$）、道路数量（$0 \le m \le 50000$）和通勤者人数（$0 \le c \le 1000$）。接下来 $m$ 行，每行描述一条双向道路，包含三个整数 $x_i$、$y_i$、$t_i$，表示连接交叉口 $x_i$ 和 $y_i$ 的道路行驶时间为 $t_i$（$1 \le t_i \le 10000$），$x_i \neq y_i$。题目保证从每个交叉口均可到达市中心 $1$。最后一行包含 $c$ 个整数，表示各通勤者的起点交叉口。

## 输出格式

对于每个测试用例，输出一行一个整数，表示能无拥堵到达市中心的通勤者的最大数量。

## 样例

输入

```
3 3 2
1 2 42
2 3 1
2 3 1
2 3
4 4 5
1 2 5
1 3 4
4 2 5
4 3 6
4 4 4 4 1
```

输出

```
2
3
```

## 题目分析

本题的关键约束是：每个通勤者必须沿从起点到 $1$ 的最短路径行驶。如果一条道路在某个方向被两个或多个通勤者同时使用，则发生拥堵，这是不允许的。由于所有通勤者同时出发，且沿最短路行驶，那么同一时刻到达同一条道路并同向行驶的通勤者必然是在同一条最短路径的子路径上。因此，我们可以将问题转化为：在有向无环图（由所有最短路径构成）中，每个通勤者从各自的起点出发，沿着有向边向汇点 $1$ 移动，每条有向边在同一时刻最多只能被一个人使用。由于所有通勤者速度相同，且同时出发，若两人沿同一条有向边行驶，则他们必然同时到达该边的起点并同时进入该边，因此边容量为 $1$ 即可保证无拥堵。

但问题并非简单的网络流，因为不同通勤者可能走不同长度的最短路径，即到达 $1$ 的时间可能不同。题目允许不同通勤者在不同时刻进入同一条道路，因此如果两人走的最短路长度不同，他们到达某条公共边的时间就不同，此时即使该边被两人先后使用，也不构成拥堵。因此，只有**最短距离相同**（即从起点到 $1$ 的距离相同）的通勤者，才可能在同一条边的同一时刻相遇。若距离不同，则他们在时间上错开，不会产生冲突。

因此，我们可以按起点到 $1$ 的最短距离对通勤者进行分组。同一组内的通勤者距离相同，他们沿最短路径行驶时，到达任何节点的时间都相同（因为距离相等），所以他们可能在同一时间争夺同一条有向边。不同组之间不存在资源竞争，因为时间上的错开使得边可以被不同组依次使用，不会同时。所以总体最大数量等于各组最大数量的和。

对于每个距离组，问题转化为：给定一个有向无环图（由所有最短路径组成，方向为远离 $1$ 指向靠近 $1$），源点为该组中的各个起点，汇点为 $1$，每条边的容量为 $1$，求从所有源点出发能到达汇点的最大流。由于同一个起点可能有多位通勤者，该起点作为源点，提供的容量等于该起点在该组内的通勤者人数。求最大流即可。

## 解题思路

### 步骤一：计算所有节点到 $1$ 的最短距离

由于图是无向带权图，且 $n$ 最大 $25000$，$m$ 最大 $50000$，使用 $\texttt{Dijkstra}$ 算法从节点 $1$ 出发，计算 $dist[i]$ 表示节点 $i$ 到 $1$ 的最短距离。时间复杂度 $O(m \log n)$。

### 步骤二：构建最短路径有向图

对于每条无向边 $(u, v, t)$，若 $dist[u] = dist[v] + t$，则说明 $u$ 到 $1$ 的最短路径可能经过 $v$，因此添加有向边 $u \to v$（方向指向 $1$）。若 $dist[v] = dist[u] + t$，则添加有向边 $v \to u$。这样构成的有向图是 $\texttt{DAG}$（因为沿边方向距离严格递减）。

### 步骤三：按距离分组

统计每个交叉口作为起点的通勤者人数，按 $dist$ 值分组。对于每个不同的距离值，收集该组内所有起点及其人数。

### 步骤四：对每组单独求最大流

对每一组，建立一个网络流模型：
- 添加超级源点 $S$，连接到该组的每个起点，容量为该起点在该组的人数。
- 将所有最短路径有向边加入网络，每条边容量为 $1$。
- 汇点为节点 $1$。
- 求 $S$ 到 $1$ 的最大流，该值即为该组最多能无拥堵到达的通勤者数。

由于 $c \le 1000$，且起点数量有限，每组内总通勤者数不大，最大流可使用 $\texttt{Dinic}$ 算法，复杂度 $O(E \sqrt{V})$ 或 $O(E V^2)$ 均可接受。但注意每组都要重建图，但图规模为 $n + m$，若每组都重建一次会导致复杂度 $O(\text{组数} \cdot (n+m))$，最大可能 $O(c \cdot (n+m))$，仍可接受（因为 $c \le 1000$，$n=25000, m=50000$，最坏 $1000 \times 75000 = 7.5e7$，加上 $\texttt{Dinic}$ 的常数，可能稍大但实际测试可通过）。更优的方法是统一建图后对每组做一次流，但实现复杂，这里直接每组独立建图。

### 正确性证明

- 必要性：任意无拥堵方案中，同一距离组内任意两人若使用同一条有向边，则他们同时到达该边起点，由于边容量为 $1$，故该边最多被一人使用。这正好是网络流容量限制的体现。不同距离组因到达时间不同，不会冲突，可独立处理。
- 充分性：若某组内存在一个可行流，即每条边流量不超过 $1$，则可将流量分解为从各源点到汇点的路径，每条路径对应一个通勤者的路线。由于路径中的边流量为 $1$，任意两条路径不会共享有向边，因此不会发生拥堵。不同组的路径在时间上错开，综合起来整体无拥堵。

### 复杂度分析

- $\texttt{Dijkstra}$：$O(m \log n)$。
- 构建最短路径有向图：$O(m)$。
- 统计分组：$O(c)$。
- 最大流：每组使用 $\texttt{Dinic}$，节点数 $O(n)$，边数 $O(m)$，组数最多 $c$（实际不同距离值最多 $c$ 个）。总复杂度 $O(\text{组数} \cdot \text{Dinic}(n, m))$，在本题数据下可行。

## 代码实现

```cpp
// Surely You Congest
// UVa ID: 1574
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.710s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// Dinic最大流，用于每组距离相同的通勤者
class Dinic {
public:
    struct Edge {
        int to, rev, cap;
    };
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {}
    void addEdge(int fr, int to, int cap) {
        Edge f{to, (int)g[to].size(), cap};
        Edge r{fr, (int)g[fr].size(), 0};
        g[fr].push_back(f);
        g[to].push_back(r);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int ret = dfs(e.to, t, min(f, e.cap));
                if (ret > 0) {
                    e.cap -= ret;
                    g[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        const int INF = 1e9;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                int f = dfs(s, t, INF);
                if (!f) break;
                flow += f;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c;
    while (cin >> n >> m >> c) {
        // 存储无向边
        vector<pair<pair<int,int>, int>> roads; // ((u,v), t)
        vector<vector<pair<int,int>>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int x, y, t;
            cin >> x >> y >> t;
            roads.push_back({{x, y}, t});
            adj[x].push_back({y, t});
            adj[y].push_back({x, t});
        }

        // 读取所有通勤者的起点
        vector<int> starts(c);
        for (int i = 0; i < c; ++i) cin >> starts[i];

        // Dijkstra 求所有点到 1 的最短距离（无向图，从1出发）
        const long long INF = 4e18;
        vector<long long> dist(n + 1, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        dist[1] = 0;
        pq.push({0, 1});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto &[v, t] : adj[u]) {
                if (dist[v] > d + t) {
                    dist[v] = d + t;
                    pq.push({dist[v], v});
                }
            }
        }

        // 构建最短路径 DAG 的有向边（方向从高距离指向低距离）
        vector<pair<int,int>> dagEdges;
        for (auto &road : roads) {
            int u = road.first.first, v = road.first.second, t = road.second;
            if (dist[u] == dist[v] + t) dagEdges.push_back({u, v});
            if (dist[v] == dist[u] + t) dagEdges.push_back({v, u});
        }

        // 统计每个起点出现的次数
        vector<int> startCnt(n + 1, 0);
        for (int s : starts) startCnt[s]++;

        // 按距离分组，每组记录起点及数量
        map<long long, vector<pair<int,int>>> groups;
        for (int i = 1; i <= n; ++i) {
            if (startCnt[i] > 0) {
                groups[dist[i]].push_back({i, startCnt[i]});
            }
        }

        long long answer = 0; // 答案最大不超过 c，int 足够
        for (auto &kv : groups) {
            auto &vec = kv.second;
            // 特判：如果所有起点就在市中心（距离0），直接全部计入
            // 但统一走最大流也可，此处不特判，保持通用
            Dinic din(n + 1); // 节点编号 0..n，0 为超级源，1 为汇
            // 添加所有 DAG 边，容量 1（同距离组内不可共享）
            for (auto &e : dagEdges) {
                din.addEdge(e.first, e.second, 1);
            }
            // 超级源连接到该组每个起点，容量为该起点通勤者数
            for (auto &p : vec) {
                din.addEdge(0, p.first, p.second);
            }
            // 求从超级源到节点 1 的最大流
            answer += din.maxFlow(0, 1);
        }

        cout << answer << '\n';
    }

    return 0;
}
```

## 总结

本题将实际问题转化为图论模型，关键点在于：
- 识别出只有最短距离相同的通勤者才会产生竞争，据此将问题分解为多个独立的最大流子问题。
- 最短路径图的构建使用 $\texttt{Dijkstra}$ 加距离条件。
- 网络流模型中使用容量为 $1$ 的边表示道路在同一时刻只能被一人占用。
- 分组处理降低问题规模，同时利用最大流求解每组的最优值。

本题综合了最短路、$\texttt{DAG}$ 和最大流算法，是图论建模的典型例题。
