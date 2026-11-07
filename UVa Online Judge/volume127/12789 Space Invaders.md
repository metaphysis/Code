
> **摘要**：本题给定一个 $r \times c$ 的护盾网格，格子分为激活（`#`）与禁用（`.`），当存在一条由禁用格子组成的四连通路径从第 $1$ 行贯通到第 $r$ 行时护盾被攻破。外星人从北向南、飞船从南向北交替射击，每次射击将指定列中最靠近射击方向的激活格子变为禁用。需要判断护盾首次被攻破的时刻及造成者：初始即攻破输出 `0`，从未攻破输出 `X`，外星人第 $k$ 次射击攻破输出 $k$，飞船第 $k$ 次射击攻破输出 $-k$。由于操作只增不减，可用并查集维护连通块并记录其是否触顶、触底，配合每列的有序集合快速定位射击目标，总复杂度为 $O(rc + s \log r)$。

## 题目描述

在 $\texttt{2551}$ 年，飞船“无限怀旧”号面对外星敌舰，依靠一块 $r$ 行 $c$ 列的矩形护盾进行防御。护盾的每个格子处于激活（`#`）或禁用（`.`）状态。若存在一条由禁用格子组成的四连通路径，从第 $1$ 行连通到第 $r$ 行，则称护盾被攻破。

外星飞船位于护盾北侧（第 $1$ 行以北），向正南方向射击；“无限怀旧”号位于护盾南侧（第 $r$ 行以南），向正北方向射击。一次射击指定一个列号，效果是：在该列上，将最靠近射击方向的那个激活格子变为禁用。若该列没有激活格子，则该射击无效。

战斗开始前护盾可能已经处于攻破状态。战斗过程中，每次射击后护盾可能被攻破。需要判断首次攻破发生的时间以及由谁造成，若从未攻破则输出特定符号。

## 输入格式

每个测试用例包含：
- 第一行三个整数 $r$、$c$、$s$，分别表示行数、列数和射击次数（$1 \le r, c \le 1000$，$0 \le s \le 10000$）。
- 接下来 $r$ 行，每行一个长度为 $c$ 的字符串，由 `#` 和 `.` 组成，表示护盾初始状态。
- 接下来 $s$ 行，每行一个整数 $a$，满足 $1 \le |a| \le c$。若 $a > 0$ 表示外星人射击列 $|a|$；若 $a < 0$ 表示“无限怀旧”号射击列 $|a|$。

输入包含多个测试用例，直到文件结束。

## 输出格式

对于每个测试用例，输出一行：
- 若初始已攻破，输出 `0`（注意是数字零，非字母 `O`）。
- 若战斗中从未攻破，输出 `X`。
- 若外星人首次在第 $k$ 次射击时攻破，输出正整数 $k$。
- 若“无限怀旧”号首次在第 $k$ 次射击时攻破，输出负整数 $-k$。

## 样例

**输入**
```text
2 2 2
.#
#.
1
-1
2 3 2
##.
.##
2
-2
2 3 2
##.
.##
-2
2
2 1 1
#
#
-1
```

**输出**
```text
0
-2
2
X
```

## 题目分析

护盾的攻破本质是判断一个动态图中是否出现了从顶部到底部的连通路径。初始状态给定，之后每次操作将某个激活格子转换为禁用，等价于向图中添加一个新节点，并可能与上下左右的已禁用节点合并连通块。

由于所有操作均为“添加”操作，没有删除，因此可以使用并查集（$\texttt{DSU}$）来维护连通块的动态合并。每个连通块需要记录两个属性：是否接触第 $1$ 行（顶部）和是否接触第 $r$ 行（底部）。当某个连通块同时具有这两个属性时，护盾即被攻破。

关键点在于如何快速找到每次射击要禁用的格子。根据射击方向：
- 外星人从北向南射击，应选择该列中最靠北（行号最小）的激活格子。
- 人类从南向北射击，应选择该列中最靠南（行号最大）的激活格子。

因此，每一列需要维护一个有序集合，存储该列所有激活格子的行号。射击时从集合中取出对应的行号并删除，然后将该格子改为禁用，加入并查集并尝试与邻居合并。

由于 $r \cdot c$ 最大可达 $10^6$，$s$ 最大为 $10^4$，并查集和集合操作的总复杂度可接受。

## 解题思路

### 步骤 $\texttt{1}$. 初始化并查集与基础连通性

为每个格子分配唯一编号 $\textit{id} = i \times c + j$（$0 \le i < r$，$0 \le j < c$）。并查集维护每个节点所在连通块，并额外维护两个布尔数组 $\textit{touchTop}$ 和 $\textit{touchBottom}$，分别表示该连通块是否接触顶部或底部。

首先扫描整个网格，对所有初始为 `.` 的格子，调用 $\texttt{initNode}$ 设置其初始接触属性（若 $i=0$ 则触顶，若 $i=r-1$ 则触底）。然后再次扫描所有 `.` 格子，将其与右边或下边的 `.` 格子合并（四连通只需考虑右和下即可覆盖所有相邻关系）。

合并操作 $\texttt{unite}$ 会将两个连通块的接触属性取逻辑或，并更新根节点的属性。若合并后根节点同时触顶和触底，则标记全局变量 $\textit{connected} = \texttt{true}$。

### 步骤 $\texttt{2}$. 初始攻破判断

遍历所有初始为 `.` 的格子，找到其所在连通块的根，检查该根的 $\textit{touchTop}$ 与 $\textit{touchBottom}$ 是否均为 $\text{true}$。若存在，则说明初始已攻破，输出 `0` 并跳过当前测试用例的后续处理（仍需读取射击数据，但已提前读入，故可直接继续）。

### 步骤 $\texttt{3}$. 建立每列激活格子的集合

对于每个格子若为 `#`，则将其行号插入到该列对应的 $\texttt{set<int>}$ 中。由于 $\texttt{set}$ 有序，可以快速获取最小和最大元素。

### 步骤 $\texttt{4}$. 按顺序处理射击

遍历射击序列 $k = 1, 2, \dots, s$。对于每次射击：
- 解析绝对值得到列索引 $j = |a| - 1$。
- 若 $a > 0$（外星人），从 $\textit{colSets}[j]$ 中取出最小行号 $i$（即 $\texttt{begin()}$），删除该元素。
- 若 $a < 0$（人类），取出最大行号 $i$（即 $\texttt{rbegin()}$），删除该元素。
- 若该列集合为空，则射击无效，继续下一次循环。
- 否则，将格子 $(i, j)$ 在网格中标记为 `.`，并为其创建并查集节点，调用 $\texttt{initNode}$ 设置接触属性。
- 检查该节点自身是否同时触顶触底（即仅有一行时可能发生），若是则立即设置 $\textit{connected} = \texttt{true}$。
- 枚举该格子的四个邻居（上、下、左、右），若邻居在网格内且为 `.`，则将当前节点与邻居节点合并。
- 合并后若 $\textit{connected}$ 为 $\texttt{true}$，则当前射击导致了首次攻破，输出 $\pm k$（正数表示外星人，负数表示人类），并跳出循环。

若所有射击处理完毕仍未发生攻破，则输出 `X`。

### 复杂度分析

- 并查集操作近似 $O(\alpha(rc))$，其中 $\alpha$ 为阿克曼函数的反函数，可视为常数。
- 每列集合操作（插入、删除、查找最小/最大）复杂度为 $O(\log r)$。
- 初始化扫描网格为 $O(rc)$，合并相邻禁用格为 $O(rc)$。
- 总时间复杂度为 $O(rc + s \log r)$。
- 空间复杂度为 $O(rc)$，用于存储网格、并查集数组和集合。

## 代码实现

```cpp
// Space Invaders
// UVa ID: 12789
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.200s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rankv;
    vector<char> touchTop, touchBottom;
    bool connected;

    DSU(int n) : parent(n), rankv(n, 0), touchTop(n, 0), touchBottom(n, 0), connected(false) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    void initNode(int id, bool top, bool bottom) {
        touchTop[id] = top;
        touchBottom[id] = bottom;
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rankv[ra] < rankv[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rankv[ra] == rankv[rb]) ++rankv[ra];
        touchTop[ra] = touchTop[ra] || touchTop[rb];
        touchBottom[ra] = touchBottom[ra] || touchBottom[rb];
        if (touchTop[ra] && touchBottom[ra]) connected = true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, s;
    while (cin >> r >> c >> s) {
        vector<string> grid(r);
        for (int i = 0; i < r; ++i) cin >> grid[i];

        vector<int> shots(s);
        for (int i = 0; i < s; ++i) cin >> shots[i];

        int n = r * c;
        DSU dsu(n);

        // 初始化所有初始禁用格子的节点信息并合并相邻
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '.') {
                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                }
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '.') {
                    int id = i * c + j;
                    if (j + 1 < c && grid[i][j + 1] == '.')
                        dsu.unite(id, i * c + (j + 1));
                    if (i + 1 < r && grid[i + 1][j] == '.')
                        dsu.unite(id, (i + 1) * c + j);
                }

        // 检查初始连通性
        bool initialBreach = false;
        for (int i = 0; i < r && !initialBreach; ++i)
            for (int j = 0; j < c && !initialBreach; ++j)
                if (grid[i][j] == '.') {
                    int root = dsu.find(i * c + j);
                    if (dsu.touchTop[root] && dsu.touchBottom[root])
                        initialBreach = true;
                }
        if (initialBreach) {
            cout << "0\n";    // 注意：输出数字 0，不是字母 O
            continue;
        }

        // 每列激活格子的行号集合
        vector< set<int> > colSets(c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '#')
                    colSets[j].insert(i);

        bool found = false;
        for (int k = 0; k < s; ++k) {
            int a = shots[k];
            int j = abs(a) - 1;

            if (a > 0) { // 外星人：从北向南
                if (!colSets[j].empty()) {
                    int i = *colSets[j].begin();
                    colSets[j].erase(colSets[j].begin());
                    grid[i][j] = '.';

                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                    if (dsu.touchTop[id] && dsu.touchBottom[id])
                        dsu.connected = true;

                    const int dx[4] = {-1, 1, 0, 0};
                    const int dy[4] = {0, 0, -1, 1};
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && grid[ni][nj] == '.')
                            dsu.unite(id, ni * c + nj);
                    }

                    if (dsu.connected) {
                        cout << (k + 1) << '\n';
                        found = true;
                        break;
                    }
                }
            } else { // Nostalgia for Infinity：从南向北
                if (!colSets[j].empty()) {
                    int i = *colSets[j].rbegin();
                    colSets[j].erase(prev(colSets[j].end()));
                    grid[i][j] = '.';

                    int id = i * c + j;
                    dsu.initNode(id, (i == 0), (i == r - 1));
                    if (dsu.touchTop[id] && dsu.touchBottom[id])
                        dsu.connected = true;

                    const int dx[4] = {-1, 1, 0, 0};
                    const int dy[4] = {0, 0, -1, 1};
                    for (int d = 0; d < 4; ++d) {
                        int ni = i + dx[d], nj = j + dy[d];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && grid[ni][nj] == '.')
                            dsu.unite(id, ni * c + nj);
                    }

                    if (dsu.connected) {
                        cout << -(k + 1) << '\n';
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found) cout << "X\n";
    }
    return 0;
}
```

## 总结

本题的核心技巧在于将动态添加点的连通性问题转化为并查集维护连通块属性，并利用有序集合高效定位每次射击的目标格子。关键点包括：

- **只增不改**：所有操作均为将 `#` 变为 `.`，适合离线使用并查集。
- **双向接触标记**：每个连通块同时记录是否接触顶部和底部，合并时传递属性，一旦满足条件即判定攻破。
- **方向决定目标**：根据射击方向选择列中的最小或最大行号，利用 $\texttt{set}$ 的自动有序性实现快速存取。
- **输出细节**：初始攻破输出数字 `0` 而非字母 `O`，这是在线评测的约定。

此方法时间复杂度线性于网格大小，并能在射击次数较多的场景下高效运行，是处理此类动态连通性问题的常用范式。
