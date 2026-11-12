[UVa 132 Bumpy Objects](https://blog.csdn.net/metaphysis/article/details/156787420)

## 问题描述

题目定义了一类“凹凸不平的物体”（$\texttt{Bumpy Objects}$）。每个物体由一个多边形表示，已知其质心坐标和按逆时针顺序排列的顶点坐标。

一个物体能够**稳定旋转站立**的条件是：存在两个顶点，可以用一条**不与物体相交的直线**将它们连接起来，并且当这条直线水平时，**质心位于该直线上方**，且严格位于两个端点的投影之间。满足上述条件的这条直线称为物体的**基线（$\texttt{base line}$）**。一个物体通常有多个稳定位置（对应多条基线）。每条基线由其接触到的**编号最大的顶点**来标识（顶点编号从 $1$ 开始，按逆时针顺序递增）。

题目要求：对于给定的物体，找到所有稳定位置中，**基线标识号最小的那个位置**，并输出其基线标识号。

**输入** 包含多个数据集，每个数据集包含：
1.  一个长度小于 $20$ 的字符串，表示物体名称。
2.  两个整数，表示质心的坐标。
3.  多对整数，表示多边形顶点的坐标，以 `0 0` 结束。
所有数据集以单个 `#` 结束。

**输出** 对于每个物体，输出其名称和满足条件的最小基线标识号。

## 题目分析与建模

### 关键条件解读
1.  **基线定义**：基线是连接两个顶点的线段，且线段本身不与多边形相交（即，是多边形的一条“支撑弦”）。
2.  **稳定条件**：
    *   当这条线段被放置为水平时，质心必须在它的正上方。
    *   质心在水平方向上的投影，必须严格位于线段两个端点的投影之间（即，不能与端点重合）。
3.  **基线标识**：由线段接触到的**编号最大的顶点**决定。因此，我们需要记录每个顶点的原始输入编号。

### 核心难点与突破口
1.  **几何搜索范围**：一个凹多边形的潜在基线数量可能很多（任意两个顶点都可能）。但是，根据物理直觉和几何性质，**只有凸包（$\texttt{Convex Hull}$）上的边或弦，才有可能成为有效的基线**。为什么？
    *   如果一条边在凸包内部，那么它必然与多边形自身相交（因为它穿过了多边形的“内部”），这违反了基线“不与物体相交”的条件。
    *   因此，**所有有效的基线，其两个端点必然是多边形凸包的顶点**。更进一步，**基线本身必须是凸包的一条边，或者是凸包的一条弦（连接两个非相邻凸包顶点的线段）**。
2.  **稳定条件判定**：对于一个候选的基线 $(A, B)$，设其被旋转至水平。要判断质心 $C$ 是否在其上方且投影严格在 $A, B$ 之间，可以等价于判断以下两个条件（在原始坐标系下）：
    *   **上方性**：质心 $C$ 位于有向直线 $AB$ 的**左侧**（假设顶点是逆时针排列，那么多边形内部在每条边的左侧）。用叉积判断：$(B-A) \times (C-A) > 0$。
    *   **投影在内部**：这等价于角 $\angle ACB$ 和 $\angle BCA$ 都是**锐角**。如果质心投影在线段端点之外，那么其中一个角将是钝角或直角（当投影与端点重合时）。因此，我们可以通过余弦定理 $a^2 + b^2 > c^2$ 来判断一个角是否为锐角。

### 算法思路
1.  **输入与存储**：读入物体名称和质心坐标。读入所有顶点，并记录其**原始输入序号（从 1 开始）**。
2.  **求凸包**：使用 $\texttt{Andrew}$ 算法（或称单调链算法）求出所有顶点的**凸包**。该算法能 $O(n \log n)$ 时间内得到按逆时针顺序排列的凸包顶点序列。
3.  **枚举候选基线**：遍历凸包上的所有**边**（相邻顶点对）。根据分析，只需检查凸包的边。
    *   对于凸包的边 $(V_i, V_{i+1})$，检查它是否可能是一条有效基线：
        *   **条件 $1$**：质心 $C$ 是否位于该边的**左侧**（`cw(V_i, V_{i+1}, C)` 为 `true`）。注意，代码中的 `cw` 函数（$\texttt{clockwise}$）判断点是否在向量右侧，由于顶点是逆时针的，多边形内部在左侧，所以这里判断质心在右侧，即从多边形的“外部”看，质心在边的上方。这与分析中的“左侧”是等价的，只是坐标系和判断函数实现的差异。
        *   **条件 $2$ & $3$**：角 $\angle (C, V_i, V_{i+1})$ 和角 $\angle (C, V_{i+1}, V_i)$ 是否都是锐角（`isAcuteAngle` 函数）。
4.  **计算基线标识并更新**：如果当前凸包的边满足以上三个条件，那么它就是一个稳定位置对应的基线。这条基线接触到的顶点是 $V_i$ 和 $V_{i+1}$。根据题目定义，该基线的标识号为这两个顶点**原始编号的较大值**。我们需要在所有满足条件的基线中，找到这个标识号的**最小值**。
5.  **输出结果**：输出物体名称和找到的最小基线标识号。

### 复杂度分析
*   **时间复杂度**：
    *   凸包计算：$O(n \log n)$，其中 $n$ 为顶点数。
    *   凸包边枚举与条件判断：$O(n)$。
    *   总体复杂度为 $O(n \log n)$，对于 $n \leq 100$ 的数据范围非常高效。
*   **空间复杂度**：$O(n)$，用于存储顶点和凸包。

## 代码实现

```cpp
// Bumpy Objects
// UVa ID: 132
// Verdict: Accepted
// Submission Date: 2015-12-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAX_VERTICES 105
#define EPSILON 1E-10

struct point {
    int x;
    int y;
    int index; // 顶点的原始编号
};

struct polygon {
    int number; // 顶点数
    point vertex[MAX_VERTICES]; // 顶点数组
};

// 计算叉积 (c - a) x (b - a)
int crossProduct(point a, point b, point c) {
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 判断点 c 是否在向量 ab 的顺时针方向（右侧）
bool cw(point a, point b, point c) {
    return crossProduct(a, b, c) > EPSILON;
}

// 判断点 c 是否在向量 ab 的逆时针方向（左侧）
bool ccw(point a, point b, point c) {
    return crossProduct(a, b, c) < -EPSILON;
}

// 判断三点是否共线
bool collinear(point a, point b, point c) {
    return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 判断点 c 在向量 ab 的左侧或共线
bool ccwOrCollinear(point a, point b, point c) {
    return ccw(a, b, c) || collinear(a, b, c);
}

// 排序比较函数：先按 y 坐标升序，y 相同则按 x 坐标升序
bool lowerLeft(point a, point b) {
    return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// Andrew 凸包算法（单调链）
void andrewConvexHull(point vertex[], int number, polygon & hull) {
    // 1. 按 lowerLeft 规则排序
    sort(vertex, vertex + number, lowerLeft);
    point upper[MAX_VERTICES], lower[MAX_VERTICES];
    int top;
    // 2. 构造上凸包
    upper[0] = vertex[0];
    upper[1] = vertex[1];
    top = 2;
    for (int i = 2; i < number; i++) {
        upper[top] = vertex[i];
        // 当新点导致上凸包出现“右转”或“直行”时，删除栈顶的点
        while (top >= 2 && ccwOrCollinear(upper[top - 2], upper[top - 1], upper[top])) {
            upper[top - 1] = upper[top];
            top--;
        }
        top++;
    }
    // 将上凸包的点存入结果 hull
    hull.number = 0;
    for (int i = 0; i < top; i++) hull.vertex[hull.number++] = upper[i];
    // 3. 构造下凸包
    lower[0] = vertex[number - 1];
    lower[1] = vertex[number - 2];
    top = 2;
    for (int i = number - 3; i >= 0; i--) {
        lower[top] = vertex[i];
        // 同理，删除导致“右转”或“直行”的点
        while (top >= 2 && ccwOrCollinear(lower[top - 2], lower[top - 1], lower[top])) {
            lower[top - 1] = lower[top];
            top--;
        }
        top++;
    }
    // 将下凸包的点（去掉首尾，避免重复）加入结果 hull
    for (int i = 1; i < top - 1; i++) hull.vertex[hull.number++] = lower[i];
}

// 计算两点距离的平方（避免开方）
double distances(point a, point b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

// 根据余弦定理判断角 abc 是否为锐角。
// 对于角 ABC，边为 a = |B-C|, b = |A-C|, c = |A-B|。
// 余弦定理：cos(B) = (a^2 + c^2 - b^2) / (2ac)。
// 角 B 为锐角当且仅当 cos(B) > 0，即 a^2 + c^2 - b^2 > 0。
bool isAcuteAngle(point a, point b, point c) {
    double A = distances(b, c), B = distances(a, c), C = distances(a, b);
    return (A + C - B) > 0;
}

// 在凸包中寻找最小基线编号
int lowestNumber(polygon pg, point center, int number) {
    int minNumber = number; // 初始化为顶点总数（一个上界）
    for (int i = 0; i < pg.number; i++) {
        point p1 = pg.vertex[i];
        point p2 = pg.vertex[(i + 1) % pg.number];
        // 检查三个条件：
        // 1. 质心在凸包边的“上方”（cw 判断）
        // 2. 角 <center, p1, p2> 是锐角
        // 3. 角 <center, p2, p1> 是锐角
        if (cw(p1, p2, center) &&
            isAcuteAngle(p1, p2, center) &&
            isAcuteAngle(p2, p1, center)) {
            // 基线标识号为两个端点原始编号的较大值
            int lineNumber = max(p1.index, p2.index);
            minNumber = min(minNumber, lineNumber);
        }
    }
    return minNumber;
}

int main() {
    point tile[MAX_VERTICES], centerOfMass;
    polygon container;
    string name;
    // 循环读取每个物体，直到遇到 "#"
    while (cin >> name, name != "#") {
        cout << name; // 先输出名称
        cin >> centerOfMass.x >> centerOfMass.y;
        int x, y, number = 0;
        // 读取顶点，直到遇到 0 0
        while (cin >> x >> y, x || y) {
            // 存储顶点，并记录其原始序号（从1开始）
            tile[number] = (point){x, y, number + 1};
            number++;
        }
        // 计算顶点的凸包
        andrewConvexHull(tile, number, container);
        // 在凸包上寻找最小基线标识号并输出
        cout << " " << lowestNumber(container, centerOfMass, number) << endl;
    }
    return 0;
}
```
