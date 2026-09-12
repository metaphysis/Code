#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, d;
};

struct Point {
    int x, y;
};

void dfs1(int u, const vector<vector<int>>& graph, vector<char>& vis, vector<int>& order) {
    vis[u] = 1;
    for (int v : graph[u])
        if (!vis[v]) dfs1(v, graph, vis, order);
    order.push_back(u);
}

void dfs2(int u, int id, const vector<vector<int>>& revGraph, vector<int>& comp) {
    comp[u] = id;
    for (int v : revGraph[u])
        if (comp[v] == -1) dfs2(v, id, revGraph, comp);
}

bool checkSat(int n, int flip, const vector<int>& x, const vector<int>& y, const vector<int>& parity, const vector<Edge>& edges) {
    int sz = 2 * (n + 1);
    vector<array<Point, 2>> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int cur = parity[i] ^ flip, base = (x[i] + y[i]) & 1;
        if (cur == base) {
            pos[i][0] = {x[i], y[i]};
            pos[i][1] = {x[i] + 1, y[i] + 1};
        } else {
            pos[i][0] = {x[i] + 1, y[i]};
            pos[i][1] = {x[i], y[i] + 1};
        }
    }
    vector<int> deg(sz), revDeg(sz);
    for (const Edge& edge : edges) {
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                int dis = abs(pos[edge.u][a].x - pos[edge.v][b].x) + abs(pos[edge.u][a].y - pos[edge.v][b].y);
                if (dis == edge.d) continue;
                int lu = 2 * edge.u + (1 - a), lv = 2 * edge.v + (1 - b);
                int from1 = lu ^ 1, from2 = lv ^ 1;
                deg[from1]++;
                revDeg[lv]++;
                deg[from2]++;
                revDeg[lu]++;
            }
        }
    }
    vector<vector<int>> graph(sz), revGraph(sz);
    for (int i = 0; i < sz; i++) {
        graph[i].reserve(deg[i]);
        revGraph[i].reserve(revDeg[i]);
    }
    for (const Edge& edge : edges) {
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                int dis = abs(pos[edge.u][a].x - pos[edge.v][b].x) + abs(pos[edge.u][a].y - pos[edge.v][b].y);
                if (dis == edge.d) continue;
                int lu = 2 * edge.u + (1 - a), lv = 2 * edge.v + (1 - b);
                int from1 = lu ^ 1, from2 = lv ^ 1;
                graph[from1].push_back(lv);
                revGraph[lv].push_back(from1);
                graph[from2].push_back(lu);
                revGraph[lu].push_back(from2);
            }
        }
    }
    vector<char> vis(sz, 0);
    vector<int> order, comp(sz, -1);
    order.reserve(sz);
    for (int i = 0; i < sz; i++)
        if (!vis[i]) dfs1(i, graph, vis, order);
    int id = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == -1) dfs2(u, id++, revGraph, comp);
    }
    for (int i = 1; i <= n; i++)
        if (comp[2 * i] == comp[2 * i + 1]) return false;
    return true;
}

bool solveCase() {
    int n, m;
    cin >> n;
    vector<int> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    cin >> m;
    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].d;
        int need = edges[i].d & 1;
        graph[edges[i].u].push_back({edges[i].v, need});
        graph[edges[i].v].push_back({edges[i].u, need});
    }
    vector<int> parity(n + 1, -1), compId(n + 1, -1);
    vector<vector<int>> comps;
    for (int start = 1; start <= n; start++) {
        if (parity[start] != -1) continue;
        int cid = (int)comps.size();
        queue<int> que;
        comps.push_back({});
        parity[start] = 0;
        compId[start] = cid;
        que.push(start);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            comps[cid].push_back(u);
            for (const auto& item : graph[u]) {
                int v = item.first, need = parity[u] ^ item.second;
                if (parity[v] == -1) {
                    parity[v] = need;
                    compId[v] = cid;
                    que.push(v);
                } else if (parity[v] != need) {
                    return false;
                }
            }
        }
    }
    for (int cid = 0; cid < (int)comps.size(); cid++) {
        int k = (int)comps[cid].size();
        vector<int> localId(n + 1, -1), localX(k + 1), localY(k + 1), localParity(k + 1);
        for (int i = 0; i < k; i++) {
            int u = comps[cid][i], id = i + 1;
            localId[u] = id;
            localX[id] = x[u];
            localY[id] = y[u];
            localParity[id] = parity[u];
        }
        vector<Edge> localEdges;
        for (const Edge& edge : edges) {
            if (compId[edge.u] != cid) continue;
            localEdges.push_back({localId[edge.u], localId[edge.v], edge.d});
        }
        if (!checkSat(k, 0, localX, localY, localParity, localEdges) &&
            !checkSat(k, 1, localX, localY, localParity, localEdges))
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        if (solveCase()) cout << "possible\n";
        else cout << "impossible\n";
    }
    return 0;
}
