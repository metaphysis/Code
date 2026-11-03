
> **摘要**：本题要求在 $10000 \times 10000$ 的连续房间中，计算捕食者在不穿越隔间墙壁的前提下能够到达的区域总面积。由于房间规模巨大而隔间数量极少（$C \le 4$），采用**坐标离散化**将连续坐标压缩为至多 $9 \times 9$ 的网格，再精确标记隔间墙壁所在的公共边，最后用 $\texttt{BFS}$ 从起点单元格出发累加可达单元格的实际面积。整体时间复杂度为 $O(T \cdot (C^3 + Q C^2))$，空间复杂度 $O(C^2)$。

## 题目描述

在一个大小为 $10000 \times 10000$ 的正方形房间中，存在若干个正方形隔间。每个隔间面积不超过 $10000$ 平方单位（即边长不超过 $100$），隔间边与房间边平行，可能相互重叠，且所有隔间都严格位于房间内部（不与房间边界重合）。房间内有一只捕食者，它不能穿越隔间的墙壁或房间的墙壁。给定捕食者的起始坐标，要求计算捕食者能够到达的区域总面积。

房间可视为一个 $10000 \times 10000$ 的方形网格，坐标从 $0$ 到 $10000$ 连续变化。

## 输入格式

输入包含多组测试用例，直到文件结束。每组用例格式如下：

- 第一行包含一个整数 $C$（$C \le 4$），表示隔间的数量。
- 接下来 $C$ 行，每行三个整数 $r$、$c$、$s$，分别表示一个隔间的**行坐标**（纵坐标）、**列坐标**（横坐标）和边长。隔间的左边界为 $c$，右边界为 $c+s$；下边界为 $r$，上边界为 $r+s$。
- 接下来一行包含一个整数 $Q$（$Q \le 5$），表示捕食者位置查询的数量。
- 接下来 $Q$ 行，每行两个整数 $pr$、$pc$，表示捕食者的行坐标和列坐标。

房间坐标为 $0$ 到 $10000$，包括边界。隔间墙壁坐标与房间墙壁坐标不重合。

## 输出格式

对于每组测试用例，首先输出一行 `Case X:`，其中 $X$ 为用例编号（从 $1$ 开始）。然后对于每个查询，输出一行，包含该捕食者能够到达的区域总面积。

## 样例

**输入**
```
3
2 2 3
6 3 4
4 6 3
3
3 2
6 6
10000 10000
1
5 5 10
1
5 5
```

**输出**
```
Case 1:
9
1
99999967
Case 2:
100
```

## 题目分析

本题的核心在于处理连续空间中的障碍物，且房间规模巨大（$10^8$ 个网格单位），无法直接枚举全部坐标点。隔间数量极少（$C \le 4$），因此考虑使用**坐标离散化**将连续坐标映射到有限的单元格集合。

离散化后的单元格由相邻关键坐标（隔间边界及房间边界）围成矩形区域，其宽度和高度由原始坐标差决定。每个单元格代表一段连续区域，且内部不包含任何隔间边界，因此隔间边界必然落在单元格的公共边上。

障碍物为隔间的**墙壁**，而非内部空间。捕食者可以进入隔间内部，但不能穿越墙壁。因此，在离散化网格中，需要标记所有被隔间边界占据的公共边（垂直边和水平边）。$\texttt{BFS}$ 从起点所在的单元格出发，仅当相邻单元格之间的公共边未被墙壁占据时，才允许通行。

## 解题思路

### 步骤 $\texttt{1}$. 收集关键坐标

对于每组测试用例，首先收集所有隔间的左右边界（$c$ 和 $c+s$）以及上下边界（$r$ 和 $r+s$），并加入房间边界 $0$ 和 $10000$。分别对这些 $x$ 坐标和 $y$ 坐标排序去重，得到数组 $xs$ 和 $ys$。此时，$xs$ 中相邻两个值构成一个水平区间，$ys$ 中相邻两个值构成一个垂直区间，所有区间交叉形成一个离散网格。

### 步骤 $\texttt{2}$. 标记墙壁边

对于每个隔间，其四条边分别对应一条直线（左边界 $x=c$，右边界 $x=c+s$，下边界 $y=r$，上边界 $y=r+s$）。遍历所有相邻单元格的公共边：

- **垂直公共边**：位于 $x = xs[i+1]$（$0 \le i < nx-1$），其纵向范围覆盖 $y \in [ys[j], ys[j+1])$（$0 \le j < ny$）。若该垂直边与某个隔间的左边界或右边界重合，且该隔间的纵向范围与该公共边的纵向范围有正面积重叠（即重叠长度大于 $0$），则将该公共边标记为墙（不可穿越）。
- **水平公共边**：位于 $y = ys[j+1]$（$0 \le j < ny-1$），其横向范围覆盖 $x \in [xs[i], xs[i+1])$（$0 \le i < nx$）。若该水平边与某个隔间的下边界或上边界重合，且横向范围有正重叠，则标记为墙。

注意：隔间内部并不作为障碍，因此无需标记单元格本身。只有边被阻塞。

### 步骤 $\texttt{3}$. 定位起点单元格

给定捕食者坐标 $(pr, pc)$（行、列），映射到离散网格中的单元格索引 $(i, j)$，满足 $xs[i] \le pc < xs[i+1]$ 且 $ys[j] \le pr < ys[j+1]$。由于起点可能落在边界坐标上（例如 $10000$），使用 `upper_bound` 找到第一个大于坐标的值，再减 $1$，即可将边界点归入最外侧单元格，保证定位有效。

### 步骤 $\texttt{4}$. 广度优先搜索

从起点单元格开始执行 $\texttt{BFS}$。对于当前单元格 $(i, j)$，尝试向四个方向（右、左、上、下）移动到相邻单元格。移动前检查对应方向的公共边是否被标记为墙，若是则禁止移动。访问过的单元格累加其实际面积（宽度 $xs[i+1]-xs[i]$ 乘以高度 $ys[j+1]-ys[j]$）。最终累加和即为该查询的答案。

由于 $C \le 4$，离散化后的网格大小至多为 $(2C+1) \times (2C+1) = 9 \times 9 = 81$ 个单元格，$\texttt{BFS}$ 可在常数时间内完成。

### 复杂度分析

- **时间复杂度**：对于每组用例，离散化排序复杂度为 $O(C \log C)$。标记墙壁边需遍历所有隔间和所有单元格公共边，最多 $O(C \cdot (nx \cdot ny))$，其中 $nx, ny \le 2C+1$，故 $O(C^3)$。每个查询 BFS 遍历所有单元格，复杂度 $O(nx \cdot ny) = O(C^2)$。总体时间复杂度为 $O(T \cdot (C^3 + Q C^2))$，其中 $T$ 为用例数，$Q \le 5$，$C \le 4$，完全可行。
- **空间复杂度**：存储离散化网格和标记数组，为 $O(C^2)$，极低。

## 代码实现

```cpp
// The Predator
// UVa ID: 10864
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Square {
    int x, y, side; // x=列坐标, y=行坐标
};

long long solveCase(int sx, int sy, const vector<Square>& squares) {
    const int ROOM = 10000;
    vector<int> xs, ys;
    xs.push_back(0);
    xs.push_back(ROOM);
    ys.push_back(0);
    ys.push_back(ROOM);

    for (const auto& sq : squares) {
        xs.push_back(sq.x);
        xs.push_back(sq.x + sq.side);
        ys.push_back(sq.y);
        ys.push_back(sq.y + sq.side);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int nx = (int)xs.size() - 1;
    int ny = (int)ys.size() - 1;

    vector<vector<bool>> vertBlock(nx - 1, vector<bool>(ny, false));
    vector<vector<bool>> horiBlock(nx, vector<bool>(ny - 1, false));

    for (const auto& sq : squares) {
        int x1 = sq.x, y1 = sq.y;
        int x2 = sq.x + sq.side, y2 = sq.y + sq.side;

        // 垂直边（左右边界）
        for (int i = 0; i < nx - 1; ++i) {
            if (xs[i + 1] == x1 || xs[i + 1] == x2) {
                for (int j = 0; j < ny; ++j) {
                    if (max(y1, ys[j]) < min(y2, ys[j + 1]))
                        vertBlock[i][j] = true;
                }
            }
        }
        // 水平边（上下边界）
        for (int j = 0; j < ny - 1; ++j) {
            if (ys[j + 1] == y1 || ys[j + 1] == y2) {
                for (int i = 0; i < nx; ++i) {
                    if (max(x1, xs[i]) < min(x2, xs[i + 1]))
                        horiBlock[i][j] = true;
                }
            }
        }
    }

    // 定位起点所在的单元格（边界点归入最外侧单元格）
    int ix = upper_bound(xs.begin(), xs.end(), sx) - xs.begin() - 1;
    if (ix < 0) ix = 0;
    if (ix >= nx) ix = nx - 1;
    int iy = upper_bound(ys.begin(), ys.end(), sy) - ys.begin() - 1;
    if (iy < 0) iy = 0;
    if (iy >= ny) iy = ny - 1;
    int si = ix, sj = iy;

    queue<pair<int, int>> q;
    q.push({si, sj});
    vector<vector<bool>> visited(nx, vector<bool>(ny, false));
    visited[si][sj] = true;
    long long area = 0;

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 右、左、上、下

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int i = cur.first, j = cur.second;
        long long w = xs[i + 1] - xs[i];
        long long h = ys[j + 1] - ys[j];
        area += w * h;

        for (int d = 0; d < 4; ++d) {
            int ni = i + dirs[d][0];
            int nj = j + dirs[d][1];
            if (ni < 0 || ni >= nx || nj < 0 || nj >= ny) continue;
            if (visited[ni][nj]) continue;

            bool blocked = false;
            if (d == 0) blocked = vertBlock[i][j];
            else if (d == 1) blocked = vertBlock[i - 1][j];
            else if (d == 2) blocked = horiBlock[i][j];
            else if (d == 3) blocked = horiBlock[i][j - 1];
            if (blocked) continue;

            visited[ni][nj] = true;
            q.push({ni, nj});
        }
    }

    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    int caseNo = 1;
    while (cin >> C) {
        vector<Square> squares(C);
        for (int i = 0; i < C; ++i) {
            int r, c, s;
            cin >> r >> c >> s;
            squares[i].x = c;
            squares[i].y = r;
            squares[i].side = s;
        }

        int Q;
        cin >> Q;
        cout << "Case " << caseNo << ":\n";
        for (int i = 0; i < Q; ++i) {
            int pr, pc;
            cin >> pr >> pc;
            long long ans = solveCase(pc, pr, squares);
            cout << ans << '\n';
        }
        ++caseNo;
    }
    return 0;
}
```

## 总结

本题的关键技巧在于**坐标离散化**，将连续空间转化为有限单元格，同时准确标记墙壁边而非整个单元格。由于隔间数量极少，离散化后网格极小，$\texttt{BFS}$ 可在常数时间完成。注意处理起点位于边界时的定位方法，以及墙壁边重叠判断中的开闭区间（使用 `<` 而非 `<=` 以排除仅接触而无重叠的情况）。本题也体现了离散化与连通性问题的经典结合，适用于规模大但障碍物少的场景。
