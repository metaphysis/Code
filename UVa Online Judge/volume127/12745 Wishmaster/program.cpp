// Wishmaster
// UVa ID: 12745
// Verdict: Accepted
// Submission Date: 2026-06-11
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> graph[2 * MAXN];
int dfn[2 * MAXN], low[2 * MAXN], scc[2 * MAXN], stk[2 * MAXN];
bool inStack[2 * MAXN];
int dfsClock, sccCnt, top;

// 将文字转换为节点编号
// 正数 x 表示 x 为真 -> 节点 x
// 负数 x 表示 -x 为真 -> 节点 (-x) + n
inline int litToNode(int x) {
    if (x > 0) return x;
    else return -x + n;
}

// 取反
inline int negNode(int node, int n) {
    if (node <= n) return node + n;
    else return node - n;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfsClock;
    stk[++top] = u;
    inStack[u] = true;
    for (int v : graph[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        int v;
        do {
            v = stk[top--];
            inStack[v] = false;
            scc[v] = sccCnt;
        } while (v != u);
    }
}

bool solve() {
    dfsClock = sccCnt = top = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        dfn[i] = low[i] = scc[i] = inStack[i] = 0;
        graph[i].clear();
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int na = litToNode(a), nb = litToNode(b);
        int notNa = negNode(na, n), notNb = negNode(nb, n);
        // a -> not b
        graph[na].push_back(notNb);
        // b -> not a
        graph[nb].push_back(notNa);
    }
    for (int i = 1; i <= 2 * n; ++i) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i) if (scc[i] == scc[i + n]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cin >> n >> m;
        bool ok = solve();
        cout << "Case " << cas << ": " << (ok ? "Yes" : "No") << "\n";
    }
    return 0;
}
