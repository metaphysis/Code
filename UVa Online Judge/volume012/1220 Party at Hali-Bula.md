
> **摘要**：本文讨论一道树形结构上的员工聚会邀请问题：员工关系构成一棵层级树，要求任何员工都不能与其直接上司同时受邀，求最多可邀请的人数并判断最优名单是否唯一。文章将问题转化为树的最大独立集与唯一性判定，给出树形动态规划的状态设计与转移方程，并说明如何沿最优状态递归检查名单唯一性。

# 题目描述

某公司的员工关系构成一棵层级树：除最高负责人外，每名员工恰好有一名直接上司。现在要邀请员工参加聚会，要求任何员工都不能与其直接上司同时受邀。

求最多能够邀请多少名员工，并判断达到这一人数的受邀名单是否唯一。

# 输入格式

输入包含多组测试数据。每组数据首先给出一个整数 $n$，表示员工数量，满足 $1 \le n \le 200$。接下来一行给出最高负责人的姓名；随后 $n-1$ 行，每行给出两个人的姓名，依次表示一名员工及其直接上司。姓名只包含字母，长度为 $1$ 到 $100$。

输入以单独的 $0$ 结束，该行不属于任何测试数据。

# 输出格式

对于每组测试数据，输出一行：先输出最多受邀人数，再输出名单是否唯一。名单唯一时输出 $\texttt{Yes}$，否则输出 $\texttt{No}$，两者之间用一个空格分隔。

# 样例输入

```text
6
Jason
Jack Jason
Joe Jack
Jill Jason
John Jack
Jim Jill
2
Ming
Cho Ming
0
```

# 样例输出

```text
4 Yes
1 No
```

# 题目分析

将每名员工看作树上的一个节点，将直接上司与下属之间的关系看作一条边。限制条件等价于：不能同时选中一条边的两个端点。因此，问题转化为求树的最大独立集，同时判断最大独立集是否唯一。

对于一名员工，只有邀请和不邀请两种选择。邀请该员工时，其直接下属都不能受邀；不邀请该员工时，每名直接下属都可以独立地选择邀请或不邀请，以使各自子树中的受邀人数最大。由于不同下属的子树互不相交，这些子树的最优人数可以直接相加，适合使用树形动态规划。

判断唯一性时，需要沿着能产生最大人数的选择检查。如果某个节点不受邀，而它的一名下属在受邀和不受邀两种状态下都能取得相同的最优人数，那么选择该下属或不选择该下属会得到两份不同的最优名单，整体名单因此不唯一。如果两种状态的人数不同，则只有人数更大的状态能够用于最优解，还需继续检查该状态对应的子树名单是否唯一。

# 解题思路

设 $\textit{dp}[u][0]$ 表示在员工 $u$ 不受邀的条件下，$u$ 的子树中最多能邀请的人数；$\textit{dp}[u][1]$ 表示在员工 $u$ 受邀的条件下，$u$ 的子树中最多能邀请的人数。设 $v$ 遍历 $u$ 的所有直接下属，则转移关系为：
$$
\textit{dp}[u][0]=\sum_v \max(\textit{dp}[v][0],\textit{dp}[v][1])
$$
$$
\textit{dp}[u][1]=1+\sum_v \textit{dp}[v][0]
$$
第一式中，$u$ 不受邀，每名直接下属都可以选择更优的状态；第二式中，$u$ 受邀，所有直接下属都必须不受邀。叶节点没有下属，因此其不受邀和受邀两种状态的值分别为 $0$ 和 $1$。对整棵树进行一次深度优先搜索，先计算子节点，再计算父节点，即可得到所有状态。

设最高负责人的编号为 $0$，最多受邀人数为 $\max(\textit{dp}[0][0],\textit{dp}[0][1])$。若根节点的两个状态值相等，则邀请和不邀请最高负责人都能得到最大人数，两份名单不同，因此答案不唯一。否则，从较大的根节点状态出发，递归检查唯一性：当前节点受邀时，所有直接下属都只能取不受邀状态；当前节点不受邀时，若某名直接下属的两个状态值相等，则答案不唯一，否则沿该下属人数较大的状态继续检查。所有选定状态都通过检查时，最大受邀名单唯一。

代码使用 $\texttt{map}$ 将姓名映射为整数编号，并用邻接表保存从上司指向直接下属的边。设员工姓名的最大长度为 $L$，建树时使用有序映射，时间复杂度为 $O(nL\log n)$；两次树遍历均为 $O(n)$。保存姓名映射和树结构的空间复杂度为 $O(nL+n)$，递归栈最多使用 $O(n)$ 空间。

# 代码实现

```cpp
// Party at Hali-Bula
// UVa ID: 1220
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N;
int dp[256][2];
list<int> edges[256];

int dfs(int u)
{
    dp[u][0] = 0, dp[u][1] = 1;
    for (auto v : edges[u])
    {
        dfs(v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
    return max(dp[u][0], dp[u][1]);
}

bool isUnique(int u, int state)
{
    for (auto v : edges[u])
    {
        if (state == 0)
        {
            if (dp[v][0] == dp[v][1]) return false;
            if (!isUnique(v, dp[v][0] < dp[v][1]))
                return false;
        }
        else
        {
            if (!isUnique(v, 0))
                return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N)
    {
        if (N == 0) break;
        for (int i = 0; i <= N; i++)
            edges[i].clear();

        map<string, int> indexer;
        string name1, name2;
        // Big Boss.
        cin >> name1;
        indexer[name1] = 0;
        
        int idx = 1;
        for (int i = 1; i < N; i++)
        {
            cin >> name1 >> name2;
            if (indexer.find(name1) == indexer.end())
                indexer[name1] = idx++;
            if (indexer.find(name2) == indexer.end())
                indexer[name2] = idx++;
            edges[indexer[name2]].push_back(indexer[name1]);
        }

        cout << dfs(0) << ' ';
        if (dp[0][0] == dp[0][1])
        {
            cout << "No\n";
            continue;
        }
        cout << (isUnique(0, dp[0][0] < dp[0][1]) ? "Yes" : "No") << '\n';
    }

    return 0;
}
```

# 总结

本题通过树形动态规划分别计算每个节点受邀和不受邀时的最大人数，再沿最优状态检查名单是否唯一。判断唯一性的关键是只检查实际可能出现在全局最优解中的状态：当父节点不受邀且某个子节点的两种状态同样最优时，就存在不同的最大受邀名单。
