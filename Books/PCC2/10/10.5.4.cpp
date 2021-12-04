#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class Dinic
{
private:
    arc *arcs;
    int vertices, source, sink, idx, *head, *dist, *current;

    bool bfs()
    {
        memset(dist, -1, sizeof(int) * vertices);

        queue<int> q;
        q.push(source);
        dist[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (arcs[i].residual > 0 && dist[arcs[i].v] < 0)
                {
                    dist[arcs[i].v] = dist[u] + 1;
                    q.push(arcs[i].v);
                }
        }

        return dist[sink] > 0;
    }

    int dfs(int u, int flow)
    {
        if (u == sink) return flow;
        for (int &i = current[u]; ~i; i = arcs[i].next)
        {
            int v = arcs[i].v, r = arcs[i].residual;
            if (dist[v] == (dist[u] + 1) && r > 0)
            {
                int volume = dfs(v, min(r, flow));
                if (volume > 0)
                {
                    arcs[i].residual -= volume;
                    arcs[i ^ 1].residual += volume;
                    return volume;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int v, int e, int s, int t)
    {
        arcs = new arc[e];
        vertices = v;
        source = s, sink = t;
        idx = 0, head = new int[v], dist = new int[v], current = new int[v];
        memset(head, -1, sizeof(int) * v);
    }

    ~Dinic()
    {
        delete [] arcs, head, dist, current;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }

    int maxFlow()
    {
        int flow = 0;

        while (bfs())
        {
            for (int i = 0; i < vertices; i++) current[i] = head[i];
            while (int delta = dfs(source, INF))
                flow += delta;
        }

        return flow;
    }
};

int main(int argc, char *argv[])
{
    Dinic dinic(100, 11000, 0, 101);
    
    return 0;
}
