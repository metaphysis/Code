// Asterix and Obelix
// UVa ID: 10246
// Verdict: Accepted
// Submission Date: 2018-12-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 90, INF = 0x3f3f3f3f;

struct edge
{
    int to, weight;
    edge (int to = 0, int weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int C, R, Q;
int hosting[90], D[90][90];

void mooreDijkstra(int u)
{
    int dist[MAXV];
    memset(dist, INF, sizeof(dist));
    dist[u] = 0;
    priority_queue<edge> q;
    q.push(edge(u, dist[u]));
    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        if (dist[e1.to] < e1.weight) continue;
        for (auto e2 : edges[e1.to])
            if (dist[e2.to] > dist[e1.to] + e2.weight && hosting[e2.to] <= hosting[u])
            {
                dist[e2.to] = dist[e1.to] + e2.weight;
                q.push(edge(e2.to, dist[e2.to]));
            }
    }
    for (int i = 1; i <= C; i++) D[u][i] = dist[i];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> C >> R >> Q)
    {
        if (C == 0 && R == 0 && Q == 0) break;
        for (int i = 1; i <= C; i++)
        {
            cin >> hosting[i];
            edges[i].clear();
        }
        for (int i = 1, c1, c2, d; i <= R; i++)
        {
            cin >> c1 >> c2 >> d;
            edges[c1].push_back(edge(c2, d));
            edges[c2].push_back(edge(c1, d));
        }
        for (int i = 1; i <= C; i++) mooreDijkstra(i);
        if (cases++) cout << '\n';
        cout << "Case #" << cases << '\n';
        for (int i = 1, c1, c2; i <= Q; i++)
        {
            cin >> c1 >> c2;
            int cost = INF;
            for (int j = 1; j <= C; j++) cost = min(cost, D[j][c1] + D[j][c2] + hosting[j]);
            cout << (cost < INF ? cost : -1) << '\n';
        }
    }

    return 0;
}
