// Down Went The Titanic
// UVa ID: 11380
// Verdict: Accepted
// Submission Date: 2017-10-14
// UVa Run Time: 0.010s
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

const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *head, *path, *visited;

    bool bfs()
    {
        memset(path, -1, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> q; q.push(source);
        visited[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    q.push(arcs[i].v);
                    visited[arcs[i].v] = 1;
                    path[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        head = new int[v], path = new int[v], visited = new int[v];
        arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(head, -1, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] head, path, visited, arcs;
    }

    int maxFlow()
    {
        int flow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = path[sink]; ~i; i = path[arcs[i].u])
                delta = min(delta, arcs[i].residual);
            flow += delta;
            for (int i = path[sink]; ~i; i = path[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }
        
        return flow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }
};

int x, y, p;

void addArc(EdmondsKarp &ek, int from, int to, char start, char end)
{
    if (start == '#')
    {
        if (end == '#') ek.addArc(from, to, 1000);
        if (end == '.') ek.addArc(from, to, 1);
        if (end == '@') ek.addArc(from, to, 1000);
    }
    else if (start == '.')
    {
        if (end == '#') ek.addArc(from + 1000, to, 1);
        if (end == '.') ek.addArc(from + 1000, to, 1);
        if (end == '@') ek.addArc(from + 1000, to, 1);
    }
    else if (start == '*')
    {
        
        if (end == '#') ek.addArc(from, to, 1);
        if (end == '.') ek.addArc(from, to, 1);
        if (end == '@') ek.addArc(from, to, 1);
    }
    else if (start == '@')
    {
        if (end == '#') ek.addArc(from, to, 1000);
        if (end == '.') ek.addArc(from, to, 1);
        if (end == '@') ek.addArc(from, to, 1000);
    }
}

char g[40][40];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (cin >> x >> y >> p)
    {
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
                cin >> g[i][j];

        EdmondsKarp ek(2000, 40000, 0, 1950);
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
            {
                if (g[i][j] == '*') ek.addArc(0, (i - 1) * y + j, 1);
                if (g[i][j] == '#') ek.addArc((i - 1) * y + j, 1950, p);
                if (g[i][j] == '.') ek.addArc((i - 1) * y + j, (i - 1) * y + j + 1000, 1);
                for (int k = 0; k < 4; k++)
                {
                    int nexti = i + offset[k][0], nextj = j + offset[k][1];
                    if (nexti >= 1 && nexti <= x && nextj >= 1 && nextj <= y)
                        addArc(ek, (i - 1) * y + j, (nexti - 1) * y + nextj, g[i][j], g[nexti][nextj]);
                }
            }
        cout << ek.maxFlow() << '\n';
    }

    return 0;
}
