// Always Late
// UVa ID: 10342
// Verdict: Accepted
// Submission Date: 2023-04-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 20010, INF = 0x3f3f3f3f;

int n, m;
int cnt, head[MAXV];
int dist[MAXV], visited[MAXV];

struct edge { int v, w, next; } g[MAXE];
struct state {
    int u, fx;
    bool operator < (const state &s) const { return fx > s.fx; }
};

void clearEdge() {
    cnt = 0;
    memset(head, -1, sizeof head);
}

void addEdge(int u, int v, int w) {
    g[cnt] = edge{v, w, head[u]};
    head[u] = cnt++;
    g[cnt] = edge{u, w, head[v]};
    head[v] = cnt++;
}

priority_queue<state> q;

int ksp(int s, int t, int k) {
    for (int i = 0; i < n; i++) dist[i] = INF, visited[i] = 0;
    int u = t;
    dist[u] = 0;
    while (!visited[u]) {
        visited[u] = 1;
        for (int i = head[u]; ~i; i = g[i].next)
            if (!visited[g[i].v] && dist[g[i].v] > dist[u] + g[i].w)
                dist[g[i].v] = dist[u] + g[i].w;
        int least = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < least)
                least = dist[i], u = i;
    }
    if (dist[s] == INF) return -1;
    while (!q.empty()) q.pop();
    q.push(state{s, dist[s]});
    while (!q.empty()) {
        state ste = q.top(); q.pop();
        int walked = ste.fx - dist[ste.u];
        if (ste.u == t && walked != dist[s])
            return walked;
        for (int i = head[ste.u]; ~i; i = g[i].next)
            q.push(state{g[i].v, walked + g[i].w + dist[g[i].v]});
    }
    return -1;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int s, t, q, cases = 1;
    while (cin >> n >> m) {
        cout << "Set #" << cases++ << '\n';
        clearEdge();
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            addEdge(u, v, w);
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            cin >> s >> t;
            int r = ksp(s, t, 2);
            if (r == -1) cout << '?';
            else cout << r;
            cout << '\n';
        }
    }
    return 0;
}
