[UVa 258 Mirror Maze](https://blog.csdn.net/metaphysis/article/details/161284023)

## 题目分析

本题描述了一个奇特的迷宫，迷宫由 `M` 列 `N` 行组成，边界处除两个入口外均为黑洞（`*`）。迷宫内部包含两种元素：

- **镜子**：用 `/` 或 `\` 表示，两种状态对应镜子的两种朝向（旋转 $90$ 度）。镜子与激光束始终成 $45$ 度角。
- **黑洞**：用 `*` 表示，会完全吸收激光束。
- **空地**：用 `.` 表示，激光束可以穿过。

激光束从迷宫的一个入口进入，经过一系列镜面反射后，需要从另一个出口离开。题目保证存在一种镜子朝向的配置方案使得激光束能够成功穿越迷宫。要求我们输出这种配置方案下的迷宫地图。

需要注意的是，激光束可以在空地上以 $90$ 度角自交，即路径可以交叉。

## 解题思路

### 模型抽象

本题的核心是**寻找一种镜子的朝向组合**，使得从入口射入的激光束经过反射后恰好从出口射出。

一个关键观察是：激光束的传播路径完全由镜子的朝向决定。我们可以将迷宫建模为一个**有向图**：

- **节点**：迷宫中的每个镜子。
- **边**：从一面镜子出发，沿着某个方向（上、右、下、左）发射激光，经过若干空地后到达的另一面镜子（或出入口）。

对于每个镜子，有 $4$ 个可能的光线入射方向（上、右、下、左）。根据镜子当前的朝向（`/` 或 `\`），入射光线会被反射到特定的出射方向。

### 方向定义

为了便于处理，我们定义四个方向：

- `0`：向上（`up`）
- `1`：向右（`right`）
- `2`：向下（`down`）
- `3`：向左（`left`）

对应的行、列偏移量为：

```
offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} }
```

### 反射变换表

镜子的两种状态与光线方向的映射关系如下：

- 当镜子为 `/` 时：
  - 光线从上（`0`）入射 → 向右（`1`）出射
  - 从右（`1`）入射 → 向上（`0`）出射
  - 从下（`2`）入射 → 向左（`3`）出射
  - 从左（`3`）入射 → 向下（`2`）出射

- 当镜子为 `\` 时：
  - 光线从上（`0`）入射 → 向左（`3`）出射
  - 从右（`1`）入射 → 向下（`2`）出射
  - 从下（`2`）入射 → 向右（`1`）出射
  - 从左（`3`）入射 → 向上（`0`）出射

用表格 `transform[2][4][2]` 存储：第一维表示镜子状态（`0` 为 `/`，`1` 为 `\`），第二维表示入射方向，第三维的第一个元素是出射方向，第二个元素是出射光线的“方向”（实际上与入射方向的意义相同，此处用于计算下一个镜子）。

### 图的构建

对于每个镜子，我们需要找出从它出发沿着 $4$ 个方向直线传播时，会遇到的第一个对象（另一面镜子或出入口）。这个过程通过模拟光线直线传播完成：

1. 从当前镜子的位置 `(i, j)` 开始，沿着方向 `d` 逐步移动。
2. 如果遇到黑洞 `*`，则停止（光线被吸收）。
3. 如果遇到空地 `.`，继续前进。
4. 如果遇到出入口（边界上的空地，`indexer == -1`），记录为出口（`reflect[m][d] = -1`），并记录第一个镜子作为搜索起点。
5. 如果遇到另一面镜子，记录它的编号，停止。

这样就建立了镜子之间的邻接关系：`reflect[m][d]` 表示从镜子 `m` 沿方向 `d` 出发到达的下一个镜子编号（`-1` 表示到达出口）。

### $\texttt{DFS}$ 搜索策略

问题的目标是确定每个镜子的朝向（`/` 或 `\`），使得从入口出发的激光最终到达出口。

我们使用深度优先搜索（$\texttt{DFS}$）来尝试镜子的朝向：

- 状态：当前所在的镜子编号 `mirror` 和入射光线的方向 `light`。
- 转移：根据当前镜子的当前朝向，计算反射后的出射方向，并得到下一个镜子 `next_mirror`，递归搜索。

关键点：每个镜子可以有两种状态（翻或不翻）。在 $\texttt{DFS}$ 中，我们先尝试当前状态；如果失败，则翻转该镜子的状态再尝试；如果仍然失败，则回溯。

为了避免无限循环，使用 `visited` 数组记录当前搜索路径上已经访问过的镜子（注意：这里的“访问”是针对于一次搜索路径的，而非全局永久标记）。

### 入口的确定

我们需要找到激光的起始位置。题目没有明确说明哪个是入口，但我们可以通过构建图的过程自然地找到：第一个通过直线传播到达出口的镜子（及其入射方向）就是搜索的起点。具体地，在构建 `reflect` 数组时，如果遇到 `reflect[m][d] == -1`，则记录 `firstMirror = m` 和 `firstLight = d`。

### 输出

搜索完成后，`flapped[i]` 记录了第 `i` 面镜子的最终朝向（`1` 表示 `\`，`0` 表示 `/`）。据此更新 `grid` 数组，然后输出整个迷宫。多个迷宫之间用空行分隔。

## 复杂度分析

- 镜子数量最多为 $50 \times 50 = 2500$ 个。
- 每个镜子有 $2$ 种状态，理论上状态空间为 $2^{2500}$，但通过 $\texttt{DFS}$ 回溯和图的约束，实际搜索空间远小于此。
- 构建图的时间复杂度为 $O($镜子数量 $\times 4 \times \max(M, N))$，在本题限制下完全可行。

## 代码实现

```cpp
// Mirror Maze
// UVa ID: 258
// Verdict: Accepted
// Submission Date: 2016-06-01
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

char grid[60][60];
int row, column;
int reflect[3600][4], indexer[60][60], flapped[3600], visited[3600];
vector<pair<int, int>> mirrors(3600);

// 方向定义：0 = 上，1 = 右，2 = 下，3 = 左
int offset[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

// 反射变换表
// 第一维：镜子状态（0 = '/'，1 = '\'）
// 第二维：入射方向
// 第三维：[0] = 出射方向，[1] = 出射光线方向（用于计算下一个镜子）
int transform[2][4][2] = {
    {{3, 1}, {2, 0}, {1, 3}, {0, 2}},  // 镜子为 '/'
    {{1, 3}, {0, 2}, {3, 1}, {2, 0}}   // 镜子为 '\'
};

// 根据当前镜子和入射光线，计算下一个镜子编号和出射光线方向
inline void getNextMirror(int mirror, int light, int& next_mirror, int& next_light) {
    next_mirror = reflect[mirror][transform[flapped[mirror]][light][0]];
    next_light = transform[flapped[mirror]][light][1];
}

// 深度优先搜索，尝试为镜子确定朝向
// mirror: 当前所在的镜子编号，light: 入射光线的方向
bool dfs(int mirror, int light) {
    // 到达出口（-1 表示出口）
    if (mirror == -1)
        return true;

    // 记录当前镜子是否已经在本轮搜索路径中被访问过
    bool mirrorVisited = visited[mirror];
    visited[mirror] = true;

    int next_mirror, next_light;
    getNextMirror(mirror, light, next_mirror, next_light);

    // 尝试当前镜子的当前朝向
    if (next_mirror != 0 && dfs(next_mirror, next_light))
        return true;

    // 如果当前朝向失败且当前镜子之前未被访问过，尝试翻转该镜子
    if (!mirrorVisited)
    {
        flapped[mirror] = !flapped[mirror];  // 翻转状态

        getNextMirror(mirror, light, next_mirror, next_light);
        
        if (next_mirror != 0 && dfs(next_mirror, next_light))
            return true;

        // 回溯，恢复原状态
        flapped[mirror] = !flapped[mirror];
    }

    // 恢复 visited 状态
    visited[mirror] = mirrorVisited;

    return false;
}

int main() {
    bool printBlankLine = false;

    // 读取多个迷宫，以 "-1 -1" 结束
    while (cin >> column >> row, column > 0 && row > 0) {
        // 初始化数组
        memset(indexer, 0, sizeof(indexer));
        memset(flapped, 0, sizeof(flapped));
        memset(visited, 0, sizeof(visited));
        memset(reflect, 0, sizeof(reflect));

        int mirrorNumber = 0;

        // 读取迷宫地图
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++) {
                cin >> grid[i][j];
                // 边界上的空地视为出入口，编号为 -1
                if (grid[i][j] == '.' && (i == 0 || i == (row - 1) || j == 0 || j == (column - 1)))
                    indexer[i][j] = -1;
                else if (grid[i][j] == '/' || grid[i][j] == '\\') {
                    mirrorNumber++;
                    mirrors[mirrorNumber] = make_pair(i, j);
                    // 记录镜子的初始状态（'\' 为 1，'/' 为 0）
                    flapped[mirrorNumber] = (grid[i][j] == '\\');
                    indexer[i][j] = mirrorNumber;
                }
            }

        // 构建镜子之间的连接关系
        int firstMirror = -1, firstLight = -1;
        for (int m = 1; m <= mirrorNumber; m++)
            for (int d = 0; d < 4; d++) {
                int i = mirrors[m].first, j = mirrors[m].second;
                while (true) {
                    i += offset[d][0], j += offset[d][1];

                    // 遇到黑洞，停止
                    if (grid[i][j] == '*') break;
                    // 遇到出入口
                    if (indexer[i][j] == -1) {
                        reflect[m][d] = -1;
                        // 记录第一个镜子及其入射方向作为搜索起点
                        firstMirror = m;
                        firstLight = d;
                        break;
                    }
                    // 遇到另一面镜子
                    if (indexer[i][j] > 0) {
                        reflect[m][d] = indexer[i][j];
                        break;
                    }
                }
            }

        // 从起点开始 DFS 搜索
        if (firstMirror != -1 && firstLight != -1)
            dfs(firstMirror, firstLight);

        // 输出结果，迷宫之间用空行分隔
        if (printBlankLine) cout << endl;
        else printBlankLine = true;

        // 根据 flapped 数组更新地图中的镜子朝向
        for (int i = 1; i <= mirrorNumber; i++)
            grid[mirrors[i].first][mirrors[i].second] = (flapped[i] ? '\\' : '/');

        // 输出迷宫
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++)
                cout << grid[i][j];
            cout << endl;
        }
    }

    return 0;
}
```
