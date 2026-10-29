## 题目描述

一张数字化地图由二维网格表示，地图由轮廓线包围的一组点构成。地图的闭合轮廓（可为任意矩形形状）和轮廓内部的障碍物均用字符 `'X'` 标记；地图中的空闲点用空格表示。地图上恰好有两个起点 / 终点，用字符 `'@'` 标记。起点 / 终点不能出现在地图外部或轮廓线上。地图中除空闲点（空格）、障碍物（`X`）和起点 / 终点（`@`）外没有其他点。

两点之间的路径只能垂直和 / 或水平穿过地图内部的空闲点（在地图轮廓内）。路径的长度为路径经过的点数（包括起点和终点）。路径的转弯次数为遍历路径时方向改变的次数。

编写程序，对于从文本文件中读取的每张地图，找出**所有可能的最短路径**（长度最短）中**转弯次数最少**的路径，并用字符 `'#'` 标记这些路径上的点。

## 输入格式

每个测试用例包含一张地图，由若干行组成，每行最多 $80$ 个字符，地图行数不超过 $40$。地图中只包含字符 `'X'`、空格、`'@'`。地图的轮廓由 `'X'` 围成，且轮廓为矩形。地图内可以包含若干障碍物（`'X'`）。每张地图以一行全由下划线 `'_'` 组成的行结束。各行长度可能不同，输入数据保证正确。

## 输出格式

对于每张地图，先输出一行统计信息，格式为：

```
<路径数> paths, <点数> points, <转弯数> turns
```

其中，点数是最短路径的长度（含起点和终点），转弯数是这些最优路径的转弯次数。之后输出地图，将属于所有最优路径上的点标记为 `'#'`，但起点和终点仍保留为 `'@'`。地图格式与输入相同，包括终止行。

## 样例

### 样例输入

```
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X           X             @  X
X                   X        X
X                            X
XXXXXX          X            X
X               X            X
X        X              XXXXXX
X@       X              X
XXXXXXXXXXXXXXXXXXXXXXXXX
______________________________
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X                            X
X        @@             XXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
______________________________

```

### 样例输出

```
6 paths, 32 points, 3 turns
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X           X#############@  X
X            ###    X     #  X
X     #####################  X
XXXXXX###    ###X            X
X###############X            X
X#    ###X              XXXXXX
X@#######X              X
XXXXXXXXXXXXXXXXXXXXXXXXX
______________________________
1 paths, 2 points, 0 turns
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X                            X
X        @@             XXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
______________________________

```

## 题目分析

本题要求在地图上找出所有**长度最短**的路径，并从中筛选出**转弯次数最少**的路径，最后标记这些路径。这是一个典型的多目标优化问题，且需要输出所有满足条件的路径上的点，而不仅仅是路径数量。

地图规模为 $40 \times 80$ 的网格，点数最多 $3200$，状态空间较小，可以使用动态规划结合广度优先搜索来处理。

关键点包括：
- 路径只能在空闲格（非 `'X'`）上移动，且不能越界。
- 最短路径长度可通过从起点到终点的 $\texttt{BFS}$ 获得。
- 在保证路径长度最短的前提下，需要最小化转弯次数。
- 需要统计达到最优（最短长度 + 最少转弯）的路径条数，并标记这些路径上的所有点。

直接枚举所有最短路径会指数爆炸，因此需要设计高效的状态转移和回溯方法。

## 解题思路

### 第一步：读入与网格规范化

逐行读入地图，当遇到全由下划线组成的行时，认为当前地图结束。将地图行存储为字符串列表，由于各行长度可能不同，需要统一补齐到最大宽度（用空格填充），以便后续二维数组操作。

### 第二步：计算最短距离（长度）

从起点 `'@'` 出发，执行 $\texttt{BFS}$（广度优先搜索），计算到每个可达空格的最短步数（即经过的边数）。终点处的步数记为 $S$，则最短路径的点数为 $S + 1$（因为步数 = 点数 $- \ 1$）。只有位于该最短距离层次上的点才可能属于最优路径。

### 第三步：动态规划求最少转弯次数与路径计数

由于我们只关心最短路径，所以任何转移都只能从距离为 $d$ 的格点走到距离为 $d+1$ 的相邻格点。定义状态为 `(r, c, d)`，其中 `(r, c)` 是当前格点坐标，`d` 表示进入该格点时的方向（$0=$上，$1=$下，$2=$左，$3=$右）。状态的含义是：在满足从起点到 `(r, c)` 的距离等于 $\textit{dist}[r][c]$ 的前提下，到达该状态的最小转弯次数。

令 `turn[r][c][dir]` 表示状态 `(r, c, dir)` 的最小转弯次数，`ways[r][c][dir]` 表示达到该最小转弯次数的路径条数。初始化：从起点出发到相邻格点（距离为 $1$）的四个状态，转弯次数为 $0$，路径条数为 $1$（因为从起点直接走一步，没有转弯）。

然后按距离从小到大进行状态转移。对于每个状态 `(r, c, dir)`，尝试向四个方向 `nd` 移动一步到达新格点 `(nr, nc)`，要求 `dist[nr][nc] == dist[r][c] + 1`。新的转弯次数为 `turn[r][c][dir] + (dir != nd ? 1 : 0)`。如果小于 `turn[nr][nc][nd]`，则更新并设置路径数为当前 `ways`；如果相等，则将当前 `ways` 累加到目标状态。

注意：这里每个格点可能有多个不同方向的状态，分别存储了从不同方向进入该点时的最优值，这样能够正确处理转弯的计数。

### 第四步：统计最优结果

终点 `(er, ec)` 的最少转弯次数为 `minTurns = min(turn[er][ec][d])`，总路径数为所有达到 `minTurns` 的状态的 `ways` 之和。

### 第五步：反向回溯标记所有最优路径上的点

为了标记所有最优路径上的点，需要从终点的所有最优状态出发，反向寻找前驱状态。前驱状态 `(pr, pc, pd)` 必须满足：
- `dist[pr][pc] == dist[r][c] - 1`，即前驱距离少 $1$。
- 状态可达，即 `turn[pr][pc][pd]` 有限。
- 转移代价满足：`turn[pr][pc][pd] + (pd != d ? 1 : 0) == turn[r][c][d]`。

使用一个栈（或队列）进行深度优先回溯，标记所有访问过的格点。注意需要避免重复访问同一状态（使用 `visited` 三维布尔数组）。回溯时，如果到达起点，直接标记起点即可（起点最终保留为 `'@'`，但为了回溯完整性也进行标记）。

### 第六步：输出

先输出统计行，然后逐行输出地图。对于每个格点，如果原始字符是 `'@'`，则输出 `'@'`；否则如果被标记为路径点，则输出 `'#'`；否则输出原始字符（可能是空格或 `'X'`）。最后输出终止行。

### 复杂度分析

- $\texttt{BFS}$：$O(R \cdot C)$。
- $\texttt{DP}$ 转移：对每个格点的每个方向（$4$ 种），尝试向 $4$ 个方向转移，故 $O(R \cdot C \cdot 4 \cdot 4) = O(R \cdot C)$。
- 回溯标记：每个状态最多被访问一次，$O(R \cdot C \cdot 4)$。
- 总时间复杂度 $O(R \cdot C)$，空间复杂度 $O(R \cdot C \cdot 4)$。其中 $R \le 40$，$C \le 80$，完全可行。

## 代码实现

```cpp
// Straightest Paths
// UVa ID: 794
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c, d;
};

void solveMap(const vector<string>& mapLines, const string& termLine) {
    if (mapLines.empty()) return;
    const int R = (int)mapLines.size();
    int C = 0;
    for (const string& s : mapLines) C = max(C, (int)s.size());
    vector<string> grid(R, string(C, ' '));
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < (int)mapLines[i].size(); ++j)
            grid[i][j] = mapLines[i][j];
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (grid[i][j] == '@') {
                if (sr == -1) { sr = i; sc = j; }
                else { er = i; ec = j; }
            }
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    // BFS 求最短距离（步数）
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop();
        int r = cur.first, c = cur.second;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == 'X') continue;
            if (dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    int shortestDist = dist[er][ec];
    int points = shortestDist + 1;
    const int INF = 1e9;
    vector<vector<vector<int>>> turn(R, vector<vector<int>>(C, vector<int>(4, INF)));
    vector<vector<vector<long long>>> ways(R, vector<vector<long long>>(C, vector<long long>(4, 0)));
    // 从起点出发的第一步
    for (int d = 0; d < 4; ++d) {
        int nr = sr + dr[d], nc = sc + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (grid[nr][nc] == 'X') continue;
        if (dist[nr][nc] == 1) {
            turn[nr][nc][d] = 0;
            ways[nr][nc][d] = 1;
        }
    }
    // DP 按距离递增
    for (int step = 1; step <= shortestDist; ++step) {
        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c) {
                if (dist[r][c] != step) continue;
                for (int d = 0; d < 4; ++d) {
                    if (turn[r][c][d] == INF) continue;
                    int curTurn = turn[r][c][d];
                    long long curWays = ways[r][c][d];
                    for (int nd = 0; nd < 4; ++nd) {
                        int nr = r + dr[nd], nc = c + dc[nd];
                        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                        if (grid[nr][nc] == 'X') continue;
                        if (dist[nr][nc] != dist[r][c] + 1) continue;
                        int newTurn = curTurn + (nd != d ? 1 : 0);
                        if (newTurn < turn[nr][nc][nd]) {
                            turn[nr][nc][nd] = newTurn;
                            ways[nr][nc][nd] = curWays;
                        } else if (newTurn == turn[nr][nc][nd]) {
                            ways[nr][nc][nd] += curWays;
                        }
                    }
                }
            }
    }
    // 统计终点的最优值
    int minTurns = INF;
    long long totalPaths = 0;
    for (int d = 0; d < 4; ++d) {
        if (turn[er][ec][d] < minTurns) {
            minTurns = turn[er][ec][d];
            totalPaths = ways[er][ec][d];
        } else if (turn[er][ec][d] == minTurns) {
            totalPaths += ways[er][ec][d];
        }
    }
    // 标记所有最优路径上的点
    vector<vector<bool>> mark(R, vector<bool>(C, false));
    vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(4, false)));
    vector<State> st;
    for (int d = 0; d < 4; ++d)
        if (turn[er][ec][d] == minTurns && !visited[er][ec][d]) {
            visited[er][ec][d] = true;
            st.push_back({er, ec, d});
        }
    while (!st.empty()) {
        State cur = st.back(); st.pop_back();
        int r = cur.r, c = cur.c, d = cur.d;
        mark[r][c] = true;
        if (r == sr && c == sc) continue;
        int pr = r - dr[d], pc = c - dc[d];
        if (pr < 0 || pr >= R || pc < 0 || pc >= C) continue;
        if (grid[pr][pc] == 'X') continue;
        if (dist[pr][pc] != dist[r][c] - 1) continue;
        for (int pd = 0; pd < 4; ++pd) {
            if (turn[pr][pc][pd] == INF) continue;
            int cost = (pd != d ? 1 : 0);
            if (turn[pr][pc][pd] + cost == turn[r][c][d]) {
                if (pr == sr && pc == sc) {
                    mark[pr][pc] = true;
                } else if (!visited[pr][pc][pd]) {
                    visited[pr][pc][pd] = true;
                    st.push_back({pr, pc, pd});
                }
            }
        }
    }
    // 输出
    cout << totalPaths << " paths, " << points << " points, " << minTurns << " turns\n";
    for (int i = 0; i < R; ++i) {
        string out;
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == '@') out += '@';
            else if (mark[i][j]) out += '#';
            else out += grid[i][j];
        }
        while (out.size() && out.back() == ' ') out.pop_back();
        cout << out << '\n';
    }
    cout << termLine << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    vector<string> mapLines;
    while (getline(cin, line)) {
        bool isTerm = true;
        for (char ch : line)
            if (ch != '_') { isTerm = false; break; }
        if (isTerm) {
            solveMap(mapLines, line);
            mapLines.clear();
        } else mapLines.push_back(line);
    }
    return 0;
}
```

## 总结

本题综合运用了 $\texttt{BFS}$ 求最短距离、动态规划求多目标最优值，以及反向回溯标记所有最优路径。核心技巧是**将方向信息引入状态**，使得转弯次数的计算得以在最短路径约束下正确进行。同时，通过 `ways` 数组累计路径条数，并利用 `visited` 避免重复回溯，高效标记所有公共点。

该解法适用于小规模网格（$40 \times 80$），时空开销都在可接受范围内。如果地图规模扩大，可以考虑对状态进行压缩，但本题无需额外优化。掌握这种**状态扩展 + 多目标 $\texttt{DP}$** 的方法，对解决类似迷宫最优路径问题具有普遍意义。
