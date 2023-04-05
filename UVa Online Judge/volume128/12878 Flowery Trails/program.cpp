// Flowery Trails
// UVa ID: 12878
// Verdict: Accepted
// Submission Date: 2023-04-05
// UVa Run Time: 0.690s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010, MAXE = 500010, INF = 0x3f3f3f3f;

struct edge {
    int v, w, nxt;
} g[MAXE];

int P, T, head[MAXN], cnt, d[MAXN], visited[MAXN];

void add(int u, int v, int w) {
    g[cnt] = edge{v, w, head[u]};
    head[u] = cnt++;
    g[cnt] = edge{u, w, head[v]};
    head[v] = cnt++;
};

struct block {
    int v, w;
    bool operator<(const block &b) const { return w > b.w; }
};

vector<pair<int, int>> parent[MAXN];

int sum = 0;

void dfs(int u) {
    visited[u] = 1;
    for (auto p : parent[u]) {
        sum += p.second;
        if (!visited[p.first])
            dfs(p.first);
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> P >> T) {
        for (int i = 0; i < P; i++) {
            head[i] = -1;
            visited[i] = 0;
            d[i] = INF;
            parent[i].clear();
        }
        cnt = 0;
        for (int i = 0, u, v, w; i < T; i++) {
            cin >> u >> v >> w;
            add(u, v, w);
        }
        d[0] = 0;
        priority_queue<block> q;
        q.push(block{0, 0});
        while (!q.empty()) {
            block b = q.top(); q.pop();
            if (d[b.v] < b.w) continue;
            for (int i = head[b.v]; ~i; i = g[i].nxt)
                if (d[g[i].v] > d[b.v] + g[i].w) {
                    d[g[i].v] = d[b.v] + g[i].w;
                    parent[g[i].v].clear();
                    parent[g[i].v].push_back(make_pair(b.v, g[i].w));
                    q.push(block{g[i].v, d[g[i].v]});
                } else if (d[g[i].v] == d[b.v] + g[i].w)
                    parent[g[i].v].push_back(make_pair(b.v, g[i].w));
        }
        sum = 0;
        dfs(P - 1);
        cout << sum * 2LL << '\n';
    }
    return 0;
}
