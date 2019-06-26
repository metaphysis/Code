// Fixed Partition Memory Management
// UVa ID: 1006
// Verdict: TLE
// Submission Date: 2019-06-25
// UVa Run Time: 9.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXM = 16, MAXN = 64, MAXV = 100, MAXE = 1000, INF = 0x3f3f3f3f;

struct arc { int u, v, capacity, residual, cost, next; } arcs[MAXE];

int dist[MAXV], head[MAXV], parent[MAXV], visited[MAXV];
int m, n, idx, source, sink;

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

void addArc(int u, int v, int capacity, int cost)
{
    arcs[idx] = (arc){u, v, capacity, capacity, cost, head[u]};
    head[u] = idx++;
    arcs[idx] = (arc){v, u, capacity, 0, -cost, head[v]};
    head[v] = idx++;
}

pair<int, int> mcmf()
{
    int fee = 0, flow = 0;
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
    return make_pair(fee, flow);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> m >> n, m > 0)
    {
        source = 0, sink = m + n + 1;

        int flow = 0, fee = 0;
        int inRegion[MAXN], duration[MAXN][2], elapsed[MAXM];
        int memory[MAXM];
        int K[MAXN], ST[MAXN][MAXM][2];

        memset(inRegion, 0, sizeof(inRegion));
        memset(elapsed, 0, sizeof(elapsed));

        for (int i = 1; i <= m; i++) cin >> memory[i];
        for (int i = 1; i <= n; i++)
        {
            cin >> K[i];
            for (int j = 1; j <= K[i]; j++)
                cin >> ST[i][j][0] >> ST[i][j][1];
        }

        while (flow < n)
        {
            idx = 0;
            memset(head, -1, sizeof(head));

            for (int i = 1; i <= m; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (inRegion[j]) continue;
                    if (memory[i] < ST[j][1][0]) continue;
                    bool added = false;
                    for (int k = 1; k < K[j]; k++)
                        if (memory[i] >= ST[j][k][0] && memory[i] < ST[j][k + 1][0])
                        {
                            addArc(i, j + m, 1, elapsed[i] + ST[j][k][1]);
                            added = true;
                            break;
                        }
                    if (!added) addArc(i, j + m, 1, elapsed[i] + ST[j][K[j]][1]);
                }
            }
            for (int i = 1; i <= m; i++)
                addArc(0, i, 1, 0);
            for (int i = 1; i <= n; i++)
                if (!inRegion[i])
                    addArc(i + m, sink, 1, 0);

            pair<int, int> r = mcmf();
            fee += r.first, flow += r.second;

            for (int i = 1; i <= m; i++)
            {
                for (int j = head[i]; ~j; j = arcs[j].next)
                {
                    if (!arcs[j].residual)
                    {
                        inRegion[arcs[j].v - m] = i;
                        duration[arcs[j].v - m][0] = elapsed[i];
                        elapsed[i] = arcs[j].cost;
                        duration[arcs[j].v - m][1] = elapsed[i];
                        break; 
                    }
                }
            }
        }

        cout << "Case " << ++cases << '\n';
        cout << "Average turnaround time = ";
        cout << fixed << setprecision(2) << (1.0 * fee / n) << '\n';
        for (int i = 1; i <= n; i++)
        {
            cout << "Program " << i;
            cout << " runs in region " << inRegion[i];
            cout << " from " << duration[i][0];
            cout << " to " << duration[i][1] << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
