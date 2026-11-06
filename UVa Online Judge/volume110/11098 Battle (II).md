

> **摘要**：本题给定 $n$ 个炸弹，每个炸弹有圆心坐标、半径 $R_i$ 与破坏范围 $E_i$，炸弹 $i$ 能直接引爆炸弹 $j$ 当且仅当两圆心距离不超过 $E_i + R_i + R_j$。要求选出一个手动引爆序列，使所有炸弹最终被引爆、序列中靠前的炸弹不能引爆靠后的炸弹，且手动引爆的平均成本最小。解法将引爆关系抽象为有向图，用 $\texttt{Tarjan}$ 算法求强连通分量并缩点为 $\texttt{DAG}$：入度为 $0$ 的 $\texttt{SCC}$ 必须手动引爆，其余 $\texttt{SCC}$ 按最小 $E$ 升序贪心加入（条件 $e \times k \le C$），最后按拓扑序逆序输出所选炸弹编号。总时间复杂度 $O(n^2)$，适用于 $n \le 300$。

## 题目描述

给定 $n$ 个炸弹，每个炸弹有圆心坐标 $(X_i, Y_i)$、半径 $R_i$ 和破坏范围 $E_i$。  
若炸弹 $i$ 爆炸，则它能直接引爆炸弹 $j$ 当且仅当：

$$
dist(i, j) \le E_i + R_i + R_j
$$

其中 $dist(i, j)$ 为两圆心欧氏距离。

游戏规则如下：

规则 $\texttt{1}$. 若一个炸弹爆炸，则其破坏范围内的所有炸弹也会爆炸（连锁反应）。  
规则 $\texttt{2}$. 炸弹可因连锁反应被引爆，也可被手动引爆。  
规则 $\texttt{3}$. 手动引爆第 $i$ 个炸弹的成本等于 $E_i$。

要求选出一个手动引爆的序列，满足：

- 所有炸弹最终都被引爆。
- 序列中第 $i$ 个炸弹不能导致第 $j$ 个炸弹（$j > i$）爆炸（即前面引爆的炸弹不能引爆后面的炸弹）。
- 序列中手动引爆的炸弹的平均成本最小。

输出任意一组满足条件的序列（炸弹编号从 $0$ 开始）。

## 输入格式

第一行一个整数 $N$，表示测试用例数。  
每个测试用例第一行一个整数 $n$（$0 < n \le 300$）。  
接下来 $n$ 行，每行四个整数 $X_i, Y_i, R_i, E_i$。  
每个测试用例后跟一个空行。

## 输出格式

对于每个测试用例，输出一行 `Case #x:`，后接按顺序应手动引爆的炸弹编号，用空格分隔。输出格式与样例一致。

## 样例

输入

```text
1
3
4 7 2 2
8 5 1 0
3 -3 1 1
```

输出

```text
Case #1: 1 0 2
```

## 题目分析

本题的核心是：在有向图中寻找一个顶点子集 $S$，使得从 $S$ 中的顶点出发能到达所有顶点，且 $S$ 中任意两点之间不存在有向路径，同时最小化 $\frac{\sum_{v \in S} E_v}{|S|}$。

首先，根据引爆关系构建有向图 $G$：顶点为炸弹，边 $i \to j$ 表示炸弹 $i$ 能直接引爆炸弹 $j$（条件满足时）。连锁反应即为图上的可达性。

手动引爆的集合 $S$ 必须满足：

- **覆盖性**：$S$ 是图的一个源集（即所有顶点都能被 $S$ 中某个顶点到达）。
- **无路径约束**：$S$ 中任意两个顶点 $u, v$ 互不可达（否则若 $u$ 可达 $v$，则先引爆 $u$ 会引爆 $v$，违反条件 $\texttt{2}$）。

在有向图中，强连通分量（$\texttt{SCC}$）内的顶点两两互相可达。因此，一个 $\texttt{SCC}$ 中至多只能选择一个顶点进入 $S$。若某个 $\texttt{SCC}$ 有入度（即存在从其他 $\texttt{SCC}$ 到它的边），则它一定可以被某个前驱 $\texttt{SCC}$ 引爆，因此它不必被手动引爆。只有**入度为 $0$** 的 $\texttt{SCC}$（即 $\texttt{DAG}$ 中的源点）无法被其他 $\texttt{SCC}$ 引爆，必须手动引爆其中的一个顶点。

将原图缩点后得到一个 $\texttt{DAG}$。每个入度为 $0$ 的 $\texttt{SCC}$ 必须被选择（且选一个顶点）。对于入度非 $0$ 的 $\texttt{SCC}$，可以选择是否额外手动引爆其中的一个顶点，以增加分母，从而可能降低平均成本。

设已经选择了 $k$ 个 $\texttt{SCC}$，总成本为 $C$，当前平均成本为 $C/k$。若再选一个成本为 $e$ 的 $\texttt{SCC}$，则新平均成本为 $(C+e)/(k+1)$。新平均值小于原平均值当且仅当：

$$
\frac{C+e}{k+1} < \frac{C}{k} \iff k(C+e) < C(k+1) \iff k e < C \iff e < \frac{C}{k}
$$

即当 $e$ 小于当前平均值时，加入该 $\texttt{SCC}$ 会降低平均成本；等于时不变；大于时升高。因此贪心策略是：先将所有源 $\texttt{SCC}$ 作为必选，计算初始总成本 $C$ 和数量 $k$；然后将非源 $\texttt{SCC}$ 按成本升序排列，依次尝试加入，只要当前成本 $e \le C/k$ 就加入（等于时平均不变，但允许加入仍符合“最小”要求），否则停止（因为后续成本更大）。

最后，需要确定输出顺序以满足条件 $\texttt{2}$。缩点后的 $\texttt{DAG}$ 中，若存在边 $u \to v$，则 $u$ 能引爆 $v$。为避免先引爆 $u$ 导致 $v$ 被提前引爆，必须保证 $u$ 在输出序列中出现在 $v$ 之后。因此，对 $\texttt{DAG}$ 进行拓扑排序，然后按逆序输出被选中的 $\texttt{SCC}$ 对应的炸弹编号，即可保证前面的炸弹不会引爆后面的炸弹。

## 解题思路

### 步骤 $\texttt{1}$：建图

枚举所有炸弹对 $(i, j)$（$i \ne j$），若满足距离条件，则添加有向边 $i \to j$。距离比较时使用整数平方，避免浮点误差。

### 步骤 $\texttt{2}$：求强连通分量

使用 $\texttt{Tarjan}$ 算法求出所有 $\texttt{SCC}$，记录每个顶点所属的 $\texttt{SCC}$ 编号，并收集每个 $\texttt{SCC}$ 内的顶点列表。

### 步骤 $\texttt{3}$：缩点并计算入度

遍历原图所有边，若边的两端属于不同 $\texttt{SCC}$，则给目标 $\texttt{SCC}$ 的入度加一。同时构建缩点后的 $\texttt{DAG}$（用于拓扑排序）。

### 步骤 $\texttt{4}$：确定必选和可选 $\texttt{SCC}$

- 将所有入度为 $0$ 的 $\texttt{SCC}$ 作为必选集合，计算总成本 $C$（每个 $\texttt{SCC}$ 取其中 $E$ 最小的顶点）和数量 $k$。
- 收集所有入度非 $0$ 的 $\texttt{SCC}$，记录其最小 $E$ 值和对应的顶点编号，并按 $E$ 升序排列。

### 步骤 $\texttt{5}$：贪心选择可选 $\texttt{SCC}$

遍历排序后的可选 $\texttt{SCC}$，若当前 $E \times k \le C$，则加入该 $\texttt{SCC}$（更新 $C$ 和 $k$），否则停止（因为后续 $E$ 更大，不会再满足条件）。

### 步骤 $\texttt{6}$：生成输出序列

对 $\texttt{DAG}$ 进行拓扑排序，得到拓扑序。按逆序扫描拓扑序，若当前 $\texttt{SCC}$ 被选中，则输出该 $\texttt{SCC}$ 中 $E$ 最小的炸弹编号（若有多个相同最小 $E$，任意选择一个）。逆序确保若 $u$ 可达 $v$，则 $v$ 排在 $u$ 前面，满足条件 $\texttt{2}$。

### 正确性证明

- **必要性**：每个入度为 $0$ 的 $\texttt{SCC}$ 无法由其他 $\texttt{SCC}$ 到达，因此必须手动引爆。对于入度非 $0$ 的 $\texttt{SCC}$，即使不手动引爆，也会被某个前驱引爆，所以可选择性加入。
- **最优性**：平均成本函数在加入新元素时，若新元素成本小于当前平均值则降低，否则不降。因此，按成本升序贪心加入所有能降低平均值的元素，得到全局最优（这是经典的分数规划贪心，因为加入顺序不影响最终结果，但成本升序保证一旦停止后续不会再有收益）。
- **可行性**：输出逆拓扑序保证了若边 $u \to v$，则 $v$ 在输出序列中位于 $u$ 之前，因此先引爆 $v$ 不会引爆 $u$；且由于同一 $\texttt{SCC}$ 只选一个顶点，不会出现环内互相引爆的情况。

### 复杂度分析

- 建图：枚举 $n(n-1)$ 对，每对 $O(1)$，总 $O(n^2)$。
- $\texttt{Tarjan}$ 算法：$O(n + e)$，其中 $e \le n(n-1)$。
- 缩点、拓扑排序：$O(n + e)$。
- 排序可选 $\texttt{SCC}$：$O(m \log m)$，其中 $m \le n$。
- 总体时间复杂度：$O(n^2)$（因为 $e = O(n^2)$），空间复杂度：$O(n^2)$ 存储邻接表，$n \le 300$ 完全可行。

## 代码实现

```cpp
// Battle (II)
// UVa ID: 11098
// Verdict: Accepted
// Submission Date: 2026-07-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Bomb { int x, y, r, e; };

int n;
vector<Bomb> bombs;
vector<vector<int>> adj;
vector<int> dfn, low, stk, inStack, sccId;
int dfsClock, sccCnt;

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsClock;
    stk.push_back(u);
    inStack[u] = 1;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int v;
        do {
            v = stk.back(); stk.pop_back();
            inStack[v] = 0;
            sccId[v] = sccCnt;
        } while (v != u);
        sccCnt++;
    }
}

int main() {
    int N;
    cin >> N;
    for (int caseNo = 1; caseNo <= N; ++caseNo) {
        cin >> n;
        bombs.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> bombs[i].x >> bombs[i].y >> bombs[i].r >> bombs[i].e;

        // 建图
        adj.assign(n, {});
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                long long dx = bombs[i].x - bombs[j].x;
                long long dy = bombs[i].y - bombs[j].y;
                long long dist2 = dx * dx + dy * dy;
                long long rhs = (long long)bombs[i].e + bombs[i].r + bombs[j].r;
                if (dist2 <= rhs * rhs)
                    adj[i].push_back(j);
            }

        // Tarjan 求 SCC
        dfn.assign(n, 0); low.assign(n, 0); inStack.assign(n, 0); sccId.assign(n, -1);
        stk.clear(); dfsClock = 0; sccCnt = 0;
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) tarjan(i);

        // 每个 SCC 的最小 E 和对应炸弹编号
        vector<int> minE(sccCnt, INT_MAX), bestNode(sccCnt, -1);
        for (int i = 0; i < n; ++i) {
            int c = sccId[i];
            if (bombs[i].e < minE[c]) {
                minE[c] = bombs[i].e;
                bestNode[c] = i;
            }
        }

        // 缩点建 DAG，去重边
        vector<int> indeg(sccCnt, 0);
        vector<vector<int>> dag(sccCnt);
        vector<vector<bool>> has(sccCnt, vector<bool>(sccCnt, false));
        for (int u = 0; u < n; ++u)
            for (int v : adj[u]) {
                int cu = sccId[u], cv = sccId[v];
                if (cu != cv && !has[cu][cv]) {
                    has[cu][cv] = true;
                    dag[cu].push_back(cv);
                    indeg[cv]++;
                }
            }

        // 必选源 SCC
        vector<int> chosenScc;
        long long totalCost = 0;
        int totalCount = 0;
        for (int c = 0; c < sccCnt; ++c)
            if (indeg[c] == 0) {
                chosenScc.push_back(c);
                totalCost += minE[c];
                totalCount++;
            }

        // 可选非源 SCC，按成本排序
        vector<pair<int,int>> optional;
        for (int c = 0; c < sccCnt; ++c)
            if (indeg[c] != 0)
                optional.push_back({minE[c], c});
        sort(optional.begin(), optional.end());

        // 贪心加入能降低平均值的可选 SCC
        for (auto &p : optional) {
            int cost = p.first, cid = p.second;
            if ((long long)cost * totalCount <= totalCost) {
                chosenScc.push_back(cid);
                totalCost += cost;
                totalCount++;
            } else
                break;
        }

        // 拓扑排序（用于逆序输出）
        vector<int> indegCopy = indeg;
        queue<int> q;
        for (int c = 0; c < sccCnt; ++c)
            if (indegCopy[c] == 0) q.push(c);
        vector<int> topo;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : dag[u]) {
                indegCopy[v]--;
                if (indegCopy[v] == 0) q.push(v);
            }
        }

        vector<bool> isChosen(sccCnt, false);
        for (int c : chosenScc) isChosen[c] = true;

        vector<int> ans;
        for (int i = (int)topo.size() - 1; i >= 0; --i) {
            int c = topo[i];
            if (isChosen[c])
                ans.push_back(bestNode[c]);
        }

        cout << "Case #" << caseNo << ":";
        for (int id : ans)
            cout << ' ' << id;
        cout << '\n';
    }
    return 0;
}
```

## 总结

本题的关键在于将引爆关系抽象为有向图，并利用强连通分量缩点转化为 $\texttt{DAG}$ 上的源点问题。平均成本的最小化通过贪心加入低成本 $\texttt{SCC}$ 解决，其正确性由平均值函数的单调性保证。输出顺序通过拓扑排序的逆序满足无前向引爆约束。

**技巧要点**：
- 使用整数平方比较距离，避免浮点误差。
- 利用 $\texttt{Tarjan}$ 算法求 $\texttt{SCC}$，并缩点去重边。
- 贪心策略的条件判断：$e \times k \le C$ 等价于 $e \le C/k$，用整数乘法避免浮点除法。
- 输出顺序利用拓扑逆序，保证条件 $\texttt{2}$ 成立。

该解法时间复杂度 $O(n^2)$，对于 $n \le 300$ 非常高效，且代码易于实现。
