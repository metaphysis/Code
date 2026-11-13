[UVa 225 Golygons](https://blog.csdn.net/metaphysis/article/details/161087139)

## 题目分析

$\texttt{Golygon}$ 是一种特殊的网格路径，它从原点 $(0,0)$ 出发，第一步走 $1$ 个单位，第二步走 $2$ 个单位，依此类推，第 $n$ 步走 $n$ 个单位，且每一步必须向左转或向右转 $90^\circ$（不能直行或掉头），最终回到原点 $(0,0)$。路径可以自交。

本题在标准 $\texttt{Golygon}$ 问题的基础上增加了障碍物：某些网格点被封锁，路径不能经过这些点。需要找出所有满足条件的 $\texttt{Golygon}$，并按照字典序输出路径方向序列（$\texttt{n}$ 表示北，$\texttt{s}$ 表示南，$\texttt{e}$ 表示东，$\texttt{w}$ 表示西）。

输入包含多个测试用例，每个用例给出最大步长 $n \leq 20$ 和障碍物坐标（不超过 $50$ 个）。

## 解题思路

### 状态表示与搜索

使用深度优先搜索 ($\texttt{DFS}$) 枚举所有可能的路径。每步需要记录：
- 当前位置 $(x, y)$
- 当前行进方向（上一步的方向）
- 当前步长（已经走了几步）

方向用数字表示：$0$ 代表东 ($\texttt{e}$)，$1$ 代表北 ($\texttt{n}$)，$2$ 代表南 ($\texttt{s}$)，$3$ 代表西 ($\texttt{w}$)。

### 转向规则

由于不能直行或掉头，每一步只能左转或右转 $90^\circ$。用 `turn` 数组预计算两种转向结果：

| 当前方向 | 左转结果 | 右转结果 |
|:---:|:---:|:---:|
| $0$（东） | $1$（北） | $2$（南） |
| $1$（北） | $3$（西） | $0$（东） |
| $2$（南） | $0$（东） | $3$（西） |
| $3$（西） | $2$（南） | $1$（北） |

### 剪枝策略

由于 $n \leq 20$，直接搜索复杂度较高，需要剪枝：

1. **可行性剪枝**：如果当前点到原点的曼哈顿距离大于剩余步数所能走的最大距离，则此路径不可能回到原点。剩余步数 $k$ 到 $n$ 的最大步长和为：
   
   $$\frac{(k + n) \times (n - k + 1)}{2}$$
   
   如果 $|x| + |y| > \text{这个值}$，直接剪枝。

2. **障碍物检查**：移动过程中，如果经过的线段上有障碍物，则此方向无效。

3. **重复点标记**：用 `grid` 数组记录已经访问过的点，避免重复经过（路径可以自交，但重复访问点会导致无限循环，需要阻止）。

### 坐标偏移

障碍物坐标范围未知，但根据步长限制，最大可能坐标范围为：
- 最大步数 $n = 20$，位移最大值为 $1 + 2 + \cdots + 20 = 210$
- 考虑正负方向，坐标范围约为 $[-210, 210]$

使用 `base = 250` 将坐标偏移到非负索引，方便数组访问。

### 输出顺序

要求按字典序输出方向序列。由于方向编码 $\texttt{e} < \texttt{n} < \texttt{s} < \texttt{w}$，在搜索时按此顺序尝试即可保证字典序输出。

## 算法复杂度

最坏情况下分支数为 $2^n$，但剪枝大大减少了搜索空间。对于 $n \leq 20$，实际运行时间可以接受。

## 代码实现

```cpp
// Golygons
// UVa ID: 225 
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.390s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 点的结构体
struct point
{
    int x, y;
};

vector<point> blocks;        // 存储障碍物坐标
vector<int> golygons(30);    // 记录每一步的方向

string headingText = "ensw"; // 方向字符映射，顺序：东、北、南、西
// turn[当前方向][0]为左转，turn[当前方向][1]为右转
int turn[4][2] = { {1, 2}, {0, 3}, {0, 3}, {1, 2} };
// 四个方向对应的坐标变化：东、北、南、西
int direction[4][2] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };
int grid[500][500] = { 0 }, base = 250;  // 访问标记数组，base为坐标偏移量
int numberOfGolygons, longestEdge;       // 解的数量和最大步长

// 检查从 start 到 end 的线段上是否有障碍物
bool blocked(point start, point end)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        // 障碍物在水平线段上（x相同）
        if (blocks[i].x == start.x && blocks[i].x == end.x)
            if (blocks[i].y >= min(start.y, end.y)
                    && blocks[i].y <= max(start.y, end.y))
                return true;
        // 障碍物在垂直线段上（y相同）
        if (blocks[i].y == start.y && blocks[i].y == end.y)
            if (blocks[i].x >= min(start.x, end.x)
                    && blocks[i].x <= max(start.x, end.x))
                return true;
    }
    return false;
}

// 深度优先搜索
// traveler: 当前位置, heading: 当前方向, edge: 当前步长（已走步数）
void dfs(point traveler, int heading, int edge)
{
    // 剪枝：如果当前位置到原点的曼哈顿距离大于剩余步数能走的最大距离，则不可能返回
    if ((abs(traveler.x) + abs(traveler.y)) > ((edge + longestEdge) * (longestEdge - edge + 1) / 2))
	    return;
		    
    // heading < 0 表示第一步，需要尝试所有四个方向
    if (heading < 0)
    {
        for (int i = 0; i < 4; i++)
        {
            point newTraveler;
            newTraveler.x = traveler.x + direction[i][0];
            newTraveler.y = traveler.y + direction[i][1];
            
            // 检查第一步是否撞到障碍物
            if (blocked(traveler, newTraveler))
                continue;
                
            // 标记访问，记录方向，继续搜索
            grid[newTraveler.x + base][newTraveler.y + base] = 1;
            golygons[edge] = i;
            dfs(newTraveler, i, 1);
            grid[newTraveler.x + base][newTraveler.y + base] = 0;
        }
    }
    // 已走到最后一步，检查是否回到原点
    else if (edge == longestEdge)
    {
        if (traveler.x == 0 && traveler.y == 0)
        {
            // 输出方向序列
            for (int i = 0; i < edge; i++)
                cout << headingText[golygons[i]];
            cout << endl;
            numberOfGolygons++;
        }
    }
    else
    {
        // 左转的情况
        int turn1 = turn[heading][0];

        point end1;
        end1.x = traveler.x + direction[turn1][0] * (edge + 1);
        end1.y = traveler.y + direction[turn1][1] * (edge + 1);

        // 检查是否撞到障碍物且终点未被访问过
        if (blocked(traveler, end1) == false && grid[end1.x + base][end1.y + base] == 0)
        {
            grid[end1.x + base][end1.y + base] = 1;
            golygons[edge] = turn1;
            dfs(end1, turn1, edge + 1);
            grid[end1.x + base][end1.y + base] = 0;
        }
        
        // 右转的情况
        int turn2 = turn[heading][1];
        point end2;
        end2.x = traveler.x + direction[turn2][0] * (edge + 1);
        end2.y = traveler.y + direction[turn2][1] * (edge + 1);
        
        if (blocked(traveler, end2) == false && grid[end2.x + base][end2.y + base] == 0)
        {
            grid[end2.x + base][end2.y + base] = 1;
            golygons[edge] = turn2;
            dfs(end2, turn2, edge + 1);
            grid[end2.x + base][end2.y + base] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int cases, numberOfBlocks, x, y;
    cin >> cases;
    while (cases--)
    {
        cin >> longestEdge;

        int numberOfBlocks, x, y;

        blocks.clear();
        cin >> numberOfBlocks;
        for (int i = 1; i <= numberOfBlocks; i++)
        {
            cin >> x >> y;
            blocks.push_back((point){x, y});
        }

        point traveler;
        traveler.x = 0;
        traveler.y = 0;

        numberOfGolygons = 0;
        dfs(traveler, -1, 0);
        cout << "Found " << numberOfGolygons << " golygon(s)." << endl;
        cout << endl;
    }

    return 0;
}
```
