// Earthquake Disaster
// UVa ID: 12944
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.030s

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap, cost;
};

vector<vector<Edge>> g;

void addEdge(int v, int to, int cap, int cost) {
    Edge a{to, (int)g[to].size(), cap, cost};
    Edge b{v, (int)g[v].size(), 0, -cost};
    g[v].push_back(a);
    g[to].push_back(b);
}

pair<int, int> minCostMaxFlow(int s, int t) {
    int flow = 0, cost = 0;
    const int INF = 1e9;
    int n = (int)g.size();
    while (true) {
        vector<int> dist(n, INF), pv(n, -1), pe(n, -1);
        vector<bool> inq(n, false);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        inq[s] = true;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            inq[v] = false;
            for (int i = 0; i < (int)g[v].size(); ++i) {
                Edge &e = g[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    pv[e.to] = v;
                    pe[e.to] = i;
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if (dist[t] == INF) break;
        int add = INF;
        for (int v = t; v != s; v = pv[v])
            add = min(add, g[pv[v]][pe[v]].cap);
        flow += add;
        cost += add * dist[t];
        for (int v = t; v != s; v = pv[v]) {
            Edge &e = g[pv[v]][pe[v]];
            e.cap -= add;
            g[v][e.rev].cap += add;
        }
    }
    return {flow, cost};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    while (cin >> N >> M) {
        g.assign(N + 1, vector<Edge>());
        for (int i = 1; i <= N - 1; ++i) {
            int t;
            cin >> t;
            addEdge(0, i, t, 0);
        }
        for (int i = 0; i < M; ++i) {
            int a, b, w, c;
            cin >> a >> b >> w >> c;
            addEdge(a, b, w, c);
            addEdge(b, a, w, c);
        }
        auto ans = minCostMaxFlow(0, N);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}
