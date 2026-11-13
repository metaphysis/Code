[UVa 218 Moth Eradication](https://blog.csdn.net/metaphysis/article/details/161047408)

## 题目分析

给定若干个点的坐标，需要找到能够包围所有点的**最小周长多边形**（即凸包），并输出凸包上的所有点（按顺时针方向，首尾点相同）以及凸包的周长。输入包含多组数据，每组数据的第一行为点的数量 $n$ ，接下来 $n$ 行每行两个实数表示坐标。当 $n = 0$ 时输入结束。

输出格式要求：

- 每组数据输出三行以上，第一行为 `Region #k:`（$k$ 从 $1$ 开始）。
- 接下来一行或多行输出凸包上的所有点，格式为 `(x,y)-` 连接，首尾点相同，点坐标四舍五入保留一位小数。
- 最后一行输出周长，格式为 `Perimeter length = ` + 保留两位小数的实数。
- 两组数据之间用一个空行分隔。

## 解题思路

本题的核心是**凸包（$\texttt{Convex Hull}$）** 算法。常用的凸包算法有：

- $\texttt{Graham Scan}$（格雷厄姆扫描法）
- $\texttt{Andrew}$ 算法（单调链法）

本题提供的代码使用了 **$\texttt{Graham}$ 扫描法** 的变体，主要步骤如下：

1. **排序**：首先按 $y$ 坐标升序、$x$ 坐标升序排序，找到最低最左的点作为参考点。
2. **极角排序**：以参考点为原点，按极角从小到大排序，若极角相同则按距离从小到大排序。
3. **构建凸包**：使用一个栈结构，依次检查每个点，如果新点使得最后两个点形成的向量呈**顺时针**方向（即右转），则弹出栈顶，直到满足逆时针或共线条件，然后将新点入栈。
4. **处理共线**：题目允许共线点以任意顺序输出，因此算法中保留了共线点。
5. **输出方向**：题目要求顺时针输出，代码在得到凸包后进行了 `reverse` 反转。
6. **周长计算**：依次累加相邻点的欧几里得距离。

## 注意事项

- 浮点数比较需要引入**误差容忍值** $\epsilon = 10^{-7}$，避免精度问题。
- 当点数少于等于 $2$ 时，直接输出所有点（此时凸包就是这些点本身）。
- 输出格式要求首尾点相同，代码中在 `hull` 的最后已经包含了起始点。
- 每组数据输出后需要加一个空行，但**最后一组数据后不能有多余空行**，代码通过 `if (cases++)` 控制。

## 代码实现

```cpp
// Moth Eradication
// UVa ID: 218
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int EPSILON = 1E-7;  // 浮点数比较误差阈值

struct point {
    double x, y;  // 点的坐标
};

point lowerLeftPoint;  // 最低最左点，作为极角排序的参考点

// 叉积：计算向量 AB 和 AC 的叉积
double cp(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// 顺时针方向：点 c 在线段 ab 的右侧
bool cw(point a, point b, point c) {
    return cp(a, b, c) < -EPSILON;
}

// 逆时针方向：点 c 在线段 ab 的左侧
bool ccw(point a, point b, point c) {
    return cp(a, b, c) > EPSILON;
}

// 三点共线
bool collinear(point a, point b, point c) {
    return fabs(cp(a, b, c)) <= EPSILON;
}

// 判断是否逆时针或共线
bool ccwOrCollinear(point a, point b, point c) {
    return ccw(a, b, c) || collinear(a, b, c);
}

// 排序函数：先按 y 再按 x 升序，用于找到最低最左点
bool lowerLeft(point a, point b) {
    return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// 判断两点坐标是否相同
bool cmpPoint(point first, point second) {
    return first.x == second.x && first.y == second.y;
}

// 计算点到参考点的距离平方（避免开方，用于极角相同时的比较）
double distanceToLowerLeftPoint(point p) {
    return pow(lowerLeftPoint.x - p.x, 2) + pow(lowerLeftPoint.y - p.y, 2);
}

// 极角排序的比较函数
bool smallerAngle(point first, point second) {
    // 如果三点共线，距离近的排在前面
    if (collinear(lowerLeftPoint, first, second))
        return distanceToLowerLeftPoint(first) <= distanceToLowerLeftPoint(second);
    // 否则按逆时针方向排序
    return ccw(lowerLeftPoint, first, second);
}

// Graham 凸包扫描算法
void grahamConvexHull(vector <point> &vertices, vector <point> &hull) {
    // 按 y 和 x 升序排序，找到最低最左点
    sort(vertices.begin(), vertices.end(), lowerLeft);

    // 移除重复的点
    vertices.erase(unique(vertices.begin(), vertices.end(), cmpPoint), vertices.end());

    // 如果点数 <= 2，凸包就是所有点（注意要闭合）
    if (vertices.size() <= 2) {
        vertices.push_back(vertices[0]);  // 添加首点形成闭合
        for (int i = 0; i < vertices.size(); i++)
            hull.push_back(vertices[i]);
        return;
    }

    // 极角排序
    lowerLeftPoint = vertices[0];
    sort(vertices.begin() + 1, vertices.end(), smallerAngle);

    // 初始化栈，放入前两个点
    int i = 2;
    hull.push_back(vertices[0]);
    hull.push_back(vertices[1]);

    // 添加哨兵：最低最左点作为最后一个元素，便于扫描结束时回到起点
    vertices.push_back(lowerLeftPoint);

    while (i <= vertices.size() - 1) {
        // 如果栈顶两点与新点形成顺时针方向（右转），则弹出栈顶
        if (cw(hull[hull.size() - 2], hull.back(), vertices[i]))
            hull.erase(hull.end() - 1);
        else
            hull.push_back(vertices[i++]);  // 否则入栈
    }
}

// 计算两点之间的欧几里得距离
double distances(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);

    int n, cases = 0;

    while (cin >> n, n)  // 读入 n，n = 0 时结束
    {
        vector <point> vertices;
        for (int i = 1; i <= n; i++)
        {
            point a;
            cin >> a.x >> a.y;
            vertices.push_back(a);
        }

        vector <point> hull;
        grahamConvexHull(vertices, hull);
        reverse(hull.begin(), hull.end());  // 反转得到顺时针顺序

        if (cases++)  // 控制两组数据之间的空行
            cout << endl;
        cout << "Region #" << cases << ":" << endl;

        // 输出凸包上的点，首尾点相同
        double length = 0.0;
        cout << "(" << fixed << setprecision(1) << hull[0].x << "," << fixed << hull[0].y << ")";
        for (int i = 1; i < hull.size(); i++)
        {
            cout << "-(" << fixed << setprecision(1) << hull[i].x << "," << fixed << hull[i].y << ")";
            length += distances(hull[i], hull[i - 1]);
        }
        cout << endl;
        cout << "Perimeter length = " << fixed << setprecision(2) << length << endl;
    }

    return 0;
}
```
