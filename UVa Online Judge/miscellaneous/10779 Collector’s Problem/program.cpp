// Collector’s Problem
// UVa ID: 10779
// Verdict: Accepted
// Submission Date: 2017-09-29
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
    int vertices, idx, source, sink, *head, *parent, *visited;

    bool bfs()
    {
        memset(parent, -1, vertices * sizeof(int));
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
                    parent[arcs[i].v] = i;
                }
        }

        return visited[sink];
    }

public:
    EdmondsKarp(int v, int e, int s, int t)
    {
        vertices = v;
        head = new int[v], parent = new int[v], visited = new int[v];
        arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(head, -1, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] head, parent, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = parent[sink]; ~i; i = parent[arcs[i].u])
                delta = min(delta, arcs[i].residual);
            netFlow += delta;
            for (int i = parent[sink]; ~i; i = parent[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }

        return netFlow;
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

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        EdmondsKarp ek(50, 50 * 50 * 2, 1, 40);
        
        int n, m, k, ki, counter[30][30] = {0}, visited[30] = {0};
        set<int> stickers[30];

        cin >> n >> m;

        for (int i = 1; i <= n; i++)
        {
            cin >> k;
            for (int j = 1; j <= k; j++)
            {
                cin >> ki;
                visited[ki] = 1;
                counter[i][ki]++;
                stickers[i].insert(ki);
            }
        }

        // Bob(source) to stickers.
        for (int i = 1; i <= 25; i++)
            if (counter[1][i] > 0)
                ek.addArc(1, 10 + i, counter[1][i]);
                
        // Friends to stickers.
        for (int i = 2; i <= n; i++)
            for (int j = 1; j <= 25; j++)
                if (counter[i][j] >= 2)
                    ek.addArc(i, 10 + j, counter[i][j] - 1);
        
        // Stickers to friends.   
        for (int s = 1; s <= 25; s++)
            for (int i = 2; i <= n; i++)
                if (stickers[i].find(s) == stickers[i].end())
                    ek.addArc(10 + s, i, 1);

        // Stickers to sink.
        for (int i = 1; i <= 25; i++)
            if (visited[i])
                ek.addArc(10 + i, 40, 1);

        cout << "Case #" << c << ": " << ek.maxFlow() << '\n';
    }

    return 0;
}
