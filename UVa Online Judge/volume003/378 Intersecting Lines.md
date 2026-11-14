[UVa 378 Intersecting Lines](https://blog.csdn.net/metaphysis/article/details/161642675)

## 题目描述

平面上两个不同的点确定一条直线。平面上的两条直线有三种相交情况：
1. 无交点（平行）
2. 交于一条直线（重合）
3. 交于一点

给定四个点，确定两条直线，判断它们的相交情况并求出交点。

### 输入格式

第一行包含一个整数 $N$（$1 \leq N \leq 10$），表示直线对的数量。接下来 $N$ 行，每行包含 $8$ 个整数，按顺序 $x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4$ 表示四个点的坐标。

### 输出格式

第一行输出 `INTERSECTING LINES OUTPUT`。对于每对直线，输出一行：
- `LINE`：重合
- `NONE`：平行
- `POINT x y`：交于一点，交点坐标保留两位小数

最后一行输出 `END OF OUTPUT`。

### 样例输入

```
5
0 0 4 4 0 4 4 0
5 0 7 6 1 0 2 3
5 0 7 6 3 -6 4 -3
2 0 2 27 1 5 18 5
0 3 4 0 1 2 2 5
```

### 样例输出

```
INTERSECTING LINES OUTPUT
POINT 2.00 2.00
NONE
LINE
POINT 2.00 5.00
POINT 1.07 2.20
END OF OUTPUT
```

---

## 题目分析

### 问题的本质

这是一个**直线相交判定与交点计算**问题。需要判断两条直线的位置关系并计算交点。

### 直线表示

使用直线的一般式 $ax + by + c = 0$ 表示直线。

### 从两点确定直线

给定两点 $P_1(x_1, y_1)$ 和 $P_2(x_2, y_2)$：

- 如果 $x_1 = x_2$（垂直直线）：$a = 1$，$b = 0$，$c = -x_1$
- 否则：$a = -\frac{y_1 - y_2}{x_1 - x_2}$，$b = 1$，$c = -a x_1 - y_1$

### 位置关系判断

- **平行**：$\frac{a_1}{a_2} = \frac{b_1}{b_2} = \frac{c_1}{c_2}$？实际判断 $a_1 b_2 - a_2 b_1 = 0$
- **重合**：平行且 $\frac{c_1}{c_2}$ 也成比例

### 交点计算

解方程组：
$$
\begin{cases}
a_1 x + b_1 y + c_1 = 0 \\
a_2 x + b_2 y + c_2 = 0
\end{cases}
$$

由克莱姆法则：
$$
x = \frac{b_1 c_2 - b_2 c_1}{a_1 b_2 - a_2 b_1}, \quad
y = \frac{c_1 a_2 - c_2 a_1}{a_1 b_2 - a_2 b_1}
$$

---

## 参考代码

```cpp
// Intersecting Lines
// UVa ID: 378
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-10;

struct point
{
    double x, y;
};

struct line
{
    double a, b, c;  // ax + by + c = 0
};

// 两点确定直线的一般式
line pointsToLine(point start, point end)
{
    line lr;
    if (fabs(start.x - end.x) <= EPSILON)
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -start.x;
    }
    else
    {
        lr.a = -(start.y - end.y) / (start.x - end.x);
        lr.b = 1.0;
        lr.c = -lr.a * start.x - start.y;
    }
    return lr;
}

// 判断两直线是否平行
bool isParallel(line line1, line line2)
{
    return fabs(line1.a * line2.b - line2.a * line1.b) <= EPSILON;
}

// 判断两直线是否重合
bool isSame(line line1, line line2)
{
    return isParallel(line1, line2) && fabs(line1.c - line2.c) <= EPSILON;
}

// 计算两直线交点
point intersect(line line1, line line2)
{
    point p;
    double det = line1.a * line2.b - line2.a * line1.b;
    if (fabs(det) <= EPSILON)  // 平行或重合
        return p;
    
    p.x = (line1.b * line2.c - line2.b * line1.c) / det;
    p.y = (line2.a * line1.c - line1.a * line2.c) / det;
    return p;
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    
    cout << "INTERSECTING LINES OUTPUT" << endl;
    
    double x1, y1, x2, y2, x3, y3, x4, y4;
    for (int i = 1; i <= n; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        
        point p1 = {x1, y1}, p2 = {x2, y2}, p3 = {x3, y3}, p4 = {x4, y4};
        
        line line1 = pointsToLine(p1, p2);
        line line2 = pointsToLine(p3, p4);
        
        if (isSame(line1, line2))
            cout << "LINE" << endl;
        else if (isParallel(line1, line2))
            cout << "NONE" << endl;
        else
        {
            point p = intersect(line1, line2);
            cout << fixed << setprecision(2);
            cout << "POINT " << p.x << " " << p.y << endl;
        }
    }
    
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
