// The Great Escape
// UVa ID: 10967
// Verdict: Accepted
// Submission Date: 2018-02-10
// UVa Run Time: 0.570s
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

struct edge
{
    int r, c, d, w;
    edge (int r = 0, int c = 0, int d = 0, int w = 0): r(r), c(c), d(d), w(w) {}
    bool operator<(const edge &e) const { return w > e.w; }
};

char grid[110][110];
list<edge> edges[110][110][4];
int R, C, timing[510];
int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
map<char, int> direction = {{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
    
void buildGraph()
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            for (int k = 0; k < 4; k++)
                edges[i][j][k].clear();

    for (int i = 0, doors = 0; i < R; i++)
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int nexti = i + offset[k][0], nextj = j + offset[k][1];
                if (nexti >= 0 && nexti < R && nextj >= 0 && nextj < C)
                    edges[i][j][k].push_back(edge(nexti, nextj, (k + 2) % 4, 1));
            }
            if (grid[i][j] == '.')
            {
                for (int s = 0; s < 4; s++)
                    for (int t = 0; t < 4; t++)
                    {
                        if (s == t) continue;
                        edges[i][j][s].push_back(edge(i, j, t, 0));
                    }
            }
            if (grid[i][j] != '.' && grid[i][j] != '#')
            {
                int d = direction[grid[i][j]];
                edges[i][j][d].push_back(edge(i, j, (d + 1) % 4, timing[doors]));
                edges[i][j][d].push_back(edge(i, j, (d + 2) % 4, 2 * timing[doors]));
                edges[i][j][d].push_back(edge(i, j, (d + 3) % 4, timing[doors]));
                doors++;
            }
        }
}

void mooreDijkstra()
{
    int dist[110][110][4], INF = 0x7f7f7f7f;
    memset(dist, INF, sizeof(dist));
    priority_queue<edge> q;
    q.push(edge(R - 1, 0, 2, 0));
    q.push(edge(R - 1, 0, 3, 0));
    dist[R - 1][0][2] = dist[R - 1][0][3] = 0;
    while (!q.empty())
    {
        edge u = q.top(); q.pop();
        for (auto v : edges[u.r][u.c][u.d])
            if (dist[v.r][v.c][v.d] > dist[u.r][u.c][u.d] + v.w)
            {
                dist[v.r][v.c][v.d] = dist[u.r][u.c][u.d] + v.w;
                q.push(edge(v.r, v.c, v.d, dist[v.r][v.c][v.d]));
            }
    }
    if (min(dist[0][C - 1][2], dist[0][C - 1][3]) == INF) cout << "Poor Kianoosh\n";
    else cout << min(dist[0][C - 1][2], dist[0][C - 1][3]) << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> R >> C;
        int doors = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
            {
                cin >> grid[i][j];
                if (grid[i][j] != '.' && grid[i][j] != '#')
                    doors++;
            }
        for (int i = 0; i < doors; i++) cin >> timing[i];
        buildGraph();
        mooreDijkstra();
    }

    return 0;
}
