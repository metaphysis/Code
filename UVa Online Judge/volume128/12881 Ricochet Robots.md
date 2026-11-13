
> **摘要**：本题要求在 $10 \times 10$ 的网格工厂中，通过“滑动移动”规则操控最多 $4$ 个机器人，使 $1$ 号机器人停在指定目标格上，求最少总移动次数。由于状态可表示为机器人位置的四元组、转移代价均为 $1$，采用广度优先搜索（$\texttt{BFS}$）配合 $\texttt{set}$ 去重即可求解，并利用步数上限 $\ell \le 10$ 提前剪枝。

## 题目描述

一个由最多 $4$ 个机器人组成的团队在矩形网格工厂中运送零件。每个机器人占据一个单元格，可沿上下左右四个方向移动。机器人一旦开始运动，将沿该方向一直前进，直到其相邻位置出现障碍物（墙壁、工厂边界或其它静止机器人）时才会停止。任意时刻只有一个机器人移动。

目标是使编号为 $1$ 的机器人到达指定的目标单元格。移动过程中，其它机器人可被当作临时障碍物，用以帮助 $1$ 号机器人“弹跳”转向。注意，目标单元格本身不会使机器人停止，只有墙壁、边界和其它机器人会令其停止，且最终 $1$ 号机器人必须停在该目标格子上，而非仅仅经过。

给定工厂布局、所有机器人的初始位置以及目标位置，求 $1$ 号机器人到达目标位置所需的最少总移动次数。

## 输入格式

输入包含多个测试用例，每个测试用例格式如下：

第一行包含四个整数：机器人数量 $n$、工厂宽度 $w$、高度 $h$，以及搜索解的上限步数 $\ell$。

接下来 $h$ 行，每行一个长度为 $w$ 的字符串，表示该行每个单元格的类型：

- `'w'` 或 `'W'` 表示墙壁；
- `'X'` 表示唯一的目标单元格；
- `'1'` 至 `'4'` 表示对应编号机器人的初始位置；
- `'.'` 表示空单元格。

数据范围：$1 \le n \le 4$，$1 \le w, h \le 10$，$\max(w,h) \le 10$，$1 \le \ell \le 10$。

## 输出格式

对于每个测试用例，输出一行：若存在步数不超过 $\ell$ 的方案，则输出最少移动次数；否则输出 `NO SOLUTION`。

## 样例

**输入**

```text
2 5 4 10
.2...
...W.
WWW..
.X.1.
1 5 4 10
.....
...W.
WWW..
.X.1.
```

**输出**

```text
6
NO SOLUTION
```

## 题目分析

本题属于状态空间搜索问题。状态数量有限，因为网格最大为 $10 \times 10 = 100$ 个格子，机器人最多 $4$ 个，每个状态可表示为所有机器人所在格子的一维索引的 $4$ 元组。搜索深度上限 $\ell \le 10$ 很小，因此可以使用广度优先搜索（$\texttt{BFS}$）在状态图上求解最短路径。

状态转移的关键在于模拟单个机器人的“滑动移动”。移动规则为：选择一个机器人，向其四个方向之一发射，机器人会沿该方向连续前进，直到前方某格是墙壁、边界或其它机器人所在格时停止。若初始方向第一步即被阻挡，则机器人原地不动，该转移无效。

由于机器人在移动过程中不会停下，直到遇到障碍物，因此从一个状态出发，每个机器人每个方向最多产生一个合法的新状态。总状态数有限，且转移代价均为 $1$，故 $\texttt{BFS}$ 可保证首次到达目标状态时步数最小。

需要特别注意：目标单元格 `'X'` 不充当障碍物，机器人可穿过它但不会因此停止，只有最终停在该位置才算成功。因此判断终止条件只需检查 $1$ 号机器人的当前位置是否等于目标格子索引。

## 解题思路

### 状态表示

使用 $\texttt{array<int, 4>}$ 存储 $4$ 个机器人的位置索引（从 $0$ 到 $w \times h - 1$）。对于未使用的机器人（即编号大于 $n$），位置设为 $-1$ 并始终不参与移动。

### 移动模拟

对于状态 $S$，选择机器人 $k$（$0 \le k < n$）和方向 $d \in \{0,1,2,3\}$，从该机器人当前格出发，沿方向逐格试探，直到遇到以下情况之一则停止：

- 下一格超出边界；
- 下一格是墙壁（字符为 `'w'` 或 `'W'`）；
- 下一格被其它机器人占据（编号不等于 $k$ 的机器人位置与该格相同）。

若停止位置与起始位置相同，则该方向移动无效；否则产生新状态 $S'$，其中仅机器人 $k$ 的位置改变。

### 搜索算法

执行 $\texttt{BFS}$，初始状态为所有机器人的初始位置，步数为 $0$。维护一个集合（$\texttt{set}$）记录已访问状态，避免重复扩展。每次从队列取出状态 $S$ 及其步数 $step$：

- 若 $S[0] = targetIdx$，返回 $step$；
- 若 $step \ge \ell$，不再扩展该状态；
- 否则枚举所有机器人和四个方向，生成合法新状态并入队。

因为 $\ell \le 10$，状态总数不会超过 $(100)^4$ 的理论上限，但实际有效状态远小于该值，使用 $\texttt{set}$ 去重完全可行。

### 边界情况

- 若 $1$ 号机器人初始即在目标位置，则答案为 $0$。
- 若某个机器人无法移动（四周全被堵死），其相应方向转移会被过滤。
- 输入中可能存在大写 `'W'` 表示墙壁，判定时应同时识别大小写。

## 代码实现

```cpp
// Ricochet Robots
// UVa ID: 12881
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, w, h, l;
vector<string> grid;
int targetIdx;
array<int, 4> initPos;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 计算机器人 robot 沿方向 dir 移动后的终点（若无法移动则返回原位置）
int getMove(int robot, int dir, const array<int, 4>& pos) {
    int idx = pos[robot];
    int x = idx % w, y = idx / w;
    while (true) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || nx >= w || ny < 0 || ny >= h) break;          // 边界阻挡
        int nidx = ny * w + nx;
        // 墙壁阻挡（大小写兼容）
        if (grid[ny][nx] == 'w' || grid[ny][nx] == 'W') break;
        bool occupied = false;
        for (int i = 0; i < n; ++i)
            if (i != robot && pos[i] == nidx) { occupied = true; break; }
        if (occupied) break;                                        // 其他机器人阻挡
        // 可前进
        x = nx; y = ny; idx = nidx;
    }
    return idx;
}

// BFS 搜索，返回最小步数或 -1（无解或超过上限）
int bfsSolve() {
    queue<pair<array<int, 4>, int>> q;
    set<array<int, 4>> visited;
    array<int, 4> start;
    start.fill(-1);
    for (int i = 0; i < n; ++i) start[i] = initPos[i];
    q.push({start, 0});
    visited.insert(start);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        array<int, 4> s = cur.first;
        int steps = cur.second;
        if (s[0] == targetIdx) return steps;
        if (steps >= l) continue;   // 超出上限不再扩展
        for (int robot = 0; robot < n; ++robot) {
            for (int d = 0; d < 4; ++d) {
                int newIdx = getMove(robot, d, s);
                if (newIdx == s[robot]) continue;
                array<int, 4> ns = s;
                ns[robot] = newIdx;
                if (visited.find(ns) == visited.end()) {
                    visited.insert(ns);
                    q.push({ns, steps + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> w >> h >> l) {
        grid.resize(h);
        initPos.fill(-1);
        targetIdx = -1;
        for (int y = 0; y < h; ++y) {
            cin >> grid[y];
            for (int x = 0; x < w; ++x) {
                char ch = grid[y][x];
                if (ch == 'X') targetIdx = y * w + x;
                else if (ch >= '1' && ch <= '4') {
                    int id = ch - '1';
                    if (id < n) initPos[id] = y * w + x;
                }
            }
        }
        int ans = bfsSolve();
        if (ans == -1) cout << "NO SOLUTION\n";
        else cout << ans << '\n';
    }
    return 0;
}
```

## 总结

本题核心是利用广度优先搜索在受限深度下求解机器人滑动移动的最短路径。关键点如下：

- 状态空间小，可用简单的 $\texttt{BFS}$ 配合 $\texttt{set}$ 去重直接求解。
- 移动模拟需严格遵循“遇障碍物停”的规则，注意目标格不视为障碍物，且墙壁字符可能出现大小写两种形式。
- 步数上限 $\ell$ 较小，可提前剪枝，避免搜索超出限制。
- 多机器人场景中，其它机器人既可作为障碍物，也可被移动，因此状态转移时需考虑所有机器人，但每次仅移动一个。

此类问题的通用技巧是定义清晰的状态表示和转移函数，并利用广度优先搜索求最短步数，适合作为搜索入门的进阶练习题。
