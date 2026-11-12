[UVa 191 Intersection](https://blog.csdn.net/metaphysis/article/details/160941837)

## 题目分析

给定一个线段（由起点和终点确定）和一个矩形（由左上角和右下角确定），需要判断线段与矩形是否有至少一个公共点。矩形由其边界线和内部区域组成。

题目中给出的坐标均为整数，但交点可以是任意实数点。矩形坐标的输入顺序为 `xleft ytop xright ybottom`，但需要注意 `top left` 和 `bottom right` 仅表示名称，不保证 $xleft \leq xright$ 或 $ytop \geq ybottom$，因此需要自行处理坐标的大小关系。

## 解题思路

本题的核心是判断线段与矩形的相交关系。考虑以下几种相交情况：

1. **线段与矩形的任意一条边相交**。矩形的四条边可视为四个线段：上边、下边、左边、右边。
2. **线段的一个端点在矩形内部**。这种情况即使线段不与任何边相交，也与矩形有公共点。

因此解题分为两步：

- 使用跨立实验判断线段是否与矩形的四条边相交。
- 判断线段的两个端点是否至少有一个在矩形内部。

### 跨立实验判断线段相交

通过叉积判断方向：

设线段 $AB$ 和 $CD$，计算：

$$
d_1 = \overrightarrow{AB} \times \overrightarrow{AC} \\
d_2 = \overrightarrow{AB} \times \overrightarrow{AD} \\
d_3 = \overrightarrow{CD} \times \overrightarrow{CA} \\
d_4 = \overrightarrow{CD} \times \overrightarrow{CB} \\
$$

若 $d_1 \times d_2 < 0$ 且 $d_3 \times d_4 < 0$，则两线段严格相交。若有任一叉积为零，则需要判断对应端点是否落在另一线段上。

### 点在矩形内的判断

对于点 $(x, y)$，若：

$$
\min(xleft, xright) \leq x \leq \max(xleft, xright)
$$

且

$$
\min(ytop, ybottom) \leq y \leq \max(ytop, ybottom)
$$

则点在矩形内部（包含边界）。

## 算法步骤

1. 读取测试用例个数 $n$。
2. 对于每个测试用例，读取线段的起点、终点和矩形的两个角点坐标。
3. 构造矩形的四条边线段。
4. 分别判断线段与四条边是否相交，若任意一条相交则标记为相交。
5. 判断线段的任一端点是否在矩形内部，若是则标记为相交。
6. 根据标记输出 `T` 或 `F`。

## 复杂度分析

每个测试用例进行常数次线段相交判断，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

## 代码实现

```cpp
// Intersection
// UVa ID: 191
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 定义点结构体
struct point {
    int x, y;
};

// 定义线段结构体
struct segment {
    point start, end;
};

// 包围盒测试，判断点 p 是否在线段 ab 的包围盒内（包含边界）
bool pointInBox(point p, point a, point b) {
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

// 计算向量 AB 与 AC 的叉积
// 返回值 > 0 表示 C 在 AB 的左侧，< 0 表示在右侧，= 0 表示共线
double direction(point a, point b, point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断两条线段是否相交（包含端点情况）
bool segmentsIntersect(segment a, segment b) {
    double d1, d2, d3, d4;
    // 计算叉积
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    // 严格相交：两个端点分别位于另一线段两侧
    if ((d1 * d2 < 0) && (d3 * d4 < 0)) return true;
    // 非严格相交：端点落在另一线段上
    if (d1 == 0 && pointInBox(b.start, a.start, a.end)) return true;
    if (d2 == 0 && pointInBox(b.end, a.start, a.end)) return true;
    if (d3 == 0 && pointInBox(a.start, b.start, b.end)) return true;
    if (d4 == 0 && pointInBox(a.end, b.start, b.end)) return true;
    return false;
}

int main() {
    int n, xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
    cin >> n;  // 读取测试用例个数
    while (n > 0) {
        // 读取输入数据
        cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;
        segment line = (segment){(point){xstart, ystart}, (point){xend, yend}};
        // 构造矩形的四个顶点
        point leftTop = (point){xleft, ytop};
        point rightTop = (point){xright, ytop};
        point leftBottom = (point){xleft, ybottom};
        point rightBottom = (point){xright, ybottom};
        bool intersected = false;
        // 判断线段是否与矩形的四条边相交
        if (segmentsIntersect(line, (segment){leftTop, rightTop}))   // 上边
            intersected = true;
        if (segmentsIntersect(line, (segment){leftBottom, rightBottom})) // 下边
            intersected = true;
        if (segmentsIntersect(line, (segment){leftTop, leftBottom}))     // 左边
            intersected = true;
        if (segmentsIntersect(line, (segment){rightTop, rightBottom}))   // 右边
            intersected = true;
        // 判断线段端点是否在矩形内部
        if (min(xleft, xright) <= xstart && xstart <= max(xleft, xright) &&
            min(ytop, ybottom) <= ystart && ystart <= max(ytop, ybottom))
            intersected = true;
        if (min(xleft, xright) <= xend && xend <= max(xleft, xright) &&
            min(ytop, ybottom) <= yend && yend <= max(ytop, ybottom))
            intersected = true;
        // 输出结果
        cout << (intersected ? "T\n" : "F\n");
        n--;
    }
    return 0;
}
```

## 注意事项

- 矩形坐标输入顺序不保证 $xleft < xright$ 或 $ytop > ybottom$，需使用 $\min$ 和 $\max$ 函数处理。
- 线段与矩形相交包含线段完全在矩形内部的情况，此时线段不与任何边相交但端点在内，因此必须单独判断端点。
- 线段完全在矩形外部但与某边延长线相交的情况，通过跨立实验可以正确排除。
