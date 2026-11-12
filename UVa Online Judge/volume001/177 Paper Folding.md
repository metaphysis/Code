[UVA 177 Paper Folding](https://blog.csdn.net/metaphysis/article/details/160860685)

## 题目分析

本题描述了一个有趣的折纸问题：将一张长纸条进行 $N$ 次对折（每次将右半部分折到左边），然后每个折痕从 $180^\circ$ 打开到 $90^\circ$，从纸的边缘端视，会观察到一条被称为 “龙曲线” （$\texttt{Dragon Curve}$） 的图形。要求根据输入的 $N$ 绘制出对应的曲线，其中水平线段用下划线 `_` 表示，竖直线段用竖线 `|` 表示。

输入包含多行，每行一个整数 $N$（$1 \leq N \leq 13$），以 $0$ 表示输入结束。对于每个 $N$，输出对应的龙曲线图形，且图形需要尽可能靠左、靠上放置，每个图形后跟一行包含单个 `^` 的行作为结束标记。

## 解题思路

### 1. 折痕序列的生成规律

龙曲线的形成与折痕的方向序列密切相关。经过分析可以发现，折痕序列的生成具有自相似性（分形特征）。定义四种基本方向：
- $\texttt{R}$：向右
- $\texttt{L}$：向左  
- $\texttt{U}$：向上
- $\texttt{D}$：向下

经过一次折叠的折痕序列为：$\texttt{RU}$。

对于 $N$ 次折叠，其折痕序列可以通过 $N-1$ 次折叠的序列生成：
```
pattern(N) = pattern(N-1) + '0' + rotate(pattern(N-1))
```
其中 $\texttt{rotate}$ 表示将序列中每个字符按规则映射：$\texttt{R} \rightarrow \texttt{U}$，$\texttt{U} \rightarrow \texttt{L}$，$\texttt{L} \rightarrow \texttt{D}$，$\texttt{D} \rightarrow \texttt{R}$，然后反转顺序。

实际代码中，我们使用递归方式生成序列：先得到 $N-1$ 的序列，然后将其反转并映射后追加到自身末尾。

### 2. 坐标绘制

得到折痕序列后，从起点开始模拟绘制过程：
- 遇到 $\texttt{R}$ 或 $\texttt{L}$ 时，绘制水平线段 `_`，并相应改变 $y$ 坐标
- 遇到 $\texttt{U}$ 或 $\texttt{D}$ 时，绘制竖直线段 `|`，并相应改变 $x$ 坐标
- 由于折痕打开后线段之间是连续的，需要注意绘制位置和坐标更新的顺序

绘制过程中记录所有访问点的坐标范围，最后只输出有图形的区域，并且尽可能靠左、靠上。

### 3. 实现细节

- 使用二维字符数组 `matrix` 存储图形，大小设置为 $1024 \times 1024$ 足够容纳 $N=13$ 的图形
- 起点坐标设为 $(512, 512)$ 以避免负坐标
- 输出时逐行扫描，去掉每行末尾多余的空格

## 代码实现

```cpp
// Paper Folding
// UVa ID: 177
// Verdict: Accepted
// Submission Date: 2016-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 方向映射表：用于生成折叠序列的反转部分
map<char, char> mapped;
// 存储绘制图形的二维数组
char matrix[1024][1024];

// 递归生成 N 次折叠后的折痕方向序列
string unfolding(int n) {
    if (n > 1) {
        // 先获取 N-1 次折叠的序列
        string pattern = unfolding(n - 1);
        int length = pattern.length();
        // 将原序列反转并映射后追加到末尾
        for (int i = length - 1; i >= 0; i--)
            pattern += mapped[pattern[i]];
        return pattern;
    } else
        // 一次折叠的基本序列为 "RU"
        return "RU";
}

// 根据折痕序列绘制龙曲线
void display(int n) {
    // 获取完整的折痕序列，末尾添加 '0' 作为哨兵
    string pattern = unfolding(n);
    pattern += '0';

    // 初始化图形数组为空格
    memset(matrix, ' ', sizeof(matrix));
    int x = 512, y = 512;  // 起始坐标，取中间位置避免负坐标
    int minx = 512, maxx = 512, miny = 512, maxy = 512;
    
    // 遍历折痕序列绘制图形
    for (int i = 0; i < pattern.length() - 1; i++) {
        if (pattern[i] == 'L') {
            // 向左画水平线
            matrix[x][y] = '_';
            y -= 1;
        } else if (pattern[i] == 'R') {
            // 向右画水平线
            matrix[x][y] = '_';
            y += 1;
        } else if (pattern[i] == 'U') {
            // 向上画竖直线
            matrix[x][y] = '|';
            x -= 1;
            // 根据下一个方向确定转角后的位置
            if (pattern[i + 1] == 'L')
                y -= 1;
            if (pattern[i + 1] == 'R')
                y += 1;
        } else if (pattern[i] == 'D') {
            // 向下画竖直线
            x += 1;
            matrix[x][y] = '|';
            // 根据下一个方向确定转角后的位置
            if (pattern[i + 1] == 'L')
                y -= 1;
            if (pattern[i + 1] == 'R')
                y += 1;
        }

        // 更新坐标边界
        minx = min(x, minx);
        maxx = max(x, maxx);
        miny = min(y, miny);
        maxy = max(y, maxy);
    }

    // 输出图形，尽可能靠左、靠上
    for (int i = minx; i <= maxx; i++) {
        int lasty = maxy;
        // 去掉行尾多余的空格
        while (matrix[i][lasty] == ' ') lasty--;

        if (lasty >= 0) {
            for (int j = miny; j <= lasty; j++)
                cout << matrix[i][j];
            cout << "\n";
        }
    }

    // 每个图形以 '^' 结束
    cout << "^\n";
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    // 初始化方向映射表
    mapped.insert(make_pair('R', 'U'));
    mapped.insert(make_pair('U', 'L'));
    mapped.insert(make_pair('L', 'D'));
    mapped.insert(make_pair('D', 'R'));

    int n;
    while (cin >> n, n)
        display(n);

    return 0;
}
```

## 总结

本题的核心在于发现龙曲线折痕序列的自相似生成规律。通过递归方式生成序列后，模拟绘制过程即可得到答案。对于 $N=13$，图形宽度会超过 $80$ 个字符，但题目允许这种情况，只需要正确输出即可。
