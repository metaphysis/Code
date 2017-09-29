const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class Dinic
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *head, *dist;

    bool bfs()
    {
        memset(dist, 0xff, vertices * sizeof(int));

        queue<int> q; q.push(source);
        dist[source] = 1;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
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

        for (int i = head[u]; ~i; i = arcs[i].next)
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
        vertices = v;
        head = new int[v], dist = new int[v], arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(head, -1, vertices * sizeof(int));
    }

    ~Dinic()
    {
        delete [] head, dist, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
            while (int delta = dfs(0, INF))
                netFlow += delta;

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
