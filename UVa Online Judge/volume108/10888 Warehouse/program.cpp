// Warehouse
// UVa ID: 10888
// Verdict: Accepted
// Submission Date: 2018-04-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2048, MAXE = 20100, INF = 0x3f3f3f3f;

struct arc { int u, v, capacity, residual, cost, next; } arcs[MAXE];

int idx, source, sink, dist[MAXV], head[MAXV], parent[MAXV], visited[MAXV];
int n, m, fee, flow, h, w;
char maze[50][50];

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

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> h >> w;
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> maze[i][j];
        
        idx = 0, source = 0, sink = h * w + 1;
        memset(head, -1, sizeof(head));

        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (maze[i][j] == 'B')
                {
                    int moves[50][50], visited[50][50];
                    int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
                    memset(moves, 0x3f, sizeof(moves));
                    memset(visited, 0, sizeof(visited));
                    queue<pair<int, int>> q;
                    q.push(make_pair(i, j));
                    moves[i][j] = 0;
                    visited[i][j] = 1;
                    
                    while (!q.empty())
                    {
                        pair<int, int> u = q.front(); q.pop();
                        for (int k = 0; k < 4; k++)
                        {
                            int nexti = u.first + offset[k][0], nextj = u.second + offset[k][1];
                            if (nexti < 0 || nexti >= h || nextj < 0 || nextj >= w) continue;
                            if (visited[nexti][nextj]) continue;
                            if (maze[nexti][nextj] == '#') continue;
                            moves[nexti][nextj] = moves[u.first][u.second] + 1;
                            q.push(make_pair(nexti, nextj));
                            visited[nexti][nextj] = 1;
                        }
                    }
                    
                    addArc(0, i * h + j + 1, 1, 0);
                    for (int ii = 0; ii < h; ii++)
                        for (int jj = 0; jj < w; jj++)
                            if (maze[ii][jj] == 'X')
                                addArc(i * h + j + 1, ii * h + jj + 1, 1, moves[ii][jj]);
                }
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (maze[i][j] == 'X')
                    addArc(i * h + j + 1, sink, 1, 0);

        mcmf();

        cout << fee << '\n';
    }
    
    return 0;
}
