
> **摘要**：本题要求在单位网格上不抬笔连续绘制所有给定线段，求最少墨水量，本质是图论中的开放中国邮递员问题。解法先将每条线段按整数点拆分为单位边，构建无向图并检查连通性，再用 $\texttt{Floyd‑Warshall}$ 求任意两点最短距离，最后通过状压 DP 对奇度顶点做最小权完美匹配（枚举欧拉路径端点对），答案为总边长加上额外重复路径长度。坐标范围极小，算法高效可行。

## 题目描述

给定若干条单位网格上的线段，线段端点均为整数坐标。要求从某条线段的一个端点开始，笔尖不离开纸面，经过所有给定线段至少一次，且不得绘制额外线段。允许重复经过已有线段，仅能在整数坐标点处改变方向。求完成绘制所需的最少墨水量（单位长度墨水为 $1$ 个单位）。若无法在不抬笔的情况下完成所有线段，则输出特殊标记 `~x(`。

## 输入格式

第一行包含一个整数 $T$（$T < 20$），表示测试用例总数。  
每个测试用例第一行包含一个整数 $N$（$N < 10$），表示线段数量。  
接下来 $N$ 行，每行描述一条线段，格式为两个点 $Y_1X_1\ Y_2X_2$，其中 $Y$ 取值为 $\texttt{A}$ 到 $\texttt{E}$（对应纵坐标 $1$ 到 $5$），$X$ 取值为 $\texttt{1}$ 到 $\texttt{5}$（对应横坐标 $1$ 到 $5$）。

## 输出格式

对于每个测试用例，输出 `Case x:` 后接所需墨水量，保留两位小数。若无法完成，则输出 `~x(`。

## 样例

**输入**
```text
2
4
A1 C2
B3 C3
C4 C2
C2 D2
2
A1 A5
E1 E5
```

**输出**
```text
Case 1: 8.24
Case 2: ~x(
```

## 题目分析

本题本质是图论中的**中国邮递员问题（开放版）**。给定线段作为无向带权图的边，端点作为顶点，边权为欧氏距离。绘制要求等价于：从某个顶点出发，沿图的边行走，覆盖所有边至少一次，允许重复边，求最短行走距离。

由于允许重复经过边，问题转化为：在原图上添加若干重复边（即重复行走的部分），使得新图中存在一条欧拉路径（即从某起点出发，恰好经过所有边一次，不要求回起点）。根据欧拉路径存在条件，新图必须连通且奇度顶点数目为 $0$（欧拉回路）或 $2$（欧拉路径）。原图可能已有一些奇度顶点。由于添加重复边会改变顶点的奇偶性（重复一条边会使两端点度数的奇偶性均翻转），因此需要在奇度顶点之间通过重复路径配对连接，使得最终奇度顶点数不超过 $2$。

本题额外约束：所有顶点坐标都是整数，且线段端点均在 $[1,5]\times[1,5]$ 的网格上，但线段可能穿过中间点。然而题目给出的每条线段仅由两个端点描述，而规则 $\texttt{5}$ 要求只能在整数坐标点改变方向。因此实际绘制时，必须沿线段经过所有整数点，且方向只能在这些整数点处改变。故对于每一条原始线段，必须将其拆分为连接相邻整数点的若干小段，这些小段才是真正可走的基本单元。拆分后形成新的无向无权（但边长均为 $1$）图，原问题等价于在该新图上求最短的连续覆盖所有边的路线。

若原图不连通，则不可能不抬笔经过所有边，直接输出特殊标记。

## 解题思路

处理每个测试用例的步骤如下：

**步骤 $\texttt{1}$. 解析线段并拆分为单位线段**  
对于每条给定线段，其两个端点均为整数坐标。由于只能沿整数点转向，必须把线段上的所有整数点（包括端点）依次列出，然后将相邻整数点之间连成一条单位长度的边。这些单位边构成新图的基本边集。所有顶点为所有出现的整数坐标点。

**步骤 $\texttt{2}$. 构建无向图并计算度数**  
对每条单位边，连接两个顶点，并记录该边长度为 $1$。同时累加所有单位边的总长度 $totalLen$，并更新两端点的度数。

**步骤 $\texttt{3}$. 检查连通性**  
使用深度优先搜索遍历图，若存在顶点未被访问，则图不连通，输出特殊标记并跳过后续计算。

**步骤 $\texttt{4}$. 计算所有顶点对之间的最短路径**  
由于顶点数量很小（最多 $25$ 个整数点，实际出现的更少），使用 Floyd‑Warshall 算法计算任意两点间的最短距离（以单位边长度 $1$ 为权值）。该距离代表在图上重复走某段路径所需的最小额外墨水量。

**步骤 $\texttt{5}$. 处理奇度顶点匹配**  
设当前图中度数为奇数的顶点集合为 $S$，其大小为 $m$（必为偶数）。若 $m=0$，则图已是欧拉图，不需要额外重复，答案为 $totalLen$。  
若 $m>0$，需要添加重复路径使奇度顶点数变为 $2$（即选择一对奇度顶点作为欧拉路径的起点和终点），其余 $m-2$ 个奇度顶点两两配对，每对之间走一条最短路径作为重复边。重复路径的长度之和即为需要额外增加的墨水量。  
枚举所有可能的端点对 $(i,j)$，对剩余顶点做最小权完美匹配（状压 DP）。匹配权重为两点间的最短距离。取所有端点对中匹配权值的最小值作为额外重复长度 $repeat$。最终答案为 $totalLen + repeat$。

**步骤 $\texttt{6}$. 输出结果**  
保留两位小数输出答案。

## 代码实现

```cpp
// Continuous Drawing
// UVa ID: 11156
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

bool onSegment(const Point& p, const Point& a, const Point& b) {
    long long cross = 1LL * (p.x - a.x) * (b.y - a.y) - 1LL * (p.y - a.y) * (b.x - a.x);
    if (cross != 0) return false;
    long long dot = 1LL * (p.x - a.x) * (b.x - a.x) + 1LL * (p.y - a.y) * (b.y - a.y);
    long long len2 = 1LL * (b.x - a.x) * (b.x - a.x) + 1LL * (b.y - a.y) * (b.y - a.y);
    return 0 <= dot && dot <= len2;
}

double distPoint(const Point& a, const Point& b) {
    return sqrt(1.0 * (a.x - b.x) * (a.x - b.x) + 1.0 * (a.y - b.y) * (a.y - b.y));
}

Point parsePoint(const string& s) {
    int x = s[1] - '0';
    int y = s[0] - 'A' + 1;
    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<pair<Point, Point>> segs;
        for (int i = 0; i < N; ++i) {
            string p1s, p2s;
            cin >> p1s >> p2s;
            Point p1 = parsePoint(p1s);
            Point p2 = parsePoint(p2s);
            segs.push_back({p1, p2});
        }
        map<pair<int, int>, int> id;
        auto getIdx = [&](const Point& p) -> int {
            pair<int, int> key = {p.x, p.y};
            if (id.count(key)) return id[key];
            int idx = (int)id.size();
            id[key] = idx;
            return idx;
        };
        vector<tuple<int, int, double>> edges;
        vector<int> deg;
        double totalLen = 0.0;
        for (auto& seg : segs) {
            Point a = seg.first, b = seg.second;
            vector<Point> pts;
            for (int x = 1; x <= 5; ++x)
                for (int y = 1; y <= 5; ++y) {
                    Point p{x, y};
                    if (onSegment(p, a, b)) pts.push_back(p);
                }
            auto distSq = [&](const Point& p) -> long long {
                long long dx = p.x - a.x, dy = p.y - a.y;
                return dx * dx + dy * dy;
            };
            sort(pts.begin(), pts.end(), [&](const Point& p, const Point& q) {
                return distSq(p) < distSq(q);
            });
            for (size_t k = 0; k + 1 < pts.size(); ++k) {
                Point p = pts[k], q = pts[k + 1];
                int u = getIdx(p), v = getIdx(q);
                double w = distPoint(p, q);
                edges.emplace_back(u, v, w);
                totalLen += w;
                if ((int)deg.size() <= u) deg.resize(u + 1, 0);
                if ((int)deg.size() <= v) deg.resize(v + 1, 0);
                deg[u]++, deg[v]++;
            }
        }
        int V = (int)id.size();
        if (V == 0) {
            cout << "Case " << tc << ": 0.00\n";
            continue;
        }
        // 连通性检查
        vector<vector<int>> adj(V);
        for (auto& e : edges) {
            int u = get<0>(e), v = get<1>(e);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> vis(V, false);
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int v : adj[u])
                if (!vis[v]) dfs(v);
        };
        dfs(0);
        bool connected = true;
        for (int i = 0; i < V; ++i)
            if (!vis[i]) { connected = false; break; }
        if (!connected) {
            cout << "Case " << tc << ": ~x(\n";
            continue;
        }
        // Floyd-Warshall算法求所有点对最短路径
        const double INF = 1e100;
        vector<vector<double>> dist(V, vector<double>(V, INF));
        for (int i = 0; i < V; ++i) dist[i][i] = 0.0;
        for (auto& e : edges) {
            int u = get<0>(e), v = get<1>(e);
            double w = get<2>(e);
            if (w < dist[u][v]) dist[u][v] = dist[v][u] = w;
        }
        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        // 奇度顶点
        vector<int> odd;
        for (int i = 0; i < V; ++i)
            if (deg[i] % 2 == 1) odd.push_back(i);
        int m = (int)odd.size();
        double repeat = 0.0;
        if (m > 0) {
            // 奇度点之间的距离矩阵
            vector<vector<double>> d(m, vector<double>(m, 0.0));
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                    d[i][j] = dist[odd[i]][odd[j]];
            int fullMask = (1 << m) - 1;
            vector<double> dp(1 << m, INF);
            dp[0] = 0.0;
            for (int mask = 1; mask <= fullMask; ++mask) {
                if (__builtin_popcount((unsigned)mask) % 2) continue;
                int p = -1;
                for (int i = 0; i < m; ++i)
                    if (mask & (1 << i)) { p = i; break; }
                for (int q = p + 1; q < m; ++q) {
                    if (!(mask & (1 << q))) continue;
                    int prev = mask ^ (1 << p) ^ (1 << q);
                    dp[mask] = min(dp[mask], dp[prev] + d[p][q]);
                }
            }
            double best = INF;
            for (int i = 0; i < m; ++i)
                for (int j = i + 1; j < m; ++j) {
                    int sub = fullMask ^ (1 << i) ^ (1 << j);
                    best = min(best, dp[sub]);
                }
            repeat = best;
        }
        double ans = totalLen + repeat;
        cout << "Case " << tc << ": " << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
```

## 总结

本题的关键在于将原始线段拆分为单位边，将绘制问题转化为图论中的开放中国邮递员问题。核心技巧是利用欧拉路径的度数条件，将重复行走的优化转化为奇度顶点之间的最小权完美匹配。由于坐标范围极小，$\texttt{Floyd‑Warshall}$ 和状压 $\texttt{DP}$ 均能高效求解。注意对不连通图的特殊处理，以及严格按题意在整数点处分段处理线段，否则会忽略中间可转向点导致错误。本题展示了图论模型转换与动态规划结合的经典思路。
