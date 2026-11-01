
>  **摘要**：本文讨论 $\texttt{Secret Santa}$ 送礼分配的唯一性判定问题：给定 $p$ 位参与者与 $a$ 条已知送礼关系，要求判断是否存在且仅存在一种满足「每人送出一份、每人收到一份、无人送给自己」的完整分配。文章将送礼关系抽象为二分图，把完整分配对应为完美匹配，从而把问题转化为「完美匹配是否存在且唯一」。求解上先用 $\texttt{Kuhn}$ 匈牙利算法求一次最大匹配，若匹配数不足 $p$ 则直接判定不存在；随后依次禁用首次完美匹配中的每条边并重新求匹配，只要存在一次仍能得到大小为 $p$ 的完美匹配，就说明分配不唯一。该做法总时间复杂度为 $O(p^4)$，空间复杂度为 $O(p^2)$，并附有完整 $\texttt{C++}$ 实现与样例验证。

# 题目描述

在 $\texttt{Secret Santa}$ 游戏中，每位参与者都要给恰好一位其他参与者送礼，并且每位参与者都要恰好收到一份礼物。现已知部分送礼关系，需要判断这些信息是否足以唯一确定所有参与者的完整送礼分配。

若存在且仅存在一种满足所有已知关系、每人送给一人、每人收到一份礼物且无人送给自己的完整分配，输出 $\texttt{YES}$；其余情况输出 $\texttt{NO}$。

# 输入格式

输入包含多组测试数据。每组测试数据的第一行包含两个整数 $p$ 和 $a$，其中 $p$ 表示参与者数量，$a$ 表示已知送礼关系的数量。

随后输入 $a$ 行，每行包含两个整数 $u$ 和 $v$，表示参与者 $u$ 给参与者 $v$ 送礼。参与者编号从 $1$ 到 $p$。

当输入 $p = 0$ 时结束，终止行不处理。

# 输出格式

对于每组测试数据，若完整送礼分配能够被唯一确定，输出 $\texttt{YES}$；否则输出 $\texttt{NO}$。

# 样例输入

```text
3 1
1 2
4 2
1 2
2 3
4 2
1 2
4 3
0 0
```

# 样例输出

```text
YES
YES
NO
```

# 题目分析

每位参与者均有一个送礼对象，同时每位参与者也必须恰好被一人选择，因此完整分配本质上是参与者集合上的一个排列。题目额外规定任何参与者都不能选择自己，所以排列中不存在自环。

将送礼者和收礼者拆分为左右两个点集，构造二分图。左侧第 $i$ 个点表示送礼者 $i$，右侧第 $j$ 个点表示收礼者 $j$。若 $i$ 能够给 $j$ 送礼，则连接一条边。已知关系 $u \to v$ 表示左侧点 $u$ 只能连接右侧点 $v$；未出现已知关系的送礼者可以连接所有满足 $i \ne j$ 的收礼者。

一个合法的完整分配对应二分图中的一个完美匹配，其匹配边数量为 $p$。题目要求判断完美匹配是否唯一，因此需要先确认完美匹配存在，再确认不存在第二个不同的完美匹配。

# 解题思路

使用 $\texttt{Kuhn}$ 匈牙利算法求二分图最大匹配。数组 $\textit{mat}[v]$ 记录右侧收礼者 $v$ 当前匹配的送礼者，数组 $\textit{leftMat}[u]$ 记录左侧送礼者 $u$ 在最终匹配中对应的收礼者。

首先根据已知关系建立邻接矩阵 $\textit{adj}$。若已知同一送礼者对应不同收礼者，或者存在 $u = v$ 的已知关系，则输入条件本身无法构成合法分配，直接输出 $\texttt{NO}$。

接着求一次最大匹配。若最大匹配大小小于 $p$，说明不存在覆盖所有参与者的完美匹配，输出 $\texttt{NO}$。

设首次求得的完美匹配为 $M$。对于 $M$ 中的每条匹配边 $(u, \textit{baseMat}[u])$，临时禁止该边后重新求最大匹配。若禁用任意一条匹配边后仍然存在大小为 $p$ 的完美匹配，则新匹配必然不同于 $M$，完整分配不唯一，输出 $\texttt{NO}$。若禁用每条匹配边都会使最大匹配小于 $p$，则任何合法完美匹配都必须包含 $M$ 的全部边，完整分配唯一，输出 $\texttt{YES}$。

一次 $\texttt{Kuhn}$ 匈牙利算法的时间复杂度为 $O(p^3)$。最多执行 $p + 1$ 次匹配，因此总时间复杂度为：
$$
O(p^4)
$$
邻接矩阵、匹配数组和访问数组的空间复杂度为：
$$
O(p^2)
$$

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

int p, a;
vector<vector<int> > adj;

bool findPath(int u, int banU, int banV, vector<int>& mat, vector<int>& vis) {
    for (int v = 1; v <= p; v++) {
        if (!adj[u][v] || (u == banU && v == banV) || vis[v])
            continue;
        vis[v] = 1;
        if (mat[v] == 0 || findPath(mat[v], banU, banV, mat, vis)) {
            mat[v] = u;
            return true;
        }
    }
    return false;
}

int getMatch(int banU, int banV, vector<int>& leftMat) {
    vector<int> mat(p + 1, 0);
    int cnt = 0;
    for (int u = 1; u <= p; u++) {
        vector<int> vis(p + 1, 0);
        if (findPath(u, banU, banV, mat, vis))
            cnt++;
    }
    leftMat.assign(p + 1, 0);
    for (int v = 1; v <= p; v++)
        if (mat[v] != 0)
            leftMat[mat[v]] = v;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> p >> a && p != 0) {
        vector<int> known(p + 1, 0);
        bool ok = true;
        for (int i = 0; i < a; i++) {
            int u, v;
            cin >> u >> v;
            if (u == v)
                ok = false;
            if (known[u] != 0 && known[u] != v)
                ok = false;
            known[u] = v;
        }
        adj.assign(p + 1, vector<int>(p + 1, 0));
        for (int u = 1; u <= p; u++) {
            if (known[u] != 0)
                adj[u][known[u]] = 1;
            else {
                for (int v = 1; v <= p; v++)
                    if (u != v)
                        adj[u][v] = 1;
            }
        }
        vector<int> baseMat;
        if (!ok || getMatch(0, 0, baseMat) != p) {
            cout << "NO\n";
            continue;
        }
        for (int u = 1; u <= p; u++) {
            vector<int> tempMat;
            if (getMatch(u, baseMat[u], tempMat) == p) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
```

# 总结

本题的核心是将送礼关系转化为二分图匹配问题。完美匹配表示一组完整合法的送礼分配，唯一性通过依次删除当前完美匹配中的边并重新求匹配来判断。保存首次得到的匹配 $\textit{baseMat}$ 至关重要，后续每次匹配必须使用独立的临时数组接收结果，才能确保每次禁止的都是同一个原始完美匹配中的边。
