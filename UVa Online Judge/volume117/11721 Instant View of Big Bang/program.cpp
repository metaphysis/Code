// Instant View of Big Bang
// UVa ID: 11721
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1100, MAXE = 2100, INF = 0x3f3f3f3f;

struct edge { int from, to, weight; } edges[MAXE];
int dist[MAXV], n, m;

void bellmanFord(int u)
{
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[u] = 0;

    for (int k = 1; k < n; k++)
    {
        bool updated = false;
        for (int i = 0; i < m; i++)
            if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
            {
                dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
                updated = true;
            }
        if (!updated) break;
    }
    set<int> vertices;
    for (int i = 1; i <= m; i++)
        if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
            vertices.insert(edges[i].from);
    if (vertices.size() == 0) cout << " impossible";
    else
    {
        for (auto v : vertices) cout << ' ' << v;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;
        for (int i = 0, x, y, t; i < m; i++)
            cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        cout << "Case " << cs << ":";
        bellmanFord(0);
        cout << '\n';
    }

    return 0;
}
