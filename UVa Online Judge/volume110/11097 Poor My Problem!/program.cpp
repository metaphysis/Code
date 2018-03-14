// Poor My Problem!
// UVa ID: 11097
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 610, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
};

list<edge> edges[MAXV];
int n, m, s, t, dist[MAXV][1010], in[MAXV][1010] = {0};

void spfa()
{
    for (int i = 0; i < n; i++)
        memset(dist[i], 0x3f, sizeof(dist[i]));

    queue<edge> q;
    q.push(edge(s, 0));
    dist[s][0] = 0;
    
    while (!q.empty())
    {
        edge e1 = q.front(); q.pop();
        if (e1.w == 1000) continue;
        in[e1.v][e1.w] = 0;
        for (auto e2 : edges[e1.v])
        {
            if (dist[e2.v][e1.w + 1] > dist[e1.v][e1.w] + e2.w)
            {
                dist[e2.v][e1.w + 1] = dist[e1.v][e1.w] + e2.w;
                if (!in[e2.v][e1.w + 1])
                {
                    in[e2.v][e1.w + 1] = 1;
                    q.push(edge(e2.v, e1.w + 1));
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v, w, q;

    while (cin >> n >> m >> s)
    {
        for (int i = 0; i < n; i++)
            edges[i].clear();
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
        }
        spfa();

        cin >> q;
        for (int i = 0; i < q; i++)
        {
            cin >> t;

            int ei = -1;
            double cost = -1.0;

            if (s == t) cost = 0.0, ei = 0;
            else
            {
                for (int k = 1; k <= 1000; k++)
                {
                    if (dist[t][k] != INF)
                    {
                        double d = (double)dist[t][k] / k;
                        if (cost < 0 || cost > d)
                        {
                            cost = d;
                            ei = k;
                        }
                    }
                }
            }
            if (cost < 0) cout << "No Path\n";
            else cout << fixed << setprecision(4) << cost << ' ' << ei << '\n';
        }
        cout << '\n';
    }

    return 0;
}
