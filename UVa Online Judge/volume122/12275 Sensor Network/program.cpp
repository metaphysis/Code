// Sensor Network
// UVa ID: 12275
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 2.290s

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) { parent.resize(n); rank.resize(n, 0); for (int i = 0; i < n; ++i) parent[i] = i; }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) { int ra = find(a), rb = find(b); if (ra == rb) return false; if (rank[ra] < rank[rb]) swap(ra, rb); parent[rb] = ra; if (rank[ra] == rank[rb]) ++rank[ra]; return true; }
};

// 在树中查找从 u 到 v 路径上的最大边，返回该边（若不存在则 w=-1）
Edge findMaxEdgeOnPath(int u, int v, const vector<vector<pair<int,int>>>& tree, int parent, int curMaxW, int maxEdgeU, int maxEdgeV) {
    // 递归实现，但为了简洁，使用迭代DFS并记录前驱
    // 由于 n 很小，可以用简单DFS
    int n = tree.size();
    vector<int> visited(n, 0), parentNode(n, -1), parentEdgeW(n, 0);
    stack<int> st;
    st.push(u);
    visited[u] = 1;
    while (!st.empty()) {
        int x = st.top(); st.pop();
        if (x == v) break;
        for (auto &pr : tree[x]) {
            int y = pr.first, w = pr.second;
            if (!visited[y]) {
                visited[y] = 1;
                parentNode[y] = x;
                parentEdgeW[y] = w;
                st.push(y);
            }
        }
    }
    // 回溯路径得到最大边
    int maxW = -1, maxU = -1, maxV = -1;
    int cur = v;
    while (cur != u) {
        int p = parentNode[cur];
        int w = parentEdgeW[cur];
        if (w > maxW) { maxW = w; maxU = p; maxV = cur; }
        cur = p;
    }
    return {maxU, maxV, maxW};
}

// 从树中删除一条无向边
void removeEdgeFromTree(vector<vector<pair<int,int>>>& tree, int u, int v) {
    for (auto it = tree[u].begin(); it != tree[u].end(); ++it) {
        if (it->first == v) { tree[u].erase(it); break; }
    }
    for (auto it = tree[v].begin(); it != tree[v].end(); ++it) {
        if (it->first == u) { tree[v].erase(it); break; }
    }
}

// 从树边列表删除指定边（端点无序）
void removeEdgeFromList(vector<Edge>& treeEdges, int u, int v) {
    for (auto it = treeEdges.begin(); it != treeEdges.end(); ++it) {
        if ((it->u == u && it->v == v) || (it->u == v && it->v == u)) {
            treeEdges.erase(it);
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        int m;
        cin >> m;
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.w > b.w;
        });
        DSU dsu(n);
        vector<vector<pair<int,int>>> tree(n);
        vector<Edge> treeEdges;
        int ans = INT_MAX;
        int idx = 0;
        while (idx < m) {
            int curW = edges[idx].w;
            // 处理所有权重为 curW 的边
            while (idx < m && edges[idx].w == curW) {
                Edge e = edges[idx];
                int ru = dsu.find(e.u), rv = dsu.find(e.v);
                if (ru != rv) {
                    // 直接加入生成树
                    dsu.unite(ru, rv);
                    tree[e.u].push_back({e.v, e.w});
                    tree[e.v].push_back({e.u, e.w});
                    treeEdges.push_back(e);
                } else {
                    // 同一分量，查找环上的最大边
                    Edge maxEdge = findMaxEdgeOnPath(e.u, e.v, tree, -1, -1, -1, -1);
                    if (maxEdge.w > e.w) {
                        // 替换
                        removeEdgeFromTree(tree, maxEdge.u, maxEdge.v);
                        removeEdgeFromList(treeEdges, maxEdge.u, maxEdge.v);
                        tree[e.u].push_back({e.v, e.w});
                        tree[e.v].push_back({e.u, e.w});
                        treeEdges.push_back(e);
                    }
                }
                ++idx;
            }
            // 当前权重组处理完毕，若已连通则更新答案
            if ((int)treeEdges.size() == n - 1) {
                int curMax = 0;
                for (const Edge& ed : treeEdges) if (ed.w > curMax) curMax = ed.w;
                ans = min(ans, curMax - curW);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
