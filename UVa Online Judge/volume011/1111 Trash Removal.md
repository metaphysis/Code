
> **摘要**：给定一个简单多边形，求能让它通过的最小管道宽度。核心思路是把旋转通过问题转化为覆盖全部顶点的最窄平行带问题，利用最优平行带的一条边界必与凸包边重合的性质，将连续方向搜索转化为枚举所有顶点对，用叉积判断顶点所在侧并累加两侧最大距离，时间复杂度 $O(n^3)$，并配合提前结束扫描优化。

 # 题目描述

给定一个简单多边形，求能够让它通过的垃圾管道的最小宽度。管道在二维平面中表示为两条竖直且相互平行的直线之间的区域，宽度始终保持不变。多边形在进入管道之前能够任意旋转，进入管道后只能沿竖直方向平移，不能继续旋转。因此，需要选择合适的旋转角度，使整个多边形能够放入宽度最小的平行带中。

# 输入格式

输入包含多组测试数据。每组数据首先给出一个整数 $n$，表示多边形的顶点数，满足 $3 \le n \le 100$。接下来 $n$ 行，每行给出两个整数 $x_i$ 和 $y_i$，表示按照多边形边界顺序排列的顶点坐标，满足 $0 \le x_i,y_i \le 10^4$。同一组数据中的所有顶点互不相同，多边形的边除相邻边共享端点外不存在交点。

当读入的 $n = 0$ 时，输入结束，该行不属于任何一组测试数据。

# 输出格式

对于每组测试数据，输出测试编号及能够容纳该多边形的最小管道宽度，格式参照样例。测试编号从 $1$ 开始。

题目要求结果保留 $2$ 位小数，并向上取整到最接近的 $\frac{1}{100}$ 的整数倍。设精确答案为 $w$，对应的输出数值为：
$$
\frac{\lceil 100w\rceil}{100}
$$
评测接受与上述取整结果相差不超过 $\frac{1}{100}$ 的答案。所附通过代码直接使用固定小数格式保留 $2$ 位小数，没有显式执行向上取整；这一实现利用了题目允许的误差范围。

# 样例输入

```text
3
0 0
3 0
0 4
4
0 10
10 0
20 10
10 20
0
```

# 样例输出

```text
Case 1: 2.40
Case 2: 14.15
```

# 题目分析

多边形进入管道后只能沿管道方向平移，因此决定能否通过的关键是多边形在垂直于管道方向上的投影长度。对于一个确定的放置角度，只要多边形的所有顶点都位于两条管道边界之间，它的每条边和整个内部区域也都位于这个平行带内。于是，问题转化为：在所有方向中，寻找能够覆盖全部顶点的最窄平行带。

多边形的凹陷不会影响所需宽度，因为平行带是凸集，包含所有顶点的平行带也必然包含这些顶点的凸包。因此，原多边形与其凸包的最小宽度相同。凸多边形的最小宽度存在一个取得最优值的方向，使平行带的一条边界与某条凸包边重合。这个性质将连续的方向选择转化为有限的边方向枚举。

这一性质能够通过投影函数说明。设单位法向量为 $\boldsymbol{u}(\theta)=(\cos\theta,\sin\theta)$，某个方向上的宽度为：
$$
w(\theta)=\max_i\bigl(P_i\cdot\boldsymbol{u}(\theta)\bigr)-\min_i\bigl(P_i\cdot\boldsymbol{u}(\theta)\bigr)
$$
在取得最大投影和最小投影的顶点保持不变的一段角度区间内，设这两个顶点分别为 $P_a$ 和 $P_b$，则存在常数 $A$、$B$，使得：
$$
w(\theta)=(P_a-P_b)\cdot\boldsymbol{u}(\theta)
=A\cos\theta+B\sin\theta
$$
对于非退化多边形，宽度为正，因此：
$$
w''(\theta)=-w(\theta)<0
$$
这说明宽度函数在该区间内严格凹，最小值出现在区间端点。端点对应某个极值投影由多个顶点共同取得，此时相应支撑线包含一条凸包边。因此，枚举凸包边的方向就能覆盖最优方向。若所有顶点共线，沿这条直线设置平行带即可得到宽度 $0$，同样能够通过枚举顶点对得到。

通过代码没有显式构建凸包，而是枚举所有不同顶点组成的直线。每条凸包边的两个端点都在原顶点集合中，因此这种枚举一定包含最优方向。对于一条经过两个顶点的直线，分别求出两侧顶点到直线的最大距离，再将这两个距离相加，就得到该方向上覆盖整个多边形所需的宽度。需要注意，枚举直线能够穿过多边形内部，因此不能只取所有顶点到直线距离的最大值，必须累计两侧各自的最大距离。

# 解题思路

设当前枚举的两个顶点为 $P_i$ 和 $P_j$，它们确定直线 $L$。对于任意顶点 $P_k$，先计算有向叉积：
$$
s_k=(P_j-P_i)\times(P_k-P_i)
$$
叉积的正负表示顶点位于直线的哪一侧，绝对值则用于计算点到直线的距离：
$$
d_k=\frac{|s_k|}{\lVert P_j-P_i\rVert}
$$
所有顶点互不相同，且枚举时满足 $i<j$，因此分母始终大于 $0$。按照代码的分组方式，分别维护负叉积一侧的最大距离 $L_{\max}$，以及非负叉积一侧的最大距离 $R_{\max}$。位于直线上的顶点距离为 $0$，归入任意一侧都不影响结果。虽然代码中的 $\texttt{maxLeft}$ 对应负叉积一侧，但变量命名不影响计算，两侧的处理完全对称。

以 $L$ 为基准，在两侧分别平移距离 $L_{\max}$ 和 $R_{\max}$，得到的两条平行线能够夹住所有顶点。由于两侧最远的顶点都必须被包含，任意相同方向的平行带都至少需要这么宽，因此当前方向的最小宽度恰好为：
$$
W_{i,j}=L_{\max}+R_{\max}
$$
遍历所有顶点对，取其中的最小值：
$$
\mathrm{ans}=\min_{0\le i<j<n}W_{i,j}
$$
每个 $W_{i,j}$ 都对应一个实际能够容纳多边形的平行带，因此不会小于全局最优宽度；同时，枚举范围包含全部凸包边方向，必然存在一个候选方向达到全局最优宽度。由此可知，最终得到的最小值就是答案。

代码还使用了提前结束扫描的优化。在处理当前直线时，随着更多顶点被检查，两侧最大距离都只会保持不变或增大。因此，一旦当前的 $L_{\max}+R_{\max}$ 已经大于已知最优答案，继续扫描也无法得到更好的结果，直接结束当前直线的检查即可。此时用于更新答案的部分和已经大于已有答案，因此不会错误地改变最终结果。

每组数据共枚举 $\frac{n(n-1)}{2}$ 对顶点，每对顶点至多扫描 $n$ 个顶点，最坏时间复杂度为 $O(n^3)$。存储顶点需要 $O(n)$ 空间，其余计算只使用常数个辅助变量，因此按顶点数量分析，空间复杂度为 $O(n)$；所附代码使用固定容量数组，在题目给定范围内占用固定大小的存储空间。

# 代码实现

代码中的 $\texttt{cross}$ 计算叉积，$\texttt{cw}$ 根据叉积符号判断顶点所在的一侧，$\texttt{getDistPL}$ 计算点到直线的距离。主程序枚举所有顶点对，维护两侧最大距离之和，并取全局最小值。

输出部分保留原通过代码的行为，使用 $\texttt{fixed}$ 和 $\texttt{setprecision}$ 保留 $2$ 位小数。普通四舍五入的结果与题目要求的向上取整结果最多相差 $\frac{1}{100}$，符合题目允许的误差。例如，样例中菱形的精确最小宽度为 $10\sqrt{2}$，题面样例输出为 $14.15$，这份代码输出为 $14.14$，两者的差为 $\frac{1}{100}$。以下保留原有代码逻辑和全部注释，仅调整缩进并去除函数体内的空行。

```cpp
// Trash Removal
// UVa ID: 1111
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.120s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };
}vertices[110];

double norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < 0;
}

double getDistPL(point p, point p1, point p2)
{
    return fabs(cross(p2 - p1, p - p1) / abs(p2 - p1));
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> vertices[i].x >> vertices[i].y;
        }
        double mostH = 1e9;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                double maxLeft = 0, maxRight = 0;
                for (int k = 0; k < n; k++)
                {
                    double h = getDistPL(vertices[k], vertices[i], vertices[j]);
                    if (cw(vertices[i], vertices[j], vertices[k]))
                        maxLeft = max(maxLeft, h);
                    else
                        maxRight = max(maxRight, h);
                    if (maxLeft + maxRight > mostH) break;
                }
                mostH = min(mostH, maxLeft + maxRight);
            }
        cout << "Case " << ++cases << ": " << fixed << setprecision(2) << mostH << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是把旋转多边形通过管道的问题转化为覆盖全部顶点的最窄平行带问题，再利用最优平行带的一条边界能够与凸包边重合的性质，将连续方向搜索转化为有限枚举。由于顶点数量较少，直接枚举所有顶点对即可覆盖全部必要方向，无须显式构建凸包。对于每个方向，使用叉积判断顶点所在的一侧，并将两侧最大距离相加得到宽度，最终以 $O(n^3)$ 的时间复杂度求出答案。两侧最大距离的单调性支持提前结束无效扫描，而输出格式则需要结合题目明确给出的误差容限理解。
