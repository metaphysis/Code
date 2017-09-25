const int INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
};

class EdmondsKarp
{
private:
    arc *arcs;
    int vertices, idx, source, sink, *link, *parent, *visited;

    bool bfs()
    {
        memset(parent, 0xff, vertices * sizeof(int));
        memset(visited, 0, vertices * sizeof(int));

        queue<int> unvisited; unvisited.push(source);
        visited[source] = 1;

        while (!unvisited.empty())
        {
            int u = unvisited.front(); unvisited.pop();
            for (int i = link[u]; i != -1; i = arcs[i].next)
                if (!visited[arcs[i].v] && arcs[i].residual > 0)
                {
                    unvisited.push(arcs[i].v);
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
        link = new int[v], parent = new int[v], visited = new int[v], arcs = new arc[e];
        idx = 0, source = s, sink = t;
        memset(link, 0xff, vertices * sizeof(int));
    }

    ~EdmondsKarp()
    {
        delete [] link, parent, visited, arcs;
    }

    int maxFlow()
    {
        int netFlow = 0;

        while (bfs())
        {
            int delta = INF;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
                delta = min(delta, arcs[i].residual);

            netFlow += delta;
            for (int i = parent[sink]; i != -1; i = parent[arcs[i].u])
            {
                arcs[i].residual -= delta;
                arcs[i ^ 1].residual += delta;
            }
        }

        return netFlow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, link[u]};
        link[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, link[v]};
        link[v] = idx++;
    }
};
