
> **摘要**：本题给定 $n$ 个国家之间的树形控制关系（每个国家最多被一个国家直接控制，且无环），贿赂一个国家即可获得它及其所有后代国家的选票。要求在获得至少 $m$ 张选票的前提下，求所需的最少钻石数量。解法将控制关系建模为森林，把“贿赂某国即获得其整棵子树选票”视为不可拆分的背包选择项，通过后序遍历计算子树规模，并用动态规划按票数累计最小成本，最终在所有票数不少于 $m$ 的状态中取最小值，时间复杂度为 $O(n^2)$。

# 题目描述

有 $n$ 个国家参与投票。每个国家都有一个行贿成本，支付该成本后，该国以及它直接或间接控制的所有国家都会投票支持指定候选方。

每个国家最多被一个国家直接控制，控制关系无环。给定每个国家的直接控制对象，以及需要获得的至少 $m$ 张支持票，求获得至少 $m$ 票所需的最少钻石数量。

# 输入格式

输入包含多组测试数据。每组数据首先包含两个整数 $n$ 和 $m$，分别表示国家数量和至少需要获得的票数。

接下来 $n$ 行描述各个国家。每行首先给出国家名称和行贿成本，之后给出若干个由该国家直接控制的国家名称。若该国家没有直接控制其他国家，则该行在成本后结束。

输入以单独一行的 `#` 结束。

# 输出格式

对于每组测试数据，输出一行一个整数，表示获得至少 $m$ 票所需的最少钻石数量。

# 样例输入

```text
3 2
Aland 10
Boland 20 Aland
Coland 15
#
```

# 样例输出

```text
20
```

# 题目分析

把国家看作节点，直接控制关系看作有向边。题目保证控制关系无环，并且每个国家最多被一个国家直接控制，因此每个连通部分都是一棵以未受其他国家控制的国家为根的树。

贿赂一个国家会同时获得它及其所有后代国家的选票。若选择贿赂某个国家，就不需要再单独贿赂它的任何后代，因为这些国家已经包含在所获得的选票中。对于一个国家的子树，可以在以下选择中权衡：直接贿赂该国家并获得整棵子树的票，或分别对子树中的若干部分作选择，以更低成本获得所需票数。

要求获得至少 $m$ 票，属于带有树形依赖关系的背包问题。处理一个节点时，需要记录当前已经处理的国家集合在不同得票数下的最小成本。由于选取某个节点会一次性获得它的整棵子树的票数，树的后序遍历可以先计算子节点及子树大小，再将该节点作为一个整体加入背包状态。

题目通过代码使用并查集维护节点在遍历过程中所属的已处理连通集合，并将每个国家的“整棵子树”作为一个不可拆分的选择项加入动态规划。动态规划数组按得票数保存最小成本，最终在票数不少于 $m$ 的状态中取成本最小值。

# 解题思路

设 $\textit{dp}[i][j]$ 表示当前动态规划阶段中，处理到序列位置 $i$ 时，获得恰好 $j$ 张选票的最小成本。不可达状态设为无穷大，初始状态为 $\textit{dp}[0][0]=0$。

对每个根节点进行深度优先遍历。遍历一个节点 $u$ 时，先递归处理所有直接控制的国家，并计算以 $u$ 为根的子树大小 $r$。随后将该子树作为一次选择加入动态规划：选择贿赂 $u$，就以成本 $\textit{diamonds}[u]$ 获得 $r$ 张票；不选择该整体时，则保留原有票数和成本。并查集用于识别当前节点及其已处理后代构成的集合，避免在遍历过程中重复将同一子树作为选择项加入。

转移按票数从大到小进行，保证当前节点不会在同一次转移中被重复使用。若当前已有 $j-r$ 张票的方案，则可以用成本增加 $\textit{diamonds}[u]$ 更新获得 $j$ 张票的最小成本。若 $j<r$，选择该子树无法对应到当前票数状态，状态保持原值。

国家控制关系可能包含多个互不相连的树，因此从每个入度为 $0$ 的国家开始进行深度优先遍历。所有根节点处理完成后，枚举票数从 $m$ 到 $n$ 的状态，取其中最小成本作为答案。因为题目要求至少获得 $m$ 票，所以需要比较所有不小于 $m$ 的票数，而不是只检查恰好 $m$ 票。

设国家数量为 $n$。动态规划为每个国家处理至多 $n+1$ 个票数状态，因此时间复杂度为 $O(n^2)$；邻接表、并查集和动态规划数组的空间复杂度为 $O(n^2)$，其中主要空间开销来自动态规划数组。

# 代码实现

```cpp
// Bribing FIPA
// UVa degree: 1222
// Verdict: Accepted
// Submission Date: 2018-10-31
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210, INF = 0x3f3f3f3f;

int n, m, diamonds[MAXV], C, degree[MAXV], parent[MAXV], dp[MAXV][MAXV];
list<int> edges[MAXV];
map<string, int> menu;
vector<int> S;

void makeSet()
{
    for (int i = 0; i < MAXV; i++) parent[i] = i;
}

int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

void unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
    if (x != y) parent[y] = x;
}

int dfs(int u)
{
    int r = 1;
    for (auto v : edges[u])
    {
        r += dfs(v);
        unionSet(u, v);
    }
    int C = S.size();
    for (int i = C - 1; i >= 0; i--)
    {
        if (u == findSet(S[i])) continue;
        for (int j = n; j >= 0; j--)
        {
            if (j >= r)
                dp[C][j] = min(dp[C][j], dp[i][j - r] + diamonds[u]);
            else
                dp[C][j] = dp[i][j];
        }
    }
    S.push_back(u);
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        if (line == "#") break;
        istringstream iss(line);
        iss >> n >> m;

        int idx = 1;
        menu.clear();
        memset(degree, 0, sizeof(degree));
        for (int i = 1; i <= n; i++) edges[i].clear();

        int diamondCount, xi, yi;
        string countryName, dcName;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            iss.clear();
            iss.str(line);
            iss >> countryName >> diamondCount;
            if (menu.find(countryName) == menu.end())
            {
                menu[countryName] = idx;
                idx++;
            }
            diamonds[xi = menu[countryName]] = diamondCount;
            while (iss >> dcName)
            {
                if (menu.find(dcName) == menu.end())
                {
                    menu[dcName] = idx;
                    idx++;
                }
                edges[xi].push_back(yi = menu[dcName]);
                degree[yi]++;
            }
        }

        makeSet();
        memset(dp, INF, sizeof(dp));
        dp[0][0] = 0;
        S.clear();
        S.push_back(0);
        for (int i = 1; i <= n; i++)
            if (!degree[i])
                dfs(i);

        int cost = INF;
        for (int i = 0; i <= (n + 1); i++)
            for (int j = m; j <= n; j++)
                cost = min(cost, dp[i][j]);
        cout << cost << '\n';
    }

    return 0;
}
```

# 总结

本题将控制关系建模为森林，并把行贿选择转化为“以一个国家的成本获得其整棵子树选票”的背包决策。后序遍历负责计算子树规模，动态规划负责累计票数和最小成本，最后在所有票数不少于目标值的状态中取最小值。
