
> **摘要**：本文讨论一个带字典序约束的礼物分配问题：每位朋友需获得一件自己喜欢的礼物，每件礼物只能分配一次，要求在总价格最小的前提下，使按朋友编号排列的礼物编号序列字典序最小。文章将该问题抽象为带权二分图的最小费用匹配，使用 $\texttt{Hungarian}$ 算法求解最小总价格，并通过「逐位固定 + 重新求解剩余问题」的贪心构造保证字典序最优。

# 题目描述

商店中有若干件礼物，每种礼物只有一件。每件礼物都有一个价格，并且会被部分朋友喜欢。

需要为每位朋友选择一件他喜欢的礼物，同时同一件礼物不能分配给多位朋友。目标是使购买所有礼物的总价格最小。

如果存在多个总价格相同的最优方案，则选择按照朋友编号排列的礼物编号序列中字典序最小的方案。所有朋友和礼物的编号均从 $0$ 开始。

如果无法为每位朋友分配礼物，输出 `No solution.`。

# 输入格式

第一行包含一个整数 $T$，表示需要处理的数据组数。

对于每组数据：

- 第一行包含一个整数 $n$，表示朋友数量，满足 $n \le 20$。
- 第二行包含一个整数 $m$，表示礼物数量，满足 $m \le 25$。
- 接下来有 $m$ 行，每行描述一件礼物，包含以下内容：
  - 礼物价格 $price$；
  - 喜欢该礼物的朋友数量 $k$；
  - 接下来有 $k$ 个整数，表示喜欢该礼物的朋友编号。

# 输出格式

对于每组数据：

- 如果无法为所有朋友分配礼物，输出一行 `No solution.`。
- 如果存在可行方案，输出一行：
  - 首先输出购买礼物的最小总价格；
  - 然后按照朋友编号从 $0$ 到 $n - 1$ 的顺序，输出每位朋友获得的礼物编号。

当存在多个总价格相同的方案时，输出礼物编号序列字典序最小的方案。

# 样例输入

```text
2
3
9
20 2 0 1
15 1 0
45 0
10 2 1 2
12 2 1 2
1400 3 0 1 2
100 2 0 2
10 1 2
10 2 1 2
4
4
5 1 0
4 1 1
3 1 2
2 1 1
```

# 样例输出

```text
35 1 3 7
No solution.
```

# 题目分析

每位朋友必须获得一件自己喜欢的礼物，因此朋友与礼物之间存在匹配关系。由于每件礼物只有一件，同一件礼物不能被重复使用，所以每位朋友必须匹配不同的礼物。

可以将问题抽象为一个带权二分图：

- 左侧顶点表示朋友；
- 右侧顶点表示礼物；
- 如果朋友喜欢某件礼物，就在对应的两个顶点之间建立一条边；
- 边的权值等于礼物价格。

需要为左侧的每个朋友找到一条边，并且所有选中的边对应不同礼物，使边权之和最小。这就是一个最小费用二分图匹配问题。

朋友数量最多为 $20$，礼物数量最多为 $25$。直接枚举每位朋友的礼物选择会产生指数级复杂度，无法满足要求。因此使用 $\texttt{Hungarian}$ 算法求解最小费用匹配。

除了最小总价格，题目还要求字典序最小。设最终方案为：

$$
ans[0], ans[1], \ldots, ans[n - 1]
$$

字典序最小表示优先让 $ans[0]$ 尽可能小；在 $ans[0]$ 相同的情况下，让 $ans[1]$ 尽可能小，依次类推。

因此，不能只求出任意一个最优匹配，还需要在构造答案的过程中进行字典序处理。

# 解题思路

首先建立一个布尔矩阵 `like`，其中 `like[g][f]` 表示编号为 $g$ 的礼物是否被编号为 $f$ 的朋友喜欢。再使用数组 `price` 保存每件礼物的价格。

定义函数 `getCost`，用于计算当前已经固定部分朋友礼物分配时，完成全部分配所需的最小总价格。

函数的处理过程如下：

- 将已经确定礼物的朋友加入固定部分，并累加这些礼物的价格；
- 收集还没有确定礼物的朋友；
- 收集尚未使用的礼物；
- 根据朋友是否喜欢对应礼物建立费用矩阵；
- 对剩余朋友和剩余礼物执行 $\texttt{Hungarian}$ 算法；
- 如果无法完成匹配，则返回不可行标记；否则返回固定费用与剩余匹配费用之和。

首先令所有朋友都未分配，通过 `getCost` 求出整个问题的最小总价格 `bestCost`。如果不存在完整匹配，直接输出 `No solution.`。

随后按照朋友编号从 $0$ 到 $n - 1$ 依次确定礼物。对于当前朋友，按照礼物编号从小到大的顺序尝试每一件满足以下条件的礼物：

- 该礼物还没有被使用；
- 当前朋友喜欢该礼物。

暂时将这件礼物分配给当前朋友，再调用 `getCost` 计算完成剩余匹配后的最小总价格。如果计算结果仍然等于 `bestCost`，说明当前选择可以组成一个总价格最小的完整方案，因此确定该礼物；否则撤销本次尝试，继续检查编号更大的礼物。

由于每位朋友总是优先选择编号更小且仍能构成最优方案的礼物，所以最终得到的方案一定满足：

- 总价格等于全局最小总价格；
- 礼物编号序列的字典序最小。

## 正确性说明

首先，`getCost` 将已经固定的礼物从候选集合中移除，并对剩余朋友和剩余礼物求最小费用匹配。因此，它返回的是在当前固定选择下完成全部分配所需的最小总价格。

其次，第一次调用 `getCost` 得到的 `bestCost` 是原问题所有可行方案中的最小总价格。之后每次尝试为当前朋友固定一件礼物时，只有当剩余问题的最小完成费用与固定部分费用之和仍等于 `bestCost`，该选择才可能属于某个全局最优方案。因此，算法不会选择导致总价格增加的礼物。

最后，算法按照朋友编号顺序处理，并且对每位朋友按照礼物编号递增顺序尝试。对于当前朋友，编号更小的礼物一旦能够保留全局最优总价格，就会立即被选中。这保证了当前前缀在所有最优方案中字典序最小。对每个位置依次执行相同操作后，最终得到的完整序列就是所有最优方案中字典序最小的序列。

## 复杂度分析

设朋友数量为 $n$，礼物数量为 $m$。

一次 $\texttt{Hungarian}$ 算法处理规模不超过 $n \times m$ 的费用矩阵，时间复杂度为：

$$
O(n \times m^2)
$$

字典序构造过程中最多尝试 $n \times m$ 次礼物选择，因此总时间复杂度为：

$$
O(n^2 \times m^3)
$$

费用矩阵、匹配辅助数组以及喜好关系矩阵的空间复杂度为：

$$
O(n \times m)
$$

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long inf = LLONG_MAX / 4;

long long hungarian(const vector<vector<long long>> &cost) {
    int n = cost.size(), m = cost[0].size();
    vector<long long> u(n + 1), v(m + 1), minVal(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<bool> used(m + 1);
        fill(minVal.begin(), minVal.end(), inf);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = inf;
            for (int j = 1; j <= m; ++j) if (!used[j]) {
                long long cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < minVal[j]) {
                    minVal[j] = cur;
                    way[j] = j0;
                }
                if (minVal[j] < delta) {
                    delta = minVal[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j) if (used[j]) {
                u[p[j]] += delta;
                v[j] -= delta;
            } else {
                minVal[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    long long res = -v[0];
    for (int j = 1; j <= m; ++j) if (p[j] != 0 && cost[p[j] - 1][j - 1] >= inf / 2) return -1;
    return res;
}

long long getCost(const vector<int> &ans, const vector<long long> &price, const vector<vector<bool>> &like, int n, int m) {
    vector<int> friends, gifts;
    vector<bool> used(m);
    long long fixedCost = 0;
    for (int i = 0; i < n; ++i) {
        if (ans[i] != -1) {
            used[ans[i]] = true;
            fixedCost += price[ans[i]];
        } else {
            friends.push_back(i);
        }
    }
    for (int i = 0; i < m; ++i) if (!used[i]) gifts.push_back(i);
    if (friends.empty()) return fixedCost;
    if (friends.size() > gifts.size()) return -1;
    int fn = friends.size(), gn = gifts.size();
    vector<vector<long long>> cost(fn, vector<long long>(gn, inf));
    for (int i = 0; i < fn; ++i) {
        for (int j = 0; j < gn; ++j) {
            if (like[gifts[j]][friends[i]]) cost[i][j] = price[gifts[j]];
        }
    }
    long long remainCost = hungarian(cost);
    if (remainCost == -1) return -1;
    return fixedCost + remainCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<long long> price(m);
        vector<vector<bool>> like(m, vector<bool>(n));
        for (int i = 0; i < m; ++i) {
            int cnt, id;
            cin >> price[i] >> cnt;
            for (int j = 0; j < cnt; ++j) {
                cin >> id;
                like[i][id] = true;
            }
        }
        vector<int> ans(n, -1);
        long long bestCost = getCost(ans, price, like, n, m);
        if (bestCost == -1) {
            cout << "No solution.\n";
            continue;
        }
        vector<bool> used(m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (used[j] || !like[j][i]) continue;
                ans[i] = j;
                long long curCost = getCost(ans, price, like, n, m);
                if (curCost == bestCost) {
                    used[j] = true;
                    break;
                }
                ans[i] = -1;
            }
        }
        cout << bestCost;
        for (int i = 0; i < n; ++i) cout << ' ' << ans[i];
        cout << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将礼物分配问题转化为带权二分图最小费用匹配问题，并使用 $\texttt{Hungarian}$ 算法求解最小总价格。

处理字典序要求时，不能直接使用任意一个最优匹配，而应按照朋友编号顺序逐个确定答案。每次按照礼物编号递增尝试，并通过重新求解剩余问题判断当前选择是否仍能达到全局最优价格。这样既保证了总价格最小，也保证了结果序列字典序最小。
