// Trucks
// UVa ID: 12655
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;
const int MAXM = 100005;
const int MAXLOG = 16; // 因为 N <= 20000, 2^15 > 20000

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w; // 按权值从大到小排序，用于最大生成树
    }
};

Edge edges[MAXM];
vector<pair<int, int>> tree[MAXN]; // 最大生成树 (to, weight)
int parent[MAXN];
int depth[MAXN];
int up[MAXN][MAXLOG];
int minEdge[MAXN][MAXLOG];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;
    parent[rx] = ry;
    return true;
}

void dfs(int u, int p, int w, int d) {
    depth[u] = d;
    up[u][0] = p;
    minEdge[u][0] = w;
    for (int i = 1; i < MAXLOG; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
        minEdge[u][i] = min(minEdge[u][i-1], minEdge[up[u][i-1]][i-1]);
    }
    for (auto& e : tree[u]) {
        int v = e.first, weight = e.second;
        if (v != p) {
            dfs(v, u, weight, d + 1);
        }
    }
}

int query(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int res = 1e9;
    // 提升 a 到与 b 同一深度
    int diff = depth[a] - depth[b];
    for (int i = 0; i < MAXLOG; i++) {
        if (diff & (1 << i)) {
            res = min(res, minEdge[a][i]);
            a = up[a][i];
        }
    }
    if (a == b) return res;
    // 一起向上跳
    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (up[a][i] != up[b][i]) {
            res = min(res, minEdge[a][i]);
            res = min(res, minEdge[b][i]);
            a = up[a][i];
            b = up[b][i];
        }
    }
    res = min(res, minEdge[a][0]);
    res = min(res, minEdge[b][0]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, S;
    while (cin >> N >> M >> S) {
        for (int i = 0; i < M; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        // Kruskal 最大生成树
        sort(edges, edges + M);
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
            tree[i].clear();
        }
        for (int i = 0; i < M; i++) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            if (unite(u, v)) {
                tree[u].push_back({v, w});
                tree[v].push_back({u, w});
            }
        }
        // DFS 预处理
        memset(up, 0, sizeof(up));
        memset(minEdge, 0x3f, sizeof(minEdge));
        dfs(1, 1, 1e9, 0); // 根节点为1，父节点为1，边权设为无穷大（实际不会用到根节点的minEdge）
        // 处理查询
        for (int i = 0; i < S; i++) {
            int L, H;
            cin >> L >> H;
            cout << query(L, H) << "\n";
        }
    }
    return 0;
}
