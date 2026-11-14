[UVa 395 Board Silly](https://blog.csdn.net/metaphysis/article/details/161705466)

## 题目描述

你是一个程序员团队的成员，负责编写一款棋盘游戏。你的任务是编写检查棋盘布局并枚举给定玩家的所有可能移动的程序。

游戏在 $8 \times 8$ 的方格棋盘上进行。行从上到下用字母 $A \sim H$ 标记，列从左到右用数字 $1 \sim 8$ 标记。每个玩家在棋盘上可能有 $1$ 到 $12$ 个棋子（每个玩家只有一种棋子类型）。

### 移动规则

1. 棋子可以沿直线移动：左、右、上、下或对角线
2. 棋子移动的格子数由该棋子所在行、列或对角线上的**总棋子数**（包括自身）决定，必须移动**确切**的这个步数，不能多也不能少
3. 玩家可以跳过自己的棋子
4. 玩家不能跳过对方的棋子
5. 玩家可以吃掉对方的棋子（落在对方棋子上）
6. 玩家不能落在自己已占据的位置上

### 输入格式

输入包含一个或多个棋盘布局，每个布局后跟一行指定要显示移动的棋子（`X` 或 `O`）。

每个棋盘由 $8$ 行组成，每行 $8$ 个字符：
- `X`、`O`：被占据的位置
- `.`：空位

输入以文件结束符（$\texttt{EOF}$）结束。

### 输出格式

对于每个可能的移动，输出一行，格式为 `origin-destination`（如 `A1-B3`）。按**起始位置**的字母顺序排序，起始位置相同时按**目标位置**排序。如果无移动可能，输出 `No moves are possible`。每个棋盘输出后跟一个空行。

### 样例输入

```
O.......
O......X
O.....XX
O....XXX
O...XXX.
......X.
.....X..
....X...
X
```

### 样例输出

```
A1-E5
A1-F6
A1-G7
A1-H8
B2-F6
```

---

## 题目分析

### 问题的本质

这是一个**棋盘移动枚举**问题。需要根据规则枚举所有合法移动。

### 移动步数计算

对于位于 $(r, c)$ 的棋子，沿方向 $d$ 移动的步数 = 该方向上的总棋子数（包括自身）。

即：从该棋子出发，沿方向 $d$ 一直走直到棋盘边界，统计该直线上**所有格子**（包括起点）上的棋子总数，记为 $n$。棋子可以移动 $n$ 步（方向 $d$），落到距起点 $n$ 步的位置。

### 移动合法性检查

设起点为 $S$，目标点为 $T$，方向为 $d$，步数 $n = \text{steps}$：
1. $T$ 必须在棋盘内
2. $T$ 不能被己方棋子占据
3. 路径上（不包括起点，包括终点？实际上规则要求“不能跳过对方棋子”，意味着路径上的中间格子不能有对方棋子）
   - 可以经过己方棋子（跳过）
   - 不能经过对方棋子
   - 终点可以是对方棋子（吃子）

---
## 参考代码

```cpp
// Board Silly
// UVa ID: 395
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[8][8];
int steps[8][8][8];      // 每个位置每个方向的移动步数
int copies[8][8][8];     // 每个方向上的棋子数（不含自身）
int offset[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, 
                    {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

struct action
{
    string from, to;
    bool operator<(const action &next) const
    {
        if (from != next.from)
            return from < next.from;
        else
            return to < next.to;
    }
};

void findMove(char piece)
{
    memset(steps, 0, sizeof(steps));
    memset(copies, 0, sizeof(copies));

    // 统计每个位置每个方向上的棋子数（不含自身）
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] == piece)
            {
                for (int d = 0; d < 8; d++)
                {
                    int totalPieces = 0;
                    int ni = i + offset[d][0], nj = j + offset[d][1];
                    while (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
                    {
                        if (grid[ni][nj] != '.')
                            totalPieces++;
                        ni += offset[d][0];
                        nj += offset[d][1];
                    }
                    copies[i][j][d] = totalPieces;
                }
                
                // 计算移动步数 = 两个相反方向棋子数 + 1
                for (int d = 0; d < 4; d++)
                {
                    steps[i][j][2 * d] = copies[i][j][2 * d] + copies[i][j][2 * d + 1] + 1;
                    steps[i][j][2 * d + 1] = copies[i][j][2 * d] + copies[i][j][2 * d + 1] + 1;
                }
            }

    vector<action> allMoves;
    // 枚举所有可能的移动
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] == piece)
            {
                for (int d = 0; d < 8; d++)
                {
                    int ni = i + offset[d][0] * steps[i][j][d];
                    int nj = j + offset[d][1] * steps[i][j][d];
                    
                    // 目标位置必须在棋盘内且不能是己方棋子
                    if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8 && grid[ni][nj] != piece)
                    {
                        bool valid = true;
                        // 检查路径上是否有对方棋子
                        for (int k = 1; k < steps[i][j][d]; k++)
                        {
                            int mi = i + offset[d][0] * k;
                            int mj = j + offset[d][1] * k;
                            if (grid[mi][mj] != '.' && grid[mi][mj] != piece)
                            {
                                valid = false;
                                break;
                            }
                        }
                        if (valid)
                        {
                            action a;
                            a.from = string(1, 'A' + i) + to_string(j + 1);
                            a.to = string(1, 'A' + ni) + to_string(nj + 1);
                            allMoves.push_back(a);
                        }
                    }
                }
            }

    // 排序并输出
    sort(allMoves.begin(), allMoves.end());
    for (auto& move : allMoves)
        cout << move.from << "-" << move.to << endl;

    if (allMoves.empty()) 
        cout << "No moves are possible" << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    char piece;
    int counter = 0, cases = 0;

    // 读取棋盘（8x8 = 64 个字符）
    while (cin >> piece)
    {
        grid[counter / 8][counter % 8] = piece;
        counter++;
        if (counter == 64) 
        {
            if (cases++) cout << endl;
            cin >> piece;  // 读取要移动的棋子类型
            findMove(piece);
            counter = 0;
        }
    }

    return 0;
}
```
