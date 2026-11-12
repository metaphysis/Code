
> **摘要**：在河流两岸各有一列城市，每座城市带有操作系统类型与贸易值，要求修建互不交叉、且两端操作系统相同的桥梁，使经济价值总和最大，并在价值最大时使桥梁数量最少。文章将不交叉约束转化为两岸配对顺序一致的序列限制，采用二维前缀动态规划，把「最大经济价值 + 最少桥梁数」作为一个二元状态整体维护，统一按「价值优先、桥数次优」的比较规则转移，并给出自底向上递推与自顶向下记忆化搜索两种实现，时间复杂度为 $O(nm)$。

 # 题目描述

一条河流的北岸和南岸分布着若干城市，两岸的城市均按照从左到右的顺序给出。每座城市都有城市名称、操作系统类型和贸易值。国王计划在两岸之间修建桥梁，每座桥连接北岸的一座城市与南岸的一座城市，连接的两座城市必须使用相同的操作系统，且所有桥梁之间不能交叉。

一座桥的经济价值等于两端城市的贸易值之和。要求在满足建桥限制的前提下，使所有桥梁的经济价值总和最大；在经济价值总和达到最大值的所有方案中，选择桥梁数量最少的方案。输出最大经济价值总和以及对应的最少桥梁数量。

# 输入格式

第一行包含一个整数 $T$，表示测试用例数量。

每组测试用例首先输入一个整数 $n$，表示北岸城市数量，满足 $0 \le n \le 1000$。接下来 $n$ 行按照从左到右的顺序描述北岸城市，每行依次包含城市名称、操作系统类型和贸易值，各字段之间用空格分隔。

随后输入一个整数 $m$，表示南岸城市数量，满足 $0 \le m \le 1000$。接下来 $m$ 行采用相同格式，按照从左到右的顺序描述南岸城市。

城市名称和操作系统类型均为长度不超过 $10$ 的字符串，贸易值为不超过 $10^6$ 的非负整数。

# 输出格式

对于每组测试用例，输出一行，包含最大经济价值总和以及达到该价值所需的最少桥梁数量，两个整数之间用一个空格分隔。

# 样例输入

```text
1
3
mordor Vista 1000000
xanadu Mac 1000
shangrila OS2 400
4
atlantis Mac 5000
hell Vista 1200
rivendell OS2 100
appleTree Mac 50
```

# 样例输出

```text
1002250 2
```

# 题目分析

本题的核心限制是桥梁不能交叉。设北岸城市依次为 $a_1,a_2,\ldots,a_n$，南岸城市依次为 $b_1,b_2,\ldots,b_m$。如果两座桥分别连接 $(a_i,b_j)$ 和 $(a_k,b_l)$，且 $i<k$，那么合法的连接顺序必须满足 $j<l$。因此，所有被选中的城市配对在两岸都保持从左到右的顺序，问题转化为：从两个城市序列中选择若干组顺序一致、操作系统相同的配对，使配对权值之和最大，并在权值相同时使配对数量最少。这与最长公共子序列的状态划分一致，但匹配收益由两座城市的贸易值之和决定，同时还需要维护桥梁数量这一附加目标。

两个优化目标具有明确的优先级，必须先比较经济价值，再比较桥梁数量。将一个方案表示为 $(v,c)$，其中 $v$ 为经济价值总和，$c$ 为桥梁数量。方案 $(v_1,c_1)$ 优于方案 $(v_2,c_2)$ 的条件为
$$
v_1>v_2
\quad\text{或}\quad
\bigl(v_1=v_2\ \land\ c_1<c_2\bigr).
$$
每次状态更新都必须按照这一标准同时维护两个量，保证桥梁数量始终对应当前的最大经济价值。由于贸易值允许为 $0$，新增一座桥的收益也允许为 $0$；此时只有桥梁数量增加，方案不会变优，因此不能在操作系统相同时直接决定建桥，必须将建桥方案与跳过城市的方案进行比较。

样例中，连接北岸的 $\texttt{mordor}$ 与南岸的 $\texttt{hell}$，得到经济价值 $1000000+1200=1001200$；连接北岸的 $\texttt{xanadu}$ 与南岸的 $\texttt{appleTree}$，得到经济价值 $1000+50=1050$。这两座桥的端点顺序一致，总经济价值为 $1001200+1050=1002250$，对应桥梁数量为 $2$。

# 解题思路

设 $V[i][j]$ 表示仅考虑北岸前 $i$ 座城市和南岸前 $j$ 座城市时的最大经济价值总和，$C[i][j]$ 表示达到该最大价值所需的最少桥梁数量。将两者合并记为状态 $F[i][j]=(V[i][j],C[i][j])$。设北岸第 $i$ 座城市的操作系统和贸易值分别为 $s_i$、$p_i$，南岸第 $j$ 座城市的操作系统和贸易值分别为 $t_j$、$q_j$。定义 $\operatorname{best}$ 为按照“价值优先最大、桥数其次最少”的标准选择最优状态的运算。

当任意一岸没有城市时，无法修建桥梁，因此边界状态为

$$
F[i][0]=F[0][j]=(0,0).
$$

对于一般状态，跳过北岸第 $i$ 座城市得到 $F[i-1][j]$，跳过南岸第 $j$ 座城市得到 $F[i][j-1]$。两座城市都跳过的方案由 $F[i-1][j-1]$ 表示。给出的通过代码将这三个状态都纳入比较，其中同时跳过两座城市的候选已经包含在前两个候选所覆盖的方案范围内，保留它不影响正确性。首先得到

$$
F[i][j]=
\operatorname{best}
\bigl(
F[i-1][j],\,
F[i][j-1],\,
F[i-1][j-1]
\bigr).
$$
如果 $s_i=t_j$，还存在连接当前两座城市的方案。由于桥梁不能交叉，其余桥梁必须全部位于两岸当前城市之前，因此该方案必须从 $F[i-1][j-1]$ 转移而来，对应候选状态为
$$
\left(
V[i-1][j-1]+p_i+q_j,\,
C[i-1][j-1]+1
\right).
$$
将这一候选与已有状态继续比较，即完成当前状态的计算。如果 $s_i\ne t_j$，当前两座城市之间不能建桥，仅保留跳过城市所得的最优结果。最终答案为 $V[n][m]$ 和 $C[n][m]$。

上述转移覆盖了所有合法方案。在任意一个最优方案中，如果北岸第 $i$ 座城市或南岸第 $j$ 座城市没有参与建桥，该方案就属于相应的跳过状态；如果两座城市都参与建桥，却分别连接其他城市，那么连接北岸第 $i$ 座城市的桥与连接南岸第 $j$ 座城市的桥必然交叉，因此两座城市必须互相连接，此时其余部分恰好属于前缀状态 $F[i-1][j-1]$。各类候选既覆盖全部合法方案，又不会引入交叉桥梁。进一步地，对于同一个前缀状态，较大的经济价值在添加相同后续桥梁后仍然更优；经济价值相同时，较少的桥梁数量在添加相同后续桥梁后仍然更优。因此，每个状态仅保留一个最优二元结果就足以完成后续转移。

代码同时提供自底向上递推和自顶向下记忆化搜索两种实现，默认通过 $\texttt{useBottomUp}$ 选择记忆化搜索。数组 $\texttt{maxValue}$ 对应 $V$，数组 $\texttt{minBridge}$ 对应 $C$；前者初始化为 $-1$，用于标记尚未计算的状态，后者初始化为常量 $\texttt{INF}$。由于实际经济价值非负，$-1$ 与所有合法结果严格区分。函数 $\texttt{update}$ 负责比较并合并已经计算完成的状态，函数 $\texttt{dp}$ 负责递归计算所需前缀。每次递归都会减小至少一个前缀长度，因此递归最终到达边界状态。

共有 $(n+1)(m+1)$ 个状态，每个状态只进行常数次转移，操作系统字符串长度上界为 $10$，因此每组测试用例的时间复杂度为 $O((n+1)(m+1))$，两岸均非空时写作 $O(nm)$。状态数组的空间复杂度为 $O((n+1)(m+1))$，记忆化搜索额外使用 $O(n+m)$ 的递归栈空间，总空间复杂度仍为 $O((n+1)(m+1))$。桥梁数量最多为 $\min(n,m)$，每座桥的经济价值最多为 $2\times10^6$，因此总经济价值最多为 $2\times10^9$，处于代码所用的有符号整数范围内。

# 代码实现

```cpp
// The Bridges of Kölsberg
// UVa ID: 1172
// Verdict: Accepted
// Submission Date: 2018-09-10
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool useBottomUp = false;

const int INF = 0x3f3f3f3f;

struct city
{
    string cityName, osType;
    int tradeValue;
} north[1001], south[1001];

int maxValue[1001][1001], minBridge[1001][1001];

void update(int i, int j, int ii, int jj)
{
    if (maxValue[i][j] < maxValue[ii][jj])
    {
        maxValue[i][j] = maxValue[ii][jj];
        minBridge[i][j] = minBridge[ii][jj];
    }
    else if (maxValue[i][j] == maxValue[ii][jj])
    {
        if (minBridge[i][j] > minBridge[ii][jj])
            minBridge[i][j] = minBridge[ii][jj];
    }
}

void dp(int i, int j)
{
    if (i == 0 || j == 0)
    {
        maxValue[i][j] = minBridge[i][j] = 0;
        return;
    }
    if (maxValue[i - 1][j] == -1) dp(i - 1, j);
    if (maxValue[i][j - 1] == -1) dp(i, j - 1);
    if (maxValue[i - 1][j - 1] == -1) dp(i - 1, j - 1);
    update(i, j, i - 1, j);
    update(i, j, i, j - 1);
    update(i, j, i - 1, j - 1);
    if (north[i].osType == south[j].osType)
    {
        int new_value = maxValue[i - 1][j - 1] + north[i].tradeValue + south[j].tradeValue;
        int new_bridge = minBridge[i - 1][j - 1] + 1;
        if (maxValue[i][j] < new_value)
        {
            maxValue[i][j] = new_value;
            minBridge[i][j] = new_bridge;
        }
        else if (maxValue[i][j] == new_value)
        {
            if (minBridge[i][j] > new_bridge)
                minBridge[i][j] = new_bridge;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, n1, n2;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n1;
        for (int i = 1; i <= n1; i++)
            cin >> north[i].cityName >> north[i].osType >> north[i].tradeValue;
        cin >> n2;
        for (int i = 1; i <= n2; i++)
            cin >> south[i].cityName >> south[i].osType >> south[i].tradeValue;
        // initialize
        for (int i = 0; i <= n1; i++)
            for (int j = 0; j <= n2; j++)
            {
                maxValue[i][j] = -1;
                minBridge[i][j] = INF;
            }
        // bottom-up
        if (useBottomUp)
        {
            for (int i = 0; i <= n1; i++)
            {
                maxValue[i][0] = 0;
                minBridge[i][0] = 0;
            }
            for (int i = 0; i <= n2; i++)
            {
                maxValue[0][i] = 0;
                minBridge[0][i] = 0;
            }
            for (int i = 1; i <= n1; i++)
                for (int j = 1; j <= n2; j++)
                {
                    update(i, j, i - 1, j - 1);
                    update(i, j, i - 1, j);
                    update(i, j, i, j - 1);
                    if (north[i].osType == south[j].osType)
                    {
                        int new_value = maxValue[i - 1][j - 1] + north[i].tradeValue + south[j].tradeValue;
                        int new_bridge = minBridge[i - 1][j - 1] + 1;
                        if (maxValue[i][j] < new_value)
                        {
                            maxValue[i][j] = new_value;
                            minBridge[i][j] = new_bridge;
                        }
                        else if (maxValue[i][j] == new_value)
                        {
                            if (minBridge[i][j] > new_bridge)
                                minBridge[i][j] = new_bridge;
                        }
                    }
                }
        }
        // top-down
        else
            dp(n1, n2);
        cout << maxValue[n1][n2] << ' ' << minBridge[n1][n2] << '\n';
    }
    return 0;
}
```

# 总结

本题将桥梁不交叉的几何限制转化为两岸城市配对顺序一致的序列限制，再通过二维前缀动态规划处理跳过城市与匹配城市的选择。关键技巧是把最大经济价值和最少桥梁数量作为一个整体维护，并在所有转移中统一使用价值优先、桥数次优的比较规则。对于匹配收益为零、存在多种等价方案以及某一岸没有城市的情况，这一状态设计和边界初始化都能直接给出正确结果。
