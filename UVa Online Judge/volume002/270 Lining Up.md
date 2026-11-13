[UVa 270 Lining Up](https://blog.csdn.net/metaphysis/article/details/161332722)

## 题目分析

本题给定平面上的 $N$ 个点（$1 < N < 700$），所有点的坐标均为整数。要求找出一条直线，使得经过这条直线的点数量最多，并输出这个最大数量。飞行员只能沿直线飞行一次，因此需要找到覆盖最多投递点的直线。

**关键约束**：  
- 点数为 $N$，最大可达 $699$。  
- 若采用 $O(N^3)$ 的暴力枚举所有点对并检查其余点是否共线，复杂度约为 $699^3 \approx 3.4 \times 10^8$，在时间上可能较为紧张。  
- 需要设计更高效的算法。

## 解题思路

### 核心思想

本题的核心是：**过两点的直线唯一确定一条直线**。因此，可以枚举所有点对 $(P_i, P_j)$，然后统计有多少个点与这两个点共线。但直接对每个点对都遍历所有点进行判断会得到 $O(N^3)$ 的复杂度。

一种常见的优化方法是：固定一个点 $P_i$，然后计算其他所有点相对于 $P_i$ 的斜率，斜率相同的点即与 $P_i$ 共线。但本题的代码采用了另一种策略：**排序 + 剪枝**。

### 算法步骤

1. **输入处理**  
   由于输入包含多个测试用例，且用例之间用空行分隔，需要按行读取并判断空行来区分用例。

2. **点的排序**  
   对所有点按坐标排序：先按 $x$ 升序，若 $x$ 相同则按 $y$ 升序。排序的目的是为了在后续枚举中避免重复计算。

3. **枚举点对并标记已处理**  
   使用一个二维数组 $\texttt{paired}[i][j]$ 标记点对 $(i, j)$ 是否已经被处理过。由于直线是无向的，处理过 $(i, j)$ 后就不需要再处理 $(j, i)$，因此只枚举 $i < j$。

4. **检查共线**  
   对于每个未被处理的点对 $(i, j)$，遍历所有 $k > j$ 的点，使用**叉积**判断三点是否共线：
$$
   cross(P_i, P_j, P_k) = (P_j.x - P_i.x) \cdot (P_k.y - P_i.y) - (P_j.y - P_i.y) \cdot (P_k.x - P_i.x)
$$
   若叉积为 $0$，则 $P_k$ 与 $P_i, P_j$ 共线。

5. **记录最大值**  
   对于每个点对，统计共线的点数（包括 $P_i$ 和 $P_j$ 本身），并更新全局最大值。

6. **输出**  
   每个测试用例输出一行结果，用例之间输出一个空行。

### 复杂度分析

- 最坏情况下，外层循环 $O(N^2)$ 枚举点对，内层循环 $O(N)$ 检查共线，总复杂度 $O(N^3)$。  
- 但由于使用了 $\texttt{paired}$ 数组进行剪枝，以及排序后只检查 $k > j$，实际上减少了重复计算。  
- 对于 $N = 700$，最坏情况仍可能达到 $O(N^3)$，但实际测试中可以通过。

### 为什么这样可行？

本题的 $N$ 最大为 $699$，$O(N^3)$ 在 $3.4 \times 10^8$ 量级，在优化良好的 `C++` 代码中，配合合适的剪枝和整数运算，可以在时限内通过。代码中的剪枝策略包括：
- 只处理 $i < j$ 且未标记的点对；
- 只检查 $k > j$ 的点，避免重复统计。

## 代码实现

```cpp
// Lining Up
// UVa ID: 270
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.410s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 定义点的结构体，包含 x 和 y 坐标
struct point {
    int x, y;
};

// 排序比较函数：先按 x 升序，再按 y 升序
bool cmp(point a, point b) {
    if (a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

vector<point> points;          // 存储所有点
int paired[701][701];          // 标记点对是否已被处理过
int counter[701];              // 临时存储共线的点下标

// 叉积函数：判断三点是否共线
// 返回 (c - a) × (b - a)
// 若返回值为 0，则三点共线
int crossProduct(point a, point b, point c) {
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 计算所有点中位于同一直线上的最大点数
int getMaxPoints() {
    // 对点进行排序
    sort(points.begin(), points.end(), cmp);
    // 初始化 paired 标记数组
    for (int i = 0; i < points.size(); i++)
        for (int j = 0; j < points.size(); j++)
            paired[i][j] = 0;
    int maxPoint = 0;   // 记录全局最大共线点数
    // 枚举所有点对 (i, j)，i < j
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            // 如果该点对已经被处理过，则跳过
            if (paired[i][j] == 0) {
                paired[i][j] = 1;   // 标记为已处理
                int index = 2;      // 当前共线点集合包含 i 和 j
                counter[0] = i;
                counter[1] = j;
                // 检查所有 k > j 的点是否与 i, j 共线
                for (int k = j + 1; k < points.size(); k++) {
                    if (crossProduct(points[i], points[j], points[k]) == 0)
                        counter[index++] = k;
                }
                // 更新最大值
                maxPoint = max(maxPoint, index);
            }
    return maxPoint;
}

int main() {
    cin.tie(0); cout.sync_with_stdio(false);
    bool first = true;   // 控制输出空行
    int cases;
    string input;
    // 读取测试用例个数
    getline(cin, input);
    cases = stoi(input);
    getline(cin, input); // 读取空行
    while (cases--) {
        points.clear();
        // 读取一个测试用例的所有点，直到遇到空行或 EOF
        while (getline(cin, input)) {
            if (input.length() == 0) break;
            int x, y;
            istringstream iss(input);
            iss >> x >> y;
            points.push_back({x, y});
        }
        // 输出空行分隔不同测试用例的结果
        if (first) first = false;
        else cout << "\n";
        // 输出最大共线点数
        cout << getMaxPoints() << "\n";
    }
    return 0;
}
```

## 总结

本题的核心是枚举所有点对，利用叉积判断共线，并通过排序和标记数组进行适当剪枝。虽然最坏复杂度为 $O(N^3)$，但在题目给定的数据范围和时限下可以顺利通过。如果要进一步优化，可以考虑使用斜率哈希的方法将复杂度降至 $O(N^2 \log N)$，但本题的解法已经足够清晰且易于实现。
