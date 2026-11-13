[UVa 298 Race Tracks](https://blog.csdn.net/metaphysis/article/details/161389705)

## 题目分析

**$\texttt{Race Tracks}$** 是一个在网格上进行的路径搜索问题，但与传统的最短路径问题不同，移动的主体是一个带有速度的 “跳跃者”（$\texttt{Hopper}$）。问题描述如下：

- 网格大小为 $X \times Y$，其中 $1 \leq X, Y \leq 30$。
- 每个格子要么是空的，要么被障碍物占据。跳跃者只能落在空地上，但可以飞越障碍物。
- 跳跃者在每个时刻有一个速度向量 $(v_x, v_y)$，表示在 $x$ 方向和 $y$ 方向上每次移动的步长，每个分量的取值范围是 $[-3, 3]$ 之间的整数。
- 每次移动时，跳跃者可以将其速度的每个分量改变 $-1$、$0$ 或 $+1$。也就是说，从当前速度 $(v_x, v_y)$ 可以变化到 $(v_x + \Delta x, v_y + \Delta y)$，其中 $\Delta x, \Delta y \in \{-1, 0, 1\}$，且变化后的速度分量不能超过 $[-3, 3]$ 的范围。
- 跳跃者从起点 $S$ 出发，初始速度为 $(0, 0)$，目标是在最少的移动次数内到达终点 $F$。到达终点时对速度没有要求。
- 如果无法到达终点，输出 `No solution.`；否则输出 `Optimal solution takes N hops.`。

### 问题的难点

1. **状态空间扩展**：传统 BFS 只记录位置 $(x, y)$，而本题的状态还包括当前速度 $(v_x, v_y)$。因为速度会影响下一步能够到达的位置，所以状态总数最多为 $30 \times 30 \times 7 \times 7 = 44100$，这在 $\texttt{BFS}$ 的可接受范围内。
2. **障碍物处理**：障碍物以矩形区域的形式给出，需要标记所有被占据的格子。跳跃者不能落在障碍物上，但可以飞越。
3. **无解判断**：当所有可能的状态都被探索完仍未到达终点时，输出 `No solution.`。

## 解题思路

### 状态表示

在 $\texttt{BFS}$ 中，每个状态可以表示为 $(x, y, v_x, v_y)$，其中：

- $(x, y)$ 表示当前所在位置（格子坐标）。
- $(v_x, v_y)$ 表示当前速度（即下一步移动时的步长）。

起点状态为 $(startx, starty, 0, 0)$，步数为 $0$。

### $\texttt{BFS}$ 过程

由于每次移动的代价为 $1$（一次跳跃），且状态空间有限，使用 **广度优先搜索（$\texttt{BFS}$）** 可以保证首次到达终点的步数最少。

对于当前状态 $(x, y, v_x, v_y)$，考虑所有合法的速度变化：

- 对 $\Delta x \in \{-1, 0, 1\}$，$\Delta y \in \{-1, 0, 1\}$，计算新的速度 $(v_x + \Delta x, v_y + \Delta y)$。
- 检查新速度的每个分量是否在 $[-3, 3]$ 范围内。若超出，则跳过。
- 计算新位置 $(x + v_x', y + v_y')$。
- 检查新位置是否在网格范围内，且不是障碍物。
- 若该状态未被访问过，则标记为已访问，并将其加入 $\texttt{BFS}$ 队列。

### 访问标记

由于状态包含位置和速度，使用一个 $X \times Y \times 7 \times 7$ 的三维或四维布尔数组即可标记访问状态。代码中使用了一个 $\texttt{set<string>}$ 来存储状态键值，这是一种简便但效率稍低的方法。在网格规模较小时（$30 \times 30$），这种方法仍能通过。

### 障碍物预处理

输入中障碍物以矩形区域的形式给出。我们需要将所有被覆盖的格子标记为不可用。由于网格最大为 $30 \times 30$，可以直接使用二维数组 $\texttt{grid}[x][y]$ 标记，$1$ 表示障碍物，$0$ 表示空地。

### 边界条件

- 起点保证不是障碍物。
- 终点可能是障碍物吗？题目没有明确禁止，但根据常理和样例，终点应为空地。若终点是障碍物，则必然无解。
- 速度分量的变化每次只能为 $\pm 1$ 或 $0$，这保证了速度不会突变，符合物理直觉。

## 时间复杂度分析

- 状态总数：$X \times Y \times 7 \times 7 \leq 30 \times 30 \times 49 = 44100$。
- 每个状态的转移：$3 \times 3 = 9$ 种可能的速度变化。
- 总操作数约为 $4 \times 10^4 \times 9 = 3.6 \times 10^5$，在时间和空间上均可接受。

## 代码实现

```cpp
// Race Tracks
// UVa ID: 298
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.820s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 定义状态结构体：位置 (x, y)，速度 (vx, vy)，当前步数 step
struct hop
{
    int x, y, vx, vy, step;
};

int grid[31][31];   // 网格，0 表示空地，1 表示障碍物
int X, Y;           // 网格宽度和高度
int startx, starty, endx, endy;  // 起点和终点坐标
set<string> visited;  // 记录已访问的状态

// 将状态编码为字符串，用于在 set 中判重
string getKey(int x, int y, int vx, int vy)
{
    return to_string(x) + "*" + to_string(y) + "*" + to_string(vx) + "*" + to_string(vy);
}

// 广度优先搜索求解最少跳跃次数
void bfs()
{
    visited.clear();
    
    queue<hop> unvisited;
    // 初始状态：起点，速度为 (0,0)，步数为 0
    unvisited.push((hop){startx, starty, 0, 0, 0});
    
    while (unvisited.size())
    {
        hop current = unvisited.front();
        unvisited.pop();
        
        // 到达终点，输出结果
        if (current.x == endx && current.y == endy)
        {
            cout << "Optimal solution takes " << current.step << " hops." << endl;
            return;
        }
        
        // 枚举速度的三种变化：-1, 0, 1
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {   
                int vxx = current.vx + i;  // 新的 x 方向速度
                int vyy = current.vy + j;  // 新的 y 方向速度
                
                // 速度分量必须在 [-3, 3] 范围内
                if (abs(vxx) > 3 || abs(vyy) > 3)
                    continue;
                    
                // 计算新位置
                int xx = current.x + vxx;
                int yy = current.y + vyy;
                
                // 检查新位置是否在网格范围内
                if (xx >= 0 && xx < X && yy >= 0 && yy < Y)
                {
                    // 检查新位置是否为障碍物
                    if (grid[xx][yy] == 1)
                        continue;
                        
                    // 检查该状态是否已被访问过
                    string key = getKey(xx, yy, vxx, vyy);
                    if (visited.count(key) > 0)
                        continue;
                    else
                        visited.insert(key);
                        
                    // 将新状态加入队列，步数加 1
                    unvisited.push((hop){xx, yy, vxx, vyy, current.step + 1});
                }
            }
    }
    
    // 队列为空仍未到达终点，无解
    cout << "No solution." << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int N;
    cin >> N;
    
    while (N--)
    {
        cin >> X >> Y;
        
        // 初始化网格，全部设为空地
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                grid[i][j] = 0;
        
        // 读取起点和终点坐标
        cin >> startx >> starty >> endx >> endy;
                
        int P;
        cin >> P;
        // 读取并标记障碍物矩形区域
        for (int i = 1; i <= P; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            
            for (int m = x1; m <= x2; m++)
                for (int n = y1; n <= y2; n++)
                    grid[m][n] = 1;
        }
        
        bfs();
    }
    
	return 0;
}
```

## 总结

本题是一个典型的状态空间 BFS 问题，关键在于将速度纳入状态表示中。由于速度范围小、网格规模适中，BFS 可以高效求解。解题时需注意：

1. 速度变化限制为 $\pm 1$ 或 $0$，且速度分量绝对值不超过 $3$。
2. 障碍物以矩形区域给出，需要预处理标记。
3. 使用 BFS 保证首次到达终点的步数最少。

通过合理设计状态和转移规则，即可在有限时间内得到正确结果。
