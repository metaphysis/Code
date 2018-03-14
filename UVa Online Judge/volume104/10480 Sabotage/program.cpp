// Sabotage
// UVa ID: 10480
// Verdict: Accepted
// Submission Date: 2017-09-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3fffffff;

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
    
    void dfs(int u)
    {
        visited[u] = 1;
        for (int i = head[u]; ~i; i = arcs[i].next)
            if (!visited[arcs[i].v] && arcs[i].residual > 0)
                dfs(arcs[i].v);
    }
    
    void printMinCut()
    {
        memset(visited, 0, vertices * sizeof(int));
        dfs(0);
        for (int i = 0; i < idx; i += 2)
            if (arcs[i].u < arcs[i].v && visited[arcs[i].u] != visited[arcs[i].v])
                cout << (arcs[i].u + 1) << ' ' << (arcs[i].v + 1) << '\n';
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, from, to, cost;
    
    while (cin >> n >> m, n > 0)
    {
        EdmondsKarp ek(n, m * 4, 0, 1);
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to >> cost;
            from--, to--;
            ek.addArc(from, to, cost);
            ek.addArc(to, from, cost);
        }
        
        ek.maxFlow();
        ek.printMinCut();

        cout << '\n';
    }
    
    return 0;
}
