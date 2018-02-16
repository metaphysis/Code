// New to Bangladesh?
// UVa ID: 10525
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run sTime: 0.000s
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

const int MAXV = 256, INF = 0x3f3f3f3f;

struct edge
{
    int v, t, l;
    edge (int v = 0, int t = 0, int l = 0): v(v), t(t), l(l) {}
    bool operator<(const edge &e) const { t > e.t; }
};

list<edge> edges[MAXV];
int n, m, sTime[MAXV], sLength[MAXV];

void mooreDijkstra(int s)
{
    memset(sTime, 0x3f, sizeof(sTime));
    memset(sLength, 0x3f, sizeof(sLength));
    
    priority_queue<edge> q;
    q.push(edge(s, 0, 0));
    sLength[s] = sTime[s] = 0;

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (auto e2 : edges[e1.v])
        {
            if (sTime[e2.v] > sTime[e1.v] + e2.t)
            {
                sTime[e2.v] = sTime[e1.v] + e2.t;
                sLength[e2.v] = sLength[e1.v] + e2.l;
                q.push(edge(e2.v, sTime[e2.v], sLength[e2.v]));
            }
            else if (sTime[e2.v] == sTime[e1.v] + e2.t)
            {
                if (sLength[e2.v] > sLength[e1.v] + e2.l)
                {
                    sLength[e2.v] = sLength[e1.v] + e2.l;
                    q.push(edge(e2.v, sTime[e2.v], sLength[e2.v]));
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, u, v, t, l, q;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;

        for (int i = 1; i <= n; i++) edges[i].clear();
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> t >> l;
            edges[u].push_back(edge(v, t, l));
            edges[v].push_back(edge(u, t, l));
        }

        if (c > 1) cout << '\n';
        cin >> q;
        for (int i = 1; i <= q; i++)
        {
            cin >> u >> v;
            mooreDijkstra(u);
            if (sLength[v] != INF)
            {
                cout << "Distance and time to reach destination is ";
                cout << sLength[v] << " & " << sTime[v] << ".\n";
            }
            else
                cout << "No Path.\n";
        }
    }

    return 0;
}
