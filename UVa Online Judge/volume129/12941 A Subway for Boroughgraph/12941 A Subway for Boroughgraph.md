 # 题目描述

给定若干个无向简单图，顶点编号从 $1$ 到 $N$，每个顶点的邻接表由输入给出。题面要求判断每个图是否为平面图，即能否将图绘制在平面上，使任意两条不相邻的边不发生相交。

本题的在线评测标准采用特定的图化简规则进行判断。程序需要按照该评测标准处理每个图，并输出对应的判断字符。

# 输入格式

输入由多组数据组成，读到文件结束为止。

每组数据先给出一个整数 $N$，满足 $2 \le N \le 64$。随后给出 $N$ 行邻接表，第 $i$ 行表示顶点 $i$ 的所有邻接点。

每个顶点的度数为 $d_i$，满足 $1 \le d_i \le N-1$。输入图满足以下条件：

- 图是无向图，邻接关系具有对称性。
- 不存在自环。
- 不存在重复邻接点。
- 不存在孤立顶点，因此不存在空邻接行。
- 每个邻接点编号都在 $1$ 到 $N$ 的范围内。

# 输出格式

对于每组数据输出一行。

按照评测标准完成图化简后：

- 若剩余图不含直接的 $K_5$ 或 $K_{3,3}$ 子图，输出 $\texttt{Y}$。
- 若剩余图含有直接的 $K_5$ 或 $K_{3,3}$ 子图，输出 $\texttt{N}$。

# 样例输入

```text
5
2 3 4 5
1 3 4 5
1 2 4 5
1 2 3
1 2 3
5
2 3 4 5
1 3 4 5
1 2 4 5
1 2 3 5
1 2 3 4
```

# 样例输出

```text
Y
N
```

# 题目分析

本题的评测程序并不是准确的平面图判定算法，而是采用了一种存在瑕疵的化简判定。对于输入图，程序反复执行两种操作：删除度数不超过 $1$ 的顶点，以及平滑度数恰好为 $2$ 的顶点。化简结束后，程序只检查剩余图中是否含有直接的 $K_5$ 或 $K_{3,3}$ 子图。

真正的平面图判定应当依据 $\texttt{Kuratowski}$ 定理。该定理指出，一个图非平面，当且仅当它包含某个 $K_5$ 或 $K_{3,3}$ 的细分图作为子图。判断细分图时，需要先删除与目标结构无关的边，再平滑细分路径上的度数为 $2$ 的内部顶点。

评测程序没有执行上述完整过程。若某个细分顶点在目标结构中度数为 $2$，但它在原图中还连接着额外边，那么它在原图中的度数至少为 $3$。评测程序不会删除额外边，因此不会平滑该顶点，最终也不会得到直接的 $K_5$ 或 $K_{3,3}$。这样会使评测程序输出 $\texttt{Y}$，而真正的平面图算法会输出非平面结果。

因此，使用数学上准确的平面图判定算法，例如 $\texttt{Boost}$ 提供的判定函数，会与在线评测的标准答案产生差异并得到错误答案。只有按照评测程序采用的有瑕疵化简逻辑实现，才能获得在线通过。

# 解题思路

步骤 $\texttt{1}$：使用位掩码保存图。

程序在内部将输入顶点编号从 $1$ 到 $N$ 转换为从 $0$ 到 $N-1$。由于 $N \le 64$，每个顶点的邻接集合都可以用一个 $64$ 位整数表示。

数组 $\texttt{adj}[u]$ 的第 $v$ 位为 $1$，表示顶点 $u$ 与顶点 $v$ 相邻。变量 $\texttt{alive}$ 保存当前仍存在的顶点集合，其第 $v$ 位为 $1$ 表示顶点 $v$ 尚未被删除。顶点的当前度数通过 $\texttt{adj}[v]$ 与 $\texttt{alive}$ 的按位与结果统计得到。

读入一条边时，同时设置两个方向的邻接位。这样能够直接维护无向图的邻接关系。对于题目保证的合法输入，邻接表本身已经对称；双向设置不会改变图结构。

步骤 $\texttt{2}$：删除度数不超过 $1$ 的顶点。

扫描所有仍然存在的顶点，将当前度数为 $0$ 或 $1$ 的顶点全部标记为删除。删除顶点后，将所有邻接掩码与新的 $\texttt{alive}$ 做按位与，从而清除已经删除的顶点及其关联边。

删除操作可能使其他顶点的度数降到 $1$ 或 $0$，因此删除完成后继续重新扫描。该过程持续到当前图中不存在度数不超过 $1$ 的顶点。

步骤 $\texttt{3}$：平滑度数为 $2$ 的顶点。

若当前顶点 $v$ 的两个邻居为 $u$ 和 $w$，则删除顶点 $v$ 以及边 $uv$、$vw$，然后添加边 $uw$。若边 $uw$ 原本已经存在，则仍然只保留一条边，因为图是简单图。

每次平滑操作都会减少一个仍存在的顶点。平滑后，其他顶点的度数可能发生变化，因此重新执行删除和寻找度数为 $2$ 的顶点的过程，直到图中不存在度数不超过 $2$ 的顶点。

步骤 $\texttt{4}$：检查直接的 $K_5$ 子图。

直接的 $K_5$ 需要存在五个顶点，并且这五个顶点两两相邻。程序按编号递增的顺序枚举前四个顶点 $a<b<c<d$：

- 选择与 $a$ 相邻的顶点 $b$。
- 在同时与 $a$、$b$ 相邻的顶点中选择 $c$。
- 在同时与 $a$、$b$、$c$ 相邻的顶点中选择 $d$。
- 在同时与 $a$、$b$、$c$、$d$ 相邻的顶点中寻找第五个顶点。

邻接集合的交集通过位运算完成。若最后的交集中存在编号大于 $d$ 的顶点，则这五个顶点两两相邻，剩余图含有 $K_5$，输出 $\texttt{N}$。

这里检查的是子图而不是导出子图，因此所选顶点之间存在额外边不会影响判断。

步骤 $\texttt{5}$：检查直接的 $K_{3,3}$ 子图。

对于 $K_{3,3}$，先枚举一侧的三个顶点 $a<b<c$。求出这三个顶点的邻接集合交集，并去除 $a$、$b$、$c$ 本身。

若交集中至少有 $3$ 个顶点，则任选其中三个顶点作为另一侧。因为它们同时与 $a$、$b$、$c$ 相邻，所以两侧之间的全部 $9$ 条边都存在，剩余图含有 $K_{3,3}$，输出 $\texttt{N}$。

同样，两个部分内部是否存在额外边不影响判断，因为直接子图允许删除多余边。

步骤 $\texttt{6}$：输出结果。

当化简结束后，若检测到 $K_5$ 或 $K_{3,3}$，输出 $\texttt{N}$；若两种结构都不存在，输出 $\texttt{Y}$。

相对于评测标准，算法的正确性如下。删除操作严格删除度数不超过 $1$ 的顶点，平滑操作严格处理度数为 $2$ 的顶点，因此化简过程与评测规则一致。$K_5$ 检查完整枚举了五个顶点的团结构，$K_{3,3}$ 检查完整枚举了一侧三个顶点及其至少三个公共邻点，因此两种直接子图检查均与评测标准一致。最终输出完全由这两种结构的存在性决定。

复杂度方面，图的邻接表规模为 $O(N^2)$。化简过程中最多删除 $N$ 个顶点并平滑 $N$ 个顶点，每次扫描最多处理 $N$ 个顶点，因此化简复杂度为 $O(N^2)$。枚举 $K_5$ 的复杂度为 $O(N^4)$，枚举 $K_{3,3}$ 的复杂度为 $O(N^3)$，总时间复杂度为 $O(N^4)$。每个顶点使用一个 $64$ 位整数保存邻接关系，因此空间复杂度为 $O(N)$ 个机器字，也就是 $O(N^2)$ 个二进制位。

# 代码实现

代码使用 $\texttt{uint64\_t}$ 保存邻接集合。函数 $\texttt{reduceGraph}$ 完成顶点删除和平滑，函数 $\texttt{hasK5}$ 检查 $K_5$，函数 $\texttt{hasK33}$ 检查 $K_{3,3}$。所有集合交、边删除和顶点状态更新都通过位运算完成。

```cpp
#include <bits/stdc++.h>
using namespace std;

using U64 = uint64_t;

int n;
U64 adj[64];
U64 alive;

U64 bit(int v) { return U64(1) << v; }

int degreeOf(int v) { return __builtin_popcountll(adj[v] & alive); }

U64 greaterThan(int v) {
    if (v + 1 >= n) return 0;
    return (~U64(0)) << (v + 1);
}

void reduceGraph() {
    while (true) {
        U64 removed = 0;
        for (int v = 0; v < n; ++v)
            if ((alive & bit(v)) && degreeOf(v) <= 1)
                removed |= bit(v);
        if (removed) {
            alive &= ~removed;
            for (int v = 0; v < n; ++v) adj[v] &= alive;
            continue;
        }
        bool smoothed = false;
        for (int v = 0; v < n; ++v) {
            if (!(alive & bit(v)) || degreeOf(v) != 2) continue;
            U64 neighbors = adj[v] & alive;
            int u = __builtin_ctzll(neighbors);
            neighbors &= neighbors - 1;
            int w = __builtin_ctzll(neighbors);
            alive &= ~bit(v);
            adj[v] = 0;
            adj[u] &= ~bit(v);
            adj[w] &= ~bit(v);
            adj[u] |= bit(w);
            adj[w] |= bit(u);
            smoothed = true;
            break;
        }
        if (!smoothed) break;
    }
}

bool hasK5() {
    for (int a = 0; a < n; ++a) {
        if (!(alive & bit(a))) continue;
        U64 bs = adj[a] & alive & greaterThan(a);
        while (bs) {
            int b = __builtin_ctzll(bs);
            bs &= bs - 1;
            U64 cs = adj[a] & adj[b] & alive & greaterThan(b);
            while (cs) {
                int c = __builtin_ctzll(cs);
                cs &= cs - 1;
                U64 ds = adj[a] & adj[b] & adj[c] & alive & greaterThan(c);
                while (ds) {
                    int d = __builtin_ctzll(ds);
                    ds &= ds - 1;
                    U64 es = adj[a] & adj[b] & adj[c] & adj[d] & alive & greaterThan(d);
                    if (es) return true;
                }
            }
        }
    }
    return false;
}

bool hasK33() {
    for (int a = 0; a < n; ++a) {
        if (!(alive & bit(a))) continue;
        for (int b = a + 1; b < n; ++b) {
            if (!(alive & bit(b))) continue;
            for (int c = b + 1; c < n; ++c) {
                if (!(alive & bit(c))) continue;
                U64 common = adj[a] & adj[b] & adj[c] & alive;
                common &= ~(bit(a) | bit(b) | bit(c));
                if (__builtin_popcountll(common) >= 3) return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        string line;
        getline(cin, line);
        fill(begin(adj), end(adj), U64(0));
        for (int i = 0; i < n; ++i) {
            getline(cin, line);
            stringstream input(line);
            int neighbor;
            while (input >> neighbor) {
                int j = neighbor - 1;
                if (j < 0 || j >= n || j == i) continue;
                adj[i] |= bit(j);
                adj[j] |= bit(i);
            }
        }
        alive = (n == 64) ? ~U64(0) : (bit(n) - 1);
        reduceGraph();
        bool containsForbiddenGraph = hasK5() || hasK33();
        cout << (containsForbiddenGraph ? 'N' : 'Y') << '\n';
    }
    return 0;
}
```

# 总结

本题的关键不是真正执行平面图判定，而是复现评测标准采用的有瑕疵化简规则。程序先删除度数不超过 $1$ 的顶点，再平滑度数为 $2$ 的顶点，最后只检查直接的 $K_5$ 和 $K_{3,3}$ 子图。

由于 $N \le 64$，使用一个 $64$ 位整数保存每个顶点的邻接集合，可以高效完成邻接交集、边删除和公共邻点统计。真正的平面图算法在数学上更加准确，但会与本题评测标准不一致，因此位掩码实现的化简判定才是本题的通过方法。
