// Great Wall of China
// UVa ID: 11301
// Verdict: Accepted
// Submission Date: 2017-10-16
// UVa Run Time: 1.240s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int MAXV = 10010, MAXE = 200100, INF = 0x3fffffff;

struct arc { int u, v, capacity, residual, cost, next; } arcs[MAXE];

char grid[10][1010];
int idx, source, sink, dist[MAXV], head[MAXV], parent[MAXV], visited[MAXV];
int fee, flow;

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

    int n, offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (cin >> n, n > 0)
    {
        idx = 0, source = 0, sink = 10 * n + 5;
        memset(head, -1, sizeof head);

        for (int i = 1; i <= 5; i++)
            for (int j = 1; j <= n; j++)
                cin >> grid[i][j];

        for (int i = 1; i <= 5; i++)
            for (int j = 1; j <= n; j++)
            {
                if (grid[i][j] == '@')
                {
                    addArc(0, (i - 1) * n + j, 1, 0);
                }

                if (j == n)
                {
                    addArc((i - 1) * n + j + 5 * n, sink, 1, 0);
                }

                if (isdigit(grid[i][j]))
                {
                    addArc((i - 1) * n + j, (i - 1) * n + j + 5 * n, 1, grid[i][j] - '0');
                }

                for (int k = 0; k < 4; k++)
                {
                    int nexti = i + offset[k][0], nextj = j + offset[k][1];
                    if (nexti >= 1 && nexti <= 5 && nextj >= 1 && nextj <= n)
                    {
                        if (grid[i][j] == '@' && grid[nexti][nextj] != '@')
                        {
                            addArc((i - 1) * n + j, (nexti - 1) * n + nextj, 1, 0);
                        }
                        
                        if (isdigit(grid[i][j]) && isdigit(grid[nexti][nextj]))
                        {
                            addArc((i - 1) * n + j + 5 * n, (nexti - 1) * n + nextj, 1, 0);
                        }
                    }
                }
            }

        mcmf();

        cout << fee << '\n';
    }
    
    return 0;
}
