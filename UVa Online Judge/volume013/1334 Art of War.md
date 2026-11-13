
> **摘要**：本题给定 $n$ 个国家的首都坐标与 $m$ 条互不相交的边界线段，要求求出每个国家的所有敌国（即与其共享边界的国家）。解题核心是把边界线段构成的平面图转化为「面」的关系：将每条无向边拆成两条有向边，按顶点处出边的极角排序遍历出所有边界环，用有向面积判断环的方向，再用点在多边形内判断与并查集合并嵌套的边界环，从而还原出真实的国家区域；随后用首都到最近边界线段的叉积确定其所属面，最后遍历每条线段两侧的面建立敌对关系。总时间复杂度为 $O(m^2 + nm)$，空间复杂度为 $O(m + n)$。

# 题目描述

战国时期存在 $n$ 个国家，每个国家的首都由一个平面坐标表示。地图由 $m$ 条边界线段组成，每条线段分隔两个国家，或者分隔一个国家与外部荒地。

题目保证：

- 每个国家由一条连续的边界线围成；
- 每个国家恰好有一个首都；
- 荒地中没有首都；
- 边界线段互不交叉，只能在端点处相接；
- 一条边界线段两侧不能属于同一个国家；
- 荒地不能同时位于一条边界线段的两侧。

如果两个国家拥有公共边界，则这两个国家互为敌国。需要求出每个国家的所有敌国。

国家编号按照首都输入顺序确定，从 $1$ 到 $n$ 编号。

# 输入格式

输入包含多组测试数据。

每组测试数据的第一行包含两个整数 $n$ 和 $m$，分别表示国家数量和边界线段数量，满足：

$$
1 \le n \le 600
$$

$$
1 \le m \le 4000
$$

接下来 $n$ 行，每行包含两个整数 $x$ 和 $y$，表示一个国家首都的坐标。

接下来 $m$ 行，每行包含四个整数 $x_1$、$y_1$、$x_2$ 和 $y_2$，表示一条从点 $(x_1, y_1)$ 到点 $(x_2, y_2)$ 的边界线段。

当一组数据的 $n$ 和 $m$ 同时为 $0$ 时，输入结束。

# 输出格式

对于每组测试数据，输出 $n$ 行。

第 $i$ 行描述编号为 $i$ 的国家的所有敌国。该行首先输出敌国数量 $k$，随后按照编号升序输出这 $k$ 个敌国的编号。

每组测试数据之间不需要输出空行。

# 样例输入

```text
4 12
3 2
11 8
12 17
1 19
0 0 10 0
10 0 20 0
20 0 20 10
20 10 20 20
20 20 10 20
10 20 0 20
0 20 0 10
0 10 0 0
10 0 10 10
0 10 10 10
20 10 10 10
10 20 10 10
4 19
10 190
30 170
50 150
100 70
140 0 140 140
140 140 60 140
60 140 60 0
200 0 200 200
200 200 0 200
0 200 0 0
160 0 160 160
160 160 40 160
40 160 40 0
180 0 180 180
180 180 20 180
20 180 20 0
0 0 20 0
20 0 40 0
40 0 60 0
60 0 140 0
140 0 160 0
160 0 180 0
180 0 200 0
0 0
```

# 样例输出

```text
2 2 4
2 1 3
2 2 4
2 1 3
1 2
2 1 3
2 2 4
1 3
```

# 题目分析

边界线段组成了一个平面图。平面图中的每个面对应一个区域，国家和荒地都属于这些区域。直接根据首都所在位置判断国家归属并不容易，原因是边界可能存在嵌套结构。

例如，一个国家可能是一个带有内部空洞的区域。外层边界和内层边界分别形成两个面边界，但内层边界内部的区域仍然属于外部国家，而不是一个新的国家。样例中的多层嵌套正方形正是这种情况。

因此，解题过程需要完成以下任务：

- 根据线段端点建立平面图；
- 遍历平面图的所有面；
- 处理同一个国家由多个边界环组成的情况；
- 根据每个首都的位置确定其所属区域；
- 根据每条边界线段两侧的国家建立敌对关系。

对于平面图中的一条有向边，沿着该有向边到达终点后，可以根据终点处相邻边的极角顺序确定下一条边。始终选择反向边顺时针方向的下一条边，即可沿着某个面的边界完整遍历。这样能够得到所有面的边界环。

遍历边界环时，可以利用多边形有向面积判断方向：

$$
S = \frac{1}{2} \sum_{i=1}^{k} \left( x_i y_{i+1} - y_i x_{i+1} \right)
$$

其中，$S > 0$ 表示边界环按逆时针方向排列，$S < 0$ 表示边界环按顺时针方向排列。

逆时针环和顺时针环具有不同的几何含义。对于一个普通区域，其外边界通常按逆时针方向遍历，内边界通常按顺时针方向遍历。若一个顺时针边界环被某个逆时针边界环包含，则两个边界环之间的区域属于同一个面，需要使用并查集合并。

最后，需要将每个首都映射到一个面。代码采用首都到所有边界线段的最短距离来确定最近边界线段。由于首都位于某个国家内部，不会位于边界线上，因此首都相对于该线段的左右关系可以确定它位于该线段对应的哪一侧。每条无向边的两个方向分别对应两个不同的面，两个面若分别属于不同国家，则这两个国家互为敌国。

# 解题思路

首先，将每条无向边界线段拆成方向相反的两条有向边。对于原始线段 $u \rightarrow v$，建立：

- 有向边 $u \rightarrow v$；
- 有向边 $v \rightarrow u$。

两条有向边互为反向边，并记录对应关系。这样，平面图中的每个面都可以通过有向边进行遍历。

在每个顶点处，按照出边相对于该顶点的极角从小到大排序。设当前有向边为 $u \rightarrow v$，到达顶点 $v$ 后，先找到反向边 $v \rightarrow u$ 在出边序列中的位置，再选择它前面的出边作为下一条边。该选择相当于沿着当前面的边界继续行走。

从每条尚未访问的有向边出发，不断沿着下一条边行走，直到回到起点，即可得到一个边界环。遍历过程中记录边界环经过的顶点，并计算其有向面积。

设当前边界环为 $A$，另一个边界环为 $B$。如果满足以下条件：

- $B$ 的绝对面积大于 $A$；
- $A$ 的代表点位于 $B$ 内部；
- $B$ 的有向面积为正；
- $A$ 的有向面积为负；

则 $A$ 是 $B$ 的内部边界，二者之间的区域属于同一个面。使用并查集将这两个面合并。通过选择面积最小的包含环作为父环，可以逐层处理嵌套边界。

对于每个首都，枚举所有原始边界线段，计算首都到线段的平方距离，选择距离最小的线段。设该线段方向为 $A \rightarrow B$，通过叉积：

$$
cross(A,B,P)
$$

判断首都 $P$ 位于线段左侧还是右侧：

- 当叉积大于 $0$ 时，首都位于有向边 $A \rightarrow B$ 的左侧；
- 当叉积小于 $0$ 时，首都位于有向边 $A \rightarrow B$ 的右侧。

根据左右关系，将首都归入该无向边两侧的对应面。并查集合并完成后，多个边界环属于同一个实际面，因此使用并查集代表元保存国家编号。

最后，遍历所有原始边界线段。取该线段两个方向对应的面，若两个面都属于国家且国家编号不同，则在两个国家的敌国集合中互相加入对方。使用集合保存敌国编号可以自动去重，并保证输出顺序升序。

# 代码实现

```cpp
// Art of War
// UVa ID: 1334
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long double Eps = 1e-10L;

struct Point {
    long double x, y;
};

struct Edge {
    int from, to, rev;
};

struct Dsu {
    vector<int> fa;
    Dsu(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) fa[y] = x;
    }
};

long double cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long double disToSegment(Point p, Point a, Point b) {
    long double dx = b.x - a.x, dy = b.y - a.y;
    long double len2 = dx * dx + dy * dy;
    long double t = ((p.x - a.x) * dx + (p.y - a.y) * dy) / len2;
    t = max(0.0L, min(1.0L, t));
    Point q = {a.x + t * dx, a.y + t * dy};
    long double px = p.x - q.x, py = p.y - q.y;
    return px * px + py * py;
}

bool pointInPolygon(Point p, const vector<Point> &poly) {
    bool in = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[i], b = poly[j];
        bool up = a.y > p.y;
        bool down = b.y > p.y;
        if (up != down) {
            long double x = a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y);
            if (x > p.x) in = !in;
        }
    }
    return in;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<Point> capitals(n);
        for (int i = 0; i < n; i++) {
            long double x, y;
            cin >> x >> y;
            capitals[i] = {x, y};
        }
        vector<Point> points;
        vector<Edge> edges;
        vector<pair<int, int>> undirected;
        map<pair<long double, long double>, int> pointId;
        auto getPointId = [&](Point p) {
            pair<long double, long double> key = {p.x, p.y};
            auto it = pointId.find(key);
            if (it != pointId.end()) return it->second;
            int id = points.size();
            pointId[key] = id;
            points.push_back(p);
            return id;
        };
        for (int i = 0; i < m; i++) {
            long double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int u = getPointId({x1, y1}), v = getPointId({x2, y2});
            int id = edges.size();
            edges.push_back({u, v, id + 1});
            edges.push_back({v, u, id});
            undirected.push_back({id, id + 1});
        }
        int vertexCount = points.size();
        vector<vector<int>> out(vertexCount);
        for (int i = 0; i < (int)edges.size(); i++) out[edges[i].from].push_back(i);
        for (int i = 0; i < vertexCount; i++) {
            sort(out[i].begin(), out[i].end(), [&](int a, int b) {
                Point pa = points[edges[a].to], pb = points[edges[b].to], pc = points[edges[a].from];
                long double aa = atan2(pa.y - pc.y, pa.x - pc.x);
                long double ab = atan2(pb.y - pc.y, pb.x - pc.x);
                return aa < ab;
            });
        }
        vector<int> pos(edges.size());
        for (int i = 0; i < vertexCount; i++)
            for (int j = 0; j < (int)out[i].size(); j++)
                pos[out[i][j]] = j;
        vector<int> nextEdge(edges.size());
        for (int i = 0; i < (int)edges.size(); i++) {
            int v = edges[i].to, rev = edges[i].rev;
            int sz = out[v].size();
            int p = pos[rev];
            nextEdge[i] = out[v][(p - 1 + sz) % sz];
        }
        vector<int> faceId(edges.size(), -1);
        vector<vector<int>> faces;
        vector<long double> areas;
        for (int i = 0; i < (int)edges.size(); i++) {
            if (faceId[i] != -1) continue;
            int id = faces.size(), cur = i;
            vector<int> face;
            long double area = 0;
            do {
                faceId[cur] = id;
                face.push_back(cur);
                Point a = points[edges[cur].from], b = points[edges[cur].to];
                area += a.x * b.y - a.y * b.x;
                cur = nextEdge[cur];
            } while (cur != i);
            faces.push_back(face);
            areas.push_back(area / 2.0L);
        }
        int faceCount = faces.size();
        vector<vector<Point>> polygons(faceCount);
        vector<Point> samples(faceCount);
        for (int i = 0; i < faceCount; i++) {
            for (int e : faces[i]) polygons[i].push_back(points[edges[e].from]);
            Point a = points[edges[faces[i][0]].from], b = points[edges[faces[i][0]].to];
            long double dx = b.x - a.x, dy = b.y - a.y;
            long double len = sqrt(dx * dx + dy * dy);
            long double sign = areas[i] > 0 ? 1.0L : -1.0L;
            long double nx = -dy / len * sign, ny = dx / len * sign;
            samples[i] = {(a.x + b.x) / 2.0L + nx * 1e-7L, (a.y + b.y) / 2.0L + ny * 1e-7L};
        }
        Dsu dsu(faceCount);
        for (int i = 0; i < faceCount; i++) {
            int parent = -1;
            long double bestArea = 1e100L;
            for (int j = 0; j < faceCount; j++) {
                if (i == j || fabsl(areas[j]) <= fabsl(areas[i])) continue;
                if (!pointInPolygon(samples[i], polygons[j])) continue;
                if (fabsl(areas[j]) < bestArea) {
                    bestArea = fabsl(areas[j]);
                    parent = j;
                }
            }
            if (parent != -1 && areas[parent] > 0 && areas[i] < 0) dsu.unite(parent, i);
        }
        vector<int> faceState(faceCount, -1);
        for (int i = 0; i < n; i++) {
            int bestEdge = -1;
            long double bestDis = 1e100L;
            for (int j = 0; j < m; j++) {
                int e = undirected[j].first;
                Point a = points[edges[e].from], b = points[edges[e].to];
                long double dis = disToSegment(capitals[i], a, b);
                if (dis < bestDis) {
                    bestDis = dis;
                    bestEdge = e;
                }
            }
            Point a = points[edges[bestEdge].from], b = points[edges[bestEdge].to];
            if (cross(a, b, capitals[i]) > 0) faceState[dsu.find(faceId[bestEdge])] = i;
            else faceState[dsu.find(faceId[edges[bestEdge].rev])] = i;
        }
        vector<set<int>> enemy(n);
        for (int i = 0; i < m; i++) {
            int e1 = undirected[i].first, e2 = undirected[i].second;
            int f1 = faceState[dsu.find(faceId[e1])], f2 = faceState[dsu.find(faceId[e2])];
            if (f1 != -1 && f2 != -1 && f1 != f2) {
                enemy[f1].insert(f2);
                enemy[f2].insert(f1);
            }
        }
        for (int i = 0; i < n; i++) {
            cout << enemy[i].size();
            for (int x : enemy[i]) cout << ' ' << x + 1;
            cout << '\n';
        }
    }
    return 0;
}
```

# 总结

本题的核心是将几何区域关系转化为平面图中的面关系，主要使用了以下技巧：

- 将每条无向边拆成两条有向边；
- 通过顶点处的极角排序遍历平面图的所有面；
- 使用有向面积判断边界环方向；
- 使用点在多边形内判断边界环之间的包含关系；
- 使用并查集合并属于同一个实际区域的多个边界环；
- 使用最近边界线段和叉积确定首都所在的面；
- 遍历每条边界线段，根据两侧国家建立敌对关系。

设边界线段数量为 $m$，国家数量为 $n$。面遍历和极角排序的时间复杂度为 $O(m \log m)$；边界环包含关系判断的最坏时间复杂度为 $O(m^2)$；首都定位的时间复杂度为 $O(nm)$。因此总时间复杂度为：

$$
O(m^2 + nm)
$$

空间复杂度为：

$$
O(m + n)
$$
