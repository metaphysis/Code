// The Gossipy Gossipers Gossip Gossips
// UVa ID: 10850
// Verdict: Accepted
// Submission Date: 2021-12-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int v, t;
    edge (int v = 0, int t = 0): v(v), t(t) {}
};

struct package
{
    int u, t1, t2;
    package (int u = 0, int t1 = 0, int t2 = 0): u(u), t1(t1), t2(t2) {}
};

int visited[32];
vector<edge> edges[32];

void dfs(int u)
{
    visited[u] = 1;
    for (auto e : edges[u])
        if (!visited[e.v])
            dfs(e.v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int M, K, G1, G2, V;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> M >> K;
        assert(M > 0);
        for (int i = 1; i <= M; i++)
            edges[i].clear();
        for (int i = 1; i <= K; i++)
        {
            cin >> G1 >> G2 >> V;
            for (int j = 0, t; j < V; j++)
            {
                cin >> t;
                edges[G1].push_back(edge(G2, t));
                edges[G2].push_back(edge(G1, t));
            }
        }
        memset(visited, 0, sizeof visited);
        dfs(1);
        if (accumulate(visited + 1, visited + 1 + M, 0) != M)
        {
            cout << "-1\n";
            continue;
        }
        int instant[32];
        memset(instant, 0x3f, sizeof instant);
        queue<package> q;
        q.push(package(1, 0, 0));
        instant[1] = 0;
        while (!q.empty())
        {
            package p = q.front();
            q.pop();
            for (auto e : edges[p.u])
            {
                if (p.t1 <= e.t && p.t2 * 100 + e.t < instant[e.v])
                {
                    instant[e.v] = p.t2 * 100 + e.t;
                    q.push(package(e.v, e.t, p.t2));
                }
                if (p.t1 > e.t) q.push(package(p.u, 0, p.t2 + 1));
            }
        }
        cout << *max_element(instant + 1, instant + 1 + M) << '\n';
    }

    return 0;
}
