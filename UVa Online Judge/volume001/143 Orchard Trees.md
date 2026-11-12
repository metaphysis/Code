[UVa 143 Orchard Trees](https://blog.csdn.net/metaphysis/article/details/157463934)

## 题目描述

一个果园主在一片矩形区域内均匀种植了果树，果树在水平和垂直方向间距相等，形成一个矩形网格。每棵果树的位置可以用整数坐标表示，坐标原点位于左下角。现在给定一系列三角形，三角形的顶点坐标是 $0.0$ 到 $100.0$ 之间的实数，而果树的坐标范围是 $1$ 到 $99$ 的整数。要求编写程序计算每个三角形内部（包括边界上）包含的果树数量。输入包含多行，每行包含 $6$ 个实数，代表三角形的三个顶点坐标 $(x_1, y_1, x_2, y_2, x_3, y_3)$，文件以一行 $6$ 个 $0$ 结束。对于每个三角形，输出一行，包含一个右对齐、宽度为 $4$ 的整数，表示该三角形内的果树数量。

## 题目分析

本题的关键在于判断一个整数坐标点（代表一棵树）是否在给定的三角形内部（包括边界）。由于坐标范围较小（$1 \le x, y \le 99$），我们可以枚举所有可能的果树位置，逐一进行判断。判断点是否在三角形内通常使用向量叉积（$\texttt{cross product}$）方法。

### 点与三角形的位置关系

设三角形三个顶点为 $A$ 、 $B$ 、 $C$ ，待判断的点为 $P$ 。我们可以通过计算以下三个叉积来判断 $P$ 的位置：

$$
\begin{aligned}
cp_1 &= (B - A) \times (P - A) \\
cp_2 &= (C - B) \times (P - B) \\
cp_3 &= (A - C) \times (P - C)
\end{aligned}
$$

其中 $\times$ 表示二维向量的叉积（有向面积）。如果 $cp_1$ 、 $cp_2$ 、 $cp_3$ 全部同号（都为正或都为负），则点 $P$ 在三角形内部。如果有一个叉积为 $0$ ，则 $P$ 在对应的边上；如果两个叉积为 $0$ ，则 $P$ 与某个顶点重合。根据题目要求，只要点在边上（包括顶点），就视为在三角形内。

### 算法步骤

1. 读入三角形三个顶点坐标 $A$ 、 $B$ 、 $C$ 。
2. 确定枚举范围：由于果树坐标是整数，且范围为 $1$ 到 $99$ ，我们可以先计算三角形在 $x$ 和 $y$ 方向上的整数边界，即：
   - $minX = \max(\lceil \min(x_1, x_2, x_3) \rceil, 1)$
   - $maxX = \min(\lfloor \max(x_1, x_2, x_3) \rfloor, 99)$
   - $minY = \max(\lceil \min(y_1, y_2, y_3) \rceil, 1)$
   - $maxY = \min(\lfloor \max(y_1, y_2, y_3) \rfloor, 99)$
   这样可以大大减少需要枚举的点数。
3. 对于每个整数坐标 $(i, j)$ ，判断该点是否在三角形内：
   - 如果点在某条边上（叉积为 $0$ 且点在线段包围盒内），则计数。
   - 否则，如果三个叉积同号（顺时针或逆时针），则计数。
4. 输出计数结果，格式化为宽度 $4$ 的右对齐整数。

### 注意事项

- 由于顶点坐标是实数，计算叉积时需要考虑浮点误差，引入一个很小的常数 $\texttt{EPSILON}$ 进行比较。
- 判断点是否在线段上时，除了叉积为 $0$ ，还需要确保点在线段的包围盒内，以避免点在线段延长线上的情况。

## 代码实现

```cpp
// Orchard Trees
// UVa ID: 143
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.099s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPSILON = 1E-9;

struct point {
    double x, y;
};

double cp(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cw(point a, point b, point c) {
    return cp(a, b, c) < -EPSILON;
}

bool ccw(point a, point b, point c) {
    return cp(a, b, c) > EPSILON;
}

bool collinear(point a, point b, point c) {
    return fabs(cp(a, b, c)) <= EPSILON;
}

// 包围盒测试。
bool pointInBox(point p, point a, point b) {
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

int main() {
    point a, b, c;
    while (true) {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0 & c.x == 0 && c.y == 0)
            break;
        int counter = 0;
        int minX, maxX, minY, maxY;
        minX = min(ceil(a.x), min(ceil(b.x), ceil(c.x)));
        maxX = max(floor(a.x), max(floor(b.x), floor(c.x)));
        minY = min(ceil(a.y), min(ceil(b.y), ceil(c.y)));
        maxY = max(floor(a.y), max(floor(b.y), floor(c.y)));
        for (int i = max(minX, 1); i <= min(maxX, 99); i++)
            for (int j = max(minY, 1); j <= min(maxY, 99); j++) {
                point tree = (point) { (double)i, (double)j };
                if ((collinear(a, b, tree) && pointInBox(tree, a, b)) ||
                    (collinear(b, c, tree) && pointInBox(tree, b, c)) ||
                    (collinear(c, a, tree) && pointInBox(tree, c, a)))
                    counter++;
                else {
                    if ((cw(a, b, tree) && cw(b, c, tree) && cw(c, a, tree)) ||
                        (ccw(a, b, tree) && ccw(b, c, tree) && ccw(c, a, tree)))
                            counter++;
                }
            }
        cout << setw(4) << right << counter << "\n";
    }
    return 0;
}
```
