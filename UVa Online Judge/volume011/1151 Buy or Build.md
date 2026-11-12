
> **摘要**：本题给定 $n$ 座城市的平面坐标与 $q$ 个可整组购买的子网络（$q\le 8$），要求在“购买子网络”与“按欧氏距离平方新建线路”两种手段下使全部城市连通，求最小总费用。核心做法是枚举 $2^q$ 种购买集合，用并查集合并已购子网络覆盖的城市，再在收缩后的完全图上运行稠密 $\texttt{Prim}$ 求最小生成树，取“购买费用 + 补全费用”的最小值。文中同时指出所附通过代码以子网络排列路径近似连接结构，存在反例（输出 $404$，正确答案 $304$），并给出严格正确的思路与复杂度分析。

 # 题目描述

给定 $n$ 座城市及其平面直角坐标，需要建立一个使所有城市连通的网络。现有 $q$ 个可供购买的子网络，每个子网络包含若干座已经互相连通的城市，购买时必须支付整个子网络的费用，不能拆分购买。不同子网络包含的城市允许重叠。

除了购买子网络，还能在任意两座城市之间新建线路。连接城市 $i$ 和城市 $j$ 的费用为两点欧几里得距离的平方，即
$$
w(i,j)=(x_i-x_j)^2+(y_i-y_j)^2.
$$
求使全部城市连通的最小总费用。

# 输入格式

第一行包含一个正整数 $T$，表示测试用例数量。输入中允许在测试用例之间出现空行。

每组测试用例首先输入两个整数 $n$ 和 $q$，满足 $1\le n\le 1000$、$0\le q\le 8$。城市编号为 $1$ 至 $n$。

接下来输入 $q$ 行，每行描述一个子网络。首先输入该子网络包含的城市数量 $k$，然后输入购买费用 $c$，最后输入 $k$ 个城市编号。购买费用不超过 $2\times 10^6$。

最后输入 $n$ 行，第 $i$ 行包含两个整数 $x_i$ 和 $y_i$，表示城市 $i$ 的坐标，坐标值均在 $0$ 至 $3000$ 之间。

# 输出格式

对于每组测试用例，输出使所有城市连通的最小总费用。

相邻两组测试用例的输出之间保留一个空行。

# 样例输入

```text
1
7 3
2 4 1 2
3 3 3 6 7
3 9 2 4 5
0 2
4 0
2 0
4 2
1 3
0 5
4 4
```

# 样例输出

```text
17
```

# 题目分析

本题的核心是同时处理“整组购买”和“单独建边”两类操作。购买一个子网络之后，其中所有城市立即连通，其内部线路的具体形状不影响后续决策。因此，决定购买哪些子网络之后，需要关注的只有城市之间形成的连通关系，以及继续连接这些连通部分的最小费用。子网络数量满足 $q\le 8$，全部购买方案只有 $2^q\le 256$ 种，直接枚举每个子网络是否购买即可覆盖全部情况。

固定一个购买方案后，将购买的子网络中的城市合并，得到若干个初始连通分量。属于同一个连通分量的城市已经能够互相到达，不需要额外支付费用；不同连通分量之间仍需通过新建线路连接。将每个初始连通分量收缩为一个点，问题就转化为最小生成树。由此得到本题的标准结论：枚举购买方案，对每种方案求初始连通关系下的最小生成树补全费用，再加上购买费用，最后取最小值。

需要明确说明，题目提供的通过代码与上述标准算法存在区别，而且该区别影响正确性。原代码先把所有已购买子网络覆盖的城市同时视为已经加入生成树，再运行多源 $\texttt{Prim}$ 算法连接其余城市；随后枚举已购买子网络的排列，按照排列顺序连接相邻子网络，并取最小费用。这种处理给出了一个可行建网方案，但没有覆盖全部最优连接结构。多个子网络之间的最优连接结构是一棵树，原代码额外添加的连接结构被限制为经过所有已选子网络的一条路径，两者的最小费用并不相同。原代码注释中的通过记录不能替代算法正确性证明。

下面的反例直接说明这一差异。共有 $8$ 座城市，坐标依次为
$$
\begin{aligned}
p_1&=(10,10),&p_2&=(10,0),\\
p_3&=(0,10),&p_4&=(20,10),\\
p_5&=(0,1000),&p_6&=(1000,1000),\\
p_7&=(2000,1000),&p_8&=(3000,1000).
\end{aligned}
$$
存在 $4$ 个子网络，城市集合分别为 $\{1,5\}$、$\{2,6\}$、$\{3,7\}$、$\{4,8\}$，每个子网络的购买费用均为 $1$。全部购买后，只需新建线路 $(1,2)$、$(1,3)$ 和 $(1,4)$，每条线路费用均为 $100$，总费用为
$$
4+100+100+100=304.
$$
任意两个子网络之间的最小连接费用至少为 $100$，连接 $4$ 个互不相交的子网络至少需要 $3$ 条线路，因此 $304$ 就是该购买方案的最优费用。不购买其中任意一个子网络，都会使对应的远端城市必须通过费用至少为 $980100$ 的新建线路接入网络，因此全局最优答案同样为 $304$。原代码在全部购买时，将所有城市直接标记为已加入生成树，随后求子网络排列的最短连接路径。该路径的最小费用为 $400$，最终输出 $404$。因此，下文给出严格正确的解题思路，并在代码实现章节按要求原样保留所提供的通过代码，同时明确其适用结论。

# 解题思路

首先预处理任意两座城市之间的新建线路费用。设城市 $i$ 的坐标为 $(x_i,y_i)$，则费用矩阵满足
$$
w_{i,j}=(x_i-x_j)^2+(y_i-y_j)^2.
$$
整个城市图是完全图，使用邻接矩阵存储这些费用，预处理时间和空间均为 $O(n^2)$。

随后枚举子网络的购买集合 $S$。每次枚举开始时，初始化一个并查集，使每座城市分别构成一个连通分量。对于集合 $S$ 中的每个子网络，将其全部城市合并，并累加该子网络的购买费用。子网络之间存在重叠时，并查集会自动将它们合并为同一个连通分量。设最终城市 $i$ 所属连通分量的代表为 $r_i$，则当前购买方案对应的辅助图边权定义为
$$
w_S(i,j)=
\begin{cases}
0,&r_i=r_j,\\
w_{i,j},&r_i\ne r_j.
\end{cases}
$$
这里的零权边表示已经通过购买的子网络实现连通。它只用于表达连通关系，不代表额外建设一条实际线路。

在这个辅助图上运行稠密图版本的 $\texttt{Prim}$ 算法。维护每座未加入生成树的城市到当前生成树的最小连接费用，每轮选择连接费用最小的城市加入，再更新其他城市的连接费用。由于图是完全图，直接扫描全部城市即可，每种购买方案的最小生成树计算时间为 $O(n^2)$。同一个初始连通分量内的城市通过零权边接入，从而准确表达购买子网络产生的免费连通关系。不同连通分量之间仍按照原始新建费用连接，因此算法允许形成任意树形结构，包括反例中的星形结构。

记购买集合 $S$ 的总费用为 $C(S)$，辅助图的最小生成树权值为 $M(S)$，最终答案为
$$
\min_{S\subseteq\{1,\ldots,q\}}\bigl(C(S)+M(S)\bigr).
$$
其中空集也参与枚举，对应完全不购买子网络、只通过新建线路连接全部城市的方案。

该算法的正确性由两个方向保证。对于固定的购买集合 $S$，任意合法建网方案都能在辅助图中表示为一个连通子图：已购买子网络内部的连通关系由零权边表达，新建线路保留原有费用。所有费用均非负，从连通子图中删去环上的冗余边后得到生成树，费用不增加，因此最小生成树费用不大于任何合法补全方案的费用。反过来，辅助图最小生成树中的零权分量内部连接已由购买的子网络提供，其余边按照对应费用实际建设后，全部城市必然连通。因此，最小生成树费用恰好等于固定购买集合下的最优补全费用。枚举覆盖全部购买集合，取最小值就得到全局最优答案。

样例中，购买费用分别为 $4$ 和 $3$ 的两个子网络，再新建线路 $(1,5)$、$(2,3)$ 和 $(2,4)$，对应建设费用分别为 $2$、$4$ 和 $4$，总费用为
$$
4+3+2+4+4=17.
$$

标准算法的复杂度如下。每个子网络至多包含 $n$ 座城市，每种购买方案的合并操作耗时为 $O(qn\alpha(n))$，其中 $\alpha$ 为并查集操作复杂度中的反阿克曼函数；记录各城市代表后，稠密图 $\texttt{Prim}$ 算法耗时为 $O(n^2)$。总时间复杂度为
$$
O\left(n^2+2^q\left(qn\alpha(n)+n^2\right)\right),
$$
空间复杂度为
$$
O(n^2+qn).
$$
边权计算和总费用累加使用足够宽的整数类型，能够避免平方运算及累加过程中的溢出。

所附原代码的复杂度需要单独说明。其预处理子网络之间距离的时间复杂度为 $O(q^2n^2)$；每次使用优先队列运行 $\texttt{Prim}$ 算法的时间复杂度上界为 $O(n^2\log(n+1))$；对全部非空子集枚举排列并计算相邻连接费用的总时间复杂度为 $O(q\cdot q!)$，剪枝只减少实际运行次数。因此，原代码的总时间复杂度上界为
$$
O\left((1+q^2)n^2+2^q n^2\log(n+1)+q\cdot q!\right),
$$
空间复杂度为 $O(n^2+qn)$。该复杂度描述的是原代码的实际执行过程，不构成其最优性保证。

# 代码实现

以下代码按要求保留原有逻辑与注释，仅去除了函数体内的空行。代码中的 $\texttt{prim}$ 函数将所有被选子网络覆盖的城市作为初始集合，$\texttt{get\_cost\_of\_all}$ 函数再通过子网络排列计算额外连接费用。它与前文严格正确的“并查集合并后求最小生成树”算法不同，并在前述反例上输出 $404$，而正确答案为 $304$。

```cpp
// Buy or Build
// UVa ID: 1151
// Verdict: Accepted
// Submission Date: 2017-01-12
// UVa Run Time: 0.110s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAX_DIST = 1000000000, MAX_SUBNET = 10;

struct edge
{
    int idx, weight;

    bool operator<(const edge& x) const
    {
        return weight > x.weight;
    }
};

struct point
{
    int x, y;
};

int cases = 0;
int number_of_cities, number_of_subnet, cities_in_subnet, min_cost_of_total;
int subnet[MAX_SUBNET][MAXV], cost_of_setup[MAXV][MAXV], dist_of_subnet[MAX_SUBNET][MAX_SUBNET];
int dist_to_tree[MAXV], intree[MAXV];
point cities[MAXV];

int prim()
{
    int min_weight_sum = 0;
    // update the distance between tree and vertex which is out-of-tree.
    for (int i = 0; i < number_of_cities; i++)
    {
        dist_to_tree[i] = MAX_DIST;
        if (intree[i]) dist_to_tree[i] = 0;
        else
        {
            for (int j = 0; j < number_of_cities; j++)
                if (intree[j] && dist_to_tree[i] > cost_of_setup[i][j])
                    dist_to_tree[i] = cost_of_setup[i][j];
        }
    }
    // find a vertex which is out-the-tree.
    int u = -1;
    for (int i = 0; i < number_of_cities; i++)
        if (intree[i])
        {
            u = i;
            break;
        }
    // if no vertex added to tree, set the first vertex in tree.
    priority_queue<edge> unvisited;
    if (u == -1)
    {
        for (int i = 0; i < number_of_cities; i++)
            dist_to_tree[i] = MAX_DIST;
        unvisited.push((edge){0, 0});
    }
    else
    {
        for (int i = 0; i < number_of_cities; i++)
            if (!intree[i])
                unvisited.push((edge){i, dist_to_tree[i]});
    }
    while (!unvisited.empty())
    {
        edge v = unvisited.top(); unvisited.pop();
        if (intree[v.idx]) continue;
        intree[v.idx] = 1;
        min_weight_sum += v.weight;
        for (int i = 0; i < number_of_cities; i++)
            if (!intree[i] && dist_to_tree[i] > cost_of_setup[v.idx][i])
            {
                dist_to_tree[i] = cost_of_setup[v.idx][i];
                unvisited.push((edge){i, dist_to_tree[i]});
            }
    }
    return min_weight_sum;
}

void get_cost_of_all(int flag[], int idx)
{
    int current_cost = 0;
    memset(intree, 0, sizeof(intree));
    vector<int> selected;
    for (int i = 0; i < idx; i++)
    {
        current_cost += subnet[flag[i]][0];
        for (int j = 1; j <= number_of_cities && subnet[flag[i]][j]; j++)
            intree[subnet[flag[i]][j] - 1] = 1;
        selected.push_back(flag[i]);
    }
    current_cost += prim();
    // prune.
    if (current_cost >= min_cost_of_total) return;
    int min_cost_of_subnet = MAX_DIST;
    do
    {
        int cost_of_subnet = 0;
        for (int i = 0; i < idx - 1; i++)
            cost_of_subnet += dist_of_subnet[selected[i]][selected[i + 1]];
        min_cost_of_subnet = min(min_cost_of_subnet, cost_of_subnet);
    } while (next_permutation(selected.begin(), selected.end()));
    current_cost += min_cost_of_subnet;
    min_cost_of_total = min(min_cost_of_total, current_cost);
}

void generate(int flag[], int idx, int last)
{
    if (idx < last)
    {
        if (idx == 0)
        {
            for (int i = 0; i < number_of_subnet; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last);
            }
        }
        else
        {
            for (int i = flag[idx - 1] + 1; i < number_of_subnet; i++)
            {
                flag[idx] = i;
                generate(flag, idx + 1, last);
            }
        }
    }
    else
        get_cost_of_all(flag, idx);
}

void enumerating_subset()
{
    for (int i = 1; i <= number_of_subnet; i++)
    {
        int *flag = new int[number_of_subnet];
        generate(flag, 0, i);
        delete [] flag;
    }
}

int get_cost_of_setup(int i, int j)
{
    int x_diff = cities[i].x - cities[j].x, y_diff = cities[i].y - cities[j].y;
    return x_diff * x_diff + y_diff * y_diff;
}

int get_dist_of_subnet(int i, int j)
{
    int min_dist = MAX_DIST;
    for (int ii = 1; subnet[i][ii]; ii++)
        for (int jj = 1; subnet[j][jj]; jj++)
            min_dist = min(min_dist, cost_of_setup[subnet[i][ii] - 1][subnet[j][jj] - 1]);
    return min_dist;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        cin >> number_of_cities >> number_of_subnet;
        for (int i = 0; i < number_of_subnet; i++)
        {
            cin >> cities_in_subnet >> subnet[i][0];
            for (int j = 1; j <= cities_in_subnet; j++)
                cin >> subnet[i][j];
            subnet[i][cities_in_subnet + 1] = 0;
        }
        for (int i = 0; i < number_of_cities; i++)
            cin >> cities[i].x >> cities[i].y;
        for (int i = 0; i < number_of_cities; i++)
            for (int j = i; j < number_of_cities; j++)
                cost_of_setup[i][j] = cost_of_setup[j][i] = get_cost_of_setup(i, j);
        for (int i = 0; i < number_of_subnet; i++)
            for (int j = i + 1; j < number_of_subnet; j++)
                dist_of_subnet[i][j] = dist_of_subnet[j][i] = get_dist_of_subnet(i, j);
        // no sub network selected.
        memset(intree, 0, sizeof(intree));
        min_cost_of_total = prim();
        // some sub network selected.
        enumerating_subset();
        cout << min_cost_of_total << '\n';
    }
    return 0;
}
```

# 总结

本题利用子网络数量很小这一条件枚举购买集合，将整组购买带来的连通关系交给并查集处理，再通过最小生成树求出剩余建设费用。关键技巧是把已经连通的城市视为同一个整体，并保留不同整体之间任意树形连接的自由度。所附原代码通过枚举子网络排列构造连接路径，该限制排除了部分最优树形结构，因此必须区分其通过记录与严格的算法正确性。
