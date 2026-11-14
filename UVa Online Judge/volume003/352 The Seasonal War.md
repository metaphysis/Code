[UVa 352 The Seasonal War](https://blog.csdn.net/metaphysis/article/details/161583092)

## 题目描述

$\texttt{Tigerville}$ 和 $\texttt{Elephantville}$ 的居民正在进行一场季节性的战争。上个月，$\texttt{Elephantville}$ 成功发射并轨道运行了一台名为“大黄蜂望远镜”（$\texttt{Bumble Scope}$）的间谍望远镜。其目的是统计 $\texttt{Tigerville}$ 中战鹰的数量。然而，由于建造过程中的质量管控不佳，大黄蜂望远镜出现了两个问题：主镜头被虫子污染，遮挡了每个图像的一部分；对焦机制故障，导致图像的大小和清晰度各不相同。

必须修复大黄蜂望远镜问题的计算机程序员们被穿着老虎服装的大象扣押在 $\texttt{Alaland}$ 的一家编程竞赛酒店中。大黄蜂望远镜有缺陷的图像以像素形式存储在一个名为 `Bumble.in` 的文件中。每个图像都是正方形的，每个像素或单元格包含 $0$ 或 $1$。独特的大黄蜂望远镜相机（$\texttt{BSC}$）在每个像素位置记录 $1$（如果战鹰的部分或全部存在）和 $0$（如果任何其他物体（包括虫子）可见）。程序员必须假设：

a) 一只战鹰至少由一个二进制 $1$ 表示。
b) 共享公共边或公共顶点的相邻单元格中的二进制 $1$ 构成一只战鹰。（即八连通）
c) 不同的战鹰不会相互接触。
d) 没有环绕。底部的像素与顶部不相邻，左边与右边不相邻。

### 输入格式

输入文件包含多个图像。每个图像由一个数字（表示其正方形边长 $n$）开头，后跟 $n$ 行，每行包含 $n$ 个字符（$0$ 或 $1$）。没有维度超过 $25$。

### 输出格式

对于每个图像，输出一行，包含图像编号和战鹰数量。格式如样例所示。

### 样例输入

```
6
100100
001010
000000
110000
111000
010100
8
01100101
01000001
00011000
00000010
11000011
10100010
10000001
01100000
```

### 样例输出

```
Image number 1 contains 3 war eagles.
Image number 2 contains 6 war eagles.
```

---

## 题目分析

### 问题的本质

这是一个**连通分量计数**问题。给定一个 $n \times n$ 的二进制矩阵，需要统计其中由 $1$ 组成的连通区域的数量。连通性定义为**八连通**（包括水平、垂直和对角线方向）。

### 连通性定义

与标准的四连通（仅上下左右）不同，本题使用**八连通**（包括八个方向）。这意味着：
- 水平相邻：`(i, j)` 与 `(i, j±1)`
- 垂直相邻：`(i, j)` 与 `(i±1, j)`
- 对角相邻：`(i, j)` 与 `(i±1, j±1)`

### 算法选择

使用**洪水填充**（$\texttt{flood fill}$，也称为 $\texttt{DFS}$ 或 $\texttt{BFS}$）：
- 遍历每个像素，当遇到 $1$ 时，启动一次洪水填充
- 将所有连通的 $1$ 标记为 $0$（或已访问）
- 计数加 $1$

### 与四连通的区别

八连通比四连通更“宽松”，对角相邻的 $1$ 也会被视为同一战鹰。这在代码中通过八个方向的偏移实现。

## 参考代码

```cpp
// The Seasonal War 
// UVa ID: 352
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char matrix[30][30];  // 图像矩阵，1-based 索引
int n;                // 图像边长

// 洪水填充：将 (i,j) 所在的连通分量全部标记为 0
void flood_fill(int i, int j)
{
    // 边界检查
    if (i < 1 || i > n || j < 1 || j > n)
        return;

    // 如果是战鹰的一部分（值为 '1'）
    if (matrix[i][j] == '1')
    {
        matrix[i][j] = '0';  // 标记为已访问
        
        // 八个方向递归（包括对角线）
        for (int m = -1; m <= 1; m++)
            for (int n = -1; n <= 1; n++)
                flood_fill(i + m, j + n);
    }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> n)
    {
        // 初始化矩阵
        memset(matrix, 0, sizeof(matrix));

        // 读取图像
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> matrix[i][j];

        int eagles = 0;
        // 遍历每个像素
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (matrix[i][j] == '1')
                {
                    flood_fill(i, j);  // 填充整个连通分量
                    eagles++;          // 计数加一
                }

        cout << "Image number " << ++cases;
        cout << " contains " << eagles << " war eagles." << endl;
    }

    return 0;
}
```
