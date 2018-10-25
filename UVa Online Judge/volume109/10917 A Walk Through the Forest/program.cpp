// A Walk Through the Forest
// UVa ID: 10917
// Verdict: Accepted
// Submission Date: 2018-10-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator < (const edge &e) const { return w > e.w; }
};

int N, M;
list<edge> edges[1001];
int d[1001], dp[1001];

void mooreDijkstra()
{
    memset(d, 0x3f, sizeof(d));
    priority_queue<edge> q;
    q.push(edge(2, d[2] = 0));
    while (!q.empty())
    {
        edge a = q.top(); q.pop();
        if (d[a.v] < a.w) continue;
        for (auto b : edges[a.v])
        {
            if (d[b.v] > d[a.v] + b.w)
            {
                d[b.v] = d[a.v] + b.w;
                q.push(edge(b.v, d[b.v]));
            }
        }
    }
    
}

int dfs(int u)
{
    if (~dp[u]) return dp[u];
    int r = 0;
    for (auto a : edges[u])
        if (d[a.v] < d[u])
            r += dfs(a.v);
    return dp[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N)
    {
        if (N == 0) break;
        cin >> M;
        for (int i = 1; i <= N; i++)
            edges[i].clear();
        for (int i = 1, u, v, w; i <= M; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
        }
        mooreDijkstra();
        memset(dp, -1, sizeof(dp));
        cout << dfs(dp[2] = 1) << '\n';
    }

    return 0;
}
