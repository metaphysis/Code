
> **摘要**：本题要求在二维平面上修建一条无限延伸的直线作为超级空间道路，使所有城市到该直线的加权距离平方和最小。普通情况下各城市权值相同；查询时指定一座城市为超级城市，其权值为普通城市的 $M$ 倍。文章将问题转化为带权点集的直线拟合，利用加权协方差矩阵的较小特征值给出最小平均火箭费用，并通过预处理坐标和、平方和与乘积和，实现 $O(N+Q)$ 的常数时间查询。

# 题目描述

在二维平面上有若干座城市，城市之间只能通过火箭运输。为了降低火箭运输成本，需要修建一条无限延伸的直线作为超级空间道路。

从城市 $i$ 出发时，火箭首先飞往该城市到超级空间道路的最近点，然后沿道路移动到目的城市对应的最近点，最后由火箭飞往目的城市。火箭飞行距离为城市到直线的垂直距离，飞行距离为 $d$ 时，火箭费用为：

$$
d^2
$$

普通情况下，每座城市的进出火箭数量相同。对于某次查询，指定一座城市为超级城市，该城市的进出火箭数量是普通城市的 $M$ 倍。

需要分别求出以下结果：

- 所有城市均为普通城市时，使平均火箭费用最小的超级空间道路及其最小平均费用。
- 每次指定超级城市及倍数 $M$ 后，使平均火箭费用最小的超级空间道路及其最小平均费用。

# 输入格式

输入包含多组测试数据。

每组测试数据的第一行包含两个整数 $N$ 和 $Q$：

- $N$ 表示城市数量，满足 $0 < N \le 10000$。
- $Q$ 表示查询数量，满足 $0 < Q \le 100$。

接下来 $N$ 行，每行包含两个浮点数 $x_i$ 和 $y_i$，表示第 $i$ 座城市的坐标，满足：

$$
0.0 \le x_i, y_i \le 1000.0
$$

城市编号按照输入顺序从 $0$ 开始。

接下来 $Q$ 行，每行包含两个整数 $S$ 和 $M$：

- $S$ 表示超级城市的编号。
- $M$ 表示超级城市的进出火箭数量是普通城市的 $M$ 倍。

输入以一行 `0 0` 结束，该行不需要处理。

# 输出格式

对于每组测试数据，输出 $Q + 2$ 行。

第一行输出：

```text
Case k:
```

其中 $k$ 表示测试数据编号。

第二行输出所有城市均为普通城市时的最小平均火箭费用。

接下来每行输出一个查询的结果，格式为：

```text
i: ans
```

其中 $i$ 表示查询编号，查询编号从 $1$ 开始，$ans$ 表示该查询对应的最小平均火箭费用。

所有浮点数均保留 $5$ 位小数。

# 样例输入

```text
5 2
464.9900 243.2652
463.9409 772.4632
201.9822 561.6255
695.8948 933.4567
226.0628 93.1435
3 2
4 3
4 2
27.1679 304.2512
27.7639 16.2479
921.9150 863.0064
167.6203 929.5471
2 2
2 3
0 0
```

# 样例输出

```text
Case 1:
16172.49971
1: 14289.23473
2: 11558.37654
Case 2:
53198.72595
1: 47995.33546
2: 41543.27604
```

# 题目分析

设超级空间道路为一条直线。对于城市 $i$，从该城市出发或到达该城市时，火箭都需要飞行到这条直线上的最近点，因此火箭飞行距离就是城市到直线的垂直距离。设该距离为 $d_i$，则城市 $i$ 对总火箭费用的贡献与 $d_i^2$ 成正比。

由于每座普通城市的进出火箭数量相同，所有普通城市在平均费用计算中具有相同权值。若城市 $S$ 是超级城市，且火箭数量是普通城市的 $M$ 倍，则可以将该城市的权值设置为 $M$，其他城市权值设置为 $1$。

因此，原问题转化为带权点集的直线拟合问题：

> 求一条直线，使所有城市到该直线的加权距离平方和最小。

设城市 $i$ 的权值为 $w_i$，所有权值之和为：

$$
W = \sum_i w_i
$$

如果直线方向确定为单位向量 $\boldsymbol{u}$，则与其垂直的单位向量记为 $\boldsymbol{v}$。城市点到直线的有符号垂直距离等于城市点在 $\boldsymbol{v}$ 方向上的投影，因此加权距离平方和可以表示为：

$$
\sum_i w_i \left(\boldsymbol{v} \cdot (\boldsymbol{p}_i - \boldsymbol{p}_0)\right)^2
$$

其中 $\boldsymbol{p}_i$ 表示城市坐标，$\boldsymbol{p}_0$ 表示直线上的一点。

对于固定的直线方向，直线经过加权中心时，距离平方和最小。加权中心为：

$$
\bar{x} = \frac{\sum_i w_i x_i}{W}
$$

$$
\bar{y} = \frac{\sum_i w_i y_i}{W}
$$

因此，最优直线一定经过所有城市的加权中心。

将每个城市平移到加权中心，定义加权协方差矩阵：

$$
C =
\begin{bmatrix}
a & b \\
b & c
\end{bmatrix}
$$

其中：

$$
a = \frac{\sum_i w_i(x_i-\bar{x})^2}{W}
$$

$$
b = \frac{\sum_i w_i(x_i-\bar{x})(y_i-\bar{y})}{W}
$$

$$
c = \frac{\sum_i w_i(y_i-\bar{y})^2}{W}
$$

若直线方向选择为协方差矩阵最大特征值对应的特征向量，则城市沿直线方向的离散程度最大，垂直于直线方向的离散程度最小。因此，城市到最优直线的加权平均距离平方等于矩阵 $C$ 的较小特征值。

矩阵 $C$ 的两个特征值为：

$$
\lambda =
\frac{a+c \pm \sqrt{(a-c)^2+4b^2}}{2}
$$

所以最小平均火箭费用为：

$$
\lambda_{\min}=
\frac{a+c-\sqrt{(a-c)^2+4b^2}}{2}
$$

直接按照上述公式计算即可得到答案。

# 解题思路

首先预处理所有城市在权值均为 $1$ 时的统计量：

$$
\sum x_i,\qquad
\sum y_i,\qquad
\sum x_i^2,\qquad
\sum y_i^2,\qquad
\sum x_i y_i
$$

根据这些统计量，可以在常数时间内求出加权中心和协方差矩阵。

对于普通情况，所有城市权值均为 $1$，直接使用预处理结果计算答案。

对于一次查询，设第 $S$ 座城市的权值从 $1$ 增加到 $M$，等价于为该城市额外增加权值：

$$
\Delta w = M - 1
$$

因此只需对预处理统计量进行增量修改：

$$
W' = W + \Delta w
$$

$$
X' = \sum x_i + \Delta w \cdot x_S
$$

$$
Y' = \sum y_i + \Delta w \cdot y_S
$$

$$
XX' = \sum x_i^2 + \Delta w \cdot x_S^2
$$

$$
YY' = \sum y_i^2 + \Delta w \cdot y_S^2
$$

$$
XY' = \sum x_i y_i + \Delta w \cdot x_S y_S
$$

然后使用修正后的统计量计算：

$$
\bar{x}' = \frac{X'}{W'},\qquad
\bar{y}' = \frac{Y'}{W'}
$$

$$
a = \frac{XX'}{W'} - (\bar{x}')^2
$$

$$
b = \frac{XY'}{W'} - \bar{x}'\bar{y}'
$$

$$
c = \frac{YY'}{W'} - (\bar{y}')^2
$$

最后代入较小特征值公式：

$$
\lambda_{\min}=
\frac{a+c-\sqrt{(a-c)^2+4b^2}}{2}
$$

每次查询只需要进行常数次运算，不需要重新遍历所有城市。

时间复杂度为：

$$
O(N+Q)
$$

其中，读取并预处理城市需要 $O(N)$，每个查询需要 $O(1)$。

空间复杂度为：

$$
O(N)
$$

因为需要保存所有城市坐标，以便查询时读取超级城市的坐标。

# 代码实现

```cpp
// Optimal Spaceway
// UVa ID: 12536
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

long double calcCost(long double sumWeight, long double sumX, long double sumY, long double sumXX, long double sumYY, long double sumXY) {
    long double meanX = sumX / sumWeight, meanY = sumY / sumWeight;
    long double varX = sumXX / sumWeight - meanX * meanX;
    long double varY = sumYY / sumWeight - meanY * meanY;
    long double covXY = sumXY / sumWeight - meanX * meanY;
    long double diff = varX - varY, cost = (varX + varY - sqrtl(diff * diff + 4.0L * covXY * covXY)) / 2.0L;
    if (cost < 0) cost = 0;
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, caseId = 0;
    while (cin >> n >> q) {
        if (n == 0 && q == 0) break;
        vector<Point> cities(n);
        long double sumWeight = n, sumX = 0, sumY = 0, sumXX = 0, sumYY = 0, sumXY = 0;
        for (int i = 0; i < n; i++) {
            long double x, y;
            cin >> x >> y;
            cities[i] = {x, y};
            sumX += x;
            sumY += y;
            sumXX += x * x;
            sumYY += y * y;
            sumXY += x * y;
        }
        cout << "Case " << ++caseId << ":\n";
        cout << fixed << setprecision(5) << calcCost(sumWeight, sumX, sumY, sumXX, sumYY, sumXY) << '\n';
        for (int i = 1; i <= q; i++) {
            int s, m;
            cin >> s >> m;
            long double extra = m - 1.0L;
            long double queryWeight = sumWeight + extra;
            long double queryX = sumX + extra * cities[s].x;
            long double queryY = sumY + extra * cities[s].y;
            long double queryXX = sumXX + extra * cities[s].x * cities[s].x;
            long double queryYY = sumYY + extra * cities[s].y * cities[s].y;
            long double queryXY = sumXY + extra * cities[s].x * cities[s].y;
            cout << i << ": " << calcCost(queryWeight, queryX, queryY, queryXX, queryYY, queryXY) << '\n';
        }
    }
    return 0;
}
```

# 总结

本题的核心是将“寻找使点到直线距离平方和最小的直线”转化为二维协方差矩阵的特征值问题。

关键结论如下：

- 最优直线一定经过城市的加权中心。
- 最优直线方向是协方差矩阵最大特征值对应的特征向量。
- 最小平均火箭费用等于协方差矩阵的较小特征值。
- 超级城市只会使一个城市的权值增加 $M-1$。
- 通过维护坐标和、平方和以及乘积和，可以在 $O(1)$ 时间内完成每次查询。
- 使用 `long double` 进行计算能够降低浮点误差，满足题目的精度要求。
