
> **摘要**：本文讨论矿井逃生井的安装问题：给定一个无向连通图，要求在最坏情况下（任意一个交叉点坍塌）所有存活工人都能通过逃生井到达地面，求最少逃生井数量及对应方案数。文章将问题转化为无向图的点双连通分量分解，利用基于 $\texttt{DFS}$ 的边栈方法求出所有点双连通分量与割点，并给出按分量中割点数量分类统计答案的完整思路与 $\texttt{C++}$ 实现，时间复杂度为 $O(N \log V)$。

 # 题目描述

矿井由若干个交叉点和隧道组成，任意两个交叉点之间都可以通过隧道互相到达。若某个交叉点发生坍塌，与该交叉点相连的所有隧道同时失效，矿井可能被分割成多个部分。

需要在若干个交叉点安装逃生井，使得无论哪个交叉点坍塌，坍塌后仍然存活的所有工人都可以通过逃生井到达地面。

求安装逃生井所需的最少数量，以及在达到最少数量时的安装方案总数。结果保证可以使用有符号的 $64$ 位整数表示。

# 输入格式

输入包含多个测试用例。

每个测试用例的第一行包含一个正整数 $N$，表示隧道数量，满足 $N \le 5 \times 10^4$。接下来有 $N$ 行，每行包含两个不同的整数 $s$ 和 $t$，表示交叉点 $s$ 与交叉点 $t$ 之间存在一条隧道。

交叉点编号从 $1$ 开始连续编号，任意两个交叉点之间至多存在一条隧道。每个测试用例中的所有隧道构成一个连通图。

当输入的一行只包含 $0$ 时，输入结束。

# 输出格式

对于每个测试用例，输出一行：

```text
Case k: a b
```

其中 $k$ 表示测试用例编号，$a$ 表示最少需要安装的逃生井数量，$b$ 表示达到最少数量时的安装方案总数。

# 样例输入

```text
9
1 3
4 1
3 5
1 2
2 6
1 5
6 3
1 6
3 2
6
1 2
1 3
2 4
2 5
3 6
3 7
0
```

# 样例输出

```text
Case 1: 2 4
Case 2: 4 1
```

# 题目分析

将矿井抽象成一个无向连通图，交叉点对应顶点，隧道对应边。一个交叉点坍塌后，图中与该顶点相关的部分会被删除。若删除某个顶点后图被分成多个连通部分，则该顶点是割点。

按照双连通分量的定义，可以将图分解成若干个点双连通分量。对于任意一个点双连通分量，若其中恰好包含一个割点，则称它为叶子分量。叶子分量中除割点之外的顶点无法通过其他分量获得逃生井，因此必须在这些顶点中选择一个位置安装逃生井。

设一个点双连通分量中包含的割点数量为 $c$。

- 当 $c = 1$ 时，该分量必须安装一口逃生井，安装位置可以是该分量中任意一个非割点，因此方案数增加 $1$，总方案数乘以非割点数量。
- 当 $c \ge 2$ 时，该分量与其他分量之间存在足够的连接，工人可以通过其他叶子分量中的逃生井离开，因此该分量不需要额外安装逃生井。
- 当整个图只有一个点双连通分量时，图中不存在割点。任意一个交叉点坍塌后，剩余部分仍然连通，因此需要安装两口逃生井，并且两口逃生井必须安装在不同的交叉点上。方案数为从所有交叉点中选择两个交叉点的组合数：

$$
\binom{V}{2} = \frac{V(V-1)}{2}
$$

其中，$V$ 表示图中的交叉点数量。

程序使用基于 $\texttt{DFS}$ 的点双连通分量分解方法。遍历边时，将经过的边压入栈中；当搜索回溯到顶点 $u$，且某个子树的低值满足 $low[v] \ge dfn[u]$ 时，栈顶边不断弹出，直到当前树边被弹出，这些边的端点共同构成一个点双连通分量。

在分解完成后，程序统计每个点双连通分量中的割点数量，并根据上述分类计算答案。

# 解题思路

在搜索过程中，为每个顶点维护两个值：

- $dfn[u]$ 表示顶点 $u$ 被首次访问的时间戳。
- $low[u]$ 表示从顶点 $u$ 的子树出发，通过树边和至多一条返祖边能够到达的最早顶点时间戳。

对于当前顶点 $u$ 的一条未访问边 $(u,v)$，先将这条边压入边栈：

- 若顶点 $v$ 未被访问，则递归搜索 $v$，并使用 $low[v]$ 更新 $low[u]$。
- 若 $low[v] \ge dfn[u]$，说明以 $v$ 为根的子树无法通过返祖边到达 $u$ 的祖先，因此从栈中弹出边直到弹出 $(u,v)$，弹出的所有边构成一个点双连通分量。
- 若顶点 $v$ 已经被访问，则使用 $dfn[v]$ 更新 $low[u]$。

割点的判断规则如下：

- 对于非根顶点 $u$，只要存在一个子树顶点 $v$ 满足 $low[v] \ge dfn[u]$，顶点 $u$ 就是割点。
- 对于深度优先搜索树的根顶点，只有当它拥有至少两个子树时才是割点。

本题输入保证图连通，因此从顶点 $1$ 开始一次搜索即可访问所有顶点。每条无向边通过两条有向边存储，并使用 `used` 标记同时标记正向边和反向边，保证每条无向边只被处理一次。

点双连通分量保存完成后，逐个统计其中包含的割点数量。设当前分量中的顶点总数为 $s$，割点数量为 $c$：

- 当 $c = 1$ 时，需要安装一口逃生井，方案数乘以 $s-c$。
- 当所有分量只有一个时，直接使用 $\frac{V(V-1)}{2}$ 计算方案数，并将逃生井数量设为 $2$。
- 其他分量不增加逃生井数量，也不改变方案数。

每条边只进入和离开边栈一次，深度优先搜索的主要遍历过程为线性复杂度。程序使用 `set` 保存分量中的顶点，插入操作的复杂度为 $O(\log V)$，因此整体时间复杂度为 $O(N \log V)$，空间复杂度为 $O(N+V)$。

# 代码实现

代码通过边栈分解点双连通分量，并统计割点数量。对于只有一个点双连通分量的情况，使用组合数计算答案。

```cpp
// Mining Your Own Business
// UVa ID: 1108
// Verdict: Accepted
// Submission Date: 2024-11-24
// UVa Run Time: 0.310s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010;

struct EDGE
{
    int u, v, used, nxt;
    EDGE (int u = 0, int v = 0, int used = 0, int nxt = 0): u(u), v(v), used(used), nxt(nxt) {}
} g[MAXV << 1];

struct edge {
    int u, v;
    bool operator==(const edge e) const {
        return (e.u == u && e.v == v) || (e.u == v && e.v == u);
    }
};

int idx, head[MAXV];

void addEdge(int u, int v) {
    g[idx] = EDGE(u, v, 0, head[u]);
    head[u] = idx++;
    g[idx] = EDGE(v, u, 0, head[v]);
    head[v] = idx++;
}

int dfn[MAXV], ic[MAXV], dfstime = 0;

stack<edge> stk;

int vbcc = 0;
set<int> vbc[MAXV];

int dfs(int u, int father) {
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        if (g[i].used) continue;
        g[i].used = g[i ^ 1].used = 1;
        edge eu = edge{g[i].u, g[i].v};
        stk.push(eu);
        int v = g[i].v;
        if (!dfn[v]) {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) {
                ic[u] = 1;
                vbc[vbcc].clear();
                while (stk.size()) {
                    edge ev = stk.top();
                    stk.pop();
                    vbc[vbcc].insert(ev.u);
                    vbc[vbcc].insert(ev.v);
                    if (ev == eu) break;
                }
                vbcc++;
            }
        } else lowu = min(lowu, dfn[v]);
    }
    if (father < 0) ic[u] = children > 1;
    return lowu;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    int n;
    while (cin >> n) {
        if (n == 0) break;
        idx = 0;
        memset(head, -1, sizeof head);
        int mx = 1;
        for (int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
            mx = max(mx, max(u, v));
        }
        dfstime = 0;
        memset(ic, 0, sizeof ic);
        memset(dfn, 0, sizeof dfn);
        vbcc = 0;
        dfs(1, -1);
        cout << "Case " << cases++ << ": ";
        long long shafts = 0, ways = 1;
        for (int i = 0; i < vbcc; i++) {
            int cv = 0;
            for (auto u : vbc[i])
                if (ic[u])
                    cv++;
            if (cv == 1) shafts++, ways *= (vbc[i].size() - cv);
        }
        if (vbcc == 1) cout << 2 << ' ' << 1LL * mx * (mx - 1) / 2 << '\n';
        else cout << shafts << ' ' << ways << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将逃生井问题转化为无向图的点双连通分量问题。

关键结论如下：

- 通过基于 $\texttt{DFS}$ 的边栈方法可以在线性遍历框架下分解点双连通分量。
- 只包含一个割点的点双连通分量是必须安装逃生井的叶子分量。
- 每个叶子分量贡献一口逃生井，安装位置可以选择该分量中的任意非割点。
- 当整个图只有一个点双连通分量时，需要安装两口逃生井，方案数为 $\binom{V}{2}$。
- 使用 `long long` 保存方案数，满足题目对结果范围的要求。
