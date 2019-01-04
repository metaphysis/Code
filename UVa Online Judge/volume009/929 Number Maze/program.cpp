// Number Maze
// UVa ID: 929
// Verdict: Accepted
// Submission Date: 2017-01-11
// UVa Run Time: 0.830s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1000010, INF = 0x3f3f3f3f;

struct edge
{
    int v;
    long long weight;
    edge (int v = 0, long long weight = 0): v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
} edges[MAXE][4];

long long dist[MAXE];
int cases, N, M, maze[MAXV][MAXV];
int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void mooreDijkstra(int u)
{
    fill(dist, dist + N * M, INF);
    dist[u] = maze[0][0];

    priority_queue<edge> q;
    q.push(edge(0, dist[u]));

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        for (int i = 0; i < 4; i++)
        {
            edge e2 = edges[e1.v][i];
            if (e2.v == 0) continue;
            if (dist[e2.v] > dist[e1.v] + e2.weight)
            {
                dist[e2.v] = dist[e1.v] + e2.weight;
                q.push(edge(e2.v, dist[e2.v]));
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> M;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> maze[i][j];

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                int c = i * M + j;
                for (int k = 0; k < 4; k++)
                {
                    edges[c][k].v = 0;
                    int ii = i + offset[k][0], jj = j + offset[k][1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M)
                        edges[c][k] = edge(ii * M + jj, maze[ii][jj]);
                }
            }

        mooreDijkstra(0);
        cout << dist[N * M - 1] << '\n';
    }
    
    return 0;
}
