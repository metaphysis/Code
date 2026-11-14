[UVa 303 Pipe](https://blog.csdn.net/metaphysis/article/details/161441978)

## 题目描述

$\texttt{GX}$ 光管线公司正在为新的跨星系光管线准备弯管。在设计新管道形状的阶段，公司遇到了一个问题：如何确定光线在管道每个组件内部能够传播的最远距离。

每个管道组件由许多直管段紧密连接而成。为了编程方便，公司用一系列点 $[x_1, y_1], [x_2, y_2], \dots, [x_n, y_n]$ 来描述每个组件，其中 $x_1 < x_2 < \dots < x_n$。这些是管道轮廓的**上端点**。管道的下端点由 $y$ 坐标减 $1$ 得到：对于每个上端点 $[x_i, y_i]$，对应一个下端点 $[x_i, y_i - 1]$。

光线从光源发出，光源是一个线段，其端点为 $[x_1, y_1 - 1]$ 和 $[x_1, y_1]$（端点本身也发光）。假设光线在管道的弯折点处不会发生折射，且弯折点不会阻挡光线。管道材料既不透明也不反光。

要求：对于每个管道组件，找出光线能够到达的具有**最大 $x$ 坐标**的点。如果光线能够穿过整个管道（即到达 $x_n$ 处），则输出 `Through all the pipe.`，否则输出该最大 $x$ 坐标（保留两位小数）。

### 输入格式

输入文件包含多个数据块，每个数据块描述一个管道组件。每个数据块的第一行是一个整数 $n$（$2 \leq n \leq 20$），表示弯折点的数量。接下来 $n$ 行，每行包含两个实数 $x_i, y_i$。最后一个数据块以 $n = 0$ 表示结束。

### 输出格式

对于输入文件中的每个数据块，输出一行：要么是一个保留两位小数的实数，要么是消息 `Through all the pipe.`。

### 样例输入

```
4
0 1
2 2
4 1
6 4
6
0 1
2 -0.6
5 -4.45
7 -5.57
12 -10.8
17 -16.55
0
```

### 样例输出

```
4.67
Through all the pipe.
```

---

## 题目分析

### 问题的本质

这是一个**几何光学 + 线段相交**问题。光线从管道左端的光源出发，沿直线传播。由于管道由一系列折线段构成（上下边界），光线传播受到管道壁的限制——当光线碰到管道壁时，会被阻挡，无法继续传播。

关键要点：
- 管道由上边界和下边界组成，上下边界都是折线段
- 上边界点：$(x_i, y_i)$
- 下边界点：$(x_i, y_i - 1)$
- 光源：从 $(x_1, y_1 - 1)$ 到 $(x_1, y_1)$ 的竖直线段
- 光线是直线，只在弯折点处可能改变方向（但题目说光线不会被弯折点阻挡，实际上光线传播到管道尽头或被管道壁阻挡为止）
- 需要找到光线能到达的最大 $x$ 坐标

### 物理直觉

光线从光源的某点发出，沿直线传播。只要这条直线完全位于管道内部（即对于每个 $x$ 坐标，光线的 $y$ 坐标介于上下边界之间），它就能继续传播。一旦光线碰到上边界或下边界，就会被阻挡，无法继续前进。

因此，问题转化为：对于所有从光源发出的直线，找出它们能够到达的最大 $x$ 坐标，然后取其中的最大值。

### 关键观察

根据几何光学原理，**能够传播最远的光线一定是擦着某个上边界点或下边界点通过的**。这是因为：
- 如果一条光线在两个边界点之间自由通过，可以稍微调整其角度，使其传播得更远
- 极限情况是光线恰好经过某个上弯折点或下弯折点

更精确地说，**最优光线一定经过管道的一个上顶点和一个下顶点**（可能是同一个 $x$ 坐标处的上下顶点，也可能是不同位置的顶点）。这是典型的“最远可见点”问题的结论。

因此，我们只需要枚举所有由上顶点 $(x_i, y_i)$ 和下顶点 $(x_j, y_j - 1)$ 确定的直线，计算每条直线能传播的最远 $x$ 坐标，然后取最大值。

---

## 解题思路

### 步骤一：数据结构定义

定义点结构体和直线结构体：

```cpp
struct point { double x, y; };
struct line { double a, b, c; };  // ax + by + c = 0
```

### 步骤二：几何工具函数

需要实现以下几何函数：
- `crossProduct(a, b, c)`：计算向量 $\overrightarrow{ab}$ 和 $\overrightarrow{ac}$ 的叉积
- `cw(a, b, c)`：判断 $c$ 是否在 $\overrightarrow{ab}$ 的顺时针方向
- `ccw(a, b, c)`：判断 $c$ 是否在 $\overrightarrow{ab}$ 的逆时针方向
- `pointsToLine(from, to)`：由两点确定直线方程
- `getIntersection(line1, line2)`：计算两条直线的交点
- `pointInBox(p, a, b)`：判断点 $p$ 是否在线段 $ab$ 的包围盒内

### 步骤三：计算单条光线的最远 $x$ 坐标

函数 `getRightmostX(from, to)` 计算从点 `from` 到点 `to` 的光线能够到达的最远 $x$ 坐标。

算法流程：
1. 初始化 `rightmostX` 为管道左端的 $x$ 坐标
2. 从前向后遍历每个管道段（从第 $0$ 段到第 $n-1$ 段）
3. 对于当前段，检查光线是否在上下边界之间：
   - 使用 `cw` 和 `ccw` 判断光线相对于上下边界点的位置关系
   - 如果光线穿过了上边界或下边界，则计算光线与边界线段的交点
   - 该交点的 $x$ 坐标即为当前光线能到达的最远位置
4. 如果光线通过了所有段，则返回一个很大的值（表示可以穿过整个管道）

**判断光线是否被阻挡的方法**：

对于当前段（第 $k$ 段），上边界点为 $U_k$ 和 $U_{k+1}$，下边界点为 $L_k$ 和 $L_{k+1}$。

光线由 `from` 到 `to`。检查：
- 如果光线在 $U_k$ 的顺时针方向且 $U_{k+1}$ 的逆时针方向（或相反），说明光线穿过了上边界线段
- 类似地，检查下边界

### 步骤四：主循环

枚举所有可能的光线方向：

```cpp
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
        rightmostX = max(rightmostX, getRightmostX(upper[i], lower[j]));
        rightmostX = max(rightmostX, getRightmostX(lower[i], upper[j]));
    }
```

解释：
- `upper[i]` 和 `lower[j]`：从左上顶点到右下顶点的光线
- `lower[i]` 和 `upper[j]`：从左下顶点到右上顶点的光线

为什么是 $i < j$？因为光线从左向右传播，起点必须在终点的左边。

### 步骤五：输出结果

- 如果 `rightmostX >= upper.back().x`（即到达或超过最后一个点的 $x$ 坐标），输出 `Through all the pipe.`
- 否则输出 `rightmostX`，保留两位小数

---

## 算法复杂度分析

### 时间复杂度

- 枚举所有光线方向：$O(n^2)$，$n \leq 20$，最多 $400$ 种方向
- 每条光线计算最远 $x$ 坐标：$O(n)$
- 总时间复杂度：$O(n^3)$，约 $8000$ 次操作，完全可行

### 空间复杂度

- 存储上下边界点：$O(n)$
- 总空间复杂度：$O(1)$

---

## 正确性证明

**引理 1**：能够传播最远的光线必然经过管道的一个上顶点和一个下顶点。

证明：考虑一条能够传播到某个 $x$ 坐标的光线。将该光线稍微向上或向下旋转，可以使它擦过某个顶点而不被阻挡。极限情况就是经过顶点。由于管道由折线段构成，最远点必然出现在顶点处。$\square$

**引理 2**：对于给定的光线方向，光线与管道边界的第一个交点决定了光线能到达的最远位置。

证明：光线一旦碰到边界就会被阻挡，因此第一个交点的 $x$ 坐标即为最远 $x$ 坐标。$\square$

**引理 3**：枚举所有上顶点和下顶点的组合覆盖了所有可能的最优光线。

证明：由引理 1，最优光线经过某个上顶点 $U_i$ 和某个下顶点 $L_j$（或者经过两个上顶点？但经过两个上顶点意味着光线贴着上边界，此时也会经过某个下顶点，因为管道有宽度）。因此枚举所有 $(U_i, L_j)$ 和 $(L_i, U_j)$ 组合足以找到最优解。$\square$

---

## 参考代码

```cpp
// Pipe
// UVa ID: 303
// Verdict: Accepted
// Submission Date: 2016-07-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-7;

// 点结构体
struct point
{
    double x, y;
};

// 直线结构体，表示为 ax + by + c = 0
struct line
{
    double a, b, c;
};

// 叉积计算：向量 ab 和 ac 的叉积
double crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 判断点 c 是否在向量 ab 的顺时针方向
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}

// 判断点 c 是否在向量 ab 的逆时针方向
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

// 由两点确定直线方程
line pointsToLine(point from, point to)
{
    line lr;

    if (fabs(from.x - to.x) <= EPSILON)  // 垂直线
    {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -from.x;
    }
    else
    {
        lr.a = -(from.y - to.y) / (from.x - to.x);
        lr.b = 1.0;
        lr.c = -lr.a * from.x - from.y;
    }

    return lr;
}

// 计算两条直线的交点
point getIntersection(line line1, line line2)
{
    point pr;

    pr.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        pr.y = -(line1.a * pr.x + line1.c) / line1.b;
    else
        pr.y = -(line2.a * pr.x + line2.c) / line2.b;

    return pr;
}

// 判断点 p 是否在线段 ab 的包围盒内
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x)) && 
            (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

vector<point> upper, lower;  // 上下边界点

// 计算从 from 到 to 的光线能到达的最远 x 坐标
double getRightmostX(point from, point to)
{
    double rightmostX = upper.front().x;  // 初始为管道左端

    // 遍历每个管道段
    for (int rightmost = 0; rightmost < upper.size(); rightmost++)
        // 如果光线穿过了上边界或下边界
        if (cw(from, to, upper[rightmost]) || ccw(from, to, lower[rightmost]))
        {
            if (rightmost == 0)  // 在第一段就被阻挡，无法前进
                return rightmostX;

            // 计算光线与下边界线段的交点
            line line1 = pointsToLine(from, to);
            line line2 = pointsToLine(lower[rightmost - 1], lower[rightmost]);
            point point1 = getIntersection(line1, line2);
            if (pointInBox(point1, lower[rightmost - 1], lower[rightmost]))
                rightmostX = max(rightmostX, point1.x);
            
            // 计算光线与上边界线段的交点
            line line3 = pointsToLine(upper[rightmost - 1], upper[rightmost]);
            point point2 = getIntersection(line1, line3);
            if (pointInBox(point2, upper[rightmost - 1], upper[rightmost]))
                rightmostX = max(rightmostX, point2.x);
                
            return rightmostX;
        }
    
    // 光线通过了所有管道段
    return upper.back().x + fabs(upper.back().x);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n)
    {
        // 读取上边界点，计算下边界点
        upper.resize(n), lower.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> upper[i].x >> upper[i].y;
            lower[i].x = upper[i].x;
            lower[i].y = upper[i].y - 1.0;  // 下边界 y 坐标减 1
        }
        
        double rightmostX = upper.front().x;
        
        // 枚举所有可能的光线方向：从上顶点到下顶点，或从下顶点到上顶点
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                rightmostX = max(rightmostX, getRightmostX(upper[i], lower[j]));
                rightmostX = max(rightmostX, getRightmostX(lower[i], upper[j]));
            }

        // 输出结果
        if (rightmostX >= upper.back().x)
            cout << "Through all the pipe." << endl;
        else
            cout << fixed << setprecision(2) << rightmostX << endl;
    }
    
	return 0;
}
```

---

## 总结

本题的核心在于：
1. **几何建模**：将管道抽象为上下两条折线
2. **最优光线判定**：光线一定经过某个上顶点和某个下顶点
3. **交点计算**：计算光线与管道边界的交点
4. **枚举策略**：枚举所有上顶点与下顶点的组合

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 管道表示 | 上边界点 $(x_i, y_i)$，下边界点 $(x_i, y_i - 1)$ |
| 最优光线 | 擦过上顶点和下顶点 |
| 方向枚举 | 枚举 $(U_i, L_j)$ 和 $(L_i, U_j)$，其中 $i < j$ |
| 阻挡判断 | 使用叉积判断光线是否穿过边界 |
| 交点计算 | 直线与直线求交，再判断交点是否在线段上 |

### 精度注意事项

- 使用 `EPSILON = 1E-7` 处理浮点数比较
- 输出保留两位小数，使用 `fixed << setprecision(2)`

这种“光线传播 + 顶点枚举”的解题模式，在计算几何中具有典型性，类似问题还包括“最远可见点”、“光线反射”等。
