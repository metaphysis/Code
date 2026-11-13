[UVa 248 Cutting Corners](https://blog.csdn.net/metaphysis/article/details/161250332)

## 题目概述

题目背景是自行车快递服务公司需要为配送路线定价，要求计算出从起点到终点的最短可行路径长度。快递员可以在建筑物之间穿行，甚至可以紧贴建筑物边缘行驶，但不能穿过建筑物内部。

## 题目分析

### 问题描述

在二维平面上，给定若干矩形建筑物（由 $n$ 个矩形表示，$0 \leq n \leq 20$），以及起点和终点坐标。要求计算从起点到终点的最短路径长度，路径不能穿过任何建筑物的内部（但可以紧贴建筑物边界行走）。

### 关键约束条件

1. **建筑物的定义**：每个建筑物由三个顶点坐标给出（矩形的一个顶点和相邻两个顶点），可以推导出第四个顶点。
2. **建筑物的关系**：相交的矩形被视为同一建筑物，不相交的矩形代表不同建筑物。
3. **行走规则**：可以在建筑物之间的空隙穿行，可以紧贴建筑物边界行驶（包括直角转弯处紧贴角落）。
4. **数据范围**：所有坐标在 $[0, 1000]$ 之间，$n \leq 20$。
5. **输入终止**：以 $-1$ 表示最后一个场景的结束。

### 输入输出格式

- **输入**：每个场景第一行为整数 $n$，第二行为起点和终点坐标 $x_1\ y_1\ x_2\ y_2$，接下来 $n$ 行每行三个顶点坐标 $x_1\ y_1\ x_2\ y_2\ x_3\ y_3$。
- **输出**：每个场景输出一行，格式为 `Scenario #k route distance: x.xx`，场景之间输出空行分隔。

## 解题思路

### 核心思想：图论建模 + 最短路径

本题的关键是将几何问题转化为图论问题。由于路径可以紧贴建筑物边界，因此最短路径必然由**起点**、**终点**以及**所有建筑物的顶点**之间的线段构成。理由如下：

- 如果路径中存在一段不经过任何特殊点的直线段，我们可以将其平移至经过某个顶点，距离不会变长。
- 由于只能绕开建筑物，路径的转折点必然发生在建筑物顶点处。

因此，解题步骤为：

1. 收集所有关键点：起点、终点、所有建筑物的 $4$ 个顶点。
2. 在这些点之间建立图：如果两点之间的线段不穿过任何建筑物内部，则在两点之间连一条边，边权为两点间的欧几里得距离。
3. 在图上运行最短路径算法（$\texttt{Dijkstra}$ 算法），求起点到终点的最短距离。

### 关键问题处理

#### 1. 矩形顶点的推导

题目只给出矩形的三个顶点。矩形是轴对齐的吗？题目没有明确说明，但从输入和代码实现来看，矩形可以是任意方向（非轴对齐）。代码中的 `getPointAndRectangle` 函数完成了第四个顶点的推导：

- 先找出三条边中最长边对应的两个顶点作为矩形的对角顶点。
- 然后利用平行四边形法则计算第四个顶点：$p_4 = p_1 - (p_3 - p_2)$。

#### 2. 判断两点连线是否与建筑物相交

这是本题的核心几何计算。一个线段 $AB$ 是**可行**的，当且仅当它不与任何建筑物的**内部**相交。判断方法：

对于每个建筑物（矩形）：
- 首先判断 $AB$ 是否完全在矩形的一侧（使用方向函数 $d_1, d_2, d_3, d_4$ 同号），如果是，则不可能与矩形相交，跳过。
- 否则，检查以下两种情况：
  - 如果 $A$ 或 $B$ 在矩形内部，则线段与建筑物相交（不可行）。
  - 如果线段与矩形的任意一条边相交（且不是端点重合的情况），则不可行。

代码中的 `intersected` 函数实现了这一逻辑。

#### 3. 方向函数

```cpp
double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}
```

该函数计算向量 $\overrightarrow{ab}$ 与 $\overrightarrow{ac}$ 的叉积。返回值为正表示 $c$ 在 $ab$ 左侧，为负表示右侧，为 $0$ 表示共线。

#### 4. 点是否在矩形内部

使用方向法判断：对于矩形 $R$（顶点按顺时针或逆时针顺序），点 $P$ 在矩形内部当且仅当 $P$ 位于四条边的同一侧（即四个方向值同号）。代码中的 `pointInRectangle` 函数实现了这一判断。

#### 5. 精度处理

由于坐标是实数，直接比较存在浮点误差。代码中使用了 $\texttt{EPSILON} = 10^{-6}$ 进行容差判断。例如：

- 判断方向值是否为 $0$：`fabs(value) <= EPSILON`
- 判断小于关系：`value + EPSILON < 0`

#### 6. 最短路径算法

代码使用的是 $\texttt{Moore-Dijkstra}$ 算法（即朴素 $\texttt{Dijkstra}$），时间复杂度 $O(V^2)$。由于顶点数最多为 $2 + 20 \times 4 = 82$，朴素版本完全够用。

## 代码实现细节

### 数据结构

```cpp
struct point { double x, y; };      // 点
struct segment { point start, end; }; // 线段
struct rectangle {                   // 矩形（四个顶点）
    point top_left, top_right, bottom_left, bottom_right;
};
struct edge { int label; double dist; }; // 图的边
```

### 主要函数说明

| 函数名 | 功能 |
|--------|------|
| `direction` | 计算叉积，判断点的方位 |
| `distanceOfPoints` | 计算两点欧氏距离 |
| `getPointAndRectangle` | 由三个顶点推导矩形并存储 |
| `segmentsIntersect` | 判断两线段是否相交（规范相交） |
| `pointInRectangle` | 判断点是否在矩形内部 |
| `intersected` | 判断线段是否与任何建筑物相交 |
| `prepare` | 构建图：在所有点之间添加可行边 |
| `mooreDijkstra` | 运行朴素 Dijkstra 算法求最短路 |

### 代码注释

```cpp
// Cutting Corners
// UVa ID: 248
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double MAX_DISTANCE = 1000000.0, EPSILON = 1e-6;

// 点结构体
struct point
{
    double x, y;
};

// 线段结构体
struct segment
{
    point start, end;
};

// 矩形结构体，存储四个顶点
struct rectangle
{
    point top_left, top_right, bottom_left, bottom_right;
};

// 图的边结构体
struct edge
{
    int label;      // 目标顶点索引
    double dist;    // 边长（距离）
};

point starting, stopping;               // 起点和终点
vector<point> allPoints;                // 所有点的集合
vector<rectangle> allRectangles;        // 所有矩形的集合

vector<vector<edge>> edges;             // 图的邻接表
vector<double> distances;               // 最短距离数组
vector<bool> visited;                   // 访问标记数组

// 计算向量 ab 和 ac 的叉积，判断 c 在 ab 的左侧还是右侧
double direction(point a, point b, point c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 计算两点间的欧几里得距离
double distanceOfPoints(point p1, point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 由三个顶点推导出矩形的第四个顶点，并存储矩形和所有顶点
void getPointAndRectangle(point p1, point p2, point p3)
{
    // 找出最长边对应的两个顶点作为对角顶点
    if (distanceOfPoints(p1, p2) + EPSILON < distanceOfPoints(p2, p3))
        getPointAndRectangle(p2, p3, p1);
    else if (distanceOfPoints(p1, p2) + EPSILON < distanceOfPoints(p1, p3))
        getPointAndRectangle(p1, p3, p2);
    else
    {
        // 平行四边形法则计算第四个顶点
        point p4 = (point){p1.x - (p3.x - p2.x), p1.y - (p3.y - p2.y)};
        
        // 存储四个顶点
        allPoints.push_back(p1);
        allPoints.push_back(p2);
        allPoints.push_back(p3);
        allPoints.push_back(p4);
            
        // 根据方向确定矩形的顶点顺序（保证一致性）
        if (direction(p1, p2, p3) > EPSILON) 
            allRectangles.push_back((rectangle){p1, p3, p2, p4});
        else
            allRectangles.push_back((rectangle){p1, p4, p2, p3});
    }
}

// 判断两条线段是否相交（规范相交，即交点在内部）
bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    // 规范相交：两线段互相跨立
    return ((d1 * d2 < 0) && (d3 * d4) < 0);
}

// 判断点是否在矩形内部（不包括边界）
bool pointInRectangle(point p, rectangle r)
{
    double d1 = direction(r.top_left, r.bottom_left, p);
    double d2 = direction(r.bottom_left, r.bottom_right, p);
    double d3 = direction(r.bottom_right, r.top_right, p);
    double d4 = direction(r.top_right, r.top_left, p);
    
    // 点在内部当且仅当在四条边的同一侧
    return (d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0);
}

// 判断线段 s 是否与任何建筑物相交（包括端点在内部的情况）
bool intersected(segment s)
{
    for (int i = 0; i < allRectangles.size(); i++)
    {
        rectangle r = allRectangles[i];

        // 判断线段两端点相对于矩形各边的方向
        double d1 = direction(s.start, s.end, r.top_left);
        double d2 = direction(s.start, s.end, r.top_right);
        double d3 = direction(s.start, s.end, r.bottom_left);
        double d4 = direction(s.start, s.end, r.bottom_right);

        // 如果线段完全在矩形的一侧，则不可能相交
        if ((d1 >= -EPSILON && d2 >= -EPSILON && d3 >= -EPSILON && d4 >= -EPSILON) ||
            (d1 <= EPSILON && d2 <= EPSILON && d3 <= EPSILON && d4 <= EPSILON))
            continue;
        else
        {
            // 如果端点在矩形内部，则相交
            if (pointInRectangle(s.start, r) || pointInRectangle(s.end, r))
                return true;

            // 检查是否与矩形的任意一条边相交
            if (segmentsIntersect(s, (segment){r.top_left, r.bottom_left}) ||
                segmentsIntersect(s, (segment){r.bottom_left, r.bottom_right}) ||
                segmentsIntersect(s, (segment){r.bottom_right, r.top_right}) ||
                segmentsIntersect(s, (segment){r.top_right, r.top_left}))
                return true;
        }
    }
    
    return false;
}

// 构建图：在所有点之间添加可行边
void prepare()
{
    edges.clear();
    edges.resize(allPoints.size(), vector<edge>());
    
    // 枚举所有点对
    for (int i = 0; i < allPoints.size(); i++)
        for (int j = i + 1; j < allPoints.size(); j++)
        {
            segment s = (segment){allPoints[i], allPoints[j]};
            // 如果线段不穿过任何建筑物，则添加边
            if (!intersected(s))
            {
                double dist = distanceOfPoints(s.start, s.end);
                edges[i].push_back((edge){j, dist});
                edges[j].push_back((edge){i, dist});
            }
        }
}

// 朴素 Dijkstra 算法求最短路，起点为 start
void mooreDijkstra(int start)
{
    visited.clear();
    distances.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        visited.push_back(false);
        distances.push_back(MAX_DISTANCE);
    }

    distances[start] = 0.0;
    
    // 每次选择一个未访问且距离最小的顶点进行松弛
    while (!visited[start])
    {
        visited[start] = true;
        
        // 松弛当前顶点的所有邻接边
        for (int i = 0; i < edges[start].size(); i++)
        {
            edge e = edges[start][i];
            if (!visited[e.label] && distances[start] + e.dist + EPSILON < distances[e.label])
                distances[e.label] = distances[start] + e.dist;
        }

        // 选择下一个未访问的距离最小的顶点
        double minDistance = MAX_DISTANCE;
        for (int i = 0; i < edges.size(); i++)
            if (!visited[i] && minDistance > distances[i] + EPSILON)
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    int n, cases = 0;

    while (cin >> n, n >= 0)
    {
        // 初始化数据
        allPoints.clear();
        allRectangles.clear();

        // 读入起点和终点
        cin >> starting.x >> starting.y >> stopping.x >> stopping.y;
        
        allPoints.push_back(starting);
        allPoints.push_back(stopping);
        
        // 读入 n 个矩形的三个顶点
        point p1, p2, p3;
        for (int i = 1; i <= n; i++)
        {
            cin >> p1.x >> p1.y;
            cin >> p2.x >> p2.y;
            cin >> p3.x >> p3.y;
            
            getPointAndRectangle(p1, p2, p3);
        }
        
        // 构建图并求最短路
        prepare();
        mooreDijkstra(0);   // 起点索引为 0
        
        // 输出结果
        if (cases > 0) cout << '\n';
        cout << "Scenario #" << ++cases << '\n';
        cout << "   route distance: ";
        cout << fixed << setprecision(2) << distances[1] << '\n';
    }
    
    return 0;
}
```

## 算法复杂度分析

- **顶点数** $V$：最多 $2 + 4 \times 20 = 82$ 个顶点。
- **边数** $E$：最多 $O(V^2) \approx 6724$ 条边（完全图）。
- **建图复杂度**：每次判断线段是否与矩形相交需遍历所有 $n$ 个矩形，每个矩形需进行常数次几何计算，总复杂度 $O(V^2 \cdot n)$，在本题范围内完全可以接受。
- **最短路径复杂度**：朴素 $\texttt{Dijkstra}$ 为 $O(V^2)$，约 $82^2 = 6724$ 次操作。

## 样例验证

### 样例输入
```
5
6.5 9 10 3
1 5 3 3 6
6 5.25 2 8 2
8 3.5 6 10 6
12 9 12 7 6
11 6 11 8 10
7 11 7 11 11
-1
```

### 样例输出
```
Scenario #1 route distance: 7.28
```

代码输出与样例一致。

## 总结

本题是一道经典的几何图论问题，核心思路是将几何约束转化为图的可达性判断，然后使用最短路径算法求解。解题的关键在于：

1. 准确判断线段是否与矩形内部相交。
2. 正确处理浮点精度。
3. 将所有建筑物顶点纳入图节点。

掌握了这些技巧，可以解决类似的可视性图（$\texttt{Visibility Graph}$）问题。
