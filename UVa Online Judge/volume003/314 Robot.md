[UVa 314 Robot](https://blog.csdn.net/metaphysis/article/details/161477021)

## 题目描述

机器人研究所使用机器人在当地商店运输物品。机器人只能沿直线（轨道）移动。所有轨道形成一个矩形网格，相邻轨道相距 $1$ 米。商店是一个 $N \times M$ 米的矩形，完全被该网格覆盖。距离商店边最近的轨道恰好是 $1$ 米。

机器人呈圆形，直径 $1.6$ 米。轨道穿过机器人的中心。机器人始终面向北、南、西或东。轨道呈南北和东西方向。机器人只能朝其面向的方向移动。方向可以在每个轨道交叉点改变。

机器人初始站在一个轨道交叉点。商店中的障碍物由占据地面 $1 \times 1$ 米的碎片构成。每个障碍物都在由轨道构成的 $1 \times 1$ 方格内。

机器人的移动由两个命令控制：
- $\texttt{GO}$ 命令：参数 $n \in \{1,2,3\}$，机器人沿当前方向移动 $n$ 米
- $\texttt{TURN}$ 命令：参数为 $\texttt{left}$ 或 $\texttt{right}$，机器人按指示方向旋转 $90^\circ$

每个命令执行耗时 $1$ 秒。

要求：确定机器人从给定起点到给定目的地的最短时间。

### 输入格式

输入文件由多个数据块组成。每个数据块的第一行包含两个整数 $M \leq 50$ 和 $N \leq 50$。接下来的 $M$ 行，每行 $N$ 个数字 $0$ 或 $1$，用空格分隔。$1$ 表示障碍物，$0$ 表示空格。数据块以一行包含四个正整数 $B_1, B_2, E_1, E_2$ 和起始方向字符串结束。

坐标系统：$(0,0)$ 是商店最西北的方格，$(M-1,N-1)$ 是最东南的方格。起点和终点是方格西北角的坐标。

最后一个数据块以 $N = 0$ 和 $M = 0$ 结束。

### 输出格式

对于每个数据块（最后一个除外），输出一行，包含机器人从起点到目的地的最短时间。如果不存在路径，输出 $-1$。

### 样例输入

```
9 10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 north
0 0
```

---

## 题目分析

### 问题的本质

这是一个**带方向的状态空间搜索**问题。机器人位于网格的交叉点（即方格之间），具有方向属性。机器人可以：
1. 向前移动 $1$、$2$ 或 $3$ 米（沿当前方向）
2. 原地左转或右转（耗时 $1$ 秒）

目标是找到从起点到终点的最短时间。

### 状态表示

一个完整的状态包括：
- 机器人的位置（交叉点坐标）
- 机器人的朝向（北、东、南、西）

交叉点坐标范围：$0 \leq x \leq M$，$0 \leq y \leq N$（因为 $M \times N$ 个方格，有 $(M+1) \times (N+1)$ 个交叉点）。

### 障碍物与可达性

障碍物占据 $1 \times 1$ 的方格。机器人的身体是直径为 $1.6$ 米的圆形，半径为 $0.8$ 米。机器人中心沿轨道移动。

关键约束：机器人不能与任何障碍物相交。由于轨道位于方格之间，机器人在移动过程中会经过方格的中心区域。一个机器人位于交叉点 $(x,y)$ 时，它占据的方格是相邻的四个方格（如果存在）。

更精确地说：当机器人位于交叉点 $(x,y)$ 时，它占据了四个象限的方格：$(x-1,y-1)$、$(x-1,y)$、$(x,y-1)$、$(x,y)$（使用基于 $0$ 的索引）。因此，机器人可以站在交叉点 $(x,y)$ 当且仅当这四个方格都不是障碍物。

### 移动约束

当机器人沿某个方向移动时，它经过的路径会覆盖一系列方格。由于机器人有 $0.8$ 米的半径，它不能太靠近障碍物。实际上，机器人的移动路径必须始终与障碍物保持安全距离。

一个等效的简化模型：机器人可以安全地从一个交叉点移动到另一个交叉点，当且仅当它所经过的所有方格都不是障碍物。

对于北向移动：从 $(x,y)$ 向北移动 $n$ 步到 $(x-n,y)$，需要检查经过的方格是否为空。

---

## 解题思路

### 步骤一：坐标系统

- 方格坐标：$[0,M-1] \times [0,N-1]$
- 交叉点坐标：$[0,M] \times [0,N]$
- 起点 $(B_1,B_2)$ 和终点 $(E_1,E_2)$ 是方格西北角的坐标，即交叉点坐标

### 步骤二：障碍物映射

输入给出的是方格障碍物。为了判断机器人是否可以在交叉点 $(x,y)$ 放置，需要检查四个相邻方格：
```cpp
bool canStand(int x, int y) {
    if (x < 0 || x >= M || y < 0 || y >= N) return false;
    return !obstacles[x][y] && !obstacles[x-1][y] && 
           !obstacles[x][y-1] && !obstacles[x-1][y-1];
}
```

注意边界：机器人不能在边界外，也不能在边界上使得部分身体悬空。

### 步骤三：移动可行性

当机器人沿方向 $d$ 移动 $n$ 步（$1 \leq n \leq 3$）时，需要检查沿途经过的所有方格是否为空。

例如，北向移动（$d = \texttt{NORTH}$）：从 $(x,y)$ 移动到 $(x-n,y)$，需要检查每个中间位置 $(x-k,y)$ 处机器人是否会碰到障碍物。实际上，对于每步移动，需要检查机器人所在交叉点的四个相邻方格。

简化实现：在 $\texttt{BFS}$ 中，逐步尝试移动 $1$、$2$、$3$ 步，一旦发现某步遇到障碍物，则停止尝试更远的步数（因为障碍物会阻挡后续移动）。

### 步骤四：$\texttt{BFS}$ 搜索

使用广度优先搜索（$\texttt{BFS}$），因为每条命令耗时相同（$1$ 秒）。

状态：`(row, column, direction)`
- `row`：$0 \sim M$
- `column`：$0 \sim N$
- `direction`：$0 \sim 3$（北、东、南、西）

从起点状态开始，每次扩展：
1. 左转：`(row, column, (direction + 3) % 4)`，时间 $+1$
2. 右转：`(row, column, (direction + 1) % 4)`，时间 $+1$
3. 向前移动 $1$、$2$、$3$ 步：如果路径可行，则移动到新位置，时间 $+1$

### 步骤五：终点判断

终点是 $(E_1, E_2)$，机器人可以以任意方向到达。因此，在所有 $4$ 个方向中取最小时间。

---

## 算法复杂度分析

### 时间复杂度

- 状态数：$(M+1) \times (N+1) \times 4 \leq 51 \times 51 \times 4 \approx 10404$
- 每个状态扩展：最多 $3$ 种移动 + $2$ 种转向 = $5$ 种动作
- 总复杂度：$O(M \times N \times 4 \times 5) \approx 5 \times 10^4$，完全可行

### 空间复杂度

- 障碍物数组：$O(M \times N)$
- 距离数组：$O(M \times N \times 4)$
- 总空间复杂度：$O(M \times N)$

---

## 正确性证明

**引理 1**：状态空间 $(x,y,d)$ 完全描述了机器人的配置。

证明：机器人的位置由其中心（交叉点）唯一确定，方向由 $d$ 唯一确定。$\square$

**引理 2**：$\texttt{BFS}$ 保证找到最短时间。

证明：每条命令耗时相同，因此 $\texttt{BFS}$ 按时间递增的顺序访问状态，首次到达的状态即为最短时间。$\square$

**引理 3**：移动检查规则正确模拟了机器人与障碍物的碰撞检测。

证明：机器人中心沿轨道移动，占据 $1.6 \times 1.6$ 的正方形区域。该区域覆盖了相邻四个方格的部分。只有当这些方格都是空地时，机器人才能安全通过。$\square$

---

## 参考代码

```cpp
// Robot
// UVa ID: 314
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 方向常量：北、东、南、西
const int NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;
int obstacles[60][60];          // 障碍物网格
int seconds[60][60][4];         // 到达状态的最短时间
int visited[60][60][4];         // 是否已访问
int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };  // 方向偏移
int M, N, B1, B2, E1, E2;       // 行数、列数、起点、终点
string orientation;             // 起始方向

// 状态结构体
struct state
{
    int row, column, elapsed, direction;
};

// 广度优先搜索
void bfs(int row, int column, int elapsed, int direction)
{
    // 初始化距离和访问标记数组
    for (int i = 0; i <= M; i++)
        for (int j = 0; j <= N; j++)
            for (int k = 0; k < 4; k++)
            {
                seconds[i][j][k] = -1;
                visited[i][j][k] = 0;
            }

    queue<state> unvisited;
    unvisited.push((state){row, column, elapsed, direction});

    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();

        row = current.row, column = current.column;
        elapsed = current.elapsed, direction = current.direction;

        if (visited[row][column][direction])
            continue;
        visited[row][column][direction] = 1;

        if (seconds[row][column][direction] == -1 ||
            elapsed < seconds[row][column][direction])
            seconds[row][column][direction] = elapsed;

        // 尝试向前移动 1、2、3 步
        int step = 1, nextRow = row, nextColumn = column;
        while (step <= 3)
        {
            // 检查是否在边界内
            if ((direction == NORTH && nextRow >= 2) || 
                (direction == SOUTH && nextRow <= (M - 2)) ||
                (direction == EAST && nextColumn <= (N - 2)) || 
                (direction == WEST && nextColumn >= 2))
            {
                nextRow += offset[direction][0];
                nextColumn += offset[direction][1];
                
                // 检查移动路径上的方格是否都是空地
                if ((direction == NORTH && 
                     (obstacles[nextRow - 1][nextColumn - 1] || 
                      obstacles[nextRow - 1][nextColumn])) ||
                    (direction == SOUTH && 
                     (obstacles[nextRow][nextColumn - 1] || 
                      obstacles[nextRow][nextColumn])) ||
                    (direction == EAST && 
                     (obstacles[nextRow - 1][nextColumn] || 
                      obstacles[nextRow][nextColumn])) ||
                    (direction == WEST && 
                     (obstacles[nextRow - 1][nextColumn - 1] || 
                      obstacles[nextRow][nextColumn - 1])))
                    break;  // 遇到障碍物，停止更远步数

                unvisited.push((state){nextRow, nextColumn, elapsed + 1, direction});
            }
            
            step++;
        }

        // 转向：左转和右转
        unvisited.push((state){row, column, elapsed + 1, (direction - 1 + 4) % 4});
        unvisited.push((state){row, column, elapsed + 1, (direction + 1) % 4});
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    while (cin >> M >> N, M && N)
    {
        // 读取障碍物网格
        for (int row = 0; row < M; row++)
            for (int column = 0; column < N; column++)
                cin >> obstacles[row][column];

        // 读取起点、终点和起始方向
        cin >> B1 >> B2 >> E1 >> E2 >> orientation;

        int direction = NORTH;
        if (orientation == "east") direction = EAST;
        else if (orientation == "south") direction = SOUTH;
        else if (orientation == "west") direction = WEST;

        bfs(B1, B2, 0, direction);

        // 取所有方向中的最小值
        int minSeconds = -1;
        for (int i = 0; i < 4; i++)
        {
            if (seconds[E1][E2][i] == -1)
                continue;
            if (minSeconds == -1 || seconds[E1][E2][i] < minSeconds)
                minSeconds = seconds[E1][E2][i];
        }

        cout << minSeconds << endl;
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **状态空间建模**：位置 + 方向
2. **障碍物检测**：机器人占据 $4$ 个方格
3. **移动约束**：每次可移动 $1$、$2$ 或 $3$ 步
4. **$\texttt{BFS}$ 搜索**：边权相同的最短路径

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 状态表示 | $(x,y,d)$，$x,y$ 为交叉点坐标 |
| 障碍物检测 | 机器人占据四个相邻方格 |
| 移动步长 | $1$、$2$、$3$ 米（步进式检查） |
| 转向 | 左转和右转，耗时 $1$ 秒 |
| 最短路径 | $\texttt{BFS}$ 保证最优 |

### 常见陷阱

1. **边界处理**：机器人不能移动到使身体超出网格的位置
2. **障碍物检查**：移动过程中需要检查所有经过的方格
3. **步进检查**：遇到障碍物后不能继续移动更远步数
4. **起点和终点**：都是交叉点坐标，不是方格坐标
