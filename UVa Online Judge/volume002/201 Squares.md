[UVa 201 Squares](https://blog.csdn.net/metaphysis/article/details/161003966)

## 题目分析

本题是一个计算正方形数量的模拟问题。给定一个由点阵构成的网格，以及一些连接相邻点的水平线段（`H`）和垂直线段（`V`），需要统计该网格中所有不同边长的正方形的数量。

例如，当 $n = 4$ 时，共有 $16$ 个点，输入若干条线段后，需要输出边长为 $1, 2, \dots, n-1$ 的正方形各有多少个。

## 解题思路

### 1. 数据结构设计

由于 $n \leq 9$，网格规模很小，可以直接使用三维数组存储线段信息：

- `row[i][j][k]` 表示第 $i$ 行中，点 $(i, j)$ 与点 $(i, k)$ 之间是否存在一条水平线段
- `column[i][j][k]` 表示第 $i$ 列中，点 $(j, i)$ 与点 $(k, i)$ 之间是否存在一条垂直线段

实际上，本题只需要记录相邻点之间的线段。但为了方便判断更大边长的正方形，可以采用动态规划的思想，将连续线段的信息合并。

### 2. 线段信息预处理

输入中的每条线段 `H i j` 表示第 $i$ 行连接 $(i, j)$ 与 $(i, j+1)$；`V i j` 表示第 $j$ 行连接 $(j, i)$ 与 $(j+1, i)$。将这些相邻点的线段标记为 $1$。

接着进行扩展：对于任意 $i < j$，如果从 $i$ 到 $j-1$ 的线段存在，且从 $j-1$ 到 $j$ 的线段也存在，则合并为从 $i$ 到 $j$ 的连续线段。这样，`row[k][i][j] = 1` 就表示第 $k$ 行中，从列 $i$ 到列 $j$ 的所有相邻点之间都有水平线段。垂直线段同理。

### 3. 正方形判定

对于边长为 $k$ 的正方形，其左上角顶点位于 $(i, j)$（$1 \leq i \leq n-k, 1 \leq j \leq n-k$）。需要满足四条边都存在：

- 上边：第 $i$ 行，从列 $j$ 到列 $j+k$ 有水平线段，即 `row[i][j][j+k]`
- 下边：第 $i+k$ 行，从列 $j$ 到列 $j+k$ 有水平线段，即 `row[i+k][j][j+k]`
- 左边：第 $j$ 列，从行 $i$ 到行 $i+k$ 有垂直线段，即 `column[j][i][i+k]`
- 右边：第 $j+k$ 列，从行 $i$ 到行 $i+k$ 有垂直线段，即 `column[j+k][i][i+k]`

若四条边均存在，则计数加 $1$。

### 4. 输出格式

每组数据输出 `Problem #k`，后面空一行。然后按边长从小到大输出正方形数量。若没有正方形，输出 `No completed squares can be found.`。不同组数据之间输出一行 `******************************`，且前后各有一个空行。

## 代码实现

```cpp
// Squares
// UVa ID: 201
// Verdict: Accepted
// Submission Date: 2016-03-23
// UVa Run Time: 0.022s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int row[10][10][10];     // row[i][j][k]: 第 i 行中，点 (i,j) 到 (i,k) 是否有连续水平线段
int column[10][10][10];  // column[i][j][k]: 第 i 列中，点 (j,i) 到 (k,i) 是否有连续垂直线段
int n;                   // 网格每行/每列的点数

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    char line;            // 线段类型：'H' 或 'V'
    int m, start, end;    // m 为线段数量，start 和 end 为坐标
    int counter = 0;      // 记录当前是第几个问题
    bool printAsterisks = false;  // 控制是否打印分隔符
    
    while (cin >> n) {
        // 如果不是第一组数据，则输出分隔符（前后各有一个空行）
        if (printAsterisks) {
            cout << "\n";
            cout << "**********************************\n";
            cout << "\n";
        }

        if (printAsterisks == false) printAsterisks = true;

        counter++;
        
        // 初始化线段数组
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));

        cin >> m;
        while (m--) {
            cin >> line >> start >> end;
            if (line == 'H')
                // 水平线段：第 start 行，连接列 end 和 end+1
                row[start][end][end + 1] = 1;
            else
                // 垂直线段：第 start 列，连接行 end 和 end+1
                column[start][end][end + 1] = 1;
        }

        // 预处理：合并连续的线段，得到任意两点间是否连续连通
        // 例如：第 k 行中，若从 i 到 j-1 有线段，且从 j-1 到 j 有线段，则从 i 到 j 有线段
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n - 2; i++)
                for (int j = i + 2; j <= n; j++) {
                    if (row[k][i][j - 1] && row[k][j - 1][j]) row[k][i][j] = 1;
                    if (column[k][i][j - 1] && column[k][j - 1][j]) column[k][i][j] = 1;
                }

        // 输出问题标题，UVa 格式要求后面空一行
        cout << "Problem #" << counter << "\n";
        cout << endl;

        bool outputed = false;  // 标记是否有输出任何正方形

        // 枚举边长 k，从 1 到 n-1
        for (int k = 1; k <= n - 1; k++) {
            int total = 0;
            // 枚举左上角顶点 (i, j)
            for (int i = 1; i <= n - k; i++)
                for (int j = 1; j <= n - k; j++)
                    // 判断正方形的四条边是否都存在
                    if (row[i][j][j + k] && row[i + k][j][j + k] &&
                        column[j][i][i + k] && column[j + k][i][i + k])
                            total++;

             if (total > 0) {
                cout << total << " square (s) of size " << k << "\n";
                outputed = true;
             }            
        }

        // 如果没有找到任何正方形，输出提示信息
        if (outputed == false) cout << "No completed squares can be found." << "\n";     
    }

    return 0;
}
```

## 注意事项

- 输入中的坐标索引均从 $1$ 开始，数组也相应地从 $1$ 开始使用。
- 每组数据输出后需要空一行，不同数据之间用星号行分隔，且星号行前后各有一个空行。
- 输出 `square (s)` 中的括号和空格需与样例完全一致。
