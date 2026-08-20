// The Sultan's Feast
// UVa ID: 11390
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.650s

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int to, rev, cap;
};

class Dinic {
public:
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;
    Dinic(int n) : n(n), g(n), level(n), iter(n) {}
    void addEdge(int from, int to, int cap) {
        Edge a{to, (int)g[to].size(), cap};
        Edge b{from, (int)g[from].size(), 0};
        g[from].push_back(a);
        g[to].push_back(b);
    }
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (Edge &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<int> l(N + 1);
        vector<vector<int>> adj(N + 1);
        int sumPos = 0;
        for (int i = 1; i <= N; ++i) {
            int r;
            cin >> l[i] >> r;
            if (l[i] > 0) sumPos += l[i];
            adj[i].resize(r);
            for (int j = 0; j < r; ++j) cin >> adj[i][j];
        }
        int ans = -INF;
        int S = 0, Tnode = N + 1;
        for (int must = 1; must <= N; ++must) {
            Dinic din(N + 2);
            for (int i = 1; i <= N; ++i) {
                if (l[i] > 0) din.addEdge(S, i, l[i]);
                else if (l[i] < 0) din.addEdge(i, Tnode, -l[i]);
            }
            for (int u = 1; u <= N; ++u) {
                for (int v : adj[u]) {
                    din.addEdge(u, v, INF);
                }
            }
            din.addEdge(S, must, INF);
            int minCut = din.maxFlow(S, Tnode);
            int maxWeight = sumPos - minCut;
            ans = max(ans, maxWeight);
        }
        cout << "Case #" << tc << ": ";
        if (ans < 0) cout << "Alas, sultan can't invite anyone!\n";
        else cout << ans << '\n';
    }
    return 0;
}
