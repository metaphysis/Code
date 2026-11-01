
> **摘要**：本文讨论两个简单多边形交集区域的求解问题：给定两个按顺时针顺序给出顶点的简单多边形，要求输出其交集所包含的全部连通区域，每个区域以多边形边界顶点表示，并按题目规则规范化输出。文章从几何本质出发，指出交集边界只能由两个原多边形的边界片段构成，进而给出「求边界交点 → 切分原边 → 中点包含性判断筛选交集边界 → 建立半边结构 → 遍历平面面 → 筛选并规范化区域」的完整流程。实现上使用叉积统一处理方向判断、共线判定、线段求交与有向面积计算，借助线段参数排序完成边的正确切分，并通过极角排序与半边转移规则提取所有有界面，再用有向面积排除外部面、反复删除共线顶点以满足输出要求。该方法可完整处理边界交点、端点相交、边界重合、多个交集区域及共线冗余顶点等情况，时间复杂度为 $O((n_1+n_2)^3)$，空间复杂度为 $O((n_1+n_2)^2)$，并附有符合 $\texttt{C++11}$ 标准的完整代码实现。

# 题目描述

给定两个按顺时针顺序给出顶点的简单多边形，求出两个多边形的交集所包含的所有连通区域。每个交集区域都必须输出为一个多边形，并按照顺时针或逆时针方向输出其边界顶点。输出时，每个区域的第一个顶点必须是横坐标最小的顶点；横坐标相同时，选择纵坐标最小的顶点。输出坐标保留两位小数，并且删除共线造成的冗余顶点以及退化部分。

# 输入格式

输入包含若干组数据。每组数据依次描述两个多边形。

每个多边形的输入形式为：

```text
n x1 y1 x2 y2 ... xn yn
```

其中，$n$ 表示多边形的顶点数，随后给出 $n$ 个顶点的坐标。顶点按照沿多边形边界顺时针行走时的顺序排列，最后一个顶点和第一个顶点构成一条边。

输入以两个连续的 $0$ 结束，这两个 $0$ 不属于任何数据集。

# 输出格式

对于第 $k$ 组数据，输出：

```text
Data Set k
Number of intersection regions: r
```

其中，$r$ 是交集区域数量。随后依次输出每个区域的顶点，格式为：

```text
Region k:(x1,y1)(x2,y2)...
```

每个坐标保留两位小数。

# 样例输入

```text
3 2 1 0.5 3.5 8 5
5 1.5 3 2 7 6.5 6.5 6.5 3.25 4 4.5
0
0
```

# 样例输出

```text
Data Set 1
Number of intersection regions: 2
Region 1:(1.50,3.00)(1.59,3.72)(3.25,4.05)
Region 2:(4.43,4.29)(6.50,4.70)(6.50,4.00)(5.86,3.57)
```

# 题目分析

两个多边形的交集边界只可能由两个原多边形的边界组成。对于某一条原边，如果它的一部分位于另一个多边形内部，那么这一部分就属于交集的边界。两个多边形的边界可能相交，因此必须先找出所有边界交点，再将原边切分成若干条不包含内部交点的小线段。

直接按照原顶点连接关系寻找区域并不充分，因为一个交集区域的顶点既可能是原多边形顶点，也可能是两条边的交点。将所有原顶点和所有边界交点统一编号后，交集边界就可以表示为一个平面图。平面图中的顶点是几何点，边是位于两个多边形交集中的小线段。

对于切分后的一条小线段，取它的中点进行包含性判断。由于所有边界交点都已经加入切分点集合，所以小线段内部不会再出现边界穿越点，中点与整条小线段具有相同的内外关系。若小线段属于第一个多边形的边界，且其中点位于第二个多边形内部或边界上，则该线段属于交集边界；第二个多边形的边界同理。

构造出交集边界平面图后，需要从图中提取每个有界面。对每条无向边建立两个方向相反的半边，并在每个顶点处按照极角排序所有出边。沿当前半边到达顶点后，在该顶点的出边序列中找到当前半边的反向半边，再选择其前一个方向的半边继续行走。该规则始终沿着同一侧的面边界前进，因此可以遍历出平面图的所有面。

半边遍历会同时得到交集区域内部的有界面和外部面。按照逆时针方向计算环的有向面积，正面积环对应有界区域，负面积环对应外部方向，因此只保留面积为正的环即可。遍历得到的边界中可能包含同一直线上的中间点，需要反复删除共线顶点，直到每个相邻三点都不共线。

题目保证每个输入多边形是简单多边形，任意两条同一多边形的边只会在公共端点相交，因此平面图的局部结构满足半边遍历要求。边界重合时，程序通过无向端点对去重，避免同一条几何线段被重复加入。

# 解题思路

设两个多边形分别为 $P_1$ 和 $P_2$，顶点数量分别为 $n_1$ 和 $n_2$。

步骤 $\texttt{1}$：统一保存几何点。先将两个多边形的原顶点加入点数组。之后计算出的每个交点都通过坐标比较寻找已有编号；若不存在相同点，则加入点数组并分配新编号。

步骤 $\texttt{2}$：求边界交点。枚举 $P_1$ 的每条边和 $P_2$ 的每条边。对于严格相交的两条线段，使用叉积求出直线交点，并分别计算交点在线段上的参数。对于一条边的端点位于另一条边上的情况，也将该端点加入对应边的切分点集合。这样能够处理边界端点相交和部分重合的情况。

步骤 $\texttt{3}$：切分所有边。每条原边初始包含参数为 $0$ 和 $1$ 的两个端点。将其余交点按照在线段上的参数从小到大排序，并删除连续重复的点编号。相邻两个切分点之间形成一条小线段。

步骤 $\texttt{4}$：筛选交集边界。对每条小线段取中点。如果该小线段来自 $P_1$，则判断中点是否在 $P_2$ 内部或边界上；如果来自 $P_2$，则判断中点是否在 $P_1$ 内部或边界上。满足条件的小线段加入平面图，并用无向端点对去重。

步骤 $\texttt{5}$：建立半边结构。每条无向边建立两条方向相反的半边，并记录每条半边的起点、终点和反向半边编号。按照出边方向的极角对每个顶点的出边排序，同时记录每条半边在对应出边序列中的位置。

步骤 $\texttt{6}$：遍历平面面。依次选择尚未访问的半边开始遍历。到达当前终点后，找到当前半边的反向半边，在该顶点的极角序列中选择其前一个出边作为下一条半边。直到回到已经访问过的半边为止，得到一个闭合边界环。

步骤 $\texttt{7}$：筛选并规范化区域。删除边界环中的共线顶点。若环的顶点数少于 $3$，或者有向面积不为正，则丢弃该环。对保留的环旋转顶点序列，使最小横坐标且最小纵坐标的顶点位于首位。

点 $a$、$b$ 的叉积定义为：

$$
cross(a,b) = a_x b_y - a_y b_x
$$

三点 $a$、$b$、$c$ 是否共线，可以通过向量 $b-a$ 与 $c-a$ 的叉积判断：

$$
cross(b-a,c-a) = 0
$$

多边形环的有向面积使用鞋带公式计算：

$$
S = \frac{1}{2}\sum_{i=0}^{k-1}(x_i y_{i+1} - x_{i+1} y_i)
$$

其中下标按照环的顺序循环。按照程序中的半边转移规则，交集区域对应正面积环，因此保留 $S > 0$ 的环。

设两个多边形的边数分别为 $n_1$ 和 $n_2$。边界相交检测需要 $O(n_1 n_2)$ 的时间。每条边上的切分点数量最多为 $O(n_1+n_2)$，对切分点排序的总复杂度为 $O((n_1+n_2)^2 \log(n_1+n_2))$。点包含判断在最坏情况下需要遍历另一个多边形的全部边，因此整体实现的时间复杂度为 $O((n_1+n_2)^3)$，空间复杂度为 $O((n_1+n_2)^2)$。

# 代码实现

代码使用叉积完成方向判断和直线求交，使用射线法完成点在多边形内的判断，使用半边结构提取所有有界面。代码符合 $\texttt{C++11}$ 标准。

```cpp
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;

struct Point {
    double x, y;
};

Point operator + (const Point &a, const Point &b) { return {a.x + b.x, a.y + b.y}; }
Point operator - (const Point &a, const Point &b) { return {a.x - b.x, a.y - b.y}; }
Point operator * (const Point &a, double k) { return {a.x * k, a.y * k}; }

double cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
double cross(const Point &a, const Point &b, const Point &c) { return cross(b - a, c - a); }
double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

int sgn(double x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}

bool samePt(const Point &a, const Point &b) {
    return fabs(a.x - b.x) <= eps && fabs(a.y - b.y) <= eps;
}

bool onSeg(const Point &a, const Point &b, const Point &p) {
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

bool properCross(const Point &a, const Point &b, const Point &c, const Point &d) {
    int o1 = sgn(cross(a, b, c)), o2 = sgn(cross(a, b, d));
    int o3 = sgn(cross(c, d, a)), o4 = sgn(cross(c, d, b));
    return o1 * o2 < 0 && o3 * o4 < 0;
}

Point lineInter(const Point &a, const Point &b, const Point &c, const Point &d) {
    Point r = b - a, s = d - c;
    double t = cross(c - a, s) / cross(r, s);
    return a + r * t;
}

double paramOnSeg(const Point &a, const Point &b, const Point &p) {
    if (fabs(a.x - b.x) >= fabs(a.y - b.y)) return (p.x - a.x) / (b.x - a.x);
    return (p.y - a.y) / (b.y - a.y);
}

int getPointId(const Point &p, vector<Point> &pts) {
    for (int i = 0; i < (int)pts.size(); i++)
        if (samePt(pts[i], p)) return i;
    pts.push_back(p);
    return (int)pts.size() - 1;
}

bool inPoly(const Point &p, const vector<Point> &poly) {
    bool in = false;
    int n = (int)poly.size();
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSeg(a, b, p)) return true;
        if ((a.y > p.y) != (b.y > p.y)) {
            double x = (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
            if (x > p.x + eps) in = !in;
        }
    }
    return in;
}

vector<int> reduceCycle(const vector<int> &seq, const vector<Point> &pts) {
    vector<int> cur = seq;
    while (true) {
        int n = (int)cur.size();
        if (n < 3) break;
        vector<int> nxt;
        bool changed = false;
        for (int i = 0; i < n; i++) {
            int a = cur[(i - 1 + n) % n], b = cur[i], c = cur[(i + 1) % n];
            if (fabs(cross(pts[a], pts[b], pts[c])) <= eps) changed = true;
            else nxt.push_back(b);
        }
        cur.swap(nxt);
        if (!changed) break;
    }
    return cur;
}

double polyArea(const vector<int> &seq, const vector<Point> &pts) {
    double s = 0;
    int n = (int)seq.size();
    for (int i = 0; i < n; i++) s += cross(pts[seq[i]], pts[seq[(i + 1) % n]]);
    return s * 0.5;
}

vector<int> rotateToMin(const vector<int> &seq, const vector<Point> &pts) {
    int n = (int)seq.size(), pos = 0;
    for (int i = 1; i < n; i++) {
        Point a = pts[seq[i]], b = pts[seq[pos]];
        if (a.x < b.x - eps || (fabs(a.x - b.x) <= eps && a.y < b.y - eps)) pos = i;
    }
    vector<int> res;
    for (int i = 0; i < n; i++) res.push_back(seq[(pos + i) % n]);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);
    int n1, n2, ds = 1;
    while (cin >> n1) {
        if (n1 == 0) break;
        vector<Point> p1(n1), p2;
        for (int i = 0; i < n1; i++) cin >> p1[i].x >> p1[i].y;
        cin >> n2;
        p2.resize(n2);
        for (int i = 0; i < n2; i++) cin >> p2[i].x >> p2[i].y;
        vector<Point> pts;
        vector<int> id1(n1), id2(n2);
        for (int i = 0; i < n1; i++) id1[i] = getPointId(p1[i], pts);
        for (int i = 0; i < n2; i++) id2[i] = getPointId(p2[i], pts);
        int ec = n1 + n2;
        vector<vector<pair<double, int> > > cut(ec);
        vector<int> own(ec);
        for (int i = 0; i < n1; i++) {
            int j = (i + 1) % n1;
            own[i] = 0;
            cut[i].push_back({0.0, id1[i]});
            cut[i].push_back({1.0, id1[j]});
        }
        for (int i = 0; i < n2; i++) {
            int j = (i + 1) % n2;
            int id = n1 + i;
            own[id] = 1;
            cut[id].push_back({0.0, id2[i]});
            cut[id].push_back({1.0, id2[j]});
        }
        for (int i = 0; i < n1; i++) {
            Point a = p1[i], b = p1[(i + 1) % n1];
            for (int j = 0; j < n2; j++) {
                Point c = p2[j], d = p2[(j + 1) % n2];
                if (onSeg(a, b, c)) cut[i].push_back({paramOnSeg(a, b, c), id2[j]});
                if (onSeg(a, b, d)) cut[i].push_back({paramOnSeg(a, b, d), id2[(j + 1) % n2]});
                if (onSeg(c, d, a)) cut[n1 + j].push_back({paramOnSeg(c, d, a), id1[i]});
                if (onSeg(c, d, b)) cut[n1 + j].push_back({paramOnSeg(c, d, b), id1[(i + 1) % n1]});
                if (properCross(a, b, c, d)) {
                    Point p = lineInter(a, b, c, d);
                    int id = getPointId(p, pts);
                    cut[i].push_back({paramOnSeg(a, b, p), id});
                    cut[n1 + j].push_back({paramOnSeg(c, d, p), id});
                }
            }
        }
        set<pair<int, int> > used;
        vector<pair<int, int> > undirected;
        auto addEdge = [&](int u, int v) {
            if (u == v) return;
            pair<int, int> key = minmax(u, v);
            if (used.insert(key).second) undirected.push_back({u, v});
        };
        for (int i = 0; i < ec; i++) {
            sort(cut[i].begin(), cut[i].end(), [](const pair<double, int> &a, const pair<double, int> &b) {
                if (fabs(a.first - b.first) > eps) return a.first < b.first;
                return a.second < b.second;
            });
            vector<int> seq;
            for (int j = 0; j < (int)cut[i].size(); j++)
                if (seq.empty() || seq.back() != cut[i][j].second) seq.push_back(cut[i][j].second);
            for (int j = 0; j + 1 < (int)seq.size(); j++) {
                Point m = (pts[seq[j]] + pts[seq[j + 1]]) * 0.5;
                if (own[i] == 0) {
                    if (inPoly(m, p2)) addEdge(seq[j], seq[j + 1]);
                } else {
                    if (inPoly(m, p1)) addEdge(seq[j], seq[j + 1]);
                }
            }
        }
        vector<int> from, to, rev, vis;
        vector<vector<int> > out(pts.size());
        for (int i = 0; i < (int)undirected.size(); i++) {
            int u = undirected[i].first, v = undirected[i].second;
            int id = (int)from.size();
            from.push_back(u);
            to.push_back(v);
            rev.push_back(id + 1);
            vis.push_back(0);
            from.push_back(v);
            to.push_back(u);
            rev.push_back(id);
            vis.push_back(0);
            out[u].push_back(id);
            out[v].push_back(id + 1);
        }
        vector<int> pos(from.size(), 0);
        for (int i = 0; i < (int)pts.size(); i++) {
            auto &lst = out[i];
            sort(lst.begin(), lst.end(), [&](int a, int b) {
                Point da = pts[to[a]] - pts[from[a]];
                Point db = pts[to[b]] - pts[from[b]];
                double aa = atan2(da.y, da.x), bb = atan2(db.y, db.x);
                if (fabs(aa - bb) > eps) return aa < bb;
                double la = dot(da, da), lb = dot(db, db);
                return la < lb;
            });
            for (int j = 0; j < (int)lst.size(); j++) pos[lst[j]] = j;
        }
        vector<vector<int> > res;
        for (int i = 0; i < (int)from.size(); i++) {
            if (vis[i]) continue;
            vector<int> seq;
            int cur = i;
            while (!vis[cur]) {
                vis[cur] = 1;
                seq.push_back(from[cur]);
                int v = to[cur];
                int twin = rev[cur];
                int deg = (int)out[v].size();
                int idx = pos[twin];
                cur = out[v][(idx - 1 + deg) % deg];
            }
            seq = reduceCycle(seq, pts);
            if ((int)seq.size() < 3) continue;
            if (polyArea(seq, pts) <= eps) continue;
            seq = rotateToMin(seq, pts);
            res.push_back(seq);
        }
        cout << "Data Set " << ds++ << "\n";
        cout << "Number of intersection regions: " << res.size() << "\n";
        for (int i = 0; i < (int)res.size(); i++) {
            cout << "Region " << i + 1 << ":";
            for (int id : res[i]) cout << "(" << pts[id].x << "," << pts[id].y << ")";
            cout << "\n";
        }
    }
    return 0;
}
```

# 总结

本题的核心是将连续的几何交集边界转换为离散的平面图。首先通过边界求交得到全部切分点，再利用线段中点判断保留交集边界，最后使用半边遍历提取所有有界面。

实现中的关键技巧如下：

- 使用叉积统一处理方向、共线、线段相交和多边形面积计算。
- 使用线段参数对交点排序，保证每条原边能够正确切分。
- 使用中点包含性判断筛选交集边界，避免直接分类复杂的交点进入关系。
- 使用极角排序和半边转移规则提取平面图中的闭合区域。
- 使用有向面积排除外部面，使用共线删除处理题目要求的冗余顶点。
- 使用固定小数格式输出坐标，保证输出格式与题目要求一致。

该方法完整处理了边界交点、端点相交、边界重合、多个交集区域以及共线顶点等情况，时间复杂度为 $O((n_1+n_2)^3)$，空间复杂度为 $O((n_1+n_2)^2)$。
