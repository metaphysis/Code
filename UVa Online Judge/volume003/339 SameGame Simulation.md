[UVa 339 SameGame Simulation](https://blog.csdn.net/metaphysis/article/details/161545149)

## 题目描述

单人游戏 $\texttt{SameGame}$ 在一个 $M$ 行 $N$ 列的矩形网格上进行。每个格子中包含一个 $0$ 到 $9$ 之间的正整数。游戏的目标是移除网格中的所有数字。玩家通过重复选择一个格子进行消除来尝试达成目标。

每次选择一个格子进行消除时，包含该格子中相同数字的**连通区域**（定义如下）中的所有格子都会被移除，然后被移除格子**上方**的格子向下掉落，**右侧**的列向左滑动。当所有格子都被移除时游戏胜利，或者当无法再移除任何格子时游戏结束。一个区域只有在包含**至少两个格子**时才能被移除。

**连通区域**的定义：从区域中的任何格子出发，通过水平（左/右）和/或垂直（上/下）移动可以到达的所有格子，且这些格子必须包含相同的数值。

**坐标系统**：格子从网格的左下角开始编号，该格子为 $(1,1)$。其上方的格子为 $(2,1)$，其右侧的格子为 $(1,2)$。

### 输入格式

输入完全由非负整数组成，不考虑行结构。每个网格和消除序列以 $M$ 和 $N$ 的值开始。如果其中任何一个值为 $0$，则输入结束。

接下来是 $M \times N$ 个网格整数，按行主序给出（即按 $(1,1), (1,2), \dots, (1,N), (2,1), \dots, (M,N)$ 的顺序）。

网格数据之后是若干对整数，每对表示被选择消除的格子的行和列。这个序列以一对 `0 0` 结束。

如果游戏获胜，程序必须跳过剩余的所有整数对（包括 `0 0`），以读取下一个网格的数据。

### 输出格式

对于每个网格，输出其编号（从 $1$ 开始）。然后输出处理所有选择后剩余的网格，或者消息 `Game Won`。

### 样例输入

```
3 5
1 2 3 5 5
2 2 3 5 1
1 3 5 2 2
3 5 2 2 1 2 1 1
0 0
3 5
1 2 3 5 5
2 2 3 5 1
1 3 5 2 2
2 2 1 2 1 4 1 2 99 99
0 0
4 3
1 4 4 4 4 2 1 2 3 3 1 3
1 2 1 1 1 3 1 1
0 0
0 0
```

### 样例输出

```
Grid 1.
    Game Won

Grid 2.
       1 2 1
       2 1

Grid 3.
    Game Won
```

---

## 题目分析

### 问题的本质

这是一个**网格消除游戏**的模拟问题。核心操作包括：
1. **连通区域检测**：使用洪水填充（$\texttt{flood fill}$）标记与选中格子同值且连通的区域
2. **区域移除**：将标记的格子设为 $-1$（表示空）
3. **重力下落**：空位上方的格子向下掉落
4. **列左移**：全空的列向左滑动

### 坐标系统

注意：题目中的坐标系统与通常的二维数组索引不同：
- $(1,1)$ 是左下角
- $(2,1)$ 是 $(1,1)$ 上方的格子
- 行号从下到上递增

在代码实现中，通常使用 `grid[r][c]`，其中 `r=1` 对应最下面一行，`r=M` 对应最上面一行。这与输入顺序一致（先输入第 $1$ 行，即最下面一行）。

### 消除条件

一个选择是有效的当且仅当：
- 选中的格子存在（$1 \leq row \leq M$，$1 \leq column \leq N$）
- 选中的格子不是空的（`grid[row][column] >= 0`）
- 选中的格子属于一个**至少有两个格子**的连通区域

连通区域的判断可以通过检查上下左右四个方向是否有相同数值的格子。

---
## 参考代码

```cpp
// SameGame Simulation
// UVa ID: 339
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int M, N, grid[50][50], cases = 0;
int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// 洪水填充：标记所有与 (row, column) 连通且值为 value 的格子
void floodFill(int row, int column, int value)
{
    if (row >= 1 && row <= M && column >= 1 && column <= N)
        if (grid[row][column] == value)
        {
            grid[row][column] = -1;  // 标记为已移除
            for (int k = 0; k < 4; k++)
                floodFill(row + offset[k][0], column + offset[k][1], value);
        }
}

// 下落和左移调整
void adjust()
{
    // 阶段1：重力下落（格子向下掉落）
    for (int c = 1; c <= N; c++)
    {
        int low = 1;
        // 找到第一个空位
        while (low <= M && grid[low][c] >= 0) low++;
        if (low == M + 1) continue;  // 该列已满
        
        // 将非空格子向下移动
        for (int up = low + 1; up <= M; up++)
            if (grid[up][c] >= 0)
            {
                grid[low][c] = grid[up][c];
                grid[up][c] = -1;
                low++;
            }
    }
    
    // 阶段2：空列左移
    int movedColumn = 0;
    for (int c = N; c >= 1; c--)
    {
        // 检查当前列是否为空
        bool emptyColumn = true;
        for (int r = 1; r <= M; r++)
            if (grid[r][c] >= 0)
            {
                emptyColumn = false;
                break;
            }
        if (emptyColumn == false)
            continue;

        // 将右侧列向左移动
        for (int r = 1; r <= M; r++)
        {
            for (int emptyC = c; emptyC < N - movedColumn; emptyC++)
                grid[r][emptyC] = grid[r][emptyC + 1];
        }
        
        // 清空最右侧的列
        for (int r = 1; r <= M; r++)
            grid[r][N - movedColumn] = -1;
            
        movedColumn++;
    }
}

// 输出当前网格（从顶部行开始）
void display()
{
    for (int r = M; r >= 1; r--)
    {
        for (int c = 1; c <= N; c++)
            cout << " " << grid[r][c];
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> M >> N, M && N)
    {
        // 读取网格（从底部行开始）
        for (int r = 1; r <= M; r++)
            for (int c = 1; c <= N; c++)
                cin >> grid[r][c];
        
        int row, column;
        while (cin >> row >> column, row && column)
        {
            // 检查选择是否有效
            if (row <= 0 || row > M || column <= 0 || column > N)
                continue;
            if (grid[row][column] == -1)
                continue;
            
            // 检查是否有相邻的同值格子（区域大小 ≥ 2）
            bool linked = false;
            for (int k = 0; k < 4; k++)
            {
                int nextRow = row + offset[k][0], nextColumn = column + offset[k][1];
                if (nextRow < 1 || nextRow > M || nextColumn < 1 || nextColumn > N)
                    continue;
                if (grid[nextRow][nextColumn] == grid[row][column])
                {
                    linked = true;
                    break;
                }
            }
            
            if (linked == false)
                continue;
            
            // 执行消除
            floodFill(row, column, grid[row][column]);
            adjust();
        }
        
        // 输出结果
        if (cases)
            cout << endl;
            
        cout << "Grid " << ++cases << "." << endl;
        
        // 检查是否获胜
        int cell = 0;
        for (int r = 1; r <= M; r++)
            for (int c = 1; c <= N; c++)
                if (grid[r][c] >= 0)
                    cell++;
                    
        if (cell == 0)
            cout << "    Game Won" << endl;
        else
        {
            // 输出剩余网格
            for (int r = M; r >= 1; r--)
            {
                cout << "   ";
                for (int c = 1; c <= N; c++)
                    if (grid[r][c] >= 0)
                        cout << " " << grid[r][c];
                    else
                        cout << "  ";
                cout << endl;
            }
        }
    }
    
    return 0;
}
```
