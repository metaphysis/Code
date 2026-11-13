
> **摘要**：本题给定若干传感器的坐标与至多 $r$ 个收发器，要求确定最小的有效通信距离，使所有传感器能划分为不超过 $r$ 个连通组。核心思路是把传感器视为图的顶点，将问题转化为连通分量计数，利用通信距离增大时连通分量数不增的单调性二分答案，并用并查集快速判定可行性；全程比较距离平方以避免浮点误差，最终对结果开平方并向上取整。时间复杂度为 $O(m\log m+m\log U)$，其中 $m=\frac{n(n-1)}{2}$。


# 题目描述

农场中有若干个传感器，传感器都设置为相同的有效通信距离。两个传感器之间的距离不超过该通信距离时，它们可以直接通信。没有收发器的传感器必须通过直接或间接通信，将数据发送给某个装有收发器的传感器；装有收发器的传感器再将收集到的数据发送回基站。

给定收发器的数量以及每个传感器的位置，求使所有传感器的数据都能传到基站的最小有效通信距离，并向上取整。

# 输入格式

第一行包含测试用例数 $w$，满足 $1 \le w \le 10$。

每个测试用例首先给出收发器数量 $rt$，随后每行给出一个传感器的坐标 $X,Y$。坐标行以单独的 $-1$ 结束。农场是一个边长为 $100000$ 的正方形。

# 输出格式

对于每个测试用例，输出满足条件的最小有效通信距离的向上取整结果。

# 样例输入

```text
1
2
1 1
2 1
8 7
-1
```

# 样例输出

```text
1
```

# 题目分析

将传感器看作图的顶点。若两个传感器之间的欧几里得距离不超过有效通信距离，则在它们之间连一条边。这样，传感器之间的直接或间接通信关系对应图中的连通关系。

每个连通分量至少需要一个收发器，且一个收发器足以负责该连通分量内所有传感器的数据。因此，通信距离可行的充要条件是：按该距离建立的图中，连通分量数量不超过收发器数量 $rt$。

随着有效通信距离增大，图中的边只会增加，连通分量数量只会减少，所以可行性具有单调性。可以对距离的平方进行二分，并用并查集计算该距离下的连通分量数量。边权也使用距离平方，避免在判断阶段进行浮点运算。最终对最小可行距离开平方并向上取整。

# 解题思路

对于每一对传感器 $i$ 和 $j$，计算它们的距离平方：

$$
d_{i,j}^{2} = (x_i - x_j)^2 + (y_i - y_j)^2
$$

把所有传感器对构成的边按 $d_{i,j}^{2}$ 从小到大排序。设二分值为 $D$，仅考虑边权不超过 $D$ 的边，并使用并查集合并端点。每成功合并一次，连通分量数量减少 $1$；初始有 $n$ 个连通分量，因此合并后的数量为 $n-\textit{merged}$。当该数量不超过 $rt$ 时，$D$ 可行。

边权已排序，因此每次检查只需扫描边权不超过 $D$ 的边。二分的搜索范围为 $0$ 到 $2 \times 100000^2$，因为农场内任意两点的距离平方不超过该上界。找到最小可行的距离平方后，输出其平方根向上取整。

设传感器数量为 $n$，传感器对数量为 $m=\frac{n(n-1)}{2}$。构造边需要 $O(m)$ 时间，排序需要 $O(m\log m)$ 时间。二分过程中，每次检查扫描至多 $m$ 条边，因并查集使用路径压缩和按秩合并，单次操作的均摊复杂度为 $O(\alpha(n))$。因此总时间复杂度为 $O(m\log m + m\log U \cdot \alpha(n))$，其中 $U=2 \times 100000^2$；空间复杂度为 $O(m+n)$。

# 代码实现

```cpp
// The Bug Sensor Problem
// UVa ID: 1216
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010;

int parent[MAXV], ranks[MAXV];

struct edge
{
    int from, to;
    long long cost;
    edge (long long from = 0, int to = 0, long long cost = 0): from(from), to(to), cost(cost) {};
    bool operator<(const edge &e) const { return cost < e.cost; }
} edges[1000010];

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x, ranks[x]++;
        else parent[x] = y, ranks[y]++;
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, rt, n, m, x, y;
    long long xs[MAXV], ys[MAXV];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> rt;
        n = 0;
        while (cin >> x, x >= 0)
        {
            cin >> y;
            xs[n] = x, ys[n] = y;
            n++;
        }
        m = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges[m++] = edge(i, j, (xs[i] - xs[j]) * (xs[i] - xs[j]) + (ys[i] - ys[j]) * (ys[i] - ys[j]));

        sort(edges, edges + m);

        long long left = 0, right = 2 * 100000LL * 100000LL, middle;
        while (left <= right)
        {
            middle = (left + right) / 2;

            makeSet();
            int merged = 0;
            for (int i = 0; i < m; i++)
            {
                if (edges[i].cost <= middle)
                {
                    if (unionSet(edges[i].from, edges[i].to))
                    {
                        merged++;
                    }
                }
                else break;
            }
            if (n - merged <= rt)
                right = middle - 1;
            else
                left = middle + 1;
        }
        cout << (int)ceil(sqrt(left)) << '\n';
    }

    return 0;
}
```

# 总结

本题将几何通信条件转化为图的连通性问题。每个连通分量需要一个收发器，因此通过并查集统计分量数量即可判断给定距离是否可行。利用可行性随距离单调变化这一性质，对距离平方进行二分，最后开平方并向上取整得到答案。
