// March of the Penguins
// UVa ID: 12125
// Verdict: Accepted
// Submission Date: 2017-10-14
// UVa Run Time: 0.330s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

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

    void reset()
    {
        idx = 0;
        memset(head, -1, vertices * sizeof(int));
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

struct floe
{
    double x, y;
    int n, m;
} floes[110];

int N, T, ni, mi;
double D, xi, yi;

bool available(floe &a, floe &b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= D;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        EdmondsKarp ek(220, 30000, 0, 210);

        cin >> N >> D;
        
        T = 0;
        for (int i = 1; i <= N; i++)
        {
            cin >> xi >> yi >> ni >> mi;
            floes[i] = floe{xi, yi, ni, mi};
            T += ni;
        }
        
        D *= D;

        bool printed = false;
        for (int u = 1; u <= N; u++)
        {
            ek.reset();
            
            for (int i = 1; i <= N; i++)
            {
                ek.addArc(0, i, floes[i].n);
                if (i == u)
                    ek.addArc(i, 210, 1000);
                else
                {
                    ek.addArc(i, i + 100, floes[i].m);
                    for (int j = 1; j <= N; j++)
                    {
                        if (i == j) continue;
                        if (available(floes[i], floes[j])) ek.addArc(i + 100, j, 1000);
                    }
                }
            }
        
            if (ek.maxFlow() == T)
            {
                if (printed) cout << ' ';
                cout << (u - 1);
                printed = true;
            }
        }
        if (!printed) cout << "-1";
        cout << '\n';
    }

    return 0;
}
