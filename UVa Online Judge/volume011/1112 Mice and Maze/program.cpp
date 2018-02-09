// Mice and Maze
// UVa ID: 1112
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1010, INF = 0x3fffffff;

struct edge
{
    int to, weight;
    edge (int to = 0, int weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int dist[MAXV], parent[MAXV], visited[MAXV];
int n, m, E, T;

void mooreDijkstra(int u)
{
    for (int i = 1; i <= n; i++) dist[i] = INF, parent[i] = -1, visited[i] = 0;
    dist[u] = 0;

    while (!visited[u])
    {
        visited[u] = 1;
        for (auto e : edges[u])
            if (!visited[e.to] && dist[e.to] > dist[u] + e.weight)
                dist[e.to] = dist[u] + e.weight, parent[e.to] = u;

        int minDist = INF;
        for (int i = 1; i <= n; i++)
            if (!visited[i] && minDist > dist[i])
                minDist = dist[i], u = i;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> E >> T >> m;

        for (int i = 1; i <= n; i++)
            edges[i].clear();

        int u, v, weight;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> weight;
            edges[v].push_back(edge(u, weight));
        }
        mooreDijkstra(E);
        int mice = 0;
        for (int i = 1; i <= n; i++)
            if (dist[i] <= T) mice++;
        if (c > 1) cout << '\n';
        cout << mice << '\n';
    }

    return 0;
}
