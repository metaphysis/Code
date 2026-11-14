[UVa 308 Tin Cutter](https://blog.csdn.net/metaphysis/article/details/161446265)

## 题目描述

在锡板切割工厂中，有一台用于从锡板上切割零件的机器。它有一把极其锋利的刀，可以在锡板上进行水平或垂直的线段切割。每个切割过程由一系列这样的切割组成。每个线段切割由其端点给出，这些端点始终位于锡板内部。在切割过程中，锡板的某些部分可能会脱落，从而在板上形成孔洞。

工厂管理层需要预测在给定切割序列结束后，锡板上会留下多少个孔洞。请编写程序回答这个问题。单独的线段切割不被视为孔洞。

### 输入格式

输入文件由多个数据块组成。每个数据块（最后一个除外）描述一个切割过程。数据块的第一行是一个整数 $N \leq 100$，表示切割过程中线段切割的数量。接下来的 $N$ 行定义这些切割，每行格式为 `X1 Y1 X2 Y2`，其中 `X1 Y1` 和 `X2 Y2` 是线段端点的坐标，用空格分隔。坐标是整数，且始终定义水平或垂直线段（即与 $x$ 轴或 $y$ 轴平行的线段）。

最后一个数据块仅包含一行 `0`。

### 输出格式

输出文件包含与输入数据块对应的行（最后一个空块除外）。每行包含相应切割过程结束后锡板上剩余的孔洞数量。

### 样例输入

```
4
0 1 1 1
1 1 1 0
1 0 0 0
0 0 0 1
2
0 1 2 1
1 2 1 0
0
```

### 样例输出

```
1
0
```

---

## 题目分析

### 问题的本质

这是一个**平面图孔洞计数**问题。给定若干水平或垂直线段（切割线），它们将平面划分成若干个连通区域。我们需要计算被切割线完全包围的区域（即**孔洞**）的数量。

关键要点：
- 所有切割线都是水平或垂直的
- 切割线可能相交，形成封闭的环
- 锡板的边界也被视为切割线（实际上是外边界）
- 单独的线段（不能形成封闭环）不算孔洞

### 与经典问题的联系

这个问题可以转化为**网格图上的连通分量计数**问题。由于坐标是整数且线段是轴对齐的，我们可以使用**离散化**技术将无限精度的坐标映射到有限的网格点上，然后在网格上分析区域的连通性。

核心思想：
1. 将所有切割线的端点和交点投影到网格上
2. 在网格上标记哪些边是“墙”（切割线）
3. 使用 $\texttt{DFS}$ 或 $\texttt{BFS}$ 找出所有连通区域
4. 孔洞 = 内部连通区域的数量

### 离散化的必要性

坐标的范围未在题目中明确，但线段数量 $N \leq 100$，每个线段有两个端点，最多有 $200$ 个不同的坐标值。直接使用原始坐标进行 $\texttt{DFS}$ 需要处理无限大的平面，不现实。因此，我们需要将坐标离散化到有限的网格中。

---

## 解题思路

### 步骤一：坐标离散化

将所有切割线端点的 $x$ 坐标和 $y$ 坐标分别收集起来，排序后映射到连续的整数索引。这样，原来的坐标空间被压缩到一个 $(2N+1) \times (2N+1)$ 的网格中。

为什么是 $2N+1$？因为切割线之间可能会形成“间隙”，这些间隙也需要被表示为网格单元。离散化后，相邻原始坐标之间的区域用一个网格点表示。

具体实现：
```cpp
map<int, int> xCoordMap, yCoordMap;
for (int i = 0; i < numCuts; i++) {
    xCoordMap[startX[i]] = xCoordMap[endX[i]] = 0;
    yCoordMap[startY[i]] = yCoordMap[endY[i]] = 0;
}
int gridSizeX = 1;
for (auto& it : xCoordMap) it.second = gridSizeX++;
int gridSizeY = 1;
for (auto& it : yCoordMap) it.second = gridSizeY++;
```

### 步骤二：在网格上绘制切割线

在离散化后的网格中，每条切割线被绘制为网格点之间的“墙”。使用一个三维数组 `gridWalls[x][y][direction]` 表示在网格点 $(x, y)$ 的四个方向上是否有墙阻挡。

方向定义：
- `0`：上（$\texttt{up}$）
- `1`：下（$\texttt{down}$）
- `2`：左（$\texttt{left}$）
- `3`：右（$\texttt{right}$）

绘制垂直线段（$x$ 相同）：
```cpp
for (int y = startY; y < endY; y++) {
    gridWalls[startX][y][0] = 1;      // 当前点的上方有墙
    gridWalls[startX - 1][y][1] = 1;  // 相邻点的下方有墙
}
```

绘制水平线段（$y$ 相同）：
```cpp
for (int x = startX; x < endX; x++) {
    gridWalls[x][startY][2] = 1;      // 当前点的左方有墙
    gridWalls[x][startY - 1][3] = 1;  // 相邻点的右方有墙
}
```

### 步骤三：标记连通区域

使用深度优先搜索（$\texttt{DFS}$）标记所有网格点的连通区域。从每个未标记的网格点出发，沿着没有墙阻挡的方向移动，标记所有可达的点。

```cpp
void markConnectedRegion(int x, int y, int regionId, int maxX, int maxY) {
    if (x < 0 || y < 0 || x > maxX || y > maxY) return;
    if (regionMap[x][y]) return;
    regionMap[x][y] = regionId;
    for (int direction = 0; direction < 4; direction++) {
        if (gridWalls[x][y][direction]) continue;
        markConnectedRegion(x + dx[direction], y + dy[direction], regionId, maxX, maxY);
    }
}
```

首先标记外部区域（从边界 $(0,0)$ 开始），然后标记剩余的未标记区域。

### 步骤四：合并相邻区域

由于离散化引入了额外的网格点，同一个原始区域可能在离散化后被分割成多个相邻的网格区域。需要使用**并查集**（$\texttt{Union-Find}$）将这些相邻的区域合并。

遍历所有网格点及其四个方向，如果相邻的两个点属于不同的区域且都不是外部区域（区域 $1$），则将它们合并。

### 步骤五：计算孔洞数量

最终，孔洞的数量 = 合并后的内部区域总数。

```
孔洞数 = totalRegions - 1
```

其中 $1$ 代表外部区域（不被任何切割线包围的区域）。

---

## 算法复杂度分析

### 时间复杂度

- 离散化：$O(N \log N)$
- 绘制切割线：$O(N \times \text{maxCoordinate})$，但离散化后坐标范围是 $O(N)$，因此 $O(N^2)$
- $\texttt{DFS}$ 标记区域：$O(G^2)$，其中 $G = O(N)$，因此 $O(N^2)$
- 并查集合并：$O(G^2 \cdot \alpha(G))$，其中 $\alpha$ 是反阿克曼函数
- 总复杂度：$O(N^2)$，$N \leq 100$ 时完全可行

### 空间复杂度

- `gridWalls` 数组：$512 \times 512 \times 4$，约 $1$ MB
- `regionMap` 数组：$512 \times 512$，约 $256$ KB
- 总空间复杂度：$O(G^2)$，$G \leq 2N+1$，完全可行

---

## 正确性证明

**引理 1**：离散化保持切割线的拓扑结构。

证明：离散化将原始坐标映射到整数网格，同时保持切割线之间的相对顺序和邻接关系。由于所有切割线都是轴对齐的，离散化不会改变区域的连通性。$\square$

**引理 2**：$\texttt{DFS}$ 标记算法正确找出所有连通区域。

证明：$\texttt{DFS}$ 从每个未访问点出发，沿着没有墙的方向移动，可以访问所有与该点连通的网格点。由于墙的存在阻断了不同区域之间的连通性，每个连通区域会被赋予唯一的 `regionId`。$\square$

**引理 3**：并查集合并正确处理离散化引入的虚假分割。

证明：离散化将原始平面划分为更细的网格，同一个原始区域可能对应多个相邻的网格区域。并查集合并将这些相邻区域合并，恢复原始区域的连通性。$\square$

**引理 4**：孔洞数量 = 内部区域数量。

证明：外部区域（区域 $1$）是无限延伸的未被切割线包围的区域。所有其他区域都被切割线完全包围，因此是孔洞。$\square$

---

## 参考代码

```cpp
// Tin Cutter
// UVa ID: 308
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

/* 
 * 网格墙标记数组 gridWalls[x][y][direction]
 * 表示在网格点(x,y)在指定方向上是否有墙阻挡
 * 方向: 0=上(up), 1=下(down), 2=左(left), 3=右(right)
 */
int gridWalls[512][512][4] = {};

// 四个方向的移动增量: 上, 下, 左, 右
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

/**
 * 在网格上绘制一条切割线
 * @param startX 起点x坐标(离散化后)
 * @param startY 起点y坐标(离散化后)
 * @param endX   终点x坐标(离散化后)
 * @param endY   终点y坐标(离散化后)
 */
void drawCutLine(int startX, int startY, int endX, int endY) {
    if (startX == endX) {
        // 垂直线: 在线段两侧标记上下方向的墙
        for (int y = startY; y < endY; y++) {
            gridWalls[startX][y][0] = 1;      // 当前点的上方有墙
            gridWalls[startX - 1][y][1] = 1;  // 相邻点的下方有墙
        }
    } else {
        // 水平线: 在线段两侧标记左右方向的墙
        for (int x = startX; x < endX; x++) {
            gridWalls[x][startY][2] = 1;      // 当前点的左方有墙
            gridWalls[x][startY - 1][3] = 1;  // 相邻点的右方有墙
        }
    }
}

// 区域标记数组，记录每个网格点属于哪个连通区域
int regionMap[512][512] = {};

/**
 * 深度优先搜索标记连通区域
 * @param x 当前点的x坐标
 * @param y 当前点的y坐标
 * @param regionId 要标记的区域ID
 * @param maxX 网格的最大x坐标
 * @param maxY 网格的最大y坐标
 */
void markConnectedRegion(int x, int y, int regionId, int maxX, int maxY) {
    // 边界检查
    if (x < 0 || y < 0 || x > maxX || y > maxY) return;
    // 如果该点已经被标记过，则返回
    if (regionMap[x][y]) return;
    // 标记当前点为当前区域
    regionMap[x][y] = regionId;
    // 向四个方向探索
    for (int direction = 0; direction < 4; direction++) {
        // 如果当前方向有墙阻挡，则跳过
        if (gridWalls[x][y][direction]) continue;
        // 递归探索相邻点
        markConnectedRegion(x + dx[direction], y + dy[direction], regionId, maxX, maxY);
    }
}

// 并查集相关数组
int parent[512], ranks[512];

/**
 * 初始化并查集
 * @param n 元素数量
 */
void initUnionFind(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;  // 每个元素的父节点初始化为自己
        ranks[i] = 1;   // 每个集合的秩初始化为1
    }
}

/**
 * 查找元素所在的集合根节点（带路径压缩）
 * @param x 要查找的元素
 * @return 元素所在集合的根节点
 */
int findRoot(int x) { return parent[x] == x ? x : (parent[x] = findRoot(parent[x])); }

/**
 * 合并两个集合
 * @param x 第一个元素
 * @param y 第二个元素
 * @return 如果成功合并返回1，如果已经在同一集合返回0
 */
int unionSets(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y) {
        // 按秩合并，将小树合并到大树下
        if (ranks[x] > ranks[y]) {
            parent[y] = x;
            ranks[x] += ranks[y];
        } else {
            parent[x] = y;
            ranks[y] += ranks[x];
        }
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int numCuts;
    int startX[105], startY[105], endX[105], endY[105];
    while (scanf("%d", &numCuts) == 1 && numCuts != 0) {
        // 初始化数组
        memset(gridWalls, 0, sizeof(gridWalls));
        memset(regionMap, 0, sizeof(regionMap));
        // 用于坐标离散化的映射表
        map<int, int> xCoordMap, yCoordMap;
        // 读取所有切割线段并预处理
        for (int i = 0; i < numCuts; i++) {
            scanf("%d %d %d %d", &startX[i], &startY[i], &endX[i], &endY[i]);
            // 确保线段端点有序：起点坐标小于终点坐标
            if (startX[i] == endX[i]) {
                // 垂直线：确保y坐标有序
                if (startY[i] > endY[i]) swap(startY[i], endY[i]);
            } else {
                // 水平线：确保x坐标有序
                if (startX[i] > endX[i]) swap(startX[i], endX[i]);
            }
            // 记录所有出现的坐标值用于离散化
            xCoordMap[startX[i]] = xCoordMap[endX[i]] = 0;
            yCoordMap[startY[i]] = yCoordMap[endY[i]] = 0;
        }
        // 离散化x坐标：将原始坐标映射到连续的网格索引
        int gridSizeX = 1;
        for (map<int, int>::iterator it = xCoordMap.begin(); it != xCoordMap.end(); it++) {
            it->second = gridSizeX++;
        }
        // 离散化y坐标
        int gridSizeY = 1;
        for (map<int, int>::iterator it = yCoordMap.begin(); it != yCoordMap.end(); it++) {
            it->second = gridSizeY++;
        }
        // 在离散化后的网格上绘制所有切割线
        for (int i = 0; i < numCuts; i++) {
            int discreteStartX = xCoordMap[startX[i]];
            int discreteStartY = yCoordMap[startY[i]];
            int discreteEndX = xCoordMap[endX[i]];
            int discreteEndY = yCoordMap[endY[i]];
            drawCutLine(discreteStartX, discreteStartY, discreteEndX, discreteEndY);
        }
        // 使用DFS标记所有连通区域
        int regionCount = 0;
        // 首先标记外部区域（从网格边界开始）
        markConnectedRegion(0, 0, ++regionCount, gridSizeX, gridSizeY);
        // 标记剩余的所有内部区域
        for (int x = 0; x <= gridSizeX; x++) {
            for (int y = 0; y <= gridSizeY; y++) {
                if (regionMap[x][y] == 0) {
                    markConnectedRegion(x, y, ++regionCount, gridSizeX, gridSizeY);
                }
            }
        }
        // 使用并查集合并相邻的区域
        int totalRegions = regionCount;
        initUnionFind(regionCount);
        // 遍历所有网格点，合并相邻的连通区域
        for (int x = 0; x <= gridSizeX; x++) {
            for (int y = 0; y <= gridSizeY; y++) {
                for (int direction = 0; direction < 4; direction++) {
                    int neighborX = x + dx[direction];
                    int neighborY = y + dy[direction];
                    // 检查相邻点是否在网格范围内
                    if (neighborX < 0 || neighborY < 0 || neighborX > gridSizeX || neighborY > gridSizeY) {
                        continue;
                    }
                    // 跳过外部区域（区域1是外部区域）
                    if (regionMap[x][y] == 1 || regionMap[neighborX][neighborY] == 1) {
                        continue;
                    }
                    // 合并相邻的连通区域，成功合并则减少区域计数
                    totalRegions -= unionSets(regionMap[x][y], regionMap[neighborX][neighborY]);
                }
            }
        }
        // 输出孔洞的数量：总区域数 - 外部区域(1个)
        printf("%d\n", totalRegions - 1);
    }
    return 0;
}
```

---

## 总结

本题的核心在于：
1. **离散化**：将无限平面映射到有限网格
2. **墙标记**：用三维数组记录每个网格点的四个方向是否有墙
3. **连通区域标记**：使用 $\texttt{DFS}$ 找出所有连通区域
4. **区域合并**：使用并查集处理离散化引入的虚假分割
5. **孔洞计数**：内部区域的数量即为孔洞数

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 离散化 | 将原始坐标映射到连续整数索引 |
| 墙标记 | `gridWalls[x][y][dir]` 表示是否有墙 |
| 连通区域 | 无墙可达的网格点属于同一区域 |
| 外部区域 | 从边界出发可达的区域 |
| 内部区域 | 被墙完全包围的区域 |
| 并查集 | 合并离散化后相邻的同一原始区域 |

### 适用场景

这种“离散化 + 网格连通性分析”的解题模式，广泛适用于：
- 平面分割问题
- 矩形/线段切割问题
- 区域计数问题
- 孔洞检测问题
