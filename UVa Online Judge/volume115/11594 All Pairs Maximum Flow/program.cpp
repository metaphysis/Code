// All Pairs Maximum Flow
// UVa ID: 11594
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

struct Dinic {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

    vector<vector<Edge>> graph;
    vector<int> level, ptr;
    int n;

    Dinic(int n) : n(n), graph(n), level(n), ptr(n) {}

    void addEdge(int from, int to, int cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap, 0});
        graph[to].push_back({from, (int)graph[from].size() - 1, cap, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge& e : graph[u]) {
                if (level[e.to] == -1 && e.flow < e.cap) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int& cid = ptr[u]; cid < graph[u].size(); cid++) {
            Edge& e = graph[u][cid];
            if (level[e.to] == level[u] + 1 && e.flow < e.cap) {
                int tr = dfs(e.to, t, min(pushed, e.cap - e.flow));
                if (tr > 0) {
                    e.flow += tr;
                    graph[e.to][e.rev].flow -= tr;
                    return tr;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        for (auto& edges : graph) {
            for (Edge& e : edges) {
                e.flow = 0;
            }
        }
        int flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, t, INT_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

struct GomoryHuTree {
    int n;
    vector<vector<int>> tree;
    vector<vector<pair<int, int>>> adj;

    GomoryHuTree(int n) : n(n), tree(n, vector<int>(n, 0)), adj(n) {}

    void build(Dinic& dinic) {
        vector<int> parent(n, 0);
        for (int i = 1; i < n; i++) {
            int flow = dinic.maxFlow(i, parent[i]);
            
            // 更新树结构
            adj[i].emplace_back(parent[i], flow);
            adj[parent[i]].emplace_back(i, flow);
            
            // 更新后续节点的父节点
            for (int j = i + 1; j < n; j++) {
                if (dinic.level[j] != -1 && parent[j] == parent[i]) {
                    parent[j] = i;
                }
            }
        }
        
        // 使用BFS计算所有点对在树上的最小边权
        for (int i = 0; i < n; i++) {
            vector<int> minCapacity(n, INT_MAX);
            minCapacity[i] = INT_MAX; // 自己到自己的容量应该是无穷大，但题目要求对角线为0
            
            queue<int> q;
            q.push(i);
            vector<bool> visited(n, false);
            visited[i] = true;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int cap = edge.second;
                    
                    if (!visited[v]) {
                        visited[v] = true;
                        // 路径上的最小容量是当前路径最小容量和当前边容量的较小值
                        minCapacity[v] = min(minCapacity[u], cap);
                        q.push(v);
                    }
                }
            }
            
            // 填充结果矩阵
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    tree[i][j] = 0; // 对角线为0
                } else {
                    tree[i][j] = minCapacity[j];
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    for (int caseIdx = 1; caseIdx <= numCases; caseIdx++) {
        int n;
        cin >> n;
        vector<vector<int>> capacity(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> capacity[i][j];
            }
        }

        cout << "Case #" << caseIdx << ":\n";
        if (n == 0) {
            continue;
        }
        if (n == 1) {
            cout << "0\n";
            continue;
        }

        Dinic dinic(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (capacity[i][j] > 0) {
                    dinic.addEdge(i, j, capacity[i][j]);
                }
            }
        }

        GomoryHuTree gomoryHu(n);
        gomoryHu.build(dinic);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j > 0) cout << " ";
                cout << gomoryHu.tree[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}
