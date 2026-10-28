## 题目描述

给定一个三角形 $\triangle ABC$，其中顶点 $A(0, 0)$、$B(1000, 0)$、$C(0, 1000)$。三角形内部有 $n$ 个点 $P_1, P_2, \dots, P_n$。需要找到一个点 $Q$，使得三个小三角形 $\triangle QBC$、$\triangle QCA$、$\triangle QAB$ 内包含的给定点数目相同。边界上的点同时计入相邻的两个三角形；若 $Q$ 恰好与某个给定点重合，则该点同时计入三个三角形。

可以证明，当 $n = 3k$（$k \ge 1$）时解一定存在；对于任意 $n$，题目保证至少有一个有效解。

## 输入格式

输入包含多个测试用例。每个测试用例的第一行是一个整数 $n$（$1 \le n \le 300$），接下来 $n$ 行每行两个整数 $x_i, y_i$（$0 \le x_i, y_i \le 1000$），表示第 $i$ 个点的坐标。

所有给定点严格位于三角形内部，且不存在两点与任一顶点共线（即从任一顶点观察，任意两个点的方向角互不相同）。

输入以一行 `0` 结束。

## 输出格式

对于每个测试用例，输出一行两个浮点数 $q_x$ 和 $q_y$，表示满足条件的点 $Q$ 的坐标。小数部分至少保留七位，输出误差允许在 $0.5 \times 10^{-4}$ 以内。

## 样例

输入

```
3
100 500
200 500
300 500
5
100 300
100 600
200 100
200 700
500 100
0
```

输出

```
166.6666666 555.5555555
275.0000000 145.0000000
```

## 题目分析

本题的核心是：在三角形内部找到一个点 $Q$，使三个子三角形内的点数相等。

直接枚举所有可能的 $Q$ 是不现实的。然而，题目中的几何约束和离散点集的结构为算法设计提供了关键线索。

设三个子三角形的点数分别为 $c_1, c_2, c_3$。对于过顶点 $A$ 的直线 $AQ$，它将三角形分成两部分：$\triangle QCA$ 和 $\triangle QAB$，其点数分别为 $c_2$ 和 $c_3$。若最终 $c_1 = c_2 = c_3$，则必有 $c_2 = c_3$，即直线 $AQ$ 两侧的点数相等。同理，$BQ$ 和 $CQ$ 也必须满足相应的相等关系。

但是，**“两条平分线的交点必定满足三边相等”这一命题并不成立**，因为第三条平分线可能不经过该交点。因此，不能通过简单求解两条平分线的交点来得到答案，必须**直接验证**三个子三角形内的点数是否相等。

因此，可行的策略是：枚举所有可能的过顶点的直线方向（这些方向由给定点决定），取两条直线的交点，然后验证条件。问题关键在于如何减少候选方向的数量，使得枚举在可行时间内完成。

## 解题思路

### 候选方向的区间限制

对于顶点 $A$，假设存在满足条件的点 $Q$，则 $AQ$ 与边 $BC$ 相交于点 $M$。直线 $AM$ 将三角形 $\triangle ABC$ 分割为 $\triangle ABM$ 和 $\triangle ACM$。由于最终子三角形 $\triangle QAB$ 包含在 $\triangle ABM$ 内，$\triangle QAC$ 包含在 $\triangle ACM$ 内，且 $\triangle QAB$ 和 $\triangle QAC$ 的点数必须相等且至少为 $m = \lceil n/3 \rceil$（实际等于 $(n+2)/3$ 整除），因此 $\triangle ABM$ 和 $\triangle ACM$ 内的点数都必须至少为 $m$，否则无论 $Q$ 在 $AM$ 上如何移动，都不可能使两个子三角形同时达到 $m$ 个点。

将所有给定点按相对 $A$ 的极角排序后，直线 $AM$ 的方向角对应排序序列中的某个位置。设排序后的点索引从 $0$ 到 $n-1$，若方向角位于索引 $i$ 和 $i+1$ 之间（或正好经过某个点），则左侧（$\triangle ACM$ 侧）的点数为 $i+1$（或包含线上点），右侧（$\triangle ABM$ 侧）的点数为 $n-i-1$（或相应调整）。为了保证两侧点数均不少于 $m$，必须满足 $i+1 \ge m$ 且 $n-i-1 \ge m$，即 $m-1 \le i \le n-m$。因此，我们只需考虑极角排序后下标在 $[m-1, n-m]$ 之间的点及其组合方向。

这个区间长度约为 $n - 2m + 2$，当 $n$ 较大时仍然可观，但已经远小于 $n$。

### 候选方向的生成

对于某个顶点 $V$，我们生成所有可能的过 $V$ 的直线方向候选点 $D$，使得直线 $VD$ 可能是最终解的一部分。候选点分为两类：

1. **给定点本身**：当平分线必须经过某个给定点时，只需取中间区间内的点本身。
2. **点对的中点**：当平分线不经过任何给定点（即位于两个相邻点方向之间）时，区间内任意方向的效果相同。为了覆盖，我们取区间内所有点对的中点作为代表方向。

### 分余数处理

根据 $n \bmod 3$ 的不同，需要采用不同的候选生成策略：

- **$n \bmod 3 = 0$**：三个子三角形点数正好相等，平分线可能经过点也可能不经过。由于候选区间较大，确定性枚举可能组合过多，代码采用**随机采样**：在中间区间内随机选择两个顶点及其方向点，求交点并验证。由于题目保证有解且随机命中概率较高，多次尝试后必然找到。

- **$n \bmod 3 = 1$**：此时 $n = 3k + 1$。为了使三个子三角形点数相等（均为 $k+1$，因为边界重复计数会额外增加），需要有两个点被重复计数，即有两个点必须位于分割线上。由于题目限制“过顶点的直线不会经过两个给定点”，这两个点只能分别位于两条不同的分割线上，即两条分割线各经过一个给定点，且这两条分割线相交于 $Q$。因此，过顶点的分割线必须经过某个给定点，候选只取点本身，枚举三个顶点两两组合的交点并验证。

- **$n \bmod 3 = 2$**：此时 $n = 3k + 2$。需要有一个点被重复计数（即一个点位于分割线上），同时还需要另一条分割线不经过点（即位于两个点之间）。因此，一个顶点的候选取“仅点”，另一个顶点的候选取“点+中点”，组合使用六种情况（$A$ 仅点 + $B$ 点中点、$A$ 仅点 + $C$ 点中点、$B$ 仅点 + $A$ 点中点、$B$ 仅点 + $C$ 点中点、$C$ 仅点 + $A$ 点中点、$C$ 仅点 + $B$ 点中点）。

### 验证与输出

对于每一对候选方向（分别来自两个顶点），求两条直线的交点 $Q$，然后直接计算三个子三角形内的点数（含边界重复计数），若三者相等则输出 $Q$。该验证是最终判决，不依赖任何中间假设。

### 时间复杂度

- 候选方向数量受中间区间长度限制，最坏情况下约为 $n/3$。
- 枚举两个顶点的候选方向组合，最坏复杂度 $O((n/3)^2)$，每次验证 $O(n)$，总复杂度 $O(n^3/9)$，对于 $n \le 300$ 完全可行。
- 随机采样部分通常只需少量尝试即可成功，不影响整体时限。

## 代码实现

```cpp
// Triangle Partition
// UVa ID: 691
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 3.680s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct point { double x, y; };

point operator-(const point& a, const point& b) { return {a.x - b.x, a.y - b.y}; }
point operator+(const point& a, const point& b) { return {a.x + b.x, a.y + b.y}; }
point operator*(const point& a, double k) { return {a.x * k, a.y * k}; }
point operator/(const point& a, double k) { return {a.x / k, a.y / k}; }

double cross(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }

inline bool pointInTriangle(point& P, point& T1, point& T2, point& T3) {
    double d1 = cross(T2 - T1, P - T1), d2 = cross(T3 - T2, P - T2), d3 = cross(T1 - T3, P - T3);
    bool hasPos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
    bool hasNeg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    return !(hasPos && hasNeg);
}

typedef vector<point> polygon;

int n;
polygon pts;

bool countTriangles(point& Q) {
    static point A{0.0, 0.0}, B{1000.0, 0.0}, C{0.0, 1000.0};
    int c1 = 0, c2 = 0, c3 = 0;
    for (auto& p : pts) {
        if (pointInTriangle(p, Q, B, C)) c1++;
        if (pointInTriangle(p, Q, C, A)) c2++;
        if (pointInTriangle(p, Q, A, B)) c3++;
    }
    return c1 == c2 && c2 == c3;
}

void intersectLines(point& p1, point& p2, point& p3, point& p4, point& q) {
    point d1 = p2 - p1, d2 = p4 - p3, r = p3 - p1;
    double t = cross(r, d2) / cross(d1, d2);
    q = p1 + d1 * t;
}

void solve0() {
    point P[3] = {{0.0, 0.0}, {1000.0, 0.0}, {0.0, 1000.0}};
    polygon Ps[3];
    for (int i = 0; i < 3; i++) {
        Ps[i].insert(Ps[i].begin(), pts.begin(), pts.end());
        sort(Ps[i].begin(), Ps[i].end(), [&](const point& a, const point& b) {
            return atan2(a.y - P[i].y, a.x - P[i].x) < atan2(b.y - P[i].y, b.x - P[i].x);
        });
    }
    srand(time(0));
    int needed = (n + 2) / 3;
    int start = needed - 1, end = n - needed;
    while (true) {
        int a = rand() % 3, b = (a + 1) % 3;
        bool found = false;
        for (int i = start; i < end; i++) {
            double fa = (rand() % 10000) / 10000.0;
            point m1 = Ps[a][i] + (Ps[a][i + 1] - Ps[a][i]) * fa;
            for (int j = start; j < end; j++) {
                double fb = (rand() % 10000) / 10000.0;
                point m2 = Ps[b][j] + (Ps[b][j + 1] - Ps[b][j]) * fb;
                point Q;
                intersectLines(P[a], m1, P[b], m2, Q);
                if (countTriangles(Q)) {
                    cout << Q.x << " " << Q.y << "\n";
                    return;
                }
            }
        }
    }
}

polygon getCandidates(point& V, bool includeAll) {
    polygon sorted(pts);
    sort(sorted.begin(), sorted.end(), [&](const point& a, const point& b) {
        return atan2(a.y - V.y, a.x - V.x) < atan2(b.y - V.y, b.x - V.x);
    });
    int needed = (n + 2) / 3;
    int start = needed - 1, end = n - needed;
    polygon r;
    for (int i = start; i <= end; i++) {
        r.push_back(sorted[i]);
        if (includeAll)
            for (int j = i + 1; j <= end; j++)
                r.push_back((sorted[i] + sorted[j]) / 2);
    }
    return r;
}

bool work(polygon& As, polygon& Bs, point& A, point& B) {
    for (auto& dA : As) {
        for (auto& dB : Bs) {
            point Q;
            intersectLines(A, dA, B, dB, Q);
            if (countTriangles(Q)) {
                cout << Q.x << " " << Q.y << "\n";
                return true;
            }
        }
    }
    return false;
}

void solve1() {
    point A{0.0, 0.0}, B{1000.0, 0.0}, C{0.0, 1000.0};
    polygon As = getCandidates(A, false), Bs = getCandidates(B, false), Cs = getCandidates(C, false);
    if (work(As, Bs, A, B) || work(As, Cs, A, C) || work(Bs, Cs, B, C)) return;
}

void solve2() {
    point P[3] = {{0.0, 0.0}, {1000.0, 0.0}, {0.0, 1000.0}};
    polygon P1[3], P2[3];
    for (int i = 0; i < 3; i++) {
        P1[i] = getCandidates(P[i], false);
        P2[i] = getCandidates(P[i], true);
    }
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 3; j++)
            if (work(P1[i], P2[j], P[i], P[j]) || work(P1[j], P2[i], P[j], P[i]))
                return;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(7);
    int x, y;
    while (cin >> n, n) {
        pts.clear();
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            pts.push_back({x, y});
        }
        if (n % 3 == 0) solve0();
        if (n % 3 == 1) solve1();
        if (n % 3 == 2) solve2();
    }
    return 0;
}
```

## 总结

- 本题的关键在于**将几何计数问题转化为方向角排序和区间限制问题**，从而大幅缩小搜索空间。
- 利用 $n \bmod 3$ 的不同情况，分别采用“仅点”、“点+中点”或随机采样策略，既保证了正确性，又控制了复杂度。
- 最终验证直接计算三个子三角形内的点数，避免了任何中间假设带来的风险。
- 该算法充分利用了题目中“不存在三点与顶点共线”的约束，确保了候选方向的离散性和有限性。
