[UVa 216 Getting in Line](https://blog.csdn.net/metaphysis/article/details/161046927)

## 题目分析

题目要求在平面上给定 $n$ 个点（$2 \leq n \leq 8$），将它们连成一条链（线性网络），使得链的总长度最小。需要注意的是，每段连接电缆的长度不是两点之间的欧几里得距离，而是距离 $+ 16$ 英尺（用于连接地板到计算机以及安装余量）。

输入包含多个数据集，每个数据集第一行为计算机数量 $n$，接下来 $n$ 行每行为一个计算机的坐标（整数，$0$ 到 $150$ 之间）。以 $n = 0$ 结束输入。

输出要求：对于每个数据集，先输出网络编号，然后按照链的顺序输出每段电缆的长度（保留两位小数），最后输出总电缆长度。不同数据集之间用 `*` 分隔。

## 解题思路

由于 $n \leq 8$，可以使用全排列枚举所有可能的连接顺序。对于每种排列，计算相邻点之间的欧氏距离加上 $16$ 后累加，取最小值即为最优方案。

具体步骤：
1. 预处理所有点对之间的欧几里得距离，存入矩阵 `matrix[i][j]`。
2. 生成 $0$ 到 $n-1$ 的全排列，每个排列表示访问点的顺序。
3. 对每个排列计算总长度：`sum(matrix[perm[i]][perm[i+1]])`。
4. 记录总长度最小的排列，并保存该排列。
5. 输出时，按最优排列的顺序输出每段电缆的长度（距离 $+ 16$）以及总和。

时间复杂度为 $O(n! \cdot n)$，$n \leq 8$ 时完全可行。

---

## 代码实现

```cpp
// Getting in Line
// UVa ID: 216
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 点的结构体，存储坐标
struct point {
    int x, y;
};

vector<point> network;          // 存储所有计算机的坐标
int cases = 0, computers;       // cases 为网络编号，computers 为计算机数量
double matrix[8][8];            // 存储点对之间的欧氏距离

// 计算两点之间的欧氏距离
double distances(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 计算并输出当前数据集的最优布线方案
void calculate() {
    // 预处理所有点对之间的距离
    for (int i = 0; i < computers; i++)
        for (int j = 0; j < computers; j++)
            matrix[i][j] = distances(network[i], network[j]);
            
    // 初始化排列为 0, 1, 2, ..., computers-1
    vector<int> permutation;
    for (int i = 0; i < computers; i++)
        permutation.push_back(i);
    
    // best 用于存储最优排列，minimum 存储当前找到的最小总长度
    vector<int> best(permutation.size());
    double minimum = numeric_limits<int>::max();
    
    // 枚举所有全排列
    do
    {
        double currentLength = 0.0;
        // 计算当前排列下相邻点之间的欧氏距离之和
        for (int i = 0; i < computers - 1; i++)
            currentLength += matrix[permutation[i]][permutation[i + 1]];
        // 更新最优解
        if (currentLength < minimum)
        {
            minimum = currentLength;
            copy(permutation.begin(), permutation.end(), best.begin());
        }
    } while (next_permutation(permutation.begin(), permutation.end()));

    cases++;    // 网络编号递增
    
    // 输出结果
    cout << "**********************************************************" << endl;
    cout << "Network #" << cases << endl;
    double length = 0.0;
    for (int i = 0; i < best.size() - 1; i++)
    {
        cout << "Cable requirement to connect (";
        cout << network[best[i]].x << "," << network[best[i]].y << ") to (";
        cout << network[best[i + 1]].x << "," << network[best[i + 1]].y << ") is ";
        // 每条电缆长度 = 欧氏距离 + 16
        double cable = matrix[best[i]][best[i + 1]] + 16.0;
        cout << fixed << setprecision(2) << cable;
        cout << " feet." << endl;
        length += cable;
    }
    
    cout << "Number of feet of cable required is ";
    cout << fixed << setprecision(2) << length;
    cout << "." << endl;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    while (cin >> computers, computers)
    {
        network.clear();
        // 读取每个计算机的坐标
        for (int i = 1; i <= computers; i++)
        {
            point dot;
            cin >> dot.x >> dot.y;
            network.push_back(dot);
        }
        calculate();
    }
    
	return 0;
}
```

---

## 总结

本题的核心是枚举全排列求解旅行商问题的朴素解法，由于数据量小，直接枚举即可。需要注意两点：
- 电缆长度计算公式为 $distance + 16$，而非单纯的距离。
- 输出格式要求严格，每个网络输出前有一行 `*` 分隔，且每段电缆和总长度均保留两位小数。
