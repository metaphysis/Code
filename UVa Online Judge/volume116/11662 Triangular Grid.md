
> **摘要**：本文讨论如何统计一条线段与无限三角网格中单三角形内部相交的数量。核心思路是把三角网格视为由 $3$ 组平行直线划分的平面区域，先求出线段与所有网格边界的交点，将线段切分为若干不跨越边界的小段，再对每段取中点，用 $3$ 个归一化坐标的整数部分编码唯一确定所在三角形并去重统计。该方法时间复杂度为 $O(K \log K)$，可稳定处理水平、竖直、斜线段及沿边界延伸等特殊情况。

# 题目描述

给定一个由全等等腰三角形组成的无限三角网格，所有单三角形的底边长度为 $B$，高为 $H$。给定平面上的两个点 $P(x_1,y_1)$ 和 $Q(x_2,y_2)$，需要统计线段 $PQ$ 与多少个单三角形的内部相交。

当且仅当线段与某个三角形的内部存在公共点时，认为线段与该三角形相交。仅经过三角形边界不计入答案。题目保证端点 $P$ 与 $Q$ 均不位于任何三角形边界上，且 $P \ne Q$。

# 输入格式

输入包含多组测试数据，每组数据占一行，包含 $6$ 个整数：

$$
B\ H\ x_1\ y_1\ x_2\ y_2
$$

其中，$B$ 表示单三角形底边长度，$H$ 表示单三角形高度，$(x_1,y_1)$ 与 $(x_2,y_2)$ 分别表示线段两个端点的坐标。

当输入为 $6$ 个 $0$ 时，表示输入结束。

# 输出格式

对于每组测试数据，输出一行整数，表示线段与网格中单三角形内部相交的数量。

# 样例输入

```text
100 120 -20 -100 160 160
10 8 5 5 5 4
10 8 5 5 10 5
10 8 5 5 10 10
0 0 0 0 0 0
```

# 样例输出

```text
6
1
2
3
```

# 题目分析

三角网格的所有边界由 $3$ 组平行直线构成。第一组为水平边界，其方程为：

$$
y = kH
$$

第二组为左斜边所在直线，其方程为：

$$
x - \frac{B}{2H}y = kB
$$

第三组为右斜边所在直线，其方程为：

$$
x + \frac{B}{2H}y = kB
$$

其中 $k$ 为整数。

因此，所有单三角形的边界都可以通过上述 $3$ 组直线完整表示。线段从 $P$ 移动到 $Q$ 的过程中，只有与某条网格边界相交时，所在的三角形才会发生改变。

将线段按所有边界交点切分后，每一段内部均不再穿过任何网格边界。对于每个小线段，只需要取其内部任意一点进行判断，即可确定该小线段是否位于某个三角形内部。由于单三角形为凸多边形，线段不可能离开同一个三角形后再次进入该三角形，因此统计所有经过区域即可得到最终答案。

# 解题思路

设线段参数方程为：

$$
(x(t),y(t)) = (x_1,y_1) + t(x_2 - x_1,y_2 - y_1)
$$

其中：

$$
0 \le t \le 1
$$

步骤 $\texttt{1}$. 分别计算线段与 $3$ 组网格边界的交点参数 $t$。对于水平线，需要求解：

$$
y(t) = kH
$$

对于两组斜线，分别求解：

$$
x(t) - \frac{B}{2H}y(t) = kB
$$

以及：

$$
x(t) + \frac{B}{2H}y(t) = kB
$$

将所有满足 $0 < t < 1$ 的交点参数加入数组，同时加入端点参数 $0$ 与 $1$。

步骤 $\texttt{2}$. 对所有参数排序并去重。相邻参数 $t_i$ 与 $t_{i+1}$ 对应一段不经过网格边界的小线段。

步骤 $\texttt{3}$. 取每个参数区间的中点：

$$
t = \frac{t_i + t_{i+1}}{2}
$$

将其代入线段参数方程，得到中点坐标 $(x,y)$。

步骤 $\texttt{4}$. 对中点计算以下 $3$ 个归一化坐标：

$$
a = \frac{y}{H}
$$

$$
b = \frac{x - \frac{B}{2H}y}{B}
$$

$$
c = \frac{x + \frac{B}{2H}y}{B}
$$

若 $a$、$b$、$c$ 中存在整数，说明该中点位于某条网格边界上。此时对应的小线段完全沿边界延伸，不与任何三角形内部相交，因此直接跳过。

步骤 $\texttt{5}$. 当中点不在边界上时，三元组：

$$
(\lfloor a \rfloor,\lfloor b \rfloor,\lfloor c \rfloor)
$$

唯一标识中点所在的单三角形。将该三元组存入 $\texttt{set}$ 中，自动完成去重。

最终，集合中三元组的数量即为答案。

设线段与网格边界的交点总数为 $K$。参数排序的时间复杂度为 $O(K \log K)$，遍历所有相邻区间的时间复杂度为 $O(K)$，因此总时间复杂度为：

$$
O(K \log K)
$$

空间复杂度为：

$$
O(K)
$$

# 代码实现

代码使用 $\texttt{long double}$ 保存交点参数和坐标计算结果，通过较小误差判断浮点数是否接近整数。$\texttt{addCross}$ 函数负责枚举线段与某一组平行网格线的交点参数，$\texttt{countTriangle}$ 函数负责统计整条线段经过的不同单三角形数量。

```cpp
// Triangular Grid
// UVa ID: 11662
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isBoundary(long double value) {
    return fabsl(value - roundl(value)) < 1e-12L;
}

void addCross(vector<long double>& points, long double first, long double second, long double unit) {
    long double delta;
    long double t;
    long long left, right, index;
    delta = second - first;
    if (fabsl(delta) < 1e-18L)
        return;
    left = (long long)floorl(min(first, second) / unit) - 2;
    right = (long long)ceill(max(first, second) / unit) + 2;
    for (index = left; index <= right; index++) {
        t = (index * unit - first) / delta;
        if (t > 1e-12L && t < 1.0L - 1e-12L)
            points.push_back(t);
    }
}

long long countTriangle(int base, int height, long double x1, long double y1, long double x2, long double y2) {
    vector<long double> points;
    long double dx, dy, u1, u2, v1, v2, t, mid;
    long double x, y, a, b, c;
    long long ia, ib, ic;
    set<tuple<long long, long long, long long>> triangles;
    dx = x2 - x1;
    dy = y2 - y1;
    u1 = x1 - (long double)base * y1 / (2.0L * height);
    u2 = x2 - (long double)base * y2 / (2.0L * height);
    v1 = x1 + (long double)base * y1 / (2.0L * height);
    v2 = x2 + (long double)base * y2 / (2.0L * height);
    points.push_back(0.0L);
    points.push_back(1.0L);
    addCross(points, y1, y2, height);
    addCross(points, u1, u2, base);
    addCross(points, v1, v2, base);
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end(), [](long double first, long double second) {
        return fabsl(first - second) < 1e-12L;
    }), points.end());
    for (size_t index = 0; index + 1 < points.size(); index++) {
        mid = (points[index] + points[index + 1]) / 2.0L;
        x = x1 + dx * mid;
        y = y1 + dy * mid;
        a = y / height;
        b = (x - (long double)base * y / (2.0L * height)) / base;
        c = (x + (long double)base * y / (2.0L * height)) / base;
        if (isBoundary(a) || isBoundary(b) || isBoundary(c))
            continue;
        ia = (long long)floorl(a);
        ib = (long long)floorl(b);
        ic = (long long)floorl(c);
        triangles.insert(make_tuple(ia, ib, ic));
    }
    return (long long)triangles.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int base, height, x1, y1, x2, y2;
    while (cin >> base >> height >> x1 >> y1 >> x2 >> y2) {
        if (base == 0 && height == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)
            break;
        cout << countTriangle(base, height, x1, y1, x2, y2) << '\n';
    }
    return 0;
}
```

# 总结

本题的关键在于将三角网格看作由 $3$ 组平行直线划分而成的平面区域。通过求出线段与所有网格边界的交点，可以将原线段划分为若干不会跨越边界的小线段。对每段取中点并利用 $3$ 个归一化坐标的整数部分进行编码，即可唯一确定所在单三角形。

该方法避免了逐个枚举三角形，直接处理线段与边界的关系，能够稳定处理水平线段、竖直线段、斜线段以及沿网格边界延伸的特殊情况。
