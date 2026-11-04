
> **摘要**：本题要求在平面上从原点出发选择最少的射线（地铁线路），使得每个重要地点到某条射线的垂直距离不超过 $d$。核心思路是把每个有效点（到原点距离 $r > d$）映射为圆周上的一个角度区间 $[\varphi-\alpha,\ \varphi+\alpha]$，其中 $\alpha=\arcsin(d/r)$，从而将原问题转化为**圆上区间最小点覆盖**问题。由于圆上区间不能直接贪心，解法枚举某个区间端点作为起点将圆周剪开成直线，再用标准贪心求最小点覆盖，取所有起点中的最小值。总时间复杂度 $O(n^2\log n)$，适合 $n \le 200$ 的数据范围。

## 题目描述

政府计划在首都修建地铁系统，要求每条地铁线路从中央车站（坐标原点）出发，沿某个角度直线延伸。给定 $n$ 个重要地点的坐标以及最大允许距离 $d$，每个重要地点必须与某个地铁站（可以位于任意一条线路上）的欧几里得距离不超过 $d$。求满足条件所需的最少地铁线路数量。

## 输入格式

第一行包含整数 $N$，表示数据组数（$N \le 20$）。  
每组数据第一行包含两个整数 $n$ 和 $d$（$1 \le n \le 200$，$0 \le d < 150$），分别表示重要地点数量和最大允许距离。  
接下来 $n$ 行，每行两个整数 $x$ 和 $y$（$-100 \le x, y \le 100$），表示重要地点的坐标。中央车站坐标为 $(0, 0)$，所有坐标互不相同且没有坐标等于 $(0, 0)$。

## 输出格式

对于每组数据，输出一行一个整数，表示所需的最少地铁线路数。

## 样例

输入

```
2
7 1
-1 -4
-3 1
3 -1
2 3
2 4
2 -2
6 -2
4 0
0 4
-12 18
0 27
-34 51
```

输出

```
2
1
```

> 说明：第一组数据对应题目描述中的图示。

## 题目分析

每条地铁线是一条从原点出发的射线，方向由角度 $\theta$ 确定。对于一个重要地点 $P$，若其到原点的距离 $r \le d$，则中央车站本身即可覆盖该点，无需额外考虑。  
若 $r > d$，设 $P$ 的极角为 $\varphi$（$0 \le \varphi < 2\pi$）。若选择角度为 $\theta$ 的射线，则点 $P$ 到该射线的垂直距离为 $r \cdot |\sin(\theta - \varphi)|$（取圆上最小夹角）。要求垂直距离不超过 $d$，即  
$$
|\theta - \varphi| \le \arcsin\left(\frac{d}{r}\right)
$$
记 $\alpha = \arcsin(d/r)$，则 $P$ 可被方向角 $\theta$ 覆盖当且仅当 $\theta \in [\varphi - \alpha,\ \varphi + \alpha]$（在圆周上）。

因此，每个有效点（$r > d$）对应圆周上的一个区间，问题转化为：在圆周上选择最少的点（射线方向），使得每个区间至少包含一个被选中的点。

这是一个经典的**圆上区间最小点覆盖**问题。与直线上的区间覆盖不同，圆上区间是环形的，不能直接贪心。常用方法是枚举一个起点（通常取某个区间的端点），将圆周剪开成直线，然后使用标准贪心算法。

## 解题思路

### 1. 区间生成

对于每个点坐标 $(x, y)$，计算：
- 半径 $r = \sqrt{x^2 + y^2}$
- 极角 $\varphi = \operatorname{atan2}(y, x)$，归一化到 $[0, 2\pi)$
- 若 $r \le d$，忽略该点
- 否则，计算 $\alpha = \arcsin(d/r)$，得到区间 $[\varphi - \alpha,\ \varphi + \alpha]$（允许越界，后续会处理）

所有区间均在圆周上（模 $2\pi$）。

### 2. 枚举起点

对于圆上的区间覆盖问题，若已知一个选点 $s$，我们可以将圆周在 $s$ 处剪开，将所有区间映射到线段 $[s,\ s+2\pi)$ 上。如果某个区间本身跨越了剪切点，则会被拆成两部分（但实际计算中，我们平移每个区间，使其左端点位于 $s$ 之后）。然后，在直线上求最小点覆盖，贪心即可。

由于最优解中必定存在一个选点位于某个区间的端点（左端点或右端点），我们枚举所有有效区间的左右端点（归一化到 $[0, 2\pi)$）作为起点 $s$，分别计算所需总点数，取最小值。

### 3. 直线贪心

给定起点 $s$ 后：
- 首先判断哪些区间已经被 $s$ 自身覆盖，这些区间不再需要额外选点。
- 对于剩余区间，通过加上 $2\pi$ 的整数倍，将其左端点调整到 $(s, s+2\pi]$ 范围内，得到新的区间 $[l', r']$（注意 $r'$ 也相应平移）。
- 将所有区间按右端点 $r'$ 升序排序。
- 贪心过程：维护当前已选点的最右位置 $\textit{last}$，初始为 $s$。遍历区间，若当前区间左端点 $l' > \textit{last}$（表示未被覆盖），则在该区间的右端点 $r'$ 处放置一个新点，更新 $\textit{last} = r'$，计数器加一。
- 该起点的总点数为 $1$（起点本身）加上额外点数。

### 4. 边界处理

- 区间长度可能大于 $\pi$？由于 $\alpha = \arcsin(d/r)$ 且 $r > d$，$\alpha \in (0, \pi/2)$，区间长度 $2\alpha < \pi$，所以区间长度小于半圆，不会出现一个区间覆盖整个圆周的情况，这简化了处理。
- 若所有点 $r \le d$，则答案为 $0$（只需中央车站）。
- 枚举起点时，要处理浮点误差，使用 $\textit{EPS}$ 进行容差比较。

### 5. 复杂度分析

- 每组数据有效区间数量 $m \le n \le 200$。
- 枚举 $O(m)$ 个起点，每个起点需对剩余区间排序，复杂度 $O(m \log m)$。
- 总时间复杂度 $O(n^2 \log n)$ 每组数据，可接受。
- 空间复杂度 $O(n)$。

## 代码实现

```cpp
// Subway
// UVa ID: 10691
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

struct Interval {
    double l, r, theta, alpha;
};

double normAng(double a) {
    a = fmod(a, 2 * PI);
    if (a < 0) a += 2 * PI;
    return a;
}

bool coveredByS(double s, const Interval& in) {
    double delta = s - in.theta;
    delta = atan2(sin(delta), cos(delta));          // 归一化到 [-PI, PI]
    return fabs(delta) <= in.alpha + EPS;
}

int solveForS(double s, const vector<Interval>& intervals) {
    vector<pair<double, double>> segs;
    for (const auto& in : intervals) {
        if (coveredByS(s, in)) continue;
        // 将区间映射到 (s, s+2π) 内
        double l = in.l, r = in.r;
        long long k = (long long)ceil((s - l) / (2 * PI) - 1e-9);
        while (l + 2 * PI * k <= s + EPS) ++k;
        double l2 = l + 2 * PI * k;
        double r2 = r + 2 * PI * k;
        if (r2 <= s + EPS) {                        // 安全保护
            while (r2 <= s + EPS) { ++k; l2 += 2 * PI; r2 += 2 * PI; }
        }
        segs.push_back({l2, r2});
    }
    if (segs.empty()) return 1;                     // 仅靠 s 覆盖所有区间

    sort(segs.begin(), segs.end(),
         [](const pair<double,double>& a, const pair<double,double>& b) {
             return a.second < b.second;
         });

    int cnt = 0;
    double last = s;                                // 起点 s 作为一个已选点
    for (auto& p : segs) {
        if (p.first > last + EPS) {
            ++cnt;
            last = p.second;
        }
    }
    return 1 + cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    while (N--) {
        int n;
        double d;
        cin >> n >> d;

        vector<Interval> intervals;
        for (int i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            double r = hypot(x, y);
            if (r <= d + EPS) continue;             // 原点已覆盖
            double theta = atan2(y, x);
            if (theta < 0) theta += 2 * PI;
            double alpha = asin(d / r);
            double l = theta - alpha;
            double rr = theta + alpha;
            intervals.push_back({l, rr, theta, alpha});
        }

        if (intervals.empty()) {
            cout << 0 << '\n';
            continue;
        }

        vector<double> candidates;
        for (const auto& in : intervals) {
            candidates.push_back(normAng(in.l));
            candidates.push_back(normAng(in.r));
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end(),
            [](double a, double b) { return fabs(a - b) < EPS; }),
            candidates.end());

        int ans = (int)intervals.size();            // 上限
        for (double s : candidates) {
            int cur = solveForS(s, intervals);
            if (cur < ans) ans = cur;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

## 总结

本题将几何覆盖问题转化为圆上的区间覆盖问题，核心技巧是：
- 将每个有效点转换为圆周上的角度区间。
- 利用“最优解中必有一个选点在某个区间端点”的性质，通过枚举起点将环形问题化为线性问题。
- 使用贪心算法求解直线上的区间最小点覆盖。

该解法时间复杂度 $O(n^2 \log n)$，适合 $n \le 200$ 的数据范围，思路清晰且易于实现。关键点在于处理圆周的周期性以及浮点精度控制。
