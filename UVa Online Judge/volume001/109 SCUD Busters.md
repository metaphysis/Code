
> **摘要**：本题给定若干由点集构成的王国，每个王国的领土为其点集的凸包。导弹落在某王国领土内（含边界）即摧毁其发电站并导致断电。要求对所有被击中的王国，累加其凸包面积并输出保留两位小数的结果。解法为：对每个王国用 $\texttt{Andrew}$ 算法求凸包，用射线法判断每枚导弹是否落在凸包内，最后用有向面积公式累加被击中王国的面积，整体复杂度可接受。

## 题目大意

本题描述了一个 $500 \text{km} \times 500 \text{km}$ 的平面世界，其中有若干个王国，每个王国由若干个点（房屋和唯一的一个发电站）组成。每个王国周围有一个最小周长的围墙（即这些点构成的凸包），围墙内的区域即为该王国的领土。

当导弹落在某个王国的领土内（包括边界）时，该王国的发电站被摧毁，从而该国断电。题目会给出所有王国的点坐标，以及一系列导弹的落点坐标。要求计算所有因导弹袭击而断电的王国总面积，并输出保留两位小数的结果。

## 输入说明

输入分为两部分：
1. 王国描述：每个王国以一个整数 $N$ 开始，表示该王国有 $N$ 个点（包括发电站和房屋），接下来 $N$ 行每行给出一个点的坐标 $(x, y)$。第一个点即为发电站的位置。当 $N = -1$ 时，表示王国描述结束。
2. 导弹落点：每行一个坐标 $(x, y)$，表示一枚导弹的落点，直到文件结束。

所有坐标均为 $0$ 到 $500$ 之间的整数，王国数量不超过 $20$，每个王国的点数 $3 \leq N \leq 100$。

## 样例输入

```text
12
3 3
4 6
4 11
4 8
10 6
5 7
6 6
6 3
7 9
10 4
10 9
1 7
5
20 20
20 40
40 20
40 40
30 30
3
10 10
21 10
21 13
-1
5 5
20 12
```

## 样例输出

```text
70.50
```

## 解题思路

题目本质上是一个**计算几何**问题，可以分解为以下几个步骤：

1. **凸包构建**：对每个王国的所有点，求出其凸包顶点（即最小周长围墙的顶点）。由于围墙是“最小周长的薄墙”，实际上就是这些点的凸包边界。
2. **点是否在多边形内判断**：对于每枚导弹的落点，判断它位于哪些王国的凸包内（包括边界）。
3. **面积计算**：将所有被导弹击中的王国的凸包面积累加起来。
4. **输出结果**：输出总断电面积，保留两位小数。

### 具体实现细节

#### 凸包构建（$\texttt{Andrew}$ 算法）
- 先对所有点按 $x$ 坐标升序排序，若 $x$ 相同则按 $y$ 升序排序。
- 分别求上凸包和下凸包，然后合并。
- 对于点集规模较小的王国（点数 $≤ 3$），直接作为凸包。

#### 点是否在凸包内判断（射线法）
- 从待测点向右作一条水平射线，统计射线与凸包边界的相交次数。
- 若相交次数为奇数，则点在多边形内部；若为偶数，则在外部。
- 需要处理点在边界上的情况（叉积为 $0$ 且在线段范围内）。

#### 多边形面积计算（有向面积公式）
使用公式：
$$
area = \frac{1}{2} \left| \sum_{i=0}^{n-1} (x_i y_{i+1} - x_{i+1} y_i) \right|
$$
其中顶点按顺序排列（顺时针或逆时针均可，取绝对值后得到正值面积）。

## 复杂度分析
- 凸包构建：$O(N \log N)$。
- 点是否在凸包内：$O(n)$，其中 $n$ 为凸包顶点数。
- 总导弹数不确定，但王国数 ≤ $20$，每个凸包顶点数 ≤ $100$，因此总体复杂度是可接受的。

## 代码实现


```cpp
// SCUD Busters
// UVa ID: 109
// Verdict: Accepted
// Submission Date: 2011-11-24
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 110
#define MAXN 25

struct point {
    int x;
    int y;
};

struct polygon {
    int n;
    point p[MAXPOLY];
};

point sites[MAXPOLY];
polygon kingdom[MAXN];
bool powerOff[MAXN];
int kingdomNumber;

// 叉积，判断点 first，second，third 组成的两条线段的转折方向。当叉积大于 0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
int crossProduct(point first, point second, point third) {
    return (second.x - first.x) * (third.y - first.y) -
        (second.y - first.y) * (third.x - first.x);
}

// Andrew 凸包扫描算法的预排序，先按 x 坐标排序，若 x 坐标相同，则按 y 坐标排序。
bool leftLower(point first, point second) {
    if (first.x == second.x) return first.y < second.y;
    else return first.x < second.x;
}

// Andrew 凸包扫描算法。
void convexHull(point vertex[], int vertexNumber, polygon &container) {
    // 点个数小于等于三个，构成凸包。
    if (vertexNumber <= 3) {
        for (int i = 0; i < vertexNumber; i++)
            container.p[i] = vertex[i];
        container.n = vertexNumber;
        return;
    }

    // 排序。
    sort(vertex, vertex + vertexNumber, leftLower);
    
    point upper[MAXPOLY], lower[MAXPOLY];
    int top;

    // 求上凸包。
    upper[0] = vertex[0];
    upper[1] = vertex[1];
    top = 2;
    for (int i = 2; i < vertexNumber; i++) {
        upper[top] = vertex[i];
        while (top >= 2 && crossProduct(upper[top - 2], upper[top - 1], upper[top]) >= 0) {
            upper[top - 1] = upper[top];
            top--;
        }
        top++;
    }

    container.n = 0;
    for (int i = 0; i < top; i++) container.p[container.n++] = upper[i];

    // 求下凸包。
    lower[0] = vertex[vertexNumber - 1];
    lower[1] = vertex[vertexNumber - 2];
    top = 2;
    for (int i = vertexNumber - 3; i >= 0; i--) {
        lower[top] = vertex[i];
        while (top >= 2 && crossProduct(lower[top - 2], lower[top - 1], lower[top]) >= 0) {
            lower[top - 1] = lower[top];
            top--;
        }
        top++;
    }

    // 合并下凸包。
    for (int i = 1; i < top - 1; i++) container.p[container.n++] = lower[i];
}

// 使用射线法判断点是否在多边形内，在多边形边界上认为点在其内。
bool pointInPolygon(point pt, polygon &polygons) {
    int nCross = 0;
    int crossProduct;

    for (int i = 0, j = polygons.n - 1; i < polygons.n; j = i++) {
        // 排斥实验，检测点是否在线段外接矩形内范围内。
        if (pt.y >= polygons.p[j].y && pt.y <= polygons.p[i].y || pt.y >= polygons.p[i].y && pt.y <= polygons.p[j].y) {
            // 计算叉积。
            crossProduct = (polygons.p[i].x - polygons.p[j].x) *
                (pt.y - polygons.p[j].y) - (pt.x - polygons.p[j].x) *
                (polygons.p[i].y - polygons.p[j].y);

            // 点在线段上。
            if (crossProduct == 0 && (pt.x >= polygons.p[j].x &&
                          pt.x <= polygons.p[i].x
                          || pt.x >= polygons.p[i].x
                          && pt.x <= polygons.p[j].x))
                return true;

            // 判断以 pt 为端点的向右射线与线段是否有交点。
            if (crossProduct > 0
                && polygons.p[i].y > polygons.p[j].y
                && pt.y != polygons.p[i].y || crossProduct < 0
                && polygons.p[i].y < polygons.p[j].y
                && pt.y != polygons.p[j].y)
                nCross++;
        }
    }

    return (nCross & 1);
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point vertex[], int vertexNumber) {
    double total = 0.0;
    for (int i = 0; i < vertexNumber; i++) {
        int j = (i + 1) % vertexNumber;
        total += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
    }
    return fabs(total / 2.0);
}

int main() {
    int sitesNumber;
    
    kingdomNumber = 0;
    while (cin >> sitesNumber, sitesNumber > 0) {
        for (int i = 0; i < sitesNumber; i++)
            cin >> sites[i].x >> sites[i].y;
        convexHull(sites, sitesNumber, kingdom[kingdomNumber]);
        kingdomNumber++;
    }


    point missile;
    memset(powerOff, false, sizeof(powerOff));
    while (cin >> missile.x >> missile.y) {
        for (int i = 0; i < kingdomNumber; i++)
            if (pointInPolygon(missile, kingdom[i]))
                powerOff[i] = true;
    }

    double totalArea = 0.0;
    for (int i = 0; i < kingdomNumber; i++)
        if (powerOff[i])
            totalArea += area(kingdom[i].p, kingdom[i].n);

    cout.precision(2);
    cout.setf(ios::fixed | ios::showpoint);
    cout << totalArea << endl;

    return 0;
}
```

## 总结

本题是典型的计算几何应用题，主要考察凸包构建、点是否在多边形内判断以及多边形面积计算等基础算法。通过使用标准的模板代码，可以较为简洁地解决该问题。注意处理边界情况和精度要求，即可得到正确结果。

---

**注意**：在实际解题时，需确保凸包构建正确，射线法判断点是否在多边形内时处理好边界情况，以及面积计算时取绝对值。
