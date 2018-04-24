// Crime Wave - The Sequel
// UVa ID: 10746
// Verdict: Accepted
// Submission Date: 2018-04-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 20100, INF = 0x3f3f3f3f;
const double EPS = 1e-5;

struct arc { int u, v, capacity, residual; double cost; int next; } arcs[MAXE];

double dist[MAXV], fee;
int idx, source, sink, head[MAXV], parent[MAXV], visited[MAXV];
int n, m, flow;

bool spfa()
{
    for (int i = 0; i < MAXV; i++)
        dist[i] = INF, parent[i] = -1, visited[i] = 0;

    dist[source] = 0, visited[source] = 1;
    queue<int> q; q.push(source);

    while (!q.empty())
    {
        int u = q.front(); q.pop(); visited[u] = 0;
        for (int i = head[u]; ~i; i = arcs[i].next)
        {
            arc e = arcs[i];
            if (e.residual > 0 && dist[e.v] > dist[u] + e.cost + EPS)
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

    return dist[sink] + EPS < INF;
}

void addArc(int u, int v, int capacity, double cost)
{
    arcs[idx] = (arc){u, v, capacity, capacity, cost, head[u]};
    head[u] = idx++;
    arcs[idx] = (arc){v, u, capacity, 0, -cost, head[v]};
    head[v] = idx++;
}

void mcmf()
{
    fee = flow = 0;
    while (spfa())
    {
        int delta = INF;
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

    while (cin >> n >> m, n > 0)
    {
        idx = 0, source = 0, sink = m + n + 1;
        memset(head, -1, sizeof(head));

        double timeOfTravel;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> timeOfTravel;
                addArc(j, i + m, 1, timeOfTravel);
            }
        for (int i = 1; i <= m; i++)
            addArc(0, i, 1, 0);
        for (int i = 1; i <= n; i++)
            addArc(i + m, sink, 1, 0);

        mcmf();
        
        cout << fixed << setprecision(2) << (fee / n) + EPS << endl;
    }
    
    return 0;
}
