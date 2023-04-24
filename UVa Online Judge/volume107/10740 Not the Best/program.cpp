// Not the Best
// UVa ID: 10740
// Verdict: Accepted
// Submission Date: 2020-05-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 100010, INF = 0x3f3f3f3f;

int n, m;
int cnt, head[MAXV];
int dist[MAXV], visited[MAXV];

struct edge { int v, w, next; } edges[MAXE];
struct state {
    int u, fx;
    bool operator < (const state &s) const { return fx > s.fx; }
};

void clearEdge() {
    cnt = 0;
    memset(head, -1, sizeof head);
}

void addEdge(int u, int v, int w) {
    edges[cnt] = edge{v, w, head[u]};
    head[u] = cnt++;
}

priority_queue<state> q;

int ksp(vector<tuple<int, int, int>> &data, int s, int t, int k) {
    clearEdge();
    for (auto d : data) addEdge(get<1>(d), get<0>(d), get<2>(d));

    for (int i = 0; i < n; i++) dist[i] = INF, visited[i] = 0;
    int u = t;
    dist[u] = 0;
    while (!visited[u]) {
        visited[u] = 1;
        for (int i = head[u]; ~i; i = edges[i].next)
            if (!visited[edges[i].v] && dist[edges[i].v] > dist[u] + edges[i].w)
                dist[edges[i].v] = dist[u] + edges[i].w;
        int least = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < least)
                least = dist[i], u = i;
            
    }

    clearEdge();
    for (auto d : data) addEdge(get<0>(d), get<1>(d), get<2>(d));

    while (!q.empty()) q.pop();
    q.push(state{s, dist[s]});
    while (!q.empty()) {
        state s = q.top(); q.pop();
        int walked = s.fx - dist[s.u];
        if (s.u == t)
            if (!(--k))
                return walked;
        for (int i = head[s.u]; ~i; i = edges[i].next)
            q.push(state{edges[i].v, walked + edges[i].w + dist[edges[i].v]});
    }
    return -1;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int s, t, k;
    vector<tuple<int, int, int>> data;
    while (cin >> n >> m)
    {
        if (n == 0) break;
        data.clear();
        cin >> s >> t >> k;
        s--, t--;
        for (int i = 0, u, v, w; i < m; i++)
        {
            cin >> u >> v >> w;
            u--, v--;
            data.push_back(make_tuple(u, v, w));
        }
        cout << ksp(data, s, t, k) << '\n';
    }

    return 0;
}
