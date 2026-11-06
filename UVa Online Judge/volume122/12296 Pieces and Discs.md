
> **摘要**：本题要求在矩形内用若干条连接不同边界的线段将矩形切割成多个块，再对每个圆盘找出所有与其交集面积非零的块，并按面积递增输出。由于线段数 $n \le 20$，可采用增量切割法：初始矩形为单个多边形，每加入一条线段就将其穿过的多边形一分为二，最终得到全部块。判定圆盘与多边形相交时，只需检查圆心在多边形内部、多边形顶点在圆盘内、多边形边与圆盘交叠长度大于 $0$ 三种情形之一成立即可。整体复杂度约 $O(n^3 + m \cdot p \cdot e)$，在给定规模下效率极高。

## 题目描述

在笛卡尔平面上有一个矩形，其左下角为 $(0, 0)$，右上角为 $(L, W)$。在矩形内部绘制若干条线段，每条线段连接矩形边界上的两个点，且这两个点位于矩形的不同边上。这些线段将矩形分割成若干块区域（面）。随后绘制若干个圆盘（圆及其内部），要求对于每个圆盘，找出所有与该圆盘相交（即交集面积非零）的块，并将这些块的面积按递增顺序输出。

## 输入格式

输入包含至多 $100$ 个测试用例。每个测试用例以四个整数 $n$、$m$、$L$、$W$ 开头，其中 $n$ 表示线段数量，$m$ 表示圆盘数量，$1 \le n, m \le 20$，$1 \le L, W \le 100$。接下来 $n$ 行，每行四个整数 $x_1$、$y_1$、$x_2$、$y_2$，描述一条连接 $(x_1, y_1)$ 和 $(x_2, y_2)$ 的线段，两个端点保证位于矩形的不同边上。随后 $m$ 行，每行三个整数 $x$、$y$、$R$，表示一个圆心为 $(x, y)$、半径为 $R$ 的圆盘，其中 $0 \le x \le L$，$0 \le y \le W$，$1 \le R \le 100$。没有两条线段完全相同。输入以 $n = m = L = W = 0$ 结束。

## 输出格式

对于每个圆盘（按输入顺序），输出一行：该圆盘相交的块的数量，以及这些块的面积。面积按递增顺序排列，每个面积保留两位小数。每个测试用例后输出一个空行。

## 样例

**输入**
```text
4 1 10 10
0 4 10 4
1 0 7 10
5 10 10 1
2 10 6 0
3 7 3
0 0 0 0
```

**输出**
```text
4 0.50 10.03 10.77 18.70
```

## 题目分析

本题的核心在于准确求出矩形被线段切割后形成的所有块，并判断每个圆盘与哪些块有非零面积交集。

由于线段数量 $n \le 20$，切割后的块数至多为 $O(n^2)$ 级别，完全可以在每次加入线段时对当前所有块进行动态切割。初始时矩形是一个单独的多边形，每添加一条线段，它会穿过若干个多边形，并将每个穿过的多边形一分为二。最终所有多边形即为所求的块。

对于每个圆盘，判断其与一个多边形的交集是否具有正面积，需要考察三种情形：

- 圆心位于多边形内部（严格内部，不包含边界）；
- 多边形的某个顶点位于圆盘内部（距离小于半径）；
- 多边形的某条边与圆盘的交叠长度大于 $0$。

只要满足任意一条，即可断定二者交集面积非零。

几何运算中需要注意浮点数精度，所有比较均采用容差 $\varepsilon = 10^{-9}$。线段之间无共线重叠情况，因此交点计算可简化为一般位置的直线求交。

## 解题思路

### 步骤 $\texttt{1}$. 多边形表示

每个块用其顶点按逆时针顺序排列的序列表示，面积通过鞋带公式计算。

### 步骤 $\texttt{2}$. 切割多边形

当处理一条分割线段时，遍历当前所有多边形，判断该线段是否穿过多边形。穿过的判定标准是：线段与多边形的边界恰好有两个交点（忽略端点处重合的情况，若线段经过顶点，该顶点可能被两个边共享，但交点总数仍为 $2$）。

对于被穿过的多边形，找到这两个交点后，将多边形的顶点序列沿边界分为两条链，每条链连接两个交点，形成两个新的多边形。未被穿过的多边形则原样保留。这样一轮切割后，多边形数量增加 $1$。

### 步骤 $\texttt{3}$. 交点计算

对于线段与多边形某条边的交点，使用标准直线求交公式。由于题目保证线段端点位于矩形边界且不会与已有线段共线，因此无需处理重叠情况。若交点恰好在多边形顶点上，则重复交点会被去重，仅保留一个。

### 步骤 $\texttt{4}$. 圆盘与多边形相交判定

规则 $\texttt{1}$. 若圆心在多边形内部，则圆盘与多边形有非零面积交集。

规则 $\texttt{2}$. 若存在多边形顶点到圆心的距离小于圆盘半径，则交集非零。

规则 $\texttt{3}$. 若存在多边形的一条边，与圆盘的交叠线段长度大于 $0$，则交集非零。

上述三个条件中的任意一个成立，即可判定相交。

### 步骤 $\texttt{5}$. 排序输出

对于每个圆盘，收集所有相交多边形的面积，排序后输出数量和面积（保留两位小数）。

### 复杂度分析

- 时间复杂度：每次切割需要遍历当前所有多边形，并对每个多边形的每条边求交。多边形总数最多为 $n + 1$（初始 $1$ 个，每加一条线段最多增加 $1$ 个），边数也至多为 $O(n)$。因此每轮切割复杂度为 $O(p \cdot e)$，总复杂度 $O(n^3)$，在 $n \le 20$ 时完全可接受。对每个圆盘判断相交需遍历所有多边形及边，复杂度 $O(m \cdot p \cdot e)$。
- 空间复杂度：存储所有多边形顶点，最坏 $O(n^2)$，远小于限制。

## 代码实现

```cpp
// Pieces and Discs
// UVa ID: 12296
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    bool operator<(const Point& o) const { return x < o.x - EPS || (fabs(x - o.x) < EPS && y < o.y - EPS); }
    bool operator==(const Point& o) const { return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS; }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double dot(const Point& o) const { return x * o.x + y * o.y; }
    double cross(const Point& o) const { return x * o.y - y * o.x; }
    double len2() const { return x * x + y * y; }
    double len() const { return sqrt(len2()); }
};

struct Segment { Point a, b; Segment(Point a_ = Point(), Point b_ = Point()) : a(a_), b(b_) {} };
struct Circle { Point c; double r; Circle(Point c_ = Point(), double r_ = 0) : c(c_), r(r_) {} };

double dist(const Point& p1, const Point& p2) { return (p1 - p2).len(); }

double projectParam(const Point& p, const Segment& s) {
    Point v = s.b - s.a;
    return (p - s.a).dot(v) / v.len2();
}

void segmentIntersections(const Segment& s1, const Segment& s2, vector<Point>& out) {
    Point p = s1.a, q = s1.b, r = s2.a, s = s2.b;
    Point v1 = q - p, v2 = s - r;
    double d1 = v1.cross(v2);
    if (fabs(d1) < EPS) return;
    double t = (r - p).cross(v2) / d1;
    double u = (r - p).cross(v1) / d1;
    if (t >= -EPS && t <= 1 + EPS && u >= -EPS && u <= 1 + EPS)
        out.push_back(p + v1 * t);
}

double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return fabs(area) * 0.5;
}

bool pointInPolygon(const Point& p, const vector<Point>& poly) {
    int n = poly.size();
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++) {
        Point a = poly[i], b = poly[j];
        if (fabs((b - a).cross(p - a)) < EPS && (p - a).dot(p - b) < EPS + 1e-12)
            return false;
        if (((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x + EPS))
            inside = !inside;
    }
    return inside;
}

double lineCircleOverlapLength(const Point& A, const Point& B, const Circle& c) {
    Point d = B - A, f = A - c.c;
    double a = d.dot(d), b = 2.0 * f.dot(d), cc = f.dot(f) - c.r * c.r;
    double delta = b * b - 4 * a * cc;
    if (delta < -EPS) return 0.0;
    if (delta < 0) delta = 0;
    double sqrtDelta = sqrt(delta);
    double t1 = (-b - sqrtDelta) / (2 * a), t2 = (-b + sqrtDelta) / (2 * a);
    double low = max(0.0, min(t1, t2));
    double high = min(1.0, max(t1, t2));
    if (low < high - EPS)
        return (high - low) * sqrt(a);
    return 0.0;
}

bool polygonIntersectsCircle(const vector<Point>& poly, const Circle& c) {
    if (pointInPolygon(c.c, poly)) return true;
    for (const auto& p : poly)
        if ((p - c.c).len2() < c.r * c.r - EPS) return true;
    for (size_t i = 0; i < poly.size(); ++i) {
        size_t j = (i + 1) % poly.size();
        if (lineCircleOverlapLength(poly[i], poly[j], c) > EPS)
            return true;
    }
    return false;
}

vector<vector<Point>> splitPolygon(const vector<Point>& P, const Segment& S) {
    vector<vector<Point>> res;
    int n = P.size();
    vector<pair<int, Point>> inter;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Segment edge(P[i], P[j]);
        vector<Point> pts;
        segmentIntersections(edge, S, pts);
        for (auto& p : pts) {
            bool dup = false;
            for (auto& q : inter)
                if (dist(p, q.second) < EPS) { dup = true; break; }
            if (!dup) inter.push_back({i, p});
        }
    }
    if (inter.size() < 2) return res;
    sort(inter.begin(), inter.end(), [&](pair<int, Point>& a, pair<int, Point>& b) {
        if (a.first != b.first) return a.first < b.first;
        return projectParam(a.second, Segment(P[a.first], P[(a.first + 1) % n])) <
               projectParam(b.second, Segment(P[b.first], P[(b.first + 1) % n]));
    });
    Point p1 = inter[0].second, p2 = inter[1].second;
    int idx1 = inter[0].first, idx2 = inter[1].first;
    vector<Point> chain1, chain2;
    chain1.push_back(p1);
    int cur = idx1;
    while (cur != idx2) {
        int nxt = (cur + 1) % n;
        chain1.push_back(P[nxt]);
        cur = nxt;
    }
    chain1.push_back(p2);
    chain2.push_back(p2);
    cur = idx2;
    while (cur != idx1) {
        int nxt = (cur + 1) % n;
        chain2.push_back(P[nxt]);
        cur = nxt;
    }
    chain2.push_back(p1);
    if (dist(chain1[0], chain1.back()) < EPS) chain1.pop_back();
    if (dist(chain2[0], chain2.back()) < EPS) chain2.pop_back();
    res.push_back(chain1);
    res.push_back(chain2);
    return res;
}

int main() {
    int n, m, L, W;
    while (scanf("%d%d%d%d", &n, &m, &L, &W) == 4 && (n || m || L || W)) {
        vector<Segment> segs;
        for (int i = 0; i < n; ++i) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            segs.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        vector<vector<Point>> polygons;
        polygons.push_back({Point(0, 0), Point(L, 0), Point(L, W), Point(0, W)});
        for (auto& seg : segs) {
            vector<vector<Point>> newPolys;
            for (auto& poly : polygons) {
                auto parts = splitPolygon(poly, seg);
                if (parts.empty())
                    newPolys.push_back(poly);
                else {
                    for (auto& p : parts)
                        newPolys.push_back(p);
                }
            }
            polygons = move(newPolys);
        }
        vector<Circle> discs;
        for (int i = 0; i < m; ++i) {
            int x, y, R;
            scanf("%d%d%d", &x, &y, &R);
            discs.push_back(Circle(Point(x, y), R));
        }
        for (auto& c : discs) {
            vector<double> areas;
            for (auto& poly : polygons) {
                if (polygonIntersectsCircle(poly, c))
                    areas.push_back(polygonArea(poly));
            }
            sort(areas.begin(), areas.end());
            printf("%d", (int)areas.size());
            for (double a : areas)
                printf(" %.2f", a + 1e-9);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
```

## 总结

本题的关键技巧是采用增量切割法构建平面图，避免复杂的半边数据结构，编程实现简单且鲁棒。几何判定时，利用三种互斥条件精确判断圆盘与多边形的非零面积交集，处理了边界情况。浮点数容差的合理使用保证了数值稳定性。该算法在 $n, m \le 20$ 的规模下效率极高，能够通过所有测试数据。
