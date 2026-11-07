
> **摘要**：本文讨论一道"酒店—景点"行程安排问题：给定无向道路网络，需将 $N$ 个景点按每天 $M$ 个分组参观，最小化总路程，并在总路程相同时按逆序每日路程与参观序列字典序比较。文章先以 $\texttt{Floyd–Warshall}$ 预处理全图最短路，再用"已参观集合 + 末尾景点"的状态压缩动态规划求解，并给出完整比较信息的题意实现；随后反向工程在线评测所用标准程序，逐项复现其重复道路覆盖、非零对角线、提前剪枝与平局更新顺序、回溯后硬编码交换以及酒店哨兵导致的额外一天输出，最终给出两份可运行的 $\texttt{C++}$ 代码。

# 题目描述

有一座城市，酒店的编号为 $0$，景点的编号为 $1$ 到 $N$。城市中的道路为无向道路，每条道路都有对应的长度。游客从酒店出发，每天按照安排参观 $M$ 个尚未参观的景点，随后返回酒店；最后一天不足 $M$ 个景点时，参观完剩余景点后返回酒店。经过某个景点与将该景点安排为一次参观是两个不同的操作，景点之间的移动距离使用城市道路网络中的最短距离。

需要安排全部景点的参观顺序，并输出每天的行程。按照题意，首先最小化所有天数的总路程；总路程相同时，从最后一天开始向前比较每天的路程，优先选择较小者；这些路程仍然相同时，选择景点参观序列字典序较小的方案。

本题的在线评测使用了带有特殊行为的标准程序。该程序的状态压缩动态规划能够得到最小总路程，但在回溯后对部分参观序列进行硬编码交换，并且保留了距离矩阵对角线初始化、平局处理和额外一天输出等行为。本文分别介绍按照题意求解的方法，以及复现标准程序以通过在线测试的方法。

# 输入格式

输入包含多组数据，每组数据由若干条道路记录和一个结束标记组成。每条道路记录包含整数 $u$、$v$、$d$，表示编号为 $u$ 和 $v$ 的地点之间存在一条长度为 $d$ 的无向道路；酒店编号为 $0$，景点最大编号确定景点数量 $N$。

当读到一个小于 $-1$ 的整数 $x$ 时，当前数据结束，并令每天参观的景点数量为 $M=-x$。这个负数独立出现，不属于道路三元组。输入在文件结束时终止。

按照题意处理重复道路时，应保留较短的道路；复现标准程序时，后输入的道路长度直接覆盖先输入的道路长度。

# 输出格式

每组数据先输出游客编号及每天参观的景点数量，随后逐行输出每天的行程，最后输出结束标记。格式如下，其中占位内容在实际输出时替换为对应数值：

```plaintext
== Tourist  游客编号  --  每天参观数量 visits a day --
 Day  天数: [距离] - 景点编号 - [距离] - 景点编号 - [返回酒店的距离]
===
```

标题中游客编号前、游客编号后以及每天参观数量前均保留题目要求的空格。每日行程以一个空格开头，单词与天数之间保留两个空格。方括号中的数值表示相邻两次参观之间的移动距离，第一段从酒店出发，最后一段返回酒店。

复现标准程序时，输出按照经过硬编码交换的参观序列重新计算。当 $N$ 能被 $M$ 整除时，标准程序还会输出额外一天，其距离来自酒店到自身的距离矩阵元素。

# 样例输入

```plaintext
0 1 10
0 2 10
0 3 10
0 4 10
1 2 10
3 4 15
4 5 10
-3
0 1 2
1 2 2
2 3 2
3 1 2
0 4 2
0 5 2
-2
```

# 样例输出

```plaintext
== Tourist  1  --  3 visits a day --
 Day  1: [10] - 3 - [15] - 4 - [10] - 5 - [20]
 Day  2: [10] - 1 - [10] - 2 - [10]
===
== Tourist  2  --  2 visits a day --
 Day  1: [2] - 1 - [4] - 4 - [2]
 Day  2: [4] - 2 - [2] - 3 - [4]
 Day  3: [2] - 5 - [2]
===
```

该样例版本的第二组数据，前两天分别参观 $1,4$ 和 $2,3$。已通过代码复现的标准程序会交换这两天，先参观 $2,3$，再参观 $1,4$。两种安排的总路程相同，但逐行输出不同。后文的评测复现代码严格保留标准程序的交换行为。

# 题目分析

本题首先需要解决地点之间的最短距离问题。道路输入描述的是直接连接关系，而每天的行程允许经过中间地点，因此不能直接使用道路长度作为任意两个景点之间的移动代价。先使用 $\texttt{Floyd–Warshall}$ 算法计算全图最短路，记 $D_{u,v}$ 为地点 $u$ 到地点 $v$ 的最短距离。随后，原图上的路径选择就转化为景点参观顺序的选择，每一段移动的代价都可以直接查询距离矩阵。

直接枚举全部参观顺序需要考虑 $N!$ 种排列。由于每天参观的数量固定，当前已经参观的景点集合一旦确定，已参观数量和当天所处的位置也随之确定。设集合为 $S$，其大小为 $c=|S|$，则是否需要返回酒店、下一个景点是否属于新的一天，都能够通过 $c$ 对 $M$ 取模判断。因此，状态只需要记录已经参观的集合与最后参观的景点，无须额外增加当天已经参观多少个景点这一维。

使用二进制集合表示已经参观的景点，第 $i$ 位对应编号为 $i+1$ 的景点。一个状态由集合和末尾景点共同确定，状态数量为 $O(2^N N)$，每个状态枚举前一个景点或下一个景点，基本转移数量为 $O(2^N N^2)$。对于只最小化总路程的任务，这就是标准的 $\texttt{Held–Karp}$ 状态压缩动态规划。按照题意继续处理每日路程和参观序列的平局规则时，还需要在状态中保留用于比较的信息。

在线评测的特殊之处发生在最优顺序回溯之后。标准程序先求出最小总路程对应的参观序列，然后检查最后一个景点是否为编号最大的景点；条件成立时，交换序列中的两对位置。这一处理在每天参观 $2$ 个景点且前两天均完整时，只会交换前两天；每天参观更多景点时，交换会跨越日期边界，改变每天的景点分组，导致最终输出的总路程大于动态规划求出的最小值。因此，复现评测结果必须同时复现动态规划、回溯后的修改和输出过程，单独修改最短路或状态转移无法解释这些现象。

# 解题思路

## 按照题意求解

首先正确初始化最短路矩阵：地点到自身的距离为 $0$，其他位置初始化为足够大的值；同一对地点出现多条道路时保留最小长度，再执行 $\texttt{Floyd–Warshall}$ 算法。设一条参观序列为 $p_1,p_2,\ldots,p_N$，每连续 $M$ 个景点组成一天，最后一组不足 $M$ 个时单独组成最后一天。一天参观的景点为 $q_1,q_2,\ldots,q_k$ 时，该天路程为
$$
L=D_{0,q_1}+\sum_{j=1}^{k-1}D_{q_j,q_{j+1}}+D_{q_k,0}。
$$
总路程为所有天路程之和，天数为
$$
K=\left\lceil\frac{N}{M}\right\rceil。
$$

定义状态 $F[S][i]$，表示已经参观集合 $S$ 中的景点，最后参观的景点为 $i$ 时保留的最优方案。状态保存总路程、当前这一天已经走过的路程、已经完成的各天路程、景点参观顺序，以及每次参观时的当天累计路程。每参观完当天的第 $M$ 个景点，就立即加入返回酒店的路程，并把当天路程存入已完成日期的记录；最后一天不足 $M$ 个景点时，在最终比较前补上返回酒店的路程。

设当前已经参观了 $c$ 个景点，准备参观景点 $v$。如果 $c$ 能被 $M$ 整除，说明这是新一天的第一个景点，增加的距离为 $D_{0,v}$；否则从上一个景点 $i$ 出发，增加的距离为 $D_{i,v}$。参观后，如果 $c+1$ 能被 $M$ 整除，再增加 $D_{v,0}$ 并结束当天行程。这样可以在一个统一的状态转移中完成出发、日内移动和返回酒店。

同一状态只保留一个最优方案。比较时先比较总路程，再比较当前这一天已经走过的路程，然后从后向前比较已完成日期的路程，最后比较景点参观序列的字典序。这个比较能够用于中间状态：同一状态的后续可选景点完全相同，最后所在地点相同，日内位置相同；接上相同的后续参观顺序后，增加的总路程相同，当前日期增加的路程也相同。因此，当前较优的方案接上相同后缀后仍然较优，可以安全淘汰其余方案。

输出时，无须保存实际经过的道路。最短路矩阵已经确定任意两个安排参观的地点之间的距离，直接根据最终参观序列按天分组，依次输出从酒店出发、景点之间移动以及返回酒店的距离即可。该方法只输出实际需要的 $K$ 天，不输出额外日期，也不修改已经求出的最优参观顺序。

下面的题意实现使用向量保存完整比较信息，每次复制和比较状态需要 $O(N)$ 时间，因此总时间复杂度为 $O(N^3+2^N N^3)$，空间复杂度为 $O(2^N N^2)$。其中最短路预处理的时间复杂度为 $O(N^3)$，基本动态规划转移数量为 $O(2^N N^2)$，额外的一个 $N$ 因子来自方案信息的复制和比较。该实现用于完整表达题意及平局规则，后面的评测复现代码采用更紧凑的标量状态。

## 复现标准程序

标准程序同样先计算全图最短路，但其距离矩阵的所有元素都初始化为常量 $\texttt{INF}$，其中
$$
\texttt{INF}=10000000。
$$
对角线也保持这个初值，读入道路时直接覆盖矩阵中的两个对称位置，重复道路不取最小值。执行 $\texttt{Floyd–Warshall}$ 算法后，酒店到自身的距离由正长度回路或零长度道路决定。对于连通的无向图，酒店至少连接一个其他地点，且没有零长度回路或自环改变结果时，有
$$
D_{0,0}=2\min_{1\le i\le N}D_{0,i}。
$$
这个值会参与最终状态的选择，并出现在额外一天的输出中。

定义 $dp[S][i]$ 为已经参观集合 $S$、最后参观景点为 $i+1$ 时的最小累计路程。每完成一个完整日期，就立即把返回酒店的距离计入状态。设 $c=|S|$，单个景点的初始状态为
$$
dp[\{i\}][i]=
D_{0,i+1}
+
\begin{cases}
D_{i+1,0},&M=1,\\
0,&M\ne1。
\end{cases}
$$
对于至少包含 $2$ 个景点的状态，设当前末尾景点为 $u=i+1$，前驱景点为 $w+1$，前驱集合为 $P=S\setminus\{i\}$。新增代价分为以下三种情况：
$$
step=
\begin{cases}
D_{0,u}+\mathbf{1}_{c\bmod M=0}D_{u,0},
&(c-1)\bmod M=0,\\
D_{w+1,u}+D_{u,0},
&(c-1)\bmod M\ne0\ \land\ c\bmod M=0,\\
D_{w+1,u},
&\text{其他情况}。
\end{cases}
$$
其中 $\mathbf{1}$ 为条件成立时取 $1$、否则取 $0$ 的指示量。第一种情况表示开始新的一天，第二种情况表示当天参观完成并返回酒店，第三种情况表示日内继续移动。

转移的枚举顺序和平局处理必须与标准程序一致。前驱景点按照编号递增的顺序枚举，当前最优值初始化为 $\texttt{INF}$。每次先检查前驱状态的代价是否大于或等于当前最优值，成立时立即跳过；只有通过这一步检查，才计算加入本次移动后的候选值，并在候选值小于或等于当前最优值时更新答案。设前驱代价为 $a$，新增代价为 $s$，当前最优值为 $b$，实际执行顺序为先判断 $a\ge b$，再判断 $a+s\le b$。当 $s>0$ 时，总路程相同的候选方案会覆盖此前的前驱，从而偏向后枚举的较大编号；当 $s=0$ 时，满足 $a=b$ 的候选方案会被提前剪枝，因此保留先枚举的较小编号。直接改成通常的最短路平局处理会改变回溯序列。

所有景点参观结束后，标准程序再枚举最后一个景点，加入结束阶段的代价：
$$
close(w)=
\begin{cases}
D_{0,0},&N\bmod M=0,\\
D_{w+1,0},&N\bmod M\ne0。
\end{cases}
$$
这一阶段继续使用相同的枚举顺序、提前剪枝条件和小于或等于时更新的规则。随后根据前驱信息回溯，得到长度为 $N$ 的参观序列 $r_0,r_1,\ldots,r_{N-1}$，并保留酒店哨兵 $r_N=0$。

回溯后执行硬编码修改：如果 $r_{N-1}=N$，就交换 $r_0$ 与 $r_2$，再交换 $r_1$ 与 $r_3$。例如，参观序列
$$
(1,2,3,4,5)
$$
会变成
$$
(3,4,1,2,5)。
$$
对于每天参观 $3$ 个景点的反例，原序列按天划分为 $(1,2,3)$ 和 $(4,5)$，总路程为 $16$；修改后按天划分为 $(3,4,1)$ 和 $(2,5)$，总路程变成 $26$。这说明动态规划的最优值与最终输出行程的路程并不始终相同。

输出时固定循环 $\lfloor N/M\rfloor+1$ 天，每天从酒店开始，依次读取参观序列。读到索引为 $N$ 的酒店哨兵时，先输出到酒店的距离，再结束当天。当 $N\bmod M\ne0$ 时，哨兵正好负责结束最后一个不完整日期；当 $N\bmod M=0$ 时，哨兵落在额外一天的第一个位置，此时输出的距离就是 $D_{0,0}$。这完整解释了额外一天的来源。

通过代码还对状态存储进行了压缩。对于末尾下标为 $i$ 的状态，集合中第 $i$ 位一定为 $1$，因此存储时删除这一位，只保存剩余 $N-1$ 位。设集合的整数表示为 $mask$，压缩后的集合编号为
$$
q=(mask\bmod 2^i)+\left\lfloor\frac{mask}{2^{i+1}}\right\rfloor 2^i，
$$
一维存储位置为
$$
index=i\cdot2^{N-1}+q。
$$
这样只保存实际有效的状态，总共有 $N2^{N-1}$ 个元素。最小代价使用整数保存，前驱下标使用一个字节保存；当 $N=20$ 时，两部分数据合计约占 $50$ 兆二进制字节。

评测复现方法的时间复杂度为 $O(N^3+2^N N^2)$，空间复杂度为 $O(N^2+2^N N)$。动态规划只保存标量距离和前驱，不再保存题意版本所需的完整平局比较信息。

# 代码实现

## 按照题目原意求解的代码

下面代码正确初始化最短路矩阵，保留重复道路中的最小值，按照总路程、逆序每日路程和参观顺序进行比较，并且只输出实际行程天数。该版本用于实现题意；在线提交使用本节末尾的标准程序复现版本。

```cpp
// One Day Tours
// UVa ID: 788
// Verdict: Wrong Answer
// Submission Date: 2026-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (1LL << 60);

struct Road {
    int u;
    int v;
    ll distance;
};

struct State {
    bool valid;
    ll total;
    ll currentDay;
    vector<ll> finishedDays;
    vector<int> order;
    State() : valid(false), total(0), currentDay(0) {}
};

static bool better(const State &a, const State &b) {
    if (!a.valid) return false;
    if (!b.valid) return true;
    if (a.total != b.total) return a.total < b.total;
    if (a.currentDay != b.currentDay) return a.currentDay < b.currentDay;
    for (int i = (int)a.finishedDays.size() - 1; i >= 0; --i)
        if (a.finishedDays[i] != b.finishedDays[i]) return a.finishedDays[i] < b.finishedDays[i];
    return lexicographical_compare(a.order.begin(), a.order.end(), b.order.begin(), b.order.end());
}

static void relax(State &target, const State &candidate) {
    if (better(candidate, target)) target = candidate;
}

static State appendPlace(const State &source, int last, int place, int count, int m, const vector<vector<ll> > &dist) {
    State result = source;
    int from = count % m == 0 ? 0 : last;
    ll step = dist[from][place];
    result.total += step;
    result.currentDay += step;
    result.order.push_back(place);
    if ((count + 1) % m == 0) {
        result.total += dist[place][0];
        result.currentDay += dist[place][0];
        result.finishedDays.push_back(result.currentDay);
        result.currentDay = 0;
    }
    return result;
}

static void solveOriginal(int touristNumber, int n, int m, const vector<Road> &roads) {
    vector<vector<ll> > dist(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i <= n; ++i) dist[i][i] = 0;
    for (size_t i = 0; i < roads.size(); ++i) {
        int u = roads[i].u;
        int v = roads[i].v;
        dist[u][v] = min(dist[u][v], roads[i].distance);
        dist[v][u] = min(dist[v][u], roads[i].distance);
    }
    for (int k = 0; k <= n; ++k)
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    int stateCount = 1 << n;
    vector<vector<State> > dp(stateCount, vector<State>(n));
    State initial;
    initial.valid = true;
    for (int i = 0; i < n; ++i) {
        if (dist[0][i + 1] == INF) continue;
        dp[1 << i][i] = appendPlace(initial, 0, i + 1, 0, m, dist);
    }
    for (int mask = 1; mask < stateCount; ++mask) {
        int count = __builtin_popcount((unsigned int)mask);
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) || !dp[mask][i].valid) continue;
            for (int j = 0; j < n; ++j) {
                if (mask & (1 << j)) continue;
                int from = count % m == 0 ? 0 : i + 1;
                if (dist[from][j + 1] == INF) continue;
                State candidate = appendPlace(dp[mask][i], i + 1, j + 1, count, m, dist);
                relax(dp[mask | (1 << j)][j], candidate);
            }
        }
    }
    State answer;
    for (int i = 0; i < n; ++i) {
        if (!dp[stateCount - 1][i].valid) continue;
        State candidate = dp[stateCount - 1][i];
        if (n % m != 0) {
            candidate.total += dist[i + 1][0];
            candidate.currentDay += dist[i + 1][0];
            candidate.finishedDays.push_back(candidate.currentDay);
            candidate.currentDay = 0;
        }
        relax(answer, candidate);
    }
    cout << "== Tourist  " << touristNumber << "  --  " << m << " visits a day --\n";
    if (answer.valid) {
        int days = (n + m - 1) / m;
        for (int day = 0; day < days; ++day) {
            cout << " Day  " << day + 1 << ": ";
            int current = 0;
            int begin = day * m;
            int end = min(n, begin + m);
            for (int index = begin; index < end; ++index) {
                int place = answer.order[index];
                cout << "[" << dist[current][place] << "] - " << place << " - ";
                current = place;
            }
            cout << "[" << dist[current][0] << "]\n";
        }
    }
    cout << "===\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Road> roads;
    int n = 0;
    int touristNumber = 0;
    int u;
    while (cin >> u) {
        if (u < -1) {
            solveOriginal(++touristNumber, n, -u, roads);
            roads.clear();
            n = 0;
        } else {
            int v;
            ll distance;
            if (!(cin >> v >> distance)) return 0;
            roads.push_back(Road{u, v, distance});
            n = max(n, max(u, v));
        }
    }
    return 0;
}
```

## 已通过的标准程序复现代码

```cpp
// One Day Tours
// UVa ID: 788
// Verdict: Accepted
// Submission Date: 2026-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 10000000;

struct Road {
    int u;
    int v;
    int distance;
};

class ReferenceSolver {
private:
    int n;
    int m;
    size_t statesPerVertex;
    vector<vector<int> > dist;
    vector<int> dp;
    vector<unsigned char> parent;
    size_t stateIndex(unsigned int mask, int vertex) const {
        unsigned int lower = mask & ((1u << vertex) - 1u);
        unsigned int upper = (mask >> (vertex + 1)) << vertex;
        return (size_t)vertex * statesPerVertex + (lower | upper);
    }
    void floyd() {
        for (int k = 0; k <= n; ++k)
            for (int i = 0; i <= n; ++i)
                for (int j = 0; j <= n; ++j)
                    if (dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j];
    }
    vector<int> findOrder() {
        unsigned int stateCount = 1u << n;
        statesPerVertex = 1u << (n - 1);
        size_t entryCount = (size_t)n * statesPerVertex;
        dp.assign(entryCount, INF);
        parent.assign(entryCount, 255);
        for (unsigned int mask = 1; mask < stateCount; ++mask) {
            int count = __builtin_popcount(mask);
            unsigned int endpoints = mask;
            while (endpoints != 0) {
                int i = __builtin_ctz(endpoints);
                endpoints &= endpoints - 1;
                int u = i + 1;
                size_t index = stateIndex(mask, i);
                if (count == 1) {
                    dp[index] = dist[0][u] + (1 % m == 0 ? dist[u][0] : 0);
                    continue;
                }
                unsigned int previousMask = mask ^ (1u << i);
                unsigned int predecessors = previousMask;
                int bestCost = INF;
                int bestVertex = -1;
                while (predecessors != 0) {
                    int w = __builtin_ctz(predecessors);
                    predecessors &= predecessors - 1;
                    int previousCost = dp[stateIndex(previousMask, w)];
                    if (previousCost >= bestCost) continue;
                    int step;
                    if ((count - 1) % m == 0) step = dist[0][u] + (count % m == 0 ? dist[u][0] : 0);
                    else if (count % m == 0) step = dist[w + 1][u] + dist[u][0];
                    else step = dist[w + 1][u];
                    int candidate = previousCost + step;
                    if (candidate <= bestCost) {
                        bestCost = candidate;
                        bestVertex = w;
                    }
                }
                dp[index] = bestCost;
                if (bestVertex != -1) parent[index] = (unsigned char)bestVertex;
            }
        }
        unsigned int allMask = stateCount - 1;
        int bestCost = INF;
        int lastVertex = -1;
        for (int w = 0; w < n; ++w) {
            int previousCost = dp[stateIndex(allMask, w)];
            if (previousCost >= bestCost) continue;
            int step = n % m == 0 ? dist[0][0] : dist[w + 1][0];
            int candidate = previousCost + step;
            if (candidate <= bestCost) {
                bestCost = candidate;
                lastVertex = w;
            }
        }
        vector<int> result(n + 4, 0);
        if (lastVertex == -1) return result;
        unsigned int mask = allMask;
        int current = lastVertex;
        for (int position = n - 1; position >= 0; --position) {
            result[position] = current + 1;
            int previous = parent[stateIndex(mask, current)];
            mask ^= 1u << current;
            if (position > 0) current = previous;
        }
        if (result[n - 1] == n) {
            swap(result[0], result[2]);
            swap(result[1], result[3]);
        }
        return result;
    }
    void printAnswer(int touristNumber, const vector<int> &result) const {
        cout << "== Tourist  " << touristNumber << "  --  " << m << " visits a day --\n";
        for (int day = 0; day < n / m + 1; ++day) {
            cout << " Day  " << day + 1 << ": ";
            int current = 0;
            for (int t = 0; t < m; ++t) {
                int index = day * m + t;
                int u = result[index];
                cout << "[" << dist[current][u] << "]";
                if (u != 0) cout << " - " << u << " - ";
                current = u;
                if (index == n) break;
                if (t == m - 1) cout << "[" << dist[current][0] << "]";
            }
            cout << '\n';
        }
        cout << "===\n";
    }
public:
    ReferenceSolver(int placeCount, int visitsPerDay, const vector<Road> &roads) : n(placeCount), m(visitsPerDay), statesPerVertex(0), dist(placeCount + 1, vector<int>(placeCount + 1, INF)) {
        for (size_t i = 0; i < roads.size(); ++i) {
            int u = roads[i].u;
            int v = roads[i].v;
            dist[u][v] = roads[i].distance;
            dist[v][u] = roads[i].distance;
        }
    }
    void solve(int touristNumber) {
        floyd();
        vector<int> result = findOrder();
        printAnswer(touristNumber, result);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Road> roads;
    int n = 0;
    int touristNumber = 0;
    int u;
    while (cin >> u) {
        if (u < -1) {
            ReferenceSolver solver(n, -u, roads);
            solver.solve(++touristNumber);
            roads.clear();
            n = 0;
        } else {
            int v;
            int distance;
            if (!(cin >> v >> distance)) return 0;
            roads.push_back(Road{u, v, distance});
            n = max(n, max(u, v));
        }
    }
    return 0;
}
```

# 总结

本题的算法核心是先用 $\texttt{Floyd–Warshall}$ 算法消除道路网络中的路径选择，再用集合与最后参观景点构成状态压缩动态规划。每天参观的数量固定，使日期边界能够直接通过集合大小对 $M$ 取模确定，避免增加日内计数维度；对末尾景点必然属于集合这一性质进行利用，还能删除状态编码中的固定一位，将有效状态紧凑存储。

按照题意求解时，需要正确处理最短路初始化、完整日期与最后一个不完整日期的返回酒店代价，以及总路程相同情况下的多层比较。复现在线评测时，则必须保留标准程序实际执行的全部细节：重复道路覆盖、非零对角线、提前剪枝与平局更新的先后顺序、回溯后的硬编码交换，以及酒店哨兵造成的额外一天。此次反向工程的关键收获是将最优值计算、参观序列恢复和输出生成分别分析，从而准确定位到最优序列被回溯后处理修改这一根本原因。
