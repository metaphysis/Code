
> **摘要**：本题要求判断一个点是否会被按科赫雪花规则生长的分形细菌覆盖，并给出最早被覆盖的天数（上限 $14$ 天）。由于分形区域具有单调扩张与严格自相似性，直接枚举小三角形会指数爆炸；本文利用叉积快速排除、三等分点与外侧顶点构造，以及投影比例定位唯一子分支，将判定转化为深度不超过 $13$ 的递归，时间复杂度 $O(N)$，空间复杂度 $O(1)$。

## 题目描述

一种分形细菌正在快速生长，其形态遵循著名的科赫雪花（$\texttt{Koch Snowflake}$）构造规则。  
第 $1$ 天，细菌占据一个等边三角形区域。  
第 $2$ 天，在初始三角形的每条边上，取中间三分之一段，向外（即该边外侧）构造一个新的等边三角形，其边长为原边长的 $1/3$。  
之后每一天，都在当前所有线段的中间三分之一段上重复同样的操作。

科学家预计在第 $14$ 天（含）内可研制出药物。若细菌在第 $14$ 天之前到达你的位置，则你被摧毁；否则你安全。

给定初始等边三角形的三个顶点坐标以及你的位置坐标，判断你是否安全，若被摧毁则输出最早到达的天数。

## 输入格式

第一行包含一个整数 $N$（$0<N<6001$），表示测试用例数。  
接下来 $N$ 行，每行包含 $8$ 个浮点数：  
$x_1, y_1, x_2, y_2, x_3, y_3, x, y$  
其中 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$ 为第 $1$ 天三角形的三个顶点（按任意顺序给出），$(x,y)$ 为你的位置。  
所有坐标绝对值不超过 $400000$，输入浮点数保留 $10$ 位小数。

## 输出格式

对于每个测试用例，输出一行。  
若细菌在第 $d$ 天（$1 \le d \le 14$）首次到达你的位置，则输出：  
`The bacterium destroys you within day d. ESCAPE!!`  
其中 $d$ 为具体天数。  
若第 $14$ 天结束时仍未到达，则输出：  
`You are safe :)`  

保证程序永远不会输出大于 $14$ 的数，但可以输出 $14$。

## 样例

### 样例输入

```text
3
45233.0000000000 149056.0000000000 146297.0000000000 75838.0000000000 159173.6480142890 199970.9914080705 68004.3137563194 159230.3729762797
43726.0000000000 134821.0000000000 196858.0000000000 195926.0000000000 67373.5177017519 297989.7021323186 33994.5456040129 164685.1050602284
149787.0000000000 67376.0000000000 39536.0000000000 17919.0000000000 137492.5183949670 -52832.6667926381 58599.6651155748 35914.0994623880
```

### 样例输出

```text
The bacterium destroys you within day 1. ESCAPE!!
The bacterium destroys you within day 3. ESCAPE!!
The bacterium destroys you within day 5. ESCAPE!!
```

## 题目分析

科赫雪花的生长过程具有**单调扩张**性质，即第 $d+1$ 天的区域包含第 $d$ 天的区域。因此，若某个点被细菌覆盖，它首次被覆盖的天数等于最小的 $d$，使得该点属于第 $d$ 天的区域。

第 $1$ 天的区域就是初始三角形。从第 $2$ 天开始，每条边都会向外“生长”出耳朵形状的连续区域，这些耳朵区域本身又由更小的耳朵嵌套构成，形成严格的自相似结构。直接枚举所有小三角形（数量按指数增长）不可行，必须利用递归判定。

关键观察：对于任意一条边 $AB$，其外侧耳朵区域（相对于第三个顶点 $C$）是一个由该边向外凸出的分形区域。该区域可划分为若干个互不重叠的子区域，且每个子区域都与原耳朵具有相同的形状，只是边长缩小为原来的 $1/3$。因此，判定一个点是否在耳朵区域内，可以通过递归定位其所属的子区域，每次递归深度减 $1$，最终深度降到 $1$ 时只需检查一个基本三角形。

由于每次递归只进入唯一可能的分支，判定时间复杂度与深度成正比，最大深度为 $13$，完全可以接受。

## 解题思路

定义函数 $\texttt{inEar}(P, A, B, C, k)$，判定点 $P$ 是否位于由线段 $AB$ 向外生长、迭代 $k$ 次后的耳朵区域内。其中 $C$ 是初始三角形中与 $AB$ 相对的顶点，用于确定外侧方向。参数 $k$ 表示该线段上还需要进行的迭代次数，对于第 $d$ 天，$k = d - 1$。

判定过程按以下步骤进行：

步骤 $\texttt{1}$. 若 $k \le 0$，耳朵区域为空，直接返回假。

步骤 $\texttt{2}$. 快速排除：计算叉积 $\text{cross}(A, B, C)$ 与 $\text{cross}(A, B, P)$。若两者同号（即 $P$ 与 $C$ 位于 $AB$ 同侧），则 $P$ 不可能在向外生长的耳朵区域内，直接返回假。

步骤 $\texttt{3}$. 计算 $AB$ 的三等分点 $A_1$、$B_1$（$A_1$ 靠近 $A$，$B_1$ 靠近 $B$），并构造向外侧的外接等边三角形顶点 $D$。若 $P$ 位于三角形 $A_1B_1D$ 内，则 $P$ 在耳朵区域内，返回真。

步骤 $\texttt{4}$. 若 $k = 1$，没有更深的迭代，返回假。

步骤 $\texttt{5}$. 否则，根据 $P$ 在 $AB$ 方向上的投影比例 $t = \frac{(P-A)\cdot(B-A)}{|AB|^2}$，将 $P$ 定位到四个子线段之一：

- 若 $t < \frac13$，$P$ 可能属于子线段 $A A_1$，递归调用 $\texttt{inEar}(P, A, A_1, C, k-1)$。
- 若 $t > \frac23$，$P$ 可能属于子线段 $B_1 B$，递归调用 $\texttt{inEar}(P, B_1, B, C, k-1)$。
- 若 $\frac13 \le t \le \frac23$，$P$ 位于中间区域，进一步判断：
  - 若 $P$ 在边 $A_1D$ 的外侧（相对于参考点 $B_1$），则递归调用 $\texttt{inEar}(P, A_1, D, B_1, k-1)$；
  - 否则若 $P$ 在边 $DB_1$ 的外侧（相对于参考点 $A_1$），则递归调用 $\texttt{inEar}(P, D, B_1, A_1, k-1)$；
  - 否则 $P$ 不在任何耳朵分支内，返回假。

上述选择唯一分支，避免了指数级搜索。

对于每个测试用例，先检查点是否在第 $1$ 天的初始三角形内；若不是，则从第 $2$ 天到第 $14$ 天依次判定，对三条边分别调用 $\texttt{inEar}$ 函数，一旦某一天成立，即输出该天数并结束；若 $14$ 天都不成立，则输出安全。

## 代码实现

```cpp
// Escaping from Fractal Bacterium
// UVa ID: 11422
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

inline double cross(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

inline double dot(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.x - A.x) + (B.y - A.y) * (C.y - A.y);
}

bool pointInTriangle(const Point& P, const Point& A, const Point& B, const Point& C) {
    double d1 = cross(A, B, P);
    double d2 = cross(B, C, P);
    double d3 = cross(C, A, P);
    bool hasPos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
    bool hasNeg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    return !(hasPos && hasNeg);
}

bool inEar(const Point& P, const Point& A, const Point& B, const Point& C, int depth) {
    if (depth <= 0) return false;
    double crAB_C = cross(A, B, C);
    double crAB_P = cross(A, B, P);
    if (crAB_C * crAB_P > EPS) return false;
    Point A1, B1;
    A1.x = (2.0 * A.x + B.x) / 3.0;
    A1.y = (2.0 * A.y + B.y) / 3.0;
    B1.x = (A.x + 2.0 * B.x) / 3.0;
    B1.y = (A.y + 2.0 * B.y) / 3.0;
    double dx = B.x - A.x, dy = B.y - A.y;
    double len = hypot(dx, dy);
    double ux = dx / len, uy = dy / len;
    double nx = -uy, ny = ux;
    double sign = (crAB_C > 0) ? 1.0 : -1.0;
    nx = -sign * nx;
    ny = -sign * ny;
    Point M;
    M.x = (A1.x + B1.x) / 2.0;
    M.y = (A1.y + B1.y) / 2.0;
    double h = len * sqrt(3.0) / 6.0;
    Point D;
    D.x = M.x + nx * h;
    D.y = M.y + ny * h;
    if (pointInTriangle(P, A1, B1, D)) return true;
    if (depth == 1) return false;
    double t = dot(A, B, P) / (len * len);
    if (t < 1.0/3.0 - EPS) {
        return inEar(P, A, A1, C, depth - 1);
    } else if (t > 2.0/3.0 + EPS) {
        return inEar(P, B1, B, C, depth - 1);
    } else {
        if (cross(A1, D, B1) * cross(A1, D, P) < -EPS) return inEar(P, A1, D, B1, depth - 1);
        if (cross(D, B1, A1) * cross(D, B1, P) < -EPS) return inEar(P, D, B1, A1, depth - 1);
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        Point A, B, C, P;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> P.x >> P.y;
        if (pointInTriangle(P, A, B, C)) {
            cout << "The bacterium destroys you within day 1. ESCAPE!!\n";
            continue;
        }
        int ans = -1;
        for (int d = 2; d <= 14; ++d) {
            int depth = d - 1;
            if (inEar(P, A, B, C, depth) ||
                inEar(P, B, C, A, depth) ||
                inEar(P, C, A, B, depth)) {
                ans = d;
                break;
            }
        }
        if (ans == -1) cout << "You are safe :)\n";
        else cout << "The bacterium destroys you within day " << ans << ". ESCAPE!!\n";
    }
    return 0;
}
```

## 总结

本题核心在于利用分形的自相似性构造递归判定函数，并通过投影快速定位唯一分支，从而将指数级搜索降为线性深度搜索。  
关键技巧包括：

- 利用叉积判断点的内外侧关系；
- 三等分点与外侧顶点的几何构造；
- 投影比例 $t$ 将点映射到对应的子线段，避免分支爆炸。

时间复杂度为 $O(N \times 3 \times 14)$，即 $O(N)$，空间复杂度 $O(1)$。该算法在 $N=6000$ 时能高效运行，完全满足题目要求。  
递归深度仅为 $13$，即使不考虑优化，单次判定也仅需常数次几何运算，代码简洁且鲁棒。
