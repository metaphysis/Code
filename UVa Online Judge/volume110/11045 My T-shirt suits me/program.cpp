// My T-shirt suits me
// UVa ID: 11045
// Verdict: Accepted
// Submission Date: 2017-10-06
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    map<string, int> code = {{"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4}, {"S", 5}, {"XS", 6}};
    int cases, N, M;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> M;
        
        EdmondsKarp ek(100, 10000, 0, 90);

        for (int i = 1; i <= 6; i++)
            ek.addArc(0, i, N / 6);
            
        string size1, size2;
        for (int i = 1; i <= M; i++)
        {
            cin >> size1 >> size2;
            ek.addArc(code[size1], i + 6, 1);
            ek.addArc(code[size2], i + 6, 1);
            ek.addArc(i + 6, 90, 1);
        }

        cout << (ek.maxFlow() == M ? "YES" : "NO") << '\n';
    }

    return 0;
}
