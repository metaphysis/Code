// Chemical Plant
// UVa ID: 12138
// Verdict: Accepted
// Submission Date: 2023-05-28
// UVa Run Time: 0.55s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010, MAXE = 600010, INF = 2000000000;

int V, E, W, S, T;
int n, d[MAXE];

map<int, int> idx[MAXV];

struct tube { int u, v, sst, sct, dst, dct; } tb[MAXE];

int head[MAXE], cnt = 0;

struct edge { int v, w, nxt; } g[MAXE];

struct walk {
    int v, w;
    bool operator<(const walk &wk) const { return w > wk.w; }
};

void addEdge(int u, int v, int w) {
    g[cnt] = edge{v, w, head[u]};
    head[u] = cnt++;
}

void mooreDijkstra(int u) {
    for (int i = 0; i <= n; i++) d[i] = INF;
    d[u] = 0;
    priority_queue<walk> q;
    q.push(walk{u, d[u]});
    while (!q.empty()) {
        walk wk = q.top(); q.pop();
        for (int i = head[wk.v]; ~i; i = g[i].nxt) {
            edge e = g[i];
            if (d[e.v] > d[wk.v] + e.w) {
                d[e.v] = d[wk.v] + e.w;
                q.push(walk{e.v, d[e.v]});
            }
        }
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> V >> E >> W, V) {
        cin >> S >> T;
        for (int i = 0; i < E; i++) {
            cin >> tb[i].u >> tb[i].v >> tb[i].sst >> tb[i].sct >> tb[i].dst >> tb[i].dct;
            idx[tb[i].u][tb[i].sst] = 0;
            idx[tb[i].v][tb[i].dct] = 0;
        }
        cnt = n = 0;
        idx[1][0] = 0;
        idx[S][T] = 0;
        memset(head, -1, sizeof head);
        for (int i = 1; i <= V; i++) {
            int last = -1;
            for (auto &p : idx[i]) {
                p.second = ++n;
                if (~last) addEdge(n - 1, n, p.first - last);
                last = p.first;
            }
        }
        for (int i = 0; i < E; i++) addEdge(idx[tb[i].u][tb[i].sst], idx[tb[i].v][tb[i].dct], tb[i].sct - tb[i].sst + tb[i].dct - tb[i].dst);
        mooreDijkstra(idx[1][0]);
        cout << "Plant " << cases++ << ": ";
        W -= d[idx[S][T]];
        cout << (W < 0 ? 0 : W) << '\n';
        for (int i = 1; i <= V; i++) idx[i].clear();
    }
    return 0;
}
