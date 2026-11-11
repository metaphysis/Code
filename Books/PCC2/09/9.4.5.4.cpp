#include <bits/stdc++.h>
using namespace std;

const int MAXV = 100010;
const int MAXD = 20;
const int MAXE = 2 * MAXV + 5;

struct edge {
    int u, v, next;
};

edge data[MAXE];
int idx, head[MAXV];
int ancestor[MAXV][MAXD], depth[MAXV], visited[MAXV];

// 添加有向边
void addEdge(int u, int v) {
    data[idx] = {u, v, head[u]};
    head[u] = idx++;
}

// 迭代 DFS，计算父节点和深度
void dfs(int root) {
    stack<int> st;
    st.push(root);
    visited[root] = 1;
    ancestor[root][0] = -1;
    depth[root] = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        for (int i = head[u]; i != -1; i = data[i].next) {
            int v = data[i].v;
            if (!visited[v]) {
                visited[v] = 1;
                ancestor[v][0] = u;
                depth[v] = depth[u] + 1;
                st.push(v);
            }
        }
    }
}

// 求最近公共祖先
int getLCA(int u, int v) {
    // 保证 u 更深
    if (depth[u] < depth[v]) swap(u, v);
    // 将 u 跳到与 v 同深度
    int diff = depth[u] - depth[v];
    for (int d = 0; d < MAXD; d++) {
        if (diff & (1 << d)) {
            u = ancestor[u][d];
        }
    }
    if (u == v) return u;
    // 两者同时向上跳，直到 LCA 的下一层
    for (int d = MAXD - 1; d >= 0; d--) {
        if (ancestor[u][d] != -1 && ancestor[u][d] != ancestor[v][d]) {
            u = ancestor[u][d];
            v = ancestor[v][d];
        }
    }
    return ancestor[u][0];
}

int main() {
    int n, q;
    while (cin >> n && n) {
        idx = 0;
        memset(head, -1, sizeof(head));
        // 读入 n-1 条无向边
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            addEdge(u, v);
            addEdge(v, u);
        }
        memset(ancestor, -1, sizeof(ancestor));
        memset(visited, 0, sizeof(visited));
        memset(depth, 0, sizeof(depth));
        // 以 1 为根建树
        dfs(1);
        // 倍增预处理
        for (int d = 1; d < MAXD; d++) {
            for (int u = 0; u <= n; u++) {
                if (ancestor[u][d - 1] != -1) {
                    ancestor[u][d] = ancestor[ancestor[u][d - 1]][d - 1];
                }
            }
        }
        cin >> q;
        // 处理查询
        for (int i = 0, u, v; i < q; i++) {
            cin >> u >> v;
            cout << getLCA(u, v) << '\n';
        }
    }
    return 0;
}
