#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1 << 20, INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
} arcs[MAXE];

struct ISAP
{
    int vertices, source, sink;
    int idx, head[MAXV], d[MAXV], father[MAXV], current[MAXV], gap[MAXV];

    void initialize(int V, int S, int T)
    {
        idx = 0;
        vertices = V, source = S, sink = T;
        memset(head, -1, sizeof(head));
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }

    bool bfs()
    {
        int u, v;

        for (int i = 0; i < vertices; i++) d[i] = vertices;

        queue<int> q;
        q.push(sink);
        d[sink] = 0;

        while (!q.empty())
        {
            u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = arcs[i].next)
            {
                v = arcs[i].v;
                if (d[v] == vertices && arcs[i ^ 1].residual)
                {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }

        // Gap initialization.
        memset(gap, 0, sizeof(gap));
        for (int i = 0; i < vertices; i++) gap[d[i]]++;

        return d[source] < vertices;
    }

    int maxFlow()
    {
        int u, v, advanced, volume = INF, flow = 0;

        if (!bfs()) return flow;

        // Current arc optimization.
        memcpy(current, head, sizeof(head));
        u = father[source] = source;

        while (d[source] < vertices)
        {
            advanced = 0;
            for (int &i = current[u]; ~i; i = arcs[i].next)
            {
                v = arcs[i].v;
                if (d[u] == (d[v] + 1) && arcs[i].residual)
                {
                    // Advance.
                    father[v] = u, u = v;
                    volume = min(volume, arcs[i].residual);
                    if (v == sink)
                    {
                        // Augment.
                        flow += volume;
                        for (u = father[v]; u != source; u = father[u])
                        {
                            arcs[current[u]].residual -= volume;
                            arcs[current[u] ^ 1].residual += volume;
                        }
                        volume = INF;
                    }
                    advanced = 1;
                    break;
                }
            }
            if (advanced) continue;

            // Retreat.
            int dist = vertices - 1;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (arcs[i].residual && d[arcs[i].v] < dist)
                {
                    dist = d[arcs[i].v];
                    current[u] = i;
                }

            // Gap optimization.
            if (--gap[d[u]] == 0) break;
            d[u] = dist + 1, ++gap[d[u]];
            u = father[u];
        }

        return flow;
    }
};

int main(int argc, char *argv[])
{
    ISAP isap;

    isap.initialize(101, 0, 100);

    return 0;
}
