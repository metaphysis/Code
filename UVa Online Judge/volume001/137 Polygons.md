[UVa 137 Polygons](https://blog.csdn.net/metaphysis/article/details/157426622)

## 题目描述

题目给出了两个凸多边形，这两个多边形可能重叠，也可能不重叠。如果它们重叠，重叠的程度和方式也会有所不同。要求编写一个程序，读取两个凸多边形的顶点坐标（按顺时针顺序给出），并计算这两个多边形面积的“异或”（$\texttt{exclusive or}$）面积，即只属于其中一个多边形所包围的区域面积。所求面积在题目提供的示意图中已用阴影标出。

### 输入格式
输入由多组数据组成，每组数据包含两行：
- 第一行：第一个多边形的顶点数 $n$ ，随后是 $n$ 对整数，表示按顺时针顺序的顶点坐标 $(x, y)$ 。
- 第二行：第二个多边形的顶点数 $m$ ，随后是 $m$ 对整数，表示按顺时针顺序的顶点坐标 $(x, y)$ 。

所有坐标均为小于 $100$ 的正整数。输入以一行单独的 $0$ 结束。

### 输出格式
对于每组数据，输出所求面积，格式为 $8$ 位宽、保留 $2$ 位小数的字段。所有结果在一行内输出，字段间用空格分隔。

### 样例输入
```
3 5 5 8 1 2 3
3 5 5 8 1 2 3
4 1 2 1 4 5 4 5 2
6 6 3 8 2 8 1 4 1 4 2 5 3
0
```
### 样例输出
```
␣␣␣␣0.00␣␣␣13.50
```
（注：样例输出中的空格用 $\sqcup$ 表示）

---

## 题目分析与解题思路

### 问题转化

两个多边形 $A$ 和 $B$ 的“异或”面积可以表示为：
$$
XOR_{Area} = Area(A) + Area(B) - 2 \times Area(A \cap B)
$$
其中：
- $Area(A)$ 和 $Area(B)$ 分别表示两个多边形的面积。
- $Area(A \cap B)$ 表示两个多边形的交集面积。

因此，问题的关键在于**计算两个凸多边形的交集面积**。

### 计算凸多边形交集

两个凸多边形的交集仍然是一个凸多边形（可能为空）。我们可以使用**半平面交**（$\texttt{Half-plane Intersection}$）的方法来求交集：

1. **将多边形视为一组半平面**：
   - 对于凸多边形的每条边，将其视为一个有向线段，方向为多边形顶点的顺时针顺序。
   - 该有向线段左侧（即多边形内部）的区域构成一个半平面。

2. **构建半平面集合**：
   - 将多边形 $A$ 的每条边对应的半平面加入集合。
   - 将多边形 $B$ 的每条边对应的半平面加入集合。

3. **求半平面交**：
   - 使用排序增量法求所有半平面的交集，得到一个新的凸多边形（交集多边形）。
   - 如果交集为空，则面积为 $0$。

4. **计算面积**：
   - 使用叉积法（$\texttt{Shoelace Formula}$）计算多边形面积。

### 算法步骤

1. 读取两个多边形的顶点坐标，构建多边形对象。
2. 分别计算两个多边形的面积。
3. 构建两个多边形的半平面集合。
4. 求半平面交，得到交集多边形。
5. 计算交集多边形面积。
6. 代入公式计算异或面积并输出。

### 关键点
- 由于输入坐标是整数，计算过程中需使用浮点数以保证精度。
- 注意处理精度误差，例如使用 $\texttt{EPSILON} = 1 \times 10^{-7}$ 进行比较。
- 输出格式要求 $8$ 位宽、保留 $2$ 位小数，需使用 `setw(8)` 和 `setprecision(2)` 进行控制。

### 复杂度分析
- 设两个多边形的总边数为 $N$，则半平面交算法的时间复杂度为 $O(N \log N)$，空间复杂度为 $O(N)$。
- 由于顶点数不超过 $100$，该算法可以高效运行。

---

## 代码实现

```cpp
// Polygons
// UVa ID: 137
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016 - 2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1100;
const double EPSILON = 1E-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

struct line {
    point a, b;
    double angle;
};

double cp(point a, point b, point c) {
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c) {
    return cp(a, b, c) < -EPSILON;
}

bool cmpLine(line p, line q) {
    if (fabs(p.angle - q.angle) <= EPSILON) return cw(p.a, p.b, q.a);
    return p.angle < q.angle;
}

bool cmpAngle(line p, line q) {
    return fabs(p.angle - q.angle) <= EPSILON;
}

bool parallel(line p, line q) {
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q) {
    point p1 = p.a;
    double scale =
        ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

line pointToLine(point a, point b) {
    line lr;
    lr.a = a, lr.b = b, lr.angle = atan2(b.y - a.y, b.x - a.x);
    return lr;
}

double area(polygon &pg) {
    if (pg.size() < 3) return 0.0;
    double A = 0.0;
    int n = pg.size();
    for (int i = 0, j = (i + 1) % n; i < n; i++, j = (i + 1) % n)
        A += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
    return fabs(A / 2.0);
}

polygon halfPlaneIntersection(line *sides, int nLine) {
    polygon pg;
    line deq[MAXV];
    sort(sides, sides + nLine, cmpLine);
    nLine = unique(sides, sides + nLine, cmpAngle) - sides;
    int btm = 0, top = 1;
    deq[0] = sides[0], deq[1] = sides[1];
    for (int i = 2; i < nLine; i++) {
        if (parallel(deq[top], deq[top - 1]) || parallel(deq[btm], deq[btm + 1]))
            return pg;
        while (btm < top &&
            cw(sides[i].a, sides[i].b, getIntersection(deq[top], deq[top - 1])))
            top--;
        while (btm < top &&
            cw(sides[i].a, sides[i].b, getIntersection(deq[btm], deq[btm + 1])))
            btm++;
        deq[++top] = sides[i];
    }
    while (btm < top &&
        cw(deq[btm].a, deq[btm].b, getIntersection(deq[top], deq[top - 1])))
        top--;
    while (btm < top &&
        cw(deq[top].a, deq[top].b, getIntersection(deq[btm], deq[btm + 1])))
        btm++;
    if (top <= (btm + 1)) return pg;
    for (int i = btm; i < top; i++)
        pg.push_back(getIntersection(deq[i], deq[i + 1]));
    if (btm < (top + 1))
        pg.push_back(getIntersection(deq[btm], deq[top]));
    return pg;
}

void exclusiveOr(polygon &a, polygon &b) {
    double areaA = area(a), areaB = area(b);
    line sides[MAXV];
    int nLine = 0;
    for (int i = 0; i < a.size() - 1; i++)
        sides[nLine++] = pointToLine(a[i + 1], a[i]);
    sides[nLine++] = pointToLine(a[0], a.back());
    for (int i = 0; i < b.size() - 1; i++)
        sides[nLine++] = pointToLine(b[i + 1], b[i]);
    sides[nLine++] = pointToLine(b[0], b.back());
    polygon c = halfPlaneIntersection(sides, nLine);
    double area1 = area(c);
    double area2 = areaA + areaB - 2 * area1;
    cout << fixed << setw(8) << setfill(' ') << setprecision(2) << (area2 + 1e-9);
}

int main() {
    int n;
    double xi, yi;
    while (cin >> n, n > 0) {
        polygon a, b;
        for (int i = 1; i <= n; i++) {
            cin >> xi >> yi;
            a.push_back(point(xi, yi));
        }
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> xi >> yi;
            b.push_back(point(xi, yi));
        }
        exclusiveOr(a, b);
    }
    cout << '\n';
    return 0;
}
```

---

## 总结

本题的关键在于将问题转化为求两个凸多边形的交集面积，并利用半平面交算法高效求解。计算几何问题中需特别注意精度处理和边界条件。代码实现中使用了经典的排序增量算法求半平面交，并利用叉积法计算多边形面积，最终通过公式得到异或面积。

该算法在时间和空间上均能满足题目要求，且代码结构清晰，便于理解和调试。
