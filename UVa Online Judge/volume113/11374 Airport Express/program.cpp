// Airport Express
// UVa ID: 11374
// Verdict: Accepted
// Submission Date: 2018-02-11
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

const int MAXV = 510, INF = 0x3f3f3f3f;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

list<edge> edges[MAXV];
int n, m, s, t, distS[MAXV], distD[MAXV], parentS[MAXV], parentD[MAXV];

void mooreDijkstra(int u, int *dist, int *parent)
{
    memset(dist, 0x3f, MAXV * sizeof(int));
    memset(parent, -1, MAXV * sizeof(int));
    
    priority_queue<edge> q;
    q.push(edge(u, 0));
    dist[u] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (dist[e2.v] > dist[e1.v] + e2.w)
            {
                dist[e2.v] = dist[e1.v] + e2.w;
                parent[e2.v] = e1.v;
                q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, u, v, w;

    while (cin >> n >> s >> t)
    {
        for (int i = 1; i <= n; i++)
            edges[i].clear();
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            edges[u].push_back(edge(v, w));
            edges[v].push_back(edge(u, w));
        }
        
        mooreDijkstra(s, distS, parentS);
        mooreDijkstra(t, distD, parentD);
        
        int minTime = distS[t], from, to, useTicket = 0;

        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            if (distS[u] + w + distD[v] < minTime)
            {
                useTicket = 1;
                from = u, to = v;
                minTime = distS[u] + w + distD[v];
            }
            if (distS[v] + w + distD[u] < minTime)
            {
                useTicket = 1;
                from = v, to = u;
                minTime = distS[v] + w + distD[u];
            }
        }
        
        if (cases++ > 0) cout << '\n';
        if (useTicket)
        {
            vector<int> path1;
            u = from;
            while (parentS[u] != -1)
            {
                path1.push_back(u);
                u = parentS[u];
            }
            path1.push_back(u);
            reverse(path1.begin(), path1.end());
            
            vector<int> path2;
            u = to;
            while (parentD[u] != -1)
            {
                path2.push_back(u);
                u = parentD[u];
            }
            path2.push_back(u);
            path1.insert(path1.end(), path2.begin(), path2.end());

            for (int i = 0; i < path1.size(); i++)
            {
                if (i) cout << ' ';
                cout << path1[i];
            }
            cout << '\n';

            cout << from << '\n';
        }
        else
        {
            vector<int> path;
            u = t;
            while (parentS[u] != -1)
            {
                path.push_back(u);
                u = parentS[u];
            }
            path.push_back(u);
            reverse(path.begin(), path.end());
            for (int i = 0; i < path.size(); i++)
            {
                if (i) cout << ' ';
                cout << path[i];
            }
            cout << '\n';

            cout << "Ticket Not Used\n";
        }
        cout << minTime << '\n';
    }

    return 0;
}
