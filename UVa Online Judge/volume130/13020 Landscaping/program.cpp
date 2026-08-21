#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

class Dinic {
private:
    int size;
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const Edge &e : graph[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    long long dfs(int v, int t, long long flow) {
        if (v == t) return flow;
        for (int &i = iter[v]; i < (int)graph[v].size(); i++) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                long long ret = dfs(e.to, t, min(flow, e.cap));
                if (ret > 0) {
                    e.cap -= ret;
                    graph[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int n) : size(n), graph(n), level(n), iter(n) {}
    void addEdge(int u, int v, long long cap) {
        int ru = graph[u].size(), rv = graph[v].size();
        graph[u].push_back({v, rv, cap});
        graph[v].push_back({u, ru, 0});
    }
    long long maxFlow(int s, int t) {
        long long ans = 0, flow;
        const long long inf = 1LL << 60;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while ((flow = dfs(s, t, inf)) > 0)
                ans += flow;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, b;
    while (cin >> n >> m >> a >> b) {
        vector<string> field(n);
        for (string &row : field)
            cin >> row;
        int s = n * m, t = s + 1;
        Dinic dinic(t + 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int id = i * m + j;
                if (field[i][j] == '.')
                    dinic.addEdge(id, t, b);
                else
                    dinic.addEdge(s, id, b);
                if (i + 1 < n) {
                    int next = (i + 1) * m + j;
                    dinic.addEdge(id, next, a);
                    dinic.addEdge(next, id, a);
                }
                if (j + 1 < m) {
                    int next = i * m + j + 1;
                    dinic.addEdge(id, next, a);
                    dinic.addEdge(next, id, a);
                }
            }
        }
        cout << dinic.maxFlow(s, t) << '\n';
    }
    return 0;
}
