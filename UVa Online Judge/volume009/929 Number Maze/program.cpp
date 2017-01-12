// Number Maze
// UVa ID: 929
// Verdict: Accepted
// Submission Date: 2017-01-11
// UVa Run Time: 0.830s
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
#include <vector>

using namespace std;

const int MAX_DIST = numeric_limits<int>::max();

struct edge
{
    int idx;
    long long weight;

    bool operator<(const edge& x) const
    {
        return weight > x.weight;
    }
};

edge edges[1000000][4];
long long dist[1000000];

int cases, N, M, maze[1010][1010];
int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void moore_dijkstra(int u)
{
    fill(dist, dist + N * M, MAX_DIST);
    dist[u] = maze[0][0];
    
    priority_queue<edge> unvisited;
    unvisited.push((edge){0, dist[u]});
    
    while (!unvisited.empty())
    {
        edge v = unvisited.top(); unvisited.pop();
        for (int i = 0; i < 4; i++)
        {
            edge e = edges[v.idx][i];
            if (e.idx == 0) continue;
            if (dist[v.idx] + e.weight < dist[e.idx])
            {
                dist[e.idx] = dist[v.idx] + e.weight;
                unvisited.push((edge){e.idx, dist[e.idx]});
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
                    edges[c][k].idx = 0;
                    int ii = i + offset[k][0], jj = j + offset[k][1];
                    if (ii >= 0 && ii < N && jj >= 0 && jj < M)
                        edges[c][k] = (edge){ii * M + jj, maze[ii][jj]};
                }
            }

        moore_dijkstra(0);
        cout << dist[N * M - 1] << '\n';
    }
    
    return 0;
}
