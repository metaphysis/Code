#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

class Dinic {
private:
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e : g[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }
    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                int add = dfs(e.to, t, min(flow, e.cap));
                if (add > 0) {
                    e.cap -= add;
                    g[e.to][e.rev].cap += add;
                    return add;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int n) : n(n), g(n), level(n), it(n) {}
    int addEdge(int u, int v, int cap) {
        int id = g[u].size();
        Edge a = {v, (int)g[v].size(), cap};
        Edge b = {u, id, 0};
        g[u].push_back(a);
        g[v].push_back(b);
        return id;
    }
    int getCap(int u, int id) {
        return g[u][id].cap;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                int add = dfs(s, t, 1e9);
                if (add == 0) break;
                flow += add;
            }
        }
        return flow;
    }
};

bool reroute(int si, int sj, int t, int p, const vector<vector<int>> &active, vector<vector<int>> &match) {
    int total = t + p, target = t + sj;
    vector<int> parent(total, -1);
    queue<int> q;
    parent[si] = -2;
    q.push(si);
    while (!q.empty() && parent[target] == -1) {
        int u = q.front();
        q.pop();
        if (u < t) {
            for (int j = 0; j < p; j++) {
                if (!active[u][j] || match[u][j]) continue;
                if (u == si && j == sj) continue;
                int v = t + j;
                if (parent[v] != -1) continue;
                parent[v] = u;
                q.push(v);
            }
        } else {
            int j = u - t;
            for (int i = 0; i < t; i++) {
                if (!active[i][j] || !match[i][j]) continue;
                if (i == si && j == sj) continue;
                if (parent[i] != -1) continue;
                parent[i] = u;
                q.push(i);
            }
        }
    }
    if (parent[target] == -1) return false;
    int cur = target;
    while (cur != si) {
        int pre = parent[cur];
        if (pre < t)
            match[pre][cur - t] = 1;
        else
            match[cur][pre - t] = 0;
        cur = pre;
    }
    match[si][sj] = 0;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, p;
    bool first = true;
    while (cin >> t >> p && (t || p)) {
        vector<int> rowNeed(t), colNeed(p);
        int sumRow = 0, sumCol = 0;
        for (int i = 0; i < t; i++) {
            cin >> rowNeed[i];
            sumRow += rowNeed[i];
        }
        for (int j = 0; j < p; j++) {
            cin >> colNeed[j];
            sumCol += colNeed[j];
        }
        if (!first) cout << '\n';
        first = false;
        if (sumRow != sumCol) {
            cout << "Impossible\n";
            continue;
        }
        int s = t + p, z = s + 1;
        Dinic dinic(z + 1);
        for (int i = 0; i < t; i++)
            dinic.addEdge(s, i, rowNeed[i]);
        for (int j = 0; j < p; j++)
            dinic.addEdge(t + j, z, colNeed[j]);
        vector<vector<int>> edgeId(t, vector<int>(p));
        for (int i = 0; i < t; i++)
            for (int j = 0; j < p; j++)
                edgeId[i][j] = dinic.addEdge(i, t + j, 1);
        if (dinic.maxFlow(s, z) != sumRow) {
            cout << "Impossible\n";
            continue;
        }
        vector<vector<int>> active(t, vector<int>(p, 1));
        vector<vector<int>> match(t, vector<int>(p, 0));
        vector<string> ans(t, string(p, 'N'));
        for (int i = 0; i < t; i++)
            for (int j = 0; j < p; j++)
                if (dinic.getCap(i, edgeId[i][j]) == 0)
                    match[i][j] = 1;
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < p; j++) {
                if (!match[i][j]) {
                    active[i][j] = 0;
                    continue;
                }
                if (reroute(i, j, t, p, active, match)) {
                    active[i][j] = 0;
                    continue;
                }
                ans[i][j] = 'Y';
                active[i][j] = 0;
                match[i][j] = 0;
            }
        }
        for (int i = 0; i < t; i++)
            cout << ans[i] << '\n';
    }
    return 0;
}
