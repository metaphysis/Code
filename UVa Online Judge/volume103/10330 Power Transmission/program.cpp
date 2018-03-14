// Power Transmission
// UVa ID: 10330
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
        int flow = 0;

        while (bfs())
            while (int delta = dfs(0, INF))
                flow += delta;

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

    int n, m, u, v, w, B, D, capacity[110];
    while (cin >> n)
    {
        Dinic dinic(256, 256 * 1024, 0, 2 * n + 1);
        
        for (int i = 1; i <= n; i++)
        {
            cin >> capacity[i];
            dinic.addArc(i, n + i, capacity[i]);
        }
        
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            dinic.addArc(n + u, v, w);
        }

        cin >> B >> D;
        for (int i = 1; i <= B; i++)
        {
            cin >> u;
            dinic.addArc(0, u, capacity[u]);
            
        }
        for (int i = 1; i <= D; i++)
        {
            cin >> u;
            dinic.addArc(n + u, 2 * n + 1, capacity[u]);
        }
        cout << dinic.maxFlow() << '\n';
    }

    return 0;
}
