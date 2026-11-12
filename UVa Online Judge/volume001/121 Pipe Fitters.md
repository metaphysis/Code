[UVa 121 Pipe Fitters](https://blog.csdn.net/metaphysis/article/details/156708600)

## 题目描述
一家公司生产统一直径的管道，这些管道需要存储在矩形容器中。容器有不同尺寸，管道在容器内按行排列，同一行内管道紧贴（相切），行与行之间也紧贴（或紧贴容器底部）。  
有两种排列方式： **网格（$\texttt{grid}$）** 和 **交错（$\texttt{skew}$）** ，如下图所示（题目中给出示意图）：  
- 网格排列：管道按行列对齐排列。  
- 交错排列：管道在行与行之间交错排列，使得相邻行的管道位于间隙中。  

输入为一系列矩形容器横截面的尺寸（单位是管道直径），每个尺寸由两个实数表示。输出对于每个横截面，能够容纳的最大管道数，以及达到该最大数时所采用的排列模式（$\texttt{grid}$ 或 $\texttt{skew}$）。如果两种模式结果相同，则输出 `grid`。

## 题目分析与解题思路

### 1. 网格排列（$\texttt{grid}$）

在网格排列中，管道整齐地排成行和列。假设容器宽度为 $width$，高度为 $height$，那么能容纳的管道数为：

$$
grid = \lfloor width \rfloor \times \lfloor height \rfloor
$$

这里使用向下取整是因为管道是整数个，不能有部分管道。

### 2. 交错排列（$\texttt{skew}$）

交错排列较为复杂，需要仔细计算行数和每行的管道数。

#### 行数计算

在交错排列中，相邻两行的垂直距离为 $\frac{\sqrt{3}}{2}$（因为管道直径为单位长度，三个管道中心构成等边三角形，高为 $\frac{\sqrt{3}}{2}$）。  
若第一行紧贴底部，那么第 $i$ 行的垂直位置为 $(i-1) \times \frac{\sqrt{3}}{2}$。  
要求最后一行不能超出容器高度，即 $(layers - 1) \times \frac{\sqrt{3}}{2} + 1 \le height$。  
解得最多行数：

$$
layers = \left\lfloor \frac{2(height - 1)}{\sqrt{3}} \right\rfloor + 1
$$

注意若 $height < 1$，则无法放置任何管道。

#### 每行管道数

- 奇数行（从第一行开始计数）管道数为 $\lfloor width \rfloor$。  
- 偶数行管道数通常为 $\lfloor width \rfloor - 1$，但若 $width - \lfloor width \rfloor \ge 0.5$，则偶数行也可以放下与奇数行相同数量的管道。这是因为交错排列中偶数行管道会向左偏移 $0.5$ 个单位，若剩余空间足够，则可多放一个。

#### 总管道数

设奇数行有 $oddRows = \lceil layers / 2 \rceil$，偶数行有 $evenRows = \lfloor layers / 2 \rfloor$，则总数为：

$$
skew = oddRows \times pipesPerOddRow + evenRows \times pipesPerEvenRow
$$

#### 注意

由于容器可以旋转，因此需要计算 $skew(width, height)$ 和 $skew(height, width)$ 并取最大值。

### 3. 比较与输出

比较网格排列和交错排列的最大管道数，输出较大者及其模式；若相等则输出 `grid`。

## 代码实现

```cpp
// Pipe Fitters
// UVa ID: 121
// Verdict: Accepted
// Submission Date: 2011-12-18
// UVa Run Time: 0.056s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid(double width, double height) {
    int nGrid = 0;
    nGrid = floor(width) * floor(height);
    return nGrid;
}

int skew(double width, double height) {
    if (height < 1.0) return 0;
    int layers = floor(2.0 * (height - 1.0) / sqrt(3.0) + 1.0);
    int pipes_per_odd_full_row = floor(width);
    int pipes_per_even_full_row = pipes_per_odd_full_row - 1;
    if ((width - pipes_per_odd_full_row) >= 0.5) pipes_per_even_full_row = pipes_per_odd_full_row;
    int nSkew = ceil(layers / 2.0) * pipes_per_odd_full_row + floor(layers / 2.0) * pipes_per_even_full_row;
    return nSkew;
}

int main(int ac, char *av[]) {
    double a, b;
    while (cin >> a >> b) {
        int nGrid = grid(a, b);
        int nSkew = max(skew(a, b), skew(b, a));
        if (nGrid >= nSkew) cout << nGrid << " grid" << endl;
        else cout << nSkew << " skew" << endl;
    }
    return 0;
}
```

## 复杂度分析

对于每个输入尺寸，计算 $\texttt{grid}$ 和 $\texttt{skew}$ 均为常数时间操作，因此总时间复杂度为 $O(1)$ 每个测试用例，整体为 $O(n)$，其中 $n$ 为测试用例数。空间复杂度为 $O(1)$。

## 总结

本题主要考察几何建模和取整运算。关键在于理解交错排列的行距与每行管道数的计算，并正确处理浮点数比较与取整。通过分别计算两种排列方式的管道数并比较，即可得到答案。
