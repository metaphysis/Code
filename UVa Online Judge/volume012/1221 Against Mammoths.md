
> **摘要**：本题给定 $H$ 颗人类星球与 $A$ 颗外星星球，双方分别以固定速率生产飞船与猛犸象。需要为每颗外星星球分配一颗不同的人类星球发起进攻，并决定飞船的最早出发年份，使飞船抵达时的数量不少于猛犸象数量。解题分两步：先对每一对星球单独计算最早可获胜的抵达年份，再把「能否在给定年份 $Y$ 内攻占全部外星星球」转化为二分图最大匹配判定；由于 $Y$ 越大可用匹配边只增不减，可对答案二分，总复杂度 $O(HA^2\log V)$，无解时输出 `IMPOSSIBLE`。

# 题目描述

有 $H$ 颗人类星球和 $A$ 颗外星星球。每颗人类星球初始拥有一定数量的飞船，并以固定速率生产飞船；每颗外星星球初始拥有一定数量的猛犸象，也以固定速率生产猛犸象。

每颗外星星球必须由一颗人类星球派出的飞船攻占，且一颗人类星球最多攻打一颗外星星球。一艘飞船从人类星球出发后需要若干年才能抵达目标星球。飞船只能在每年开始时出发，抵达时间也按年初计算。

战斗时，若飞船数量不少于猛犸象数量，人类获胜。求攻占所有外星星球所需的最短时间；如果无法全部攻占，输出 `IMPOSSIBLE`。

# 输入格式

输入包含多组测试数据。每组数据首先给出两个整数 $H$ 和 $A$，分别表示人类星球和外星星球的数量。

接下来一行包含 $H$ 对非负整数，依次表示每颗人类星球的初始飞船数和飞船年产量。再下一行包含 $A$ 对非负整数，依次表示每颗外星星球的初始猛犸象数和猛犸象年产量。

之后有 $H$ 行，每行包含 $A$ 个正整数。第 $i$ 行第 $j$ 个整数表示从第 $i$ 颗人类星球到第 $j$ 颗外星星球所需的旅行年数。

输入以 `0 0` 结束。

# 输出格式

对每组测试数据输出一行：

- 若所有外星星球都能被攻占，输出最早完成攻占的年份；
- 否则输出 `IMPOSSIBLE`。

# 样例输入

```text
2 1
2 3 0 3
2 2
2
2
0 0
```

# 样例输出

```text
6
```

# 题目分析

需要同时决定两件事：每颗外星星球由哪颗人类星球攻打，以及飞船最早何时出发才能获胜。前者是匹配问题，后者可以针对每一对人类星球和外星星球单独计算。

固定一对星球后，若人类星球在第 $t$ 年年初出发，旅行时间为 $d$，那么飞船抵达时的数量为 $n_h+t p_h$；外星星球此时的猛犸象数量为 $n_a+(t+d)p_a$。战斗胜利要求：

$$
n_h+t p_h \ge n_a+(t+d)p_a
$$

这里 $n_h,p_h$ 分别是人类星球的初始飞船数和年产量，$n_a,p_a$ 分别是外星星球的初始猛犸象数和年产量。

对于每一对星球，可以据此求出最早可能的抵达年份。若人类飞船的年产量不高于猛犸象的年产量，双方数量差不会随时间改善，因此只有在第 $0$ 年出发就能取胜时，这对星球才可行。若人类飞船的年产量更高，则可以通过等待积累飞船，求出满足战斗条件的最早出发年份。

接下来，假设给定一个候选完成年份 $Y$。若某对星球的最早抵达年份不晚于 $Y$，就可以把它们之间连一条边。此时问题变成二分图匹配：能否为每颗外星星球匹配到一颗不同的人类星球？由于每颗人类星球至多攻打一颗外星星球，每颗外星星球也只需被攻占一次，完全符合二分图匹配模型。

随着 $Y$ 增大，可用的匹配边只会增加。因此“能否在 $Y$ 年内攻占所有外星星球”具有单调性，可以对 $Y$ 二分答案，并用二分图最大匹配判断可行性。

# 解题思路

先为每对人类星球 $i$ 和外星星球 $j$ 计算最早抵达年份 $\textit{years}[i][j]$。

设人类星球的初始飞船数和年产量为 $H_n,H_m$，外星星球的初始猛犸象数和年产量为 $A_n,A_m$，旅行时间为 $d$。

当 $H_m \le A_m$ 时，等待不会改善双方的数量差。若第 $0$ 年出发仍能获胜，即：

$$
H_n \ge A_n+dA_m
$$

则最早抵达年份为 $d$；否则这对星球永远不可行。

当 $H_m>A_m$ 时，飞船数量相对猛犸象数量每年净增加 $H_m-A_m$。最早出发年份 $t$ 满足：

$$
H_n+tH_m \ge A_n+(t+d)A_m
$$

即：

$$
t \ge \frac{A_n+dA_m-H_n}{H_m-A_m}
$$

出发年份不能小于 $0$，因此取满足条件的最小非负整数 $t$，最早抵达年份为 $t+d$。若右侧分子小于等于 $0$，说明无需等待，$t=0$。

二分候选完成年份 $Y$。在匹配图中，当且仅当 $\textit{years}[i][j]\le Y$ 时，加入人类星球 $i$ 与外星星球 $j$ 之间的边。运行二分图最大匹配，若匹配数等于 $A$，说明可以在 $Y$ 年内攻占所有外星星球。

先用一个足够大的年份检查是否存在完整匹配。如果不存在，则输出 `IMPOSSIBLE`。否则在可行年份范围内二分，找出最小的可行 $Y$。

设人类星球数为 $H$、外星星球数为 $A$，一次增广路匹配的时间复杂度为 $O(HA)$，二分匹配整体最坏为 $O(HA^2)$。二分答案需要 $O(\log V)$ 次匹配检查，其中 $V$ 为搜索的年份范围，因此总时间复杂度为 $O(HA^2\log V)$。存储可行年份矩阵需要 $O(HA)$ 空间。

# 代码实现

```cpp
// Against Mammoths
// UVa ID: 1221
// Verdict: Accepted
// Submission Date: 2018-12-07
// UVa Run Time: 0.330s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Human planets are NOT needed to leave for allien planets at the same time.

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256, INF = 0x3f3f3f3f;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int H, A, Hn[256], Hm[256], An[256], Am[256], years[256][256];

void build(int Y)
{
    memset(g, 0, sizeof(g));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < A; j++)
            g[i][j] = (Y >= years[i][j]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> H >> A)
    {
        if (H == 0) break;
        tx = H, ty = A;
        for (int i = 0; i < H; i++) cin >> Hn[i] >> Hm[i];
        for (int i = 0; i < A; i++) cin >> An[i] >> Am[i];

        int year;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < A; j++)
            {
                cin >> year;
                if (Hm[i] <= Am[j])
                    years[i][j] =
                        (Hn[i] >= An[j] + year * Am[j]) ? year : INF;
                else
                    years[i][j] = year +
                        (An[j] - Hn[i] + year * Am[j]
                         + (Hm[i] - Am[j]) - 1)
                        / (Hm[i] - Am[j]);
            }

        int lowY = 0, highY = INF;
        build(highY);
        if (hungarian() < A)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        while (lowY <= highY)
        {
            int Y = (lowY + highY) >> 1;
            build(Y);
            if (hungarian() == A)
                highY = Y - 1;
            else
                lowY = Y + 1;
        }
        cout << lowY << '\n';
    }

    return 0;
}
```

# 总结

本题先对每一对人类星球和外星星球计算最早可获胜的抵达时间，再将“在给定年份内是否能攻占所有外星星球”转化为二分图最大匹配。由于候选年份越大，可用匹配边只增不减，可以通过二分答案找到最短完成时间；若最大年份下仍无法匹配全部外星星球，则无解。
