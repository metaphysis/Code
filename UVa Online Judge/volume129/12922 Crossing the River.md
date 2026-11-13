
> **摘要**：本题描述了一个僵尸末日后的渡河问题：$n$ 名幸存者需要乘船从城市港口前往安全岛，船有载人数 $k$ 与载重量 $W$ 双重限制，且每次航行至少需要 $1$ 人驾驶。要求所有幸存者最终到达安全岛，求最少航行次数，无法完成则输出 $-1$。由于 $n \le 16$，可采用二进制状态压缩表示已到达安全岛的幸存者集合，并额外记录船所在的一侧，将问题转化为无权图上的最短路问题，使用 $\texttt{BFS}$ 求解，配合子集枚举完成状态转移，总时间复杂度为 $O(3^n)$，空间复杂度为 $O(2^n)$。

# 题目描述

僵尸末日后，有 $n$ 名幸存者需要乘船从城市港口前往安全岛。船最多可以乘坐 $k$ 人，并且船上所有人的总重量不能超过 $W$。

船需要在城市港口和安全岛之间往返，只有船到达一侧后，才能继续从该侧载人前往另一侧。每次航行船上至少需要有 $1$ 个人，否则无法驾驶船。

所有幸存者初始位于城市港口，船也位于城市港口。要求所有幸存者最终到达安全岛，求完成任务所需的最少航行次数。如果无法完成任务，输出 $-1$。

# 输入格式

输入包含多组测试数据，每组测试数据持续到文件结束。

每组测试数据的第一行包含 $3$ 个整数：

- $n$：幸存者人数，满足 $1 \le n \le 16$；
- $W$：船的最大载重量，满足 $1 \le W \le 100$；
- $k$：船的最大载人数，满足 $1 \le k \le 6$。

第二行包含 $n$ 个整数，第 $i$ 个整数表示第 $i$ 名幸存者的体重，记为 $w_i$，满足 $1 \le w_i \le 100$。

# 输出格式

对于每组测试数据，输出一个整数，表示所有幸存者到达安全岛所需的最少航行次数。

如果无法完成渡河，输出 $-1$。

# 样例输入

```text
2 100 2
50 50
3 50 2
10 40 40
```

# 样例输出

```text
1
3
```

# 题目分析

船的每次航行都必须满足人数限制和重量限制，因此一次航行可以看作选择一个合法的幸存者集合。由于船需要往返，去程和返程的可选人员集合不同：

- 船在城市港口时，只能选择当前位于城市港口的幸存者前往安全岛；
- 船在安全岛时，只能选择当前位于安全岛的幸存者返回城市港口。

直接枚举所有航行方案会产生大量重复状态。例如，不同的航行顺序可能让相同的幸存者集合和船位置同时出现。对于后续决策来说，这些情况完全等价，因此可以将它们合并为一个状态。

设一个二进制集合 `mask` 表示已经到达安全岛的幸存者：

- `mask` 的第 $i$ 位为 $1$，表示第 $i$ 名幸存者已经在安全岛；
- `mask` 的第 $i$ 位为 $0$，表示第 $i$ 名幸存者仍在城市港口。

除了幸存者所在位置外，还需要记录船的位置。因此，一个完整状态由以下两部分组成：

- `mask`；
- `side`，其中 $0$ 表示船在城市港口，$1$ 表示船在安全岛。

初始状态为：

- 没有幸存者到达安全岛，即 `mask = 0`；
- 船在城市港口，即 `side = 0`。

目标状态为：

- 所有幸存者到达安全岛，即 `mask = 2^n - 1`；
- 船在安全岛，即 `side = 1`。

每次航行的代价都相同，均为 $1$ 次，因此状态之间构成一张无权图。使用 $\texttt{BFS}$ 按照航行次数递增的顺序搜索，可以保证第一次到达目标状态时使用的航行次数最少。

# 解题思路

首先使用二进制状态枚举所有幸存者集合。集合的总数为：

$$
2^n
$$

对于每个非空集合，预处理以下信息：

- 集合中的幸存者人数；
- 集合中的幸存者总重量；
- 集合是否满足人数不超过 $k$ 且总重量不超过 $W$。

集合 `mask` 的最低位可以拆出一个幸存者，设该位置对应的幸存者编号为 $i$，去除该最低位后得到 `prevMask`，则有：

$$
\textit{weightSum}[\textit{mask}] = \textit{weightSum}[\textit{prevMask}] + w_i
$$

$$
\textit{personCount}[\textit{mask}] = \textit{personCount}[\textit{prevMask}] + 1
$$

这样可以在常数时间内由子集信息计算当前集合的信息。

随后建立状态距离数组：

$$
\textit{distance}[\textit{side}][\textit{mask}]
$$

它表示到达对应状态所需的最少航行次数，初始值为 $-1$，表示状态尚未访问。

当船在城市港口时，当前位于城市港口的幸存者集合为：

$$
\textit{available} = \textit{fullMask} \mathbin{\hat{~}} \textit{mask}
$$

从 `available` 的所有非空子集中枚举本次前往安全岛的人员集合 `group`。如果 `group` 合法，则转移为：

$$
\textit{nextMask} = \textit{mask} \mathbin{|} \textit{group}
$$

船的位置变为安全岛。

当船在安全岛时，从当前已经在安全岛的集合 `mask` 的所有非空子集中枚举返回城市港口的人员集合 `group`。如果 `group` 合法，则转移为：

$$
\textit{nextMask} = \textit{mask} \mathbin{\hat{~}} \textit{group}
$$

船的位置变为城市港口。

子集枚举使用以下形式：

```cpp
for (int group = available; group; group = (group - 1) & available)
```

该方法可以枚举 `available` 的所有非空子集。返程时将 `available` 换成当前的 `mask`，即可枚举所有可能返回的人员集合。

如果在搜索过程中到达 `mask = 2^n - 1` 且船位于安全岛，则立即返回当前距离。由于 $\texttt{BFS}$ 按距离从小到大扩展状态，该距离就是最少航行次数。如果搜索结束仍未到达目标状态，则输出 $-1$。

预处理所有子集需要：

$$
O(2^n)
$$

状态搜索过程中，所有状态与子集转移的总数量为：

$$
O(3^n)
$$

因此总时间复杂度为：

$$
O(3^n)
$$

距离数组、子集信息数组和队列所需的空间复杂度为：

$$
O(2^n)
$$

# 代码实现

```cpp
// Crossing the River
// UVa ID: 12922
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.770s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int solveCase(int n, int limit, int capacity, const vector<int>& weight) {
    int total = 1 << n, fullMask = total - 1;
    vector<int> sum(total, 0), count(total, 0);
    vector<char> valid(total, 0);
    valid[0] = 0;
    for (int mask = 1; mask < total; mask++) {
        int lowBit = mask & -mask, index = __builtin_ctz(lowBit), prevMask = mask ^ lowBit;
        sum[mask] = sum[prevMask] + weight[index];
        count[mask] = count[prevMask] + 1;
        if (count[mask] <= capacity && sum[mask] <= limit)
            valid[mask] = 1;
    }
    vector<vector<int>> distance(2, vector<int>(total, -1));
    queue<pair<int, int>> bfs;
    distance[0][0] = 0;
    bfs.push({0, 0});
    while (!bfs.empty()) {
        int side = bfs.front().first, mask = bfs.front().second;
        bfs.pop();
        int currentDistance = distance[side][mask];
        if (side == 0) {
            int available = fullMask ^ mask;
            for (int group = available; group; group = (group - 1) & available) {
                if (!valid[group])
                    continue;
                int nextMask = mask | group;
                if (distance[1][nextMask] != -1)
                    continue;
                distance[1][nextMask] = currentDistance + 1;
                if (nextMask == fullMask)
                    return distance[1][nextMask];
                bfs.push({1, nextMask});
            }
        } else {
            for (int group = mask; group; group = (group - 1) & mask) {
                if (!valid[group])
                    continue;
                int nextMask = mask ^ group;
                if (distance[0][nextMask] != -1)
                    continue;
                distance[0][nextMask] = currentDistance + 1;
                bfs.push({0, nextMask});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, limit, capacity;
    while (cin >> n >> limit >> capacity) {
        vector<int> weight(n);
        for (int i = 0; i < n; i++)
            cin >> weight[i];
        cout << solveCase(n, limit, capacity, weight) << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是使用二进制状态压缩表示已经到达安全岛的幸存者集合，并额外记录船所在的位置。

关键技巧如下：

- 使用位掩码表示幸存者集合；
- 预处理每个子集的人数、总重量和合法性；
- 使用子集枚举快速枚举一次航行可能选择的所有人员；
- 使用 $\texttt{BFS}$ 求无权状态图中的最短路径；
- 将船的位置加入状态，避免混淆去程和返程。

由于 $n \le 16$，状态数量最多为 $2 \times 2^n$，该方法能够在限制范围内高效完成计算。
