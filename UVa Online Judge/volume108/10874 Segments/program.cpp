// Segments
// UVa ID: 10874
// Verdict: Accepted
// Submission Date: 2018-02-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 40010, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, L1, R1, L2, R2;
    int dist[MAXV];

    while (cin >> n, n > 0)
    {
        int total = 2 * n + 1;
        for (int i = 0; i <= total; i++) edges[i].clear();
        
        // Build directed graph.
        cin >> L1 >> R1;
        edges[0].push_back(edge(1, abs(1 - R1) + abs(L1 - R1)));
        edges[0].push_back(edge(2, abs(1 - L1) + abs(L1 - R1)));
        for (int i = 2; i <= n; i++)
        {
            cin >> L2 >> R2;
            edges[2 * (i - 1) - 1].push_back(edge(2 * i, abs(L1 - L2) + abs(L2 - R2) + 1));
            edges[2 * (i - 1) - 1].push_back(edge(2 * i - 1, abs(L1 - R2) + abs(L2 - R2) + 1));
            edges[2 * (i - 1)].push_back(edge(2 * i, abs(R1 - L2) + abs(L2 - R2) + 1));
            edges[2 * (i - 1)].push_back(edge(2 * i - 1, abs(R1 - R2) + abs(L2 - R2) + 1));
            L1 = L2, R1 = R2;
        }
        edges[2 * n - 1].push_back(edge(2 * n + 1, abs(L1 - n)));
        edges[2 * n].push_back(edge(2 * n + 1, abs(R1 - n)));
        
        // Dijkstra algorithm.
        memset(dist, 0x3f, sizeof(dist));
        priority_queue<edge> q;
        q.push(edge(0, 0));
        dist[0] = 0;
        
        while (!q.empty())
        {
            edge e1 = q.top(); q.pop();
            for (auto e2 : edges[e1.v])
            {
                if (dist[e2.v] > dist[e1.v] + e2.w)
                {
                    dist[e2.v] = dist[e1.v] + e2.w;
                    q.push(edge(e2.v, dist[e2.v]));
                }
            }
        }
        
        cout << dist[total] << '\n';
    }

    return 0;
}
