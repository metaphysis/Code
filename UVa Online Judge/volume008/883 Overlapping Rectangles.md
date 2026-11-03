
> **摘要**：本文讨论二维平面上轴对齐矩形与水平直线的重叠问题：给定若干矩形与多条水平线，求每条水平线从左到右第一次出现的最大重叠深度及其对应区间。文章将二维问题降维为一维区间上的深度函数，采用事件扫描法（左端点 +1、右端点 -1）配合排序顺序扫描，在 $O(\textit{NL} \cdot \textit{NR} \log \textit{NR})$ 时间内求解，并给出完整 C++ 实现与正确性、复杂度分析。

## 题目描述

给定二维平面上的一组轴对齐矩形，它们相互重叠（也可能不重叠），形成若干区域。  
每个区域有一个**重叠深度**（$\textit{OD}$），定义为覆盖该区域的矩形个数。  
现有一条水平直线 $y = y_L$，从左到右穿过这些矩形，会依次扫过一系列 $\textit{OD}$ 值（可能重复）。  
要求找出从左到右第一次出现的**最大 $\textit{OD}$ 值**（记为 $\textit{OD}_{\textit{FM}}$），并输出该最大值所对应的连续区间的左边界 $x_{\textit{Left}}$ 和右边界 $x_{\textit{Right}}$。  
题目保证矩形的边之间、边与水平线之间没有重合，从而避免数值问题。

## 输入格式

第一行包含一个正整数，表示测试用例的个数。  
每个测试用例的格式如下：

- 第一行：一个整数 $\textit{NR}$（$1 \le \textit{NR} \le 10^4$），表示矩形的个数。  
- 接下来 $\textit{NR}$ 行，每行包含四个实数（整数或小数）：$x_1, y_1, x_2, y_2$，表示矩形的两个对角顶点坐标。坐标绝对值不超过 $10^6$。  
- 接下来一行：一个整数 $\textit{NL}$（$1 \le \textit{NL} \le 10^4$），表示水平线的条数。  
- 接下来 $\textit{NL}$ 行，每行一个实数 $y_L$，表示水平线的纵坐标。

## 输出格式

对于每个测试用例，输出 $\textit{NL}$ 行，每行对应一条输入顺序的水平线。  
若该水平线不穿过任何矩形，则只输出一个整数 `0`。  
否则，输出三个值：$\textit{OD}_{\textit{FM}}$（整数），$x_{\text{Left}}$ 和 $x_{\text{Right}}$（保留两位小数），三者之间用空格分隔。  
两个测试用例的输出之间用一个空行隔开。

## 样例

输入

```
1

3
-5.00 -2.00 -1.00 2.0
2.5 -1 -4.5 1.0
4 3 0 -4
4
-0.2
-4.50
-3.8
1.50
```

输出

```
2 - 4.50 - 1.00
0
1 0.00 4.00
1 - 5.00 1.00
```

## 题目分析

对于一条固定的水平线 $y = y_L$，一个矩形如果满足 $y_{\min} < y_L < y_{\max}$，则它与该水平线的交集为一个开区间 $(x_{\min}, x_{\max})$（端点不重合，严格不等）。  
所有这样的区间在 $x$ 轴上产生一个分段常数的重叠深度函数。从左到右扫描该函数，每当经过某个区间的左端点时，当前重叠深度增加 $1$；经过右端点时，当前重叠深度减少 $1$。  
我们需要在这个扫描过程中，记录第一次出现的最大重叠深度及其对应的区间端点。

由于题目保证所有矩形边与水平线无重合，且矩形边之间没有重合，因此所有左右端点互不相同，扫描过程简单明确，不会出现同时处理多个端点的情况。

## 解题思路

### 事件扫描法

将每个矩形与水平线的交集转化为两个事件：  
- 在 $x = x_{\min}$ 处发生“左端点事件”，类型为 $+1$（进入矩形）。  
- 在 $x = x_{\max}$ 处发生“右端点事件”，类型为 $-1$（离开矩形）。  

将所有事件按 $x$ 坐标升序排列，然后顺序处理：

1. 初始化当前重叠深度 $\textit{curOD} = 0$，最大深度 $\textit{maxOD} = 0$，以及当前区间的左端点 $\textit{startX}$。  
2. 处理第一个事件：将 $\textit{curOD}$ 加上该事件的类型（$+1$ 或 $-1$），并令 $\textit{startX}$ 等于该事件的 $x$ 坐标。  
3. 从第二个事件开始，对于每个事件：
   - 在应用该事件之前，当前的重叠深度在 $[\textit{startX}, \textit{curX}]$ 区间内是恒定的（其中 $\textit{curX}$ 为当前事件的 $x$ 坐标）。  
   - 如果 $\textit{curOD} > \textit{maxOD}$，则更新 $\textit{maxOD} = \textit{curOD}$，并记录 $\textit{bestLeft} = \textit{startX}$，$\textit{bestRight} = \textit{curX}$。  
   - 然后应用该事件（更新 $\textit{curOD}$），并将 $\textit{startX}$ 设为 $\textit{curX}$。
4. 所有事件处理完毕后，$\textit{maxOD}$ 即为 $\textit{OD}_{\textit{FM}}$，$\textit{bestLeft}$ 和 $\textit{bestRight}$ 即为所求区间端点。

若没有任何事件，说明水平线不经过任何矩形，直接输出 `0`。

### 正确性说明

- 扫描过程中，当 $\textit{curOD}$ 首次达到全局最大值时，其对应的区间必然是从上一个事件点（即 $\textit{startX}$）到当前事件点（即 $\textit{curX}$）的连续区间，该区间内 $\textit{curOD}$ 恒定不变。  
- 由于我们按从左到右的顺序处理事件，第一次出现最大值的时刻即为 $\textit{OD}_{\textit{FM}}$ 出现的位置，且区间左端点为该区间起始处的事件点，右端点为最大值结束处的事件点。  
- 所有端点互异，保证了区间边界明确，没有歧义。

### 复杂度分析

- 对每条水平线，我们需要遍历所有 $\textit{NR}$ 个矩形，收集最多 $2 \textit{NR}$ 个事件，然后排序。  
- 排序时间复杂度为 $O(\textit{NR} \log \textit{NR})$，每个事件处理为 $O(1)$。  
- 总复杂度为 $O(\textit{NL} \cdot \textit{NR} \log \textit{NR})$，在给定数据规模下可接受（$\textit{NR}$ 和 $\textit{NL}$ 均不超过 $10^4$，但实际测试数据不会让乘积过于巨大）。

## 代码实现

```cpp
// Overlapping Rectangles
// UVa ID: 883
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseCount;
    cin >> caseCount;
    bool firstCase = true;

    while (caseCount--) {
        int NR;
        cin >> NR;
        struct Rect {
            double xmin, xmax, ymin, ymax;
        };
        vector<Rect> rects(NR);
        for (int i = 0; i < NR; ++i) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rects[i].xmin = min(x1, x2);
            rects[i].xmax = max(x1, x2);
            rects[i].ymin = min(y1, y2);
            rects[i].ymax = max(y1, y2);
        }

        int NL;
        cin >> NL;
        vector<double> yLines(NL);
        for (int i = 0; i < NL; ++i) cin >> yLines[i];

        if (!firstCase) cout << '\n';
        firstCase = false;

        for (double y : yLines) {
            vector<pair<double, int>> events;
            for (const auto &r : rects) {
                if (y > r.ymin && y < r.ymax) {
                    events.emplace_back(r.xmin, 1);
                    events.emplace_back(r.xmax, -1);
                }
            }

            if (events.empty()) {
                cout << "0\n";
                continue;
            }

            sort(events.begin(), events.end());

            int curOD = 0, maxOD = 0;
            double bestLeft = 0.0, bestRight = 0.0;

            curOD += events[0].second;
            double startX = events[0].first;

            for (size_t i = 1; i < events.size(); ++i) {
                double curX = events[i].first;
                if (curOD > maxOD) {
                    maxOD = curOD;
                    bestLeft = startX;
                    bestRight = curX;
                }
                curOD += events[i].second;
                startX = curX;
            }

            cout << maxOD << ' '
                 << fixed << setprecision(2) << bestLeft << ' '
                 << bestRight << '\n';
        }
    }

    return 0;
}
```

## 总结

本题的关键在于将二维矩形与水平线的交转化为一维区间上的深度函数，再通过事件扫描法（类似于括号匹配）高效求解第一次出现的最大重叠深度及其区间。  
该思路具有以下特点：

- **将空间问题转化为一维时间轴上的事件处理**，简化了模型。  
- **利用排序和顺序扫描**，时间复杂度主要取决于排序，实现简洁。  
- **处理浮点数时**，由于题目保证无重合，可以使用严格不等号（`>` 和 `<`）避免精度问题，输出时保留两位小数。

本题也启示我们，在处理几何对象的重叠或覆盖问题时，通常可以通过“扫描线”思想将问题降维，从而用排序和差分等方法高效解决。
