const int INF = 0x7f7f7f7f;

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

    void restoreFlowNetwork()
    {
        for (int i = 0; i < idx; i++)
        {
            if (i & 1) arcs[i].residual = 0;
            else arcs[i].residual = arcs[i].capacity;
        }
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
        restoreFlowNetwork();

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
