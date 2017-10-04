// Data Flow
// UVa ID: 10594
// Verdict: Accepted
// Submission Date: 2017-10-04
// UVa Run Time: 0.190s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

const int MAXV = 110, MAXE = 20100;
const long long INF = 0xfffffffffffff;

struct arc
{
    int u, v, next;
    long long capacity, residual, cost;
};

arc arcs[MAXE];
long long dist[MAXV], fee, flow;
int idx, source, sink;
int head[MAXV], parent[MAXV], visited[MAXV];
int n, m;

bool spfa()
{
    for (int i = 0; i <= n; i++)
        dist[i] = INF, parent[i] = -1, visited[i] = 0;

    dist[source] = 0, visited[source] = 1;
    queue<int> q; q.push(source);

    while (!q.empty())
    {
        int u = q.front(); q.pop(); visited[u] = 0;
        for (int i = head[u]; ~i; i = arcs[i].next)
        {
            arc e = arcs[i];
            if (e.residual > 0 && dist[e.v] > dist[u] + e.cost)
            {
                dist[e.v] = dist[u] + e.cost;
                parent[e.v] = i;
                if (!visited[e.v])
                {
                    q.push(e.v);
                    visited[e.v] = 1;
                }
            }
        }
    }

    return dist[sink] < INF;
}

void addArc(int u, int v, long long capacity, long long cost)
{
    arcs[idx] = (arc){u, v, head[u], capacity, capacity, cost};
    head[u] = idx++;
    arcs[idx] = (arc){v, u, head[v], capacity, 0, -cost};
    head[v] = idx++;
}

void mcmf()
{
    fee = flow = 0;
    while (spfa())
    {
        long long delta = INF;
        for (int i = parent[sink]; ~i; i = parent[arcs[i].u])
            delta = min(delta, arcs[i].residual);
        flow += delta, fee += delta * dist[sink];
        for (int i = parent[sink]; ~i; i = parent[arcs[i].u])
        {
            arcs[i].residual -= delta;
            arcs[i ^ 1].residual += delta;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int u, v;
    long long t, d, k;

    while (cin >> n >> m)
    {
        idx = 0, source = 0, sink = n;
        memset(head, -1, sizeof head);

        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> t;
            addArc(u, v, 1, t);
            addArc(v, u, 1, t);
        }

        cin >> d >> k;
        for (int i = 0; i < idx; i++)
            arcs[i].capacity *= k, arcs[i].residual *= k;

        addArc(0, 1, d, 0);

        mcmf();
        
        if (flow < d) cout << "Impossible.\n";
        else cout << fee << '\n';
    }
    
    return 0;
}
