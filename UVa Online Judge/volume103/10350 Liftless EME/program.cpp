// Liftless EME
// UVa ID: 10350
// Verdict: Accepted
// Submission Date: 2018-02-14
// UVa Run Time: 0.060s
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

const int MAXV = 2048, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];

string name;
int n, m, t, dist[MAXV];

int mooreDijkstra(int s, int t)
{
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(s, 0));
    dist[s] = 0;
    
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
    
    return dist[t];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> name)
    {
        cout << name << '\n';
        cin >> n >> m;

        for (int i = 0; i < MAXV; i++)
            edges[i].clear();

        // Add a source.
        for (int i = 1; i <= m; i++)
            edges[0].push_back(edge(i, 0));

        for (int i = 1; i < n; i++)
            for (int j = 1; j <= m; j++)
                for (int k = 1; k <= m; k++)
                {
                    cin >> t;
                    edges[(i - 1) * m + j].push_back(edge(i * m + k, t + 2));
                }
        // Add a sink.
        for (int i = 1; i <= m; i++)
            edges[(n - 1) * m + i].push_back(edge(n * m + 1, 0));
            
        cout << mooreDijkstra(0, n * m + 1) << '\n';
    }

    return 0;
}
