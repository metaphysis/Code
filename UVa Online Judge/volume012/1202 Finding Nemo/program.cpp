// Finding Nemo
// UVa ID: 1202
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.020s
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

const int MAXV = 201;

struct edge
{
    int x, y, weight;
    edge (int x = 0, int y = 0, int weight = 0): x(x), y(y), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

int edges[MAXV][MAXV][4];
int dist[MAXV][MAXV];
int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void mooreDijkstra()
{
    for (int i = 0; i < MAXV; i++)
        for (int j = 0; j < MAXV; j++)
            dist[i][j] = -1;

    dist[0][0] = 0;
    priority_queue<edge> q;
    q.push(edge(0, 0, 0));

    while (!q.empty())
    {
        edge v = q.top(); q.pop();
        for (int k = 0; k < 4; k++)
            if (edges[v.x][v.y][k] >= 0)
            {
                int nextx = v.x + offset[k][0], nexty = v.y + offset[k][1];
                if (dist[nextx][nexty] < 0 || dist[nextx][nexty] > dist[v.x][v.y] + edges[v.x][v.y][k])
                {
                    dist[nextx][nexty] = dist[v.x][v.y] + edges[v.x][v.y][k];
                    q.push((edge){nextx, nexty, dist[nextx][nexty]});
                }
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int M, N, x, y, d, t, nemox, nemoy;
    double f1, f2;

    while (cin >> M >> N, M >= 0)
    {
        memset(edges, 0, sizeof(edges));
        for (int i = 0; i < MAXV; i++)
        {
            edges[0][i][3] = -1;
            edges[i][0][2] = -1;
            edges[i][MAXV - 1][0] = -1;
            edges[MAXV - 1][i][1] = -1;
        }
        
        for (int i = 0; i < M; i++)
        {
            cin >> x >> y >> d >> t;
            // Horizontal
            if (d == 0)
            {
                for (int j = 0; j < t; j++)
                {
                    edges[x + j][y][2] = edges[x + j][y - 1][0] = -1;
                }
            }
            // Vertical
            else
            {
                for (int j = 0; j < t; j++)
                {
                    edges[x][y + j][3] = edges[x - 1][y + j][1] = -1;
                }
            }
        }
        for (int i = 0; i < N; i++)
        {
            cin >> x >> y >> d;
            if (d == 0)
            {
                edges[x][y][2] = edges[x][y - 1][0] = 1;
            }
            else
            {
                edges[x][y][3] = edges[x - 1][y][1] = 1;
            }
        }
        
        cin >> f1 >> f2;
        nemox = (int)floor(f1), nemoy = (int)floor(f2);
        mooreDijkstra();
        if (nemox < MAXV && nemoy < MAXV)
            cout << dist[nemox][nemoy] << '\n';
        else
            cout << 0 << '\n';
    }

    return 0;
}
