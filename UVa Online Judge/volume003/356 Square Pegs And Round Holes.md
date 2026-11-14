[UVa 356 Square Pegs And Round Holes](https://blog.csdn.net/metaphysis/article/details/161588854)

## 题目描述

一个直径为 $2n - 1$ 单位的圆被绘制在 $2n \times 2n$ 的棋盘上。下图展示了 $n = 3$ 时的构造。

要求：编写程序，确定棋盘上**包含圆弧段的格子**数量，以及**完全位于圆内**的格子数量。

### 输入格式

输入文件的每行包含一个不超过 $150$ 的正整数 $n$。

### 输出格式

对于每个输入值 $n$，按样例输出格式输出两行，后跟一个空行。

### 样例输入

```
3
4
```

### 样例输出

```
In the case n = 3, 20 cells contain segments of the circle.
There are 12 cells completely contained in the circle.

In the case n = 4, 28 cells contain segments of the circle.
There are 24 cells completely contained in the circle.
```

---

## 题目分析

### 问题的本质

这是一个**几何计数**问题。圆被放置在 $2n \times 2n$ 的棋盘中央，圆的直径 $d = 2n - 1$，因此半径为 $r = (2n - 1)/2 = n - 0.5$。

棋盘共有 $(2n) \times (2n)$ 个单元格，每个单元格是 $1 \times 1$ 的正方形。圆与棋盘同中心。

### 坐标系统

将棋盘左下角设为 $(0,0)$，右上角为 $(2n, 2n)$。每个单元格以其左下角坐标 $(i, j)$ 标识，其中 $0 \le i, j \le 2n-1$。

圆的中心位于 $(n, n)$，半径为 $r = n - 0.5$。

### 单元格分类

- **完全在圆内**：单元格的四个顶点都在圆内（到圆心距离 $\le r$）
- **包含圆弧段**（与圆相交）：单元格至少有一个顶点在圆内，至少有一个顶点在圆外，且该单元格与圆相交

### 对称性

由于圆和棋盘都是中心对称的，只需计算四分之一的区域，然后乘以 $4$。
## 参考代码

```cpp
// Square Pegs And Round Holes
// UVa ID: 356
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, cases = 0;
    while (cin >> n)
    {
        // 输出空行分隔测试用例
        if (cases++) cout << endl;

        // 包含圆弧段的格子数 = (2n-1) * 4
        cout << "In the case n = " << n << ", " << (2 * n - 1) * 4;
        cout << " cells contain segments of the circle." << endl;

        // 统计完全位于圆内的格子数
        int contained = 0;
        // 只考虑第一象限（不含坐标轴），因为对称性
        for (int i = 1; i <= n - 1; i++)
            for (int j = 1; j <= n - 1; j++)
                // 判断右上角顶点是否在圆内
                // 等价于 4(i^2 + j^2) <= (2n-1)^2
                if (4 * (i * i + j * j) <= (2 * n - 1) * (2 * n - 1))
                    contained++;

        // 四个象限，乘以 4
        cout << "There are " << contained * 4 << " cells completely contained in the circle." << endl;
    }

    return 0;
}
```
