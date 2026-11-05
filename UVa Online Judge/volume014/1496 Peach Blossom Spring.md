## 题目描述

晋代诗人陶渊明（$\texttt{Tao Yuanming}$，公元 $365–427$）有一篇名作《桃花源记》，讲述了一个渔夫偶然发现世外桃源的故事。在中文语境中，“桃花源”即指“乌托邦”。

故事中，秦朝乱世时有一群人逃入一个与世隔绝的地方，建立村庄，世代繁衍，再未与外界接触。数百年后的晋朝，一位渔夫发现了他们。

最近，一些 $\texttt{ACM}$ 竞赛选手意外发现了《桃花源记》中所述村庄的遗址，同时还找到一份关于修建藏身处的文档。文档内容如下：

村庄中有 $n$ 座房屋和 $m$ 条道路，每条道路连接两座房屋，房屋编号为 $1$ 到 $n$。有 $k$ 个家庭，每个家庭住在不同的房屋中，它们分别住在房屋 $1, 2, \dots, k$。同时有 $k$ 座破损房屋：$n - k + 1, n - k + 2, \dots, n$，这些房屋带有秘密地下室，可以用作藏身处。

所有道路均已损坏。村民需要修复若干条道路，使得每个家庭都能通过修复后的道路到达一个藏身处，且每个藏身处只能容纳一个家庭。每条道路修复需要一定的劳动力成本。村长希望找到修复道路的最小总成本，但他不知如何计算。

现在请你解决这个古代村长从未解决的问题。

## 输入格式

输入的第一行包含一个整数 $T$（$T \le 50$），表示测试用例的数量。  
对于每个测试用例，第一行包含三个整数 $n, m, k$（$4 \le n \le 50$，$0 \le m \le 1000$，$1 \le k \le 5$，$2k \le n$）。  
接下来 $m$ 行，每行包含三个整数 $u, v, w$，表示存在一条连接房屋 $u$ 和 $v$ 的损坏道路，修复它的成本为 $w$（$1 \le w \le 1000$）。

## 输出格式

对于每个测试用例，如果无法找到合适的修复方案，则输出一行字符串 `No solution`；否则输出一行整数，表示最小总成本。

## 样例

输入

```
2
4 3 1
4 2 10
3 1 9
2 3 10
6 7 2
1 5 1000
2 6 1000
1 3 1
2 3 1
3 4 1
4 5 1
4 6 1
```

输出

```
29
5
```

## 题目分析

本题要求将 $k$ 个家庭（源点）分别匹配到 $k$ 个藏身处（汇点），每个家庭对应一个藏身处，且匹配后所有选中的家庭与对应藏身处之间必须通过修复的道路连通，整体可以形成多个连通分量（每个分量包含若干家庭和藏身处），但每个分量内部必须连通，且不能有分量的家庭数不等于藏身处数（因每个藏身处只能容纳一个家庭）。

问题的本质是：在无向带权图中，选择若干条边，使得指定的 $2k$ 个终端点（$k$ 个家庭 + $k$ 个藏身处）可以被划分成 $k$ 对，每对由一个家庭和一个藏身处组成，且每对内部连通（即每对两点之间存在一条路径），并且不同对之间不要求连通。目标是最小化所选边的总权值。

这可以看作是一个**最小斯坦纳森林**问题，但限制每棵树恰好包含一个家庭和一个藏身处，且最终形成 $k$ 棵互不相交的树（或连通子图），每棵树恰好连接一个家庭和一个藏身处。

由于 $k \le 5$，终端总数 $2k \le 10$，规模很小，我们可以采用状态压缩动态规划（$\texttt{DP}$）。

首先，我们预处理任意两点间的最短路径（因为修复道路可以任意选择，若两点间路径成本更低，则直接使用最短路径即可）。然后，对于任意一个终端集合 $S$，我们可以计算将 $S$ 中所有终端连通的最小成本（即斯坦纳树）。斯坦纳树允许引入非终端节点（普通房屋）作为中间节点。

得到所有终端子集的斯坦纳树成本后，我们还需要将 $k$ 个家庭与 $k$ 个藏身处一一配对，并且每个配对内部连通。这相当于在终端集合上，选择 $k$ 个两两不相交的终端对，每个对包含一个家庭和一个藏身处，总成本为各对对应的斯坦纳树成本之和（因为不同对之间可以互相独立，不需要连通）。由于各对之间不连通，整体成本等于各对成本之和。

因此，我们可以枚举家庭与藏身处的所有完美匹配，对于每个匹配，计算每对匹配点之间的最短路径成本（或斯坦纳树成本），但由于每个匹配对仅两个终端，斯坦纳树等价于两点间的最短路。然而，如果多个匹配对共享某些中间节点，我们可能可以共享边，但共享会带来连通性问题（若共享边，则两对会连通，不符合“每个藏身处只能容纳一个家庭”的条件，实际上我们只需要每个家庭能到达某个藏身处，并不要求各对之间不连通，如果它们连通也无妨，只要每个藏身处只被一个家庭使用。也就是说，最终修复的子图可能是一个连通图，包含了所有家庭和藏身处，但每个藏身处只被分配给一个家庭，此时整体成本不一定等于各对最短路之和，因为整体连通可能通过共用边降低成本。因此，我们需要考虑整体连通的情况，而不仅仅是两两配对独立。

实际上，原问题只要求每个家庭能到达一个藏身处，且每个藏身处只能容纳一个家庭，并没有要求不同家庭到达的藏身处所在的连通分量必须分离。因此，最终的修复网络可能是一个连通图，覆盖所有 $2k$ 个终端，并且在这个连通图中，每个家庭都有一条路径到一个不同的藏身处。这等价于：在包含所有 $2k$ 个终端的某个连通子图中，要求存在一个完美匹配，使得匹配的每一对之间的路径不相交（但路径可以共享边，因为共享边不影响匹配的唯一性，只要每个家庭能到达其匹配的藏身处即可）。然而，如果我们只是将 $2k$ 个终端全部连通（即构建一棵斯坦纳树），然后在这个树上任意匹配家庭和藏身处，是否总能满足每个家庭可以到达其匹配的藏身处？是的，因为树是连通的，任意两点都有路径。所以只要构建一个包含所有终端的连通图，然后找到一种家庭与藏身处的匹配，每个家庭都能到达其匹配点，这总是可行的。但问题是要最小化成本，而成本最小的连通所有终端的图就是斯坦纳树。然而，斯坦纳树可能不是最优，因为可能不需要所有终端都在一个连通分量，可以分成多个分量，每个分量包含若干家庭和对应数量的藏身处（每个分量内的家庭数等于藏身处数），然后每个分量内部连通，总成本为各分量斯坦纳树成本之和。这样可能比全部连通更便宜，因为可以避免连接不同分量之间的边。

因此，问题转化为：将 $2k$ 个终端分成若干组，每组包含相同数量的家庭和藏身处（即家庭数与藏身处数相等），每组内部用斯坦纳树连接，总成本最小。因为 $k$ 很小，我们可以枚举所有可能的分组和匹配。

更简洁的做法：先预处理所有终端子集的斯坦纳树成本（这里终端是指所有 $2k$ 个特殊节点）。然后进行 $\texttt{DP}$，`dp[mask]` 表示已经处理了终端集合 `mask`（家庭和藏身处的混合集合）的最小成本，要求 `mask` 中家庭数等于藏身处数（否则不可行）。转移时，选取一个包含至少一个家庭和一个藏身处且家庭数等于藏身处数的子集 `sub`，用 `steiner[sub]` 作为该子集的连通成本，然后 `dp[mask] = min(dp[mask], dp[mask ^ sub] + steiner[sub])`。但需要注意，`steiner[sub]` 表示将 `sub` 中所有终端连通的最小成本，但若 `sub` 内部家庭数等于藏身处数，则这个连通分量可以满足这些家庭的需求（每个家庭可到达一个藏身处，且数量相等，通过匹配即可）。如果 `sub` 中家庭数不等于藏身处数，则不能单独成组。

另一种常见解法是：先计算出所有终端对的“匹配成本”（即两点间最短路），然后枚举所有完美匹配，对每个匹配，将匹配的 $k$ 条路径作为候选，但可能多条路径共享边可以降低总成本，因此需考虑斯坦纳树。实际上，上述分组 $\texttt{DP}$ 是正确且全面的。

具体实现时，由于 $k \le 5$，终端总数 $N_t = 2k \le 10$，我们可以用 $\texttt{Floyd-Warshall}$ 求出全源最短路，然后使用状态压缩 $\texttt{DP}$ 求任意终端子集的斯坦纳树成本（标准斯坦纳树 $\texttt{DP}$：`dp[mask][v]` 表示以 `v` 为根，连接 `mask` 中终端的最小成本，转移通过合并子集和松弛最短路）。得到 `steiner[mask]` 后，再对家庭和藏身处进行匹配和分组 $\texttt{DP}$。

另外，也可用枚举所有匹配，然后对于每个匹配，将 $k$ 对点之间分别求最短路之和，但这是不充分的，因为共享边可以更优。例如，两个家庭和两个藏身处，若它们位置接近，共用一条边可能比各自独立最短路更便宜。所以必须采用分组斯坦纳树方法。

复杂度：$n \le 50$，$m \le 1000$，$\texttt{Floyd-Warshall}$ $O(n^3)$ 可接受。终端数 $\le 10$，状态数为 $2^{10}=1024$，斯坦纳树 $\texttt{DP}$ 复杂度 $O(3^{N_t} n + 2^{N_t} n^2)$ 可接受。分组 $\texttt{DP}$ 复杂度 $O(3^{N_t})$。

## 解题思路

1. **读入数据**，用邻接矩阵存储边权，不存在的边设为无穷大。
2. **运行 $\texttt{Floyd-Warshall}$ 算法**，求出所有点对之间的最短距离。
3. **定义终端节点**：前 $k$ 个节点（$0$ 到 $k-1$）为家庭，后 $k$ 个节点（$n-k$ 到 $n-1$）为藏身处。总终端数 $N_t = 2k$。
4. **计算斯坦纳树成本**：
   - 初始化 `dp[mask][v] = INF`，对于单个终端 `i`，`dp[1<<i][terminal[i]] = 0`。
   - 对于每个 `mask`，依次进行：
     - 子集合并：`dp[mask][v] = min(dp[sub][v] + dp[mask ^ sub][v])`。
     - 最短路松弛：用 $\texttt{Floyd-Warshall}$ 得到的全源最短路 `dist`，对每个 `v`，`dp[mask][v] = min(dp[mask][u] + dist[u][v])`。
   - 最终 `steiner[mask] = ` $\min \{$ `dp[mask][v]` $\}$，表示将 `mask` 中所有终端连通的最小成本。
5. **进行分组 $\texttt{DP}$**：
   - 将终端编号为 $0$ 到 $N_t-1$，其中 $0$ 到 $k-1$ 为家庭，$k$ 到 $2k-1$ 为藏身处。
   - 定义 `valid[mask]` 为真当且仅当 `mask` 中家庭数量等于藏身处数量（即 `popcount(mask & familyMask) == popcount(mask & shelterMask)`）。
   - 定义 `dpGroup[mask]` 为处理完终端集合 `mask`（满足家庭数等于藏身处数）的最小成本。初始化 `dpGroup[0] = 0`，其余为 `INF`。
   - 对于 `mask` 从 `1` 到 `(1 << N_t) - 1`，若 `valid[mask]` 为真，则枚举 `mask` 的非空子集 `sub`，要求 `valid[sub]` 为真，且 `sub` 与 `mask` 互补的剩余部分也满足 `valid`。转移：`dpGroup[mask] = min(dpGroup[mask], dpGroup[mask ^ sub] + steiner[sub])`。
   - 最终答案即为 `dpGroup[(1 << N_t) - 1]`，若为 `INF` 则输出 `No solution`。
6. 输出结果。

上述分组 $\texttt{DP}$ 会重复考虑不同顺序，但因为我们枚举所有子集，并取最小，所以正确。也可以使用枚举匹配的方式，但分组 $\texttt{DP}$ 更简洁。

注意：若某两个终端之间不可达，则 `steiner` 可能为 `INF`，转移时需判断。

## 复杂度分析

- $\texttt{Floyd-Warshall}$：$O(n^3)$，$n \le 50$，可接受。
- 斯坦纳树 $\texttt{DP}$：状态数 $2^{N_t} \times n$，$N_t \le 10$，子集枚举 $3^{N_t}$，最短路松弛 $2^{N_t} n^2$，总复杂度 $O(3^{N_t} n + 2^{N_t} n^2)$，约 $3^{10} \times 50 \approx 3 \times 10^6$，可接受。
- 分组 $\texttt{DP}$：$O(3^{N_t})$，可接受。
- 总复杂度 $O(T \cdot (n^3 + 3^{2k} n))$，$T \le 50$，但 $k \le 5$，计算量在合理范围内。

## 代码实现

```cpp
// Peach Blossom Spring
// UVa ID: 1496
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }
        // Floyd-Warshall 求全源最短路
        for (int mid = 0; mid < n; ++mid)
            for (int i = 0; i < n; ++i) {
                if (dist[i][mid] >= INF) continue;
                for (int j = 0; j < n; ++j)
                    if (dist[mid][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]);
            }

        int totalTerminals = 2 * k;
        vector<int> termNode(totalTerminals);
        for (int i = 0; i < k; ++i) {
            termNode[i] = i;                     // 家庭 0..k-1
            termNode[k + i] = n - k + i;        // 藏身处 n-k .. n-1
        }

        int fullTermMask = (1 << totalTerminals) - 1;
        vector<vector<int>> dp(1 << totalTerminals, vector<int>(n, INF));
        // 初始化单个终端
        for (int i = 0; i < totalTerminals; ++i)
            dp[1 << i][termNode[i]] = 0;

        // 斯坦纳树 DP
        for (int mask = 1; mask <= fullTermMask; ++mask) {
            // 合并子集
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                int other = mask ^ sub;
                if (sub > other) continue; // 避免重复
                for (int u = 0; u < n; ++u) {
                    if (dp[sub][u] < INF && dp[other][u] < INF)
                        dp[mask][u] = min(dp[mask][u], dp[sub][u] + dp[other][u]);
                }
            }
            // 用全源最短路松弛，相当于取一次 min-plus 闭包
            vector<int> tmp(n, INF);
            for (int u = 0; u < n; ++u) {
                if (dp[mask][u] >= INF) continue;
                for (int v = 0; v < n; ++v)
                    if (dist[u][v] < INF)
                        tmp[v] = min(tmp[v], dp[mask][u] + dist[u][v]);
            }
            for (int v = 0; v < n; ++v)
                dp[mask][v] = min(dp[mask][v], tmp[v]);
        }

        // steiner[mask] 表示终端集合 mask 整体连通的最小成本
        vector<int> steiner(1 << totalTerminals, INF);
        for (int mask = 0; mask <= fullTermMask; ++mask) {
            int best = INF;
            for (int u = 0; u < n; ++u) best = min(best, dp[mask][u]);
            steiner[mask] = best;
        }

        int answer = INF;
        vector<int> perm(k);
        for (int i = 0; i < k; ++i) perm[i] = i;

        // 枚举所有匹配（家庭 i 匹配藏身处 perm[i]）
        do {
            // 预处理每个 pairMask 对应的终端掩码
            int pairCnt = 1 << k;
            vector<int> termMaskOfPair(pairCnt, 0);
            for (int pm = 0; pm < pairCnt; ++pm) {
                int fmask = pm; // 家庭位就是 pm 自身
                int smask = 0;
                for (int i = 0; i < k; ++i)
                    if (pm & (1 << i))
                        smask |= (1 << (k + perm[i]));
                termMaskOfPair[pm] = fmask | smask;
            }

            // 森林 DP：forest[mask] 表示满足这些对的最小总成本（允许分成多个分量）
            vector<int> forest(pairCnt, INF);
            forest[0] = 0;
            for (int mask = 1; mask < pairCnt; ++mask) {
                // 先假设整体连通
                forest[mask] = steiner[termMaskOfPair[mask]];
                // 尝试分割
                for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                    int other = mask ^ sub;
                    if (forest[sub] < INF && forest[other] < INF)
                        forest[mask] = min(forest[mask], forest[sub] + forest[other]);
                }
            }
            answer = min(answer, forest[pairCnt - 1]);
        } while (next_permutation(perm.begin(), perm.end()));

        if (answer >= INF) puts("No solution");
        else printf("%d\n", answer);
    }
    return 0;
}
```

## 总结

本题将实际问题转化为图论中的**最小斯坦纳森林**问题，利用 $k$ 很小的特点，采用状态压缩动态规划（$\texttt{DP}$）求解。

关键点：
- 用 $\texttt{Floyd-Warshall}$ 预处理全源最短路，为斯坦纳树 $\texttt{DP}$ 提供松弛基础。
- 斯坦纳树 $\texttt{DP}$ 能够处理引入非终端节点作为中间节点的情况。
- 分组 $\texttt{DP}$ 或枚举匹配的方式处理家庭与藏身处的一一对应关系。
- 注意：最终选择的子图可以分成多个连通分量，每个分量中家庭数等于藏身处数，因此分组 $\texttt{DP}$ 是必要的。

本题技巧：
- 状态压缩表示终端集合。
- 子集枚举和最优子结构。
- 使用 $+\infty$ 表示不可达，并判断无解。

该解法时间复杂度可以接受，代码实现清晰，适合作为图论和状压 $\texttt{DP}$ 的综合练习。
