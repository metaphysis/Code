
> **摘要**：本题要求在分层电话网络 $S(n)$ 中，为每个连接请求 $(a_i, b_i)$ 选择一个 $S(0)$ 交换机作为中转，使所有路径互不干扰。核心思路是逐层将请求分配问题转化为二分图边染色：每层以输入模值和输出模值为两侧顶点、请求为边，由于每个顶点度数至多为 $2$，连通块只能是路径或偶环，交替染色即可保证端口不冲突。边颜色同时决定请求进入的子交换机与答案的一个二进制位，递归 $n$ 层后即得每个请求的 $S(0)$ 编号。时间复杂度 $O(n \times 2^n)$，空间复杂度 $O(n \times 2^n)$。

# 题目描述

电话公司需要构建一个分层电话网络，最外层为交换机 $S(n)$。每个连接请求给出一个输入端口 $a_i$ 和一个输出端口 $b_i$，要求为每个请求选择一个 $S(0)$ 交换机作为中转节点，使得所有连接路径互不干扰。

网络中的任意输入端口都能够通过唯一的路径到达任意一个 $S(0)$ 交换机，任意输出端口也能够通过唯一的路径连接到任意一个 $S(0)$ 交换机。因此，只要确定每个请求经过的 $S(0)$ 编号，就能够确定完整路径。

每个交换机的输入端口和输出端口最多只能被一条连接使用。题目保证至少存在一种合法方案。

# 输入格式

第一行输入一个正整数，表示测试数据组数，测试组数不超过 $100$。

每组测试数据的第一行输入两个整数 $n$ 和 $m$：

- $n$ 表示最外层交换机的层数，满足 $1 \le n \le 16$。
- $m$ 表示连接请求数量，满足 $1 \le m \le 2^n$。

接下来输入 $m$ 行，每行包含两个整数 $a_i$ 和 $b_i$：

- $a_i$ 表示请求的输入端口编号。
- $b_i$ 表示请求的输出端口编号。
- $0 \le a_i, b_i < 2^n$。
- 所有 $a_i$ 两两不同。
- 所有 $b_i$ 两两不同。

# 输出格式

对于每组测试数据，输出一行 $m$ 个整数。

第 $i$ 个整数表示第 $i$ 个连接请求经过的 $S(0)$ 交换机编号。输出任意一种满足所有路径互不相交的合法方案。

# 样例输入

```text
2
1 1
0 1
3 5
0 3
1 4
2 5
3 6
4 7
```

# 样例输出

```text
0
3 0 1 2 4
```

# 题目分析

交换机 $S(n)$ 由两个 $S(n - 1)$ 交换机构成，分别记为第 $0$ 个子交换机和第 $1$ 个子交换机。对于 $S(n)$ 的任意输入端口 $a$，它连接到两个子交换机中编号为 $a \bmod 2^{n-1}$ 的输入端口。对于任意输出端口 $b$，两个子交换机中编号为 $b \bmod 2^{n-1}$ 的输出端口都能够连接到该输出端口。

因此，在当前层处理中，每个连接请求 $(a_i, b_i)$ 都需要决定进入哪一个子交换机。若请求被分配到第 $0$ 个子交换机，则下一层的请求变为：

$$
(a_i \bmod 2^{n-1}, b_i \bmod 2^{n-1})
$$

若请求被分配到第 $1$ 个子交换机，下一层的请求形式完全相同，只是其最终经过的 $S(0)$ 编号在当前二进制位上为 $1$。

当前层的分配必须保证两类冲突都不会发生：

- 对于相同的 $a_i \bmod 2^{n-1}$，至多一条请求进入同一个子交换机，否则会占用同一个输入端口。
- 对于相同的 $b_i \bmod 2^{n-1}$，至多一条请求从同一个子交换机离开，否则会占用同一个输出端口。

将当前层的问题转化为二分图。左侧顶点表示输入编号 $a_i \bmod 2^{n-1}$，右侧顶点表示输出编号 $b_i \bmod 2^{n-1}$，每个连接请求对应一条连接左右顶点的边。

由于所有原始输入编号 $a_i$ 互不相同，对于任意左侧顶点，最多只会有两条边与其相连。原因是具有相同模值的输入编号只能是 $x$ 和 $x + 2^{n-1}$。同理，由于所有原始输出编号 $b_i$ 互不相同，每个右侧顶点的度数也至多为 $2$。

所以，该二分图的每个连通块只可能是路径或偶环。沿着每个连通块对边交替染色为 $0$ 和 $1$，就能够保证同一个顶点相邻的边颜色不同。颜色 $0$ 表示请求进入第 $0$ 个子交换机，颜色 $1$ 表示请求进入第 $1$ 个子交换机。

这样完成当前层分配后，两组请求分别递归处理，直到层数降为 $0$。每次递归确定答案的一个二进制位，最终组合得到每个请求所经过的 $S(0)$ 编号。

# 解题思路

步骤 $\texttt{1}$. 对当前层的所有请求建立二分图。左侧编号范围为 $[0, 2^{n-1} - 1]$，右侧编号范围也为 $[0, 2^{n-1} - 1]$，代码中将右侧顶点编号整体加上 $2^{n-1}$，从而与左侧顶点区分。

步骤 $\texttt{2}$. 优先从度数为 $1$ 的顶点开始遍历未染色边。这样的连通块一定是路径，从端点开始交替染色即可完成整条路径的染色。

步骤 $\texttt{3}$. 所有路径处理完成后，剩余未染色边只存在于环中。从任意未染色边所在的顶点开始遍历，并交替进行 $0$、$1$ 染色。二分图中的环长度一定为偶数，因此首尾边颜色不会冲突。

步骤 $\texttt{4}$. 对于每条请求边，根据颜色更新答案。当前递归层为 $level$ 时，边颜色对应答案的第 $level - 1$ 个二进制位，即：

$$
\textit{answer}[id] \mathrel{|=} color \ll (level - 1)
$$

步骤 $\texttt{5}$. 将颜色为 $0$ 的请求放入第一个子交换机，将颜色为 $1$ 的请求放入第二个子交换机。两组请求的输入和输出编号均对 $2^{level-1}$ 取模，然后继续递归。

步骤 $\texttt{6}$. 当 $level = 0$ 时，当前请求已经到达对应的 $S(0)$ 交换机，递归结束。

每一层的边染色都保证相同输入模值和相同输出模值的请求被分配到不同子交换机，因此当前层不会发生端口冲突。递归过程对每一层重复相同约束，最终所有连接路径均不共享任何输入端口、输出端口或连接线路。

时间复杂度为：

$$
O(n \times 2^n)
$$

空间复杂度为：

$$
O(n \times 2^n)
$$

# 代码实现

代码使用 $\texttt{Request}$ 结构体保存请求编号、当前输入编号和当前输出编号。$\texttt{colorFrom}$ 函数负责从一个顶点出发，对路径或环中的边进行交替染色。$\texttt{route}$ 函数负责处理当前层的二分图构造、边染色、答案位更新和递归分组。

```cpp
// Telephone Network
// UVa ID: 12267
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.860s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Request {
    int id, in, out;
};

void colorFrom(int start, const vector<int>& edgeU, const vector<int>& edgeV, const vector<vector<int>>& graph, vector<int>& color) {
    int node = start, nowColor = 0;
    while (true) {
        int edge = -1;
        for (int id : graph[node])
            if (color[id] == -1) {
                edge = id;
                break;
            }
        if (edge == -1)
            break;
        color[edge] = nowColor;
        node = edgeU[edge] == node ? edgeV[edge] : edgeU[edge];
        nowColor ^= 1;
    }
}

void route(int level, const vector<Request>& requests, vector<int>& answer) {
    if (level == 0)
        return;
    int half = 1 << (level - 1), nodeCount = half * 2, requestCount = requests.size();
    vector<int> edgeU(requestCount), edgeV(requestCount), color(requestCount, -1);
    vector<vector<int>> graph(nodeCount);
    for (int i = 0; i < requestCount; i++) {
        edgeU[i] = requests[i].in % half;
        edgeV[i] = half + requests[i].out % half;
        graph[edgeU[i]].push_back(i);
        graph[edgeV[i]].push_back(i);
    }
    for (int i = 0; i < nodeCount; i++)
        if (graph[i].size() == 1)
            colorFrom(i, edgeU, edgeV, graph, color);
    for (int i = 0; i < requestCount; i++)
        if (color[i] == -1)
            colorFrom(edgeU[i], edgeU, edgeV, graph, color);
    vector<Request> first, second;
    for (int i = 0; i < requestCount; i++) {
        int id = requests[i].id;
        answer[id] |= color[i] << (level - 1);
        Request nextRequest = {id, requests[i].in % half, requests[i].out % half};
        if (color[i] == 0)
            first.push_back(nextRequest);
        else
            second.push_back(nextRequest);
    }
    route(level - 1, first, answer);
    route(level - 1, second, answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, m;
        cin >> n >> m;
        vector<Request> requests(m);
        for (int i = 0; i < m; i++) {
            requests[i].id = i;
            cin >> requests[i].in >> requests[i].out;
        }
        vector<int> answer(m, 0);
        route(n, requests, answer);
        for (int i = 0; i < m; i++) {
            if (i > 0)
                cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将分层交换网络中的路径选择转化为二分图边染色问题。每层中，输入模值和输出模值构成二分图的两个顶点集合，而连接请求构成边。由于每个顶点度数至多为 $2$，每个连通块均为路径或偶环，交替染色能够直接保证请求分配到两个子交换机后不发生冲突。

递归处理每一层时，边颜色同时决定请求进入的子交换机和最终答案的一个二进制位。完成全部 $n$ 层递归后，每个请求对应的 $S(0)$ 编号被完整构造，所有连接路径均满足互不相交的要求。
