
> **摘要**：本题给出 $n$ 架飞机，每架飞机有两个可选降落时刻，要求为每架飞机选定一个时刻，使排序后相邻降落时刻之差的最小值（安全间隔）最大。文章先说明"相邻间隔约束"与"任意两架飞机间隔约束"等价，从而把最大化问题转化为对给定间隔 $g$ 的可行性判定；再利用每架飞机只有两个选项的特点，把成对冲突组合转化为 $\texttt{2-SAT}$ 子句，用蕴含图与 $\texttt{Tarjan}$ 强连通分量判断可行性。由于可行性具有单调性，最终通过二分答案求出最大安全间隔，单组数据时间复杂度为 $O(n^2\log(T+2))$。

 # 题目描述

某机场只有一条跑道，共有 $n$ 架飞机等待降落。每架飞机有两个可选的降落时刻：提前降落时刻和延后降落时刻。飞机直接降落时使用提前降落时刻，执行规定的等待航线后使用延后降落时刻，每架飞机必须且只能选择其中一个时刻降落。

将所有飞机按照实际降落时刻排序后，相邻两架飞机降落时刻之差的最小值称为安全间隔。要求为每架飞机选择降落时刻，使安全间隔最大，并输出这个最大值。

# 输入格式

输入包含多组测试数据，读取至文件结束。

每组测试数据的首行包含一个整数 $n$，表示飞机数量，满足 $2 \le n \le 2000$。接下来 $n$ 行，每行包含两个整数，分别表示一架飞机的提前降落时刻和延后降落时刻。所有时刻 $t$ 均满足 $0 \le t \le 10^7$。

# 输出格式

对于每组测试数据，输出一行，包含一个整数，表示最大的安全间隔。

# 样例输入

```text
10
44 156
153 182
48 109
160 201
55 186
54 207
55 165
17 58
132 160
87 197
```

# 样例输出

```text
10
```

# 题目分析

设第 $i$ 架飞机的提前降落时刻为 $e_i$，延后降落时刻为 $l_i$，最终选定的降落时刻为 $t_i$。题目要求每个 $t_i$ 都取自集合 $\{e_i,l_i\}$，并最大化排序后相邻降落时刻之差的最小值。直接枚举所有飞机的选择共有 $2^n$ 种方案，无法满足数据规模，因此需要利用每架飞机只有两个选项这一特点，将最优化问题转化为可行性判定问题。

给定一个非负整数 $g$，考虑是否存在一种安排，使安全间隔至少为 $g$。虽然题目只约束排序后相邻的飞机，但这个条件与任意两架不同飞机的降落时刻之差至少为 $g$ 等价。设排序后的降落时刻为 $b_1,b_2,\ldots,b_n$，若所有相邻时刻之差都至少为 $g$，则对任意 $p<q$，都有
$$
b_q-b_p=\sum_{r=p}^{q-1}(b_{r+1}-b_r)\ge(q-p)g\ge g.
$$
反过来，任意两架飞机都满足间隔要求时，相邻飞机自然也满足要求。因此，判定时只需枚举每一对飞机，禁止其中时间差小于 $g$ 的选项组合，无须枚举或预先确定降落顺序。

为第 $i$ 架飞机设置布尔变量 $x_i$，其中 $x_i$ 为真表示选择提前降落，$x_i$ 为假表示选择延后降落。任意两架飞机共有 $4$ 种选项组合，每种不合法组合都能转化为一个包含两个文字的析取子句。例如，当 $|e_i-e_j|<g$ 时，两架飞机不能同时提前降落，对应约束为 $\neg x_i\lor\neg x_j$。所有约束合取后构成一个 $\texttt{2-SAT}$ 问题，可以通过蕴含图和强连通分量判断是否存在合法安排。

可行性还具有单调性：若安全间隔 $g$ 可行，则所有满足 $0\le g'\le g$ 的间隔都可行，因为原安排仍然满足要求；若 $g$ 不可行，则所有大于 $g$ 的间隔都不可行。因此，所有可行间隔构成连续的整数前缀，可以通过二分查找求出其中的最大值。

# 解题思路

首先确定二分范围。设所有输入时刻中的最大值为 $T$。由于降落时刻都处于区间 $[0,T]$ 内，任意两次降落的时间差都不超过 $T$，因此答案位于 $[0,T]$。安全间隔 $0$ 始终可行，保证二分查找存在合法答案。

对于当前需要判定的间隔 $g$，建立包含 $2n$ 个顶点的蕴含图。按照代码中的下标约定，飞机下标从 $0$ 开始，顶点 $2i$ 表示文字 $x_i$，顶点 $2i+1$ 表示文字 $\neg x_i$。同一架飞机对应的两个顶点互为相反文字，因此顶点编号与 $1$ 按位异或即可得到其相反文字对应的编号。对于任意子句 $a\lor b$，分别建立蕴含边 $\neg a\Rightarrow b$ 和 $\neg b\Rightarrow a$，将逻辑约束转化为图上的可达关系。

枚举所有满足 $i<j$ 的飞机对，按照下表检查全部选项组合。只有对应时间差严格小于 $g$ 时才建立约束，时间差恰好等于 $g$ 的组合满足要求。

| 冲突组合 | 冲突条件 | 对应子句 | 建立的蕴含关系 |
| --- | --- | --- | --- |
| 两架飞机均提前降落 | $\lvert e_i-e_j\rvert<g$ | $\neg x_i\lor\neg x_j$ | $x_i\Rightarrow\neg x_j$，$x_j\Rightarrow\neg x_i$ |
| 飞机 $i$ 提前、飞机 $j$ 延后 | $\lvert e_i-l_j\rvert<g$ | $\neg x_i\lor x_j$ | $x_i\Rightarrow x_j$，$\neg x_j\Rightarrow\neg x_i$ |
| 两架飞机均延后降落 | $\lvert l_i-l_j\rvert<g$ | $x_i\lor x_j$ | $\neg x_i\Rightarrow x_j$，$\neg x_j\Rightarrow x_i$ |
| 飞机 $i$ 延后、飞机 $j$ 提前 | $\lvert l_i-e_j\rvert<g$ | $x_i\lor\neg x_j$ | $\neg x_i\Rightarrow\neg x_j$，$x_j\Rightarrow x_i$ |

若某一对飞机的 $4$ 种组合全部冲突，则无论其他飞机如何安排，这两架飞机都无法同时满足要求，可以立即判定当前间隔不可行。代码使用变量 $k$ 统计当前飞机对的冲突组合数量，并在 $k=4$ 时提前结束判定。

建图完成后，使用 $\texttt{Tarjan}$ 算法求出全部强连通分量。数组 $\textit{dfn}$ 记录顶点的访问次序，数组 $\textit{low}$ 维护搜索过程中的追溯信息，数组 $\textit{scc}$ 记录每个顶点所属的强连通分量编号。尚未访问的顶点满足 $\textit{dfn}[u]=0$，已经访问但尚未归入强连通分量的顶点满足 $\textit{scc}[u]=0$，代码据此识别仍在栈中的顶点。当 $\textit{dfn}[u]=\textit{low}[u]$ 时，从栈顶依次弹出顶点，直到弹出 $u$，这些顶点构成一个强连通分量。

$\texttt{2-SAT}$ 的可满足性判据为：对每架飞机，其两个相反文字不能属于同一个强连通分量，即
$$
\textit{scc}[2i]\ne\textit{scc}[2i+1],\qquad 0\le i<n.
$$
如果两个相反文字属于同一强连通分量，则它们能够相互推出。选择提前降落会推出必须延后降落，选择延后降落又会推出必须提前降落，从而产生矛盾。反之，当所有变量的两个相反文字都处于不同强连通分量时，将每个强连通分量缩成一个顶点后得到有向无环图，根据其拓扑顺序可以为互为相反的分量安排一致的真假取值，满足全部蕴含关系。这正是 $\texttt{2-SAT}$ 判定的充分必要条件。

上述判定与原问题完全对应。任何安全间隔至少为 $g$ 的安排都不会选中冲突组合，因此满足全部子句；任何满足全部子句的赋值都排除了所有时间差小于 $g$ 的飞机组合，因此任意两架飞机的降落间隔都至少为 $g$，排序后的相邻飞机也满足要求。由此，判定函数准确判断当前间隔是否可行。

二分查找使用闭区间 $[\textit{low},\textit{high}]$。每次取中点作为待判定间隔；若可行，就将左边界移动到中点加 $1$，继续寻找更大的答案；若不可行，就将右边界移动到中点减 $1$。循环结束时，$\textit{low}=\textit{high}+1$，其中 $\textit{high}$ 就是最大可行间隔。原代码输出 $(\textit{low}+\textit{high})/2$，由于答案非负且整数除法舍去小数部分，该表达式同样得到 $\textit{high}$。

每次判定枚举 $\binom{n}{2}$ 对飞机，每对飞机最多建立 $8$ 条边，因此建图时间为 $O(n^2)$，图的顶点数为 $O(n)$，边数为 $O(n^2)$。$\texttt{Tarjan}$ 算法的时间复杂度为 $O(n^2)$，单次判定总时间复杂度为 $O(n^2)$。二分判定次数为 $O(\log(T+2))$，每组数据的总时间复杂度为 $O(n^2\log(T+2))$，空间复杂度为 $O(n^2)$。这里使用 $T+2$ 表述对数项，涵盖 $T=0$ 时仍需进行判定的边界情况。

# 代码实现

下面保留通过代码的原有逻辑与注释，仅去除函数体内的空行。

```cpp
// Now or Later
// UVa ID: 1146
// Verdict: Accepted
// Submission Date: 2018-05-07
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 4096;

int n, time1[MAXV], time2[MAXV];
int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
vector<list<int>> edges(MAXV);
stack<int> s;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 0; u < MAXV; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

bool feasible(int gap)
{
    initialize();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            int k = 0;
            int ii = i * 2, jj = j * 2;
            // Conflict: aircraft i and j both land early.
            // !i OR !j
            if (abs(time1[i] - time1[j]) < gap)
            {
                edges[ii].push_back(jj ^ 1);
                edges[jj].push_back(ii ^ 1);
                k++;
            }
            // Conflict: Aircraft i lands early and j lands later.
            // !i OR j
            if (abs(time1[i] - time2[j]) < gap)
            {
                edges[ii].push_back(jj);
                edges[jj ^ 1].push_back(ii ^ 1);
                k++;
            }
            // Conflict: aircraft i and j both land later.
            // i OR j
            if (abs(time2[i] - time2[j]) < gap)
            {
                edges[ii ^ 1].push_back(jj);
                edges[jj ^ 1].push_back(ii);
                k++;
            }
            // Conflict: aircraft i lands later and j lands early.
            // i OR !j
            if (abs(time2[i] - time1[j]) < gap)
            {
                edges[ii ^ 1].push_back(jj ^ 1);
                edges[jj].push_back(ii);
                k++;
            }
            if (k == 4) return false;
        }
    for (int i = 0; i < 2 * n; i++)
            if (!dfn[i])
                tarjan(i);
    for (int i = 0; i < 2 * n; i += 2)
        if (scc[i] == scc[i ^ 1])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n)
    {
        int maxTime = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> time1[i] >> time2[i];
            maxTime = max(maxTime, max(time1[i], time2[i]));
        }
        int low = 0, high = maxTime, gap;
        while (low <= high)
        {
            gap = (low + high) / 2;
            if (feasible(gap)) low = gap + 1;
            else high = gap - 1;
        }
        cout << (low + high) / 2 << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是将最大化安全间隔转化为具有单调性的可行性判定，再利用每架飞机只有两个选项的特点，把成对冲突表示为 $\texttt{2-SAT}$ 子句。相邻间隔约束与任意两架飞机之间的间隔约束等价，使建模不再依赖降落顺序；蕴含图上的强连通分量判据则将全局选择的一致性转化为图论问题。掌握“二分答案、枚举冲突组合、建立蕴含关系、判断相反文字是否同属强连通分量”这一过程，就能处理同类具有双选项和成对限制的最优化问题。
