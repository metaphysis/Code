// Fixed Partition Memory Management
// UVa ID: 1006
// Verdict: Accepted
// Submission Date: 2019-06-26
// UVa Run Time: 1.280s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXM = 16, MAXN = 64, MAXV = 600, MAXE = 1000000, INF = 0x3f3f3f3f;

struct arc { int u, v, capacity, residual, cost, next; } arcs[MAXE];
struct program { int pid, mid, region, cost, from, to; } programs[MAXN];

bool cmp1(program a, program b)
{
    if (a.region != b.region) return a.region < b.region;
    return a.mid < b.mid;
}

bool cmp2(program a, program b)
{
    return a.pid < b.pid;
}

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
        source = 0, sink = (m + 1) * n + 1;

        int flow = 0, fee = 0;
        int memory[MAXM];
        int K[MAXN], ST[MAXN][MAXM][2];

        for (int i = 1; i <= m; i++) cin >> memory[i];
        for (int i = 1; i <= n; i++)
        {
            cin >> K[i];
            for (int j = 1; j <= K[i]; j++)
                cin >> ST[i][j][0] >> ST[i][j][1];
            K[i]++;
            ST[i][K[i]][0] = INF, ST[i][K[i]][1] = ST[i][K[i] - 1][1];
        }

        idx = 0;
        memset(head, -1, sizeof(head));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (memory[j] < ST[i][1][0]) continue;
                for (int k = 1; k < K[i]; k++)
                    if (ST[i][k][0] <= memory[j] && memory[j] < ST[i][k + 1][0])
                    {
                        for (int t = 1; t <= n; t++)
                            addArc(i, j * n + t, 1, (n - t + 1) * ST[i][k][1]);
                        break;
                    }
            }
        }
        for (int i = 1; i <= n; i++)
            addArc(0, i, 1, 0);
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                    addArc(i * n + j, sink, 1, 0);

        pair<int, int> r = mcmf();
        fee += r.first, flow += r.second;

        int tot = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = head[i]; ~j; j = arcs[j].next)
            {
                if (!arcs[j].residual)
                {
                    int region = (arcs[j].v - 1) / n;
                    int mid = arcs[j].v % n;
                    if (mid == 0) mid = n;
                    programs[tot++] = (program){i, mid, region, arcs[j].cost / (n - mid + 1), 0, 0};
                    break;
                }
            }
        }

        sort(programs, programs + tot, cmp1);
        int old = -1, elapsed = 0;
        for (int i = 0; i < tot; i++)
        {
            if (programs[i].region != old)
            {
                old = programs[i].region;
                elapsed = 0;
            }
            programs[i].from = elapsed;
            elapsed += programs[i].cost;
            programs[i].to = elapsed;
        }

        sort(programs, programs + tot, cmp2);

        cout << "Case " << ++cases << '\n';
        cout << "Average turnaround time = ";
        cout << fixed << setprecision(2) << (1.0 * fee / n) << '\n';
        for (int i = 0; i < tot; i++)
        {
            cout << "Program " << programs[i].pid;
            cout << " runs in region " << programs[i].region;
            cout << " from " << programs[i].from;
            cout << " to " << programs[i].to << '\n';
        }
        cout << '\n';
    }
    
    return 0;
}
