## 题目描述

某公司希望在计算机上模拟其制造过程。整个过程可划分为若干步骤，步骤间存在有向依赖关系（有向图），且所有步骤均从唯一的第一步（编号为 $1$）出发可达。若从 $1$ 到步骤 $i$ 的所有路径都必须经过步骤 $j$，则称步骤 $i$ **完全依赖于** 步骤 $j$ 。显然，所有步骤都完全依赖于步骤 $1$ 。

公司希望将上述依赖图转化为一棵 **依赖树** ，使得树中每个结点的所有后代都完全依赖于该结点。给定有向图（邻接矩阵），要求输出该依赖树的 $n-1$ 条边（直接父子关系），边按字典序升序输出。

## 输入格式

输入包含多组测试数据，每组数据格式如下：

- 第一行一个整数 $n$ （ $2 \le n \le 99$ ），表示步骤数；
- 接下来 $n$ 行，每行 $n$ 个整数（ $0$ 或 $1$ ），其中 $a_{ij}=1$ 表示存在有向边 $i \to j$ ，即步骤 $j$ 直接跟随步骤 $i$ 。

输入文件直到 $\texttt{EOF}$ 结束。

## 输出格式

对于每组数据，输出 $n-1$ 行，每行两个整数 $i$ 和 $j$ ，表示结点 $j$ 是结点 $i$ 在依赖树中的直接后代。输出顺序按字典序升序排列：先按 $i$ 递增，若相同则按 $j$ 递增。

## 样例

输入
```
10
0 1 1 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 1 0 1 1 0 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 1 0 0
0 0 1 0 0 0 0 0 1 1
1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0
```

输出
```
1 2
1 3
3 4
4 5
4 6
4 7
7 8
8 9
8 10
```

## 题目分析

本题的本质是求解有向图的 **支配树** （ $\texttt{Dominator Tree}$ ）。给定起点 $1$ 的有向图，结点 $u$ 支配结点 $v$ 当且仅当从起点到 $v$ 的每条路径都经过 $u$ 。对于每个结点 $v \ne 1$ ，其 **直接支配者** （ $\textit{idom}$ ）是支配 $v$ 且离 $v$ 最近的结点（除自身外）。将每个非根结点与它的直接支配者相连，就得到了支配树。

原题中“完全依赖于”即为支配关系，因此问题转化为：根据有向图的邻接矩阵，构造以 $1$ 为根的支配树，并按字典序输出所有父子边。

$n$ 最大仅为 $99$ ，非常适合使用经典的数据流迭代算法求解支配集合，再从中提取直接支配者。

## 解题思路

### 支配集合的迭代计算

定义 $\textit{Dom}(v)$ 为所有支配结点 $v$ 的结点集合（包含 $v$ 自身）。根据支配关系的性质， $\textit{Dom}(v)$ 满足以下数据流方程：

$$
\textit{Dom}(v) = \{ v \} \cup \bigcap_{p \in \textit{pred}(v)} \textit{Dom}(p)
$$

其中 $\textit{pred}(v)$ 是 $v$ 的所有前驱结点（即存在边 $p \to v$ 的结点）。对于起点 $1$ ，有 $\textit{Dom}(1) = \{1\}$ 。由于图保证从 $1$ 可达所有结点，该方程有唯一最小解。

初始时，令 $\textit{Dom}(1)=\{1\}$ ，其余结点的 $\textit{Dom}(v)$ 为所有结点的全集（即 $\{1,2,\dots,n\}$ ）。然后反复迭代上述方程直到所有集合不再变化。因为 $n$ 很小，迭代次数最多为 $n$ ，每次迭代需计算所有结点的交集，复杂度 $O(n^3)$ ，完全可以接受。

### 直接支配者的确定

对于每个结点 $v \ne 1$ ，在集合 $\textit{Dom}(v) \setminus \{v\}$ 中，所有结点都是 $v$ 的支配者。其中，直接支配者 $\textit{idom}(v)$ 是离 $v$ 最近的那个，即其支配集合大小最大（因为支配关系具有传递性，若 $u$ 支配 $w$ 且 $w$ 支配 $v$ ，则 $\textit{Dom}(u) \subset \textit{Dom}(w) \subset \textit{Dom}(v)$ ，支配集合越大的结点越靠近 $v$ ）。因此，只需在 $\textit{Dom}(v)$ 中查找除 $v$ 外支配集合大小最大的结点，即为直接支配者。

### 输出排序

得到所有 $\textit{idom}(v)$ 后，收集边 $( \textit{idom}(v), v )$ ，按字典序（先按第一关键字，再按第二关键字）排序输出。

### 复杂度分析

- 迭代求解支配集合：每次迭代对每个结点遍历其所有前驱，并对集合做交集运算。集合大小最大为 $n$ ，前驱总数最多 $n^2$ ，迭代次数不超过 $n$ ，故最坏时间复杂度 $O(n^4)$ ，但 $n \le 99$ 时完全可行（实际运行远小于此）。
- 求直接支配者：对每个 $v$ 遍历其支配集合 $O(n)$ ，共 $O(n^2)$ 。
- 排序输出： $O(n \log n)$ 。
- 空间复杂度： $O(n^2)$ （存储邻接矩阵及支配集合）。

## 代码实现

```cpp
// Optimisation
// UVa ID: 781
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.360s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        // 读取邻接矩阵并构建前驱列表
        vector<vector<int>> pred(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                int x;
                cin >> x;
                if (x == 1) pred[j].push_back(i); // i -> j，所以 j 的前驱包含 i
            }
        }
        // 初始化支配集合：Dom[1] = {1}，其余为全集
        vector<set<int>> dom(n + 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dom[i].insert(j);
        dom[1].clear();
        dom[1].insert(1);
        // 迭代求解支配集合
        bool changed = true;
        while (changed) {
            changed = false;
            for (int v = 2; v <= n; ++v) {
                set<int> inter;
                bool first = true;
                for (int p : pred[v]) {
                    if (first) { inter = dom[p]; first = false; }
                    else {
                        set<int> tmp;
                        set_intersection(inter.begin(), inter.end(),
                                         dom[p].begin(), dom[p].end(),
                                         inserter(tmp, tmp.begin()));
                        inter = tmp;
                    }
                }
                inter.insert(v);
                if (inter != dom[v]) {
                    dom[v] = inter;
                    changed = true;
                }
            }
        }
        // 求每个结点的直接支配者
        vector<int> idom(n + 1, 0);
        for (int v = 2; v <= n; ++v) {
            int best = -1, bestSize = -1;
            for (int u : dom[v]) {
                if (u == v) continue;
                int sz = (int)dom[u].size();
                if (sz > bestSize) {
                    bestSize = sz;
                    best = u;
                }
            }
            idom[v] = best;
        }
        // 收集边并排序
        vector<pair<int, int>> edges;
        for (int v = 2; v <= n; ++v) edges.emplace_back(idom[v], v);
        sort(edges.begin(), edges.end());
        // 输出
        for (auto &e : edges) cout << e.first << ' ' << e.second << '\n';
    }
    return 0;
}
```

## 总结

本题通过求解有向图的支配树，将“完全依赖”关系转化为树形结构。核心技巧是利用数据流迭代方程计算每个结点的支配集合，然后根据支配集合的大小确定直接支配者。由于 $n$ 很小，这种朴素算法不仅易于实现，而且足够高效。

关键点在于理解支配关系的传递性和数据流方程的正确性。对于更大规模的图，可以改用 $\texttt{Lengauer-Tarjan}$ 算法在线性时间内求解，但在本题约束下，迭代算法是最直接、最清晰的选择。本题也体现了图论中支配树在实际问题（如程序流程控制）中的应用价值。
