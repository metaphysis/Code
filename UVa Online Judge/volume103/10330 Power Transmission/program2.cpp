// Power Transmission
// UVa ID: 10330
// Verdict: Accepted
// Submission Date: 2019-06-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

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
        int u, v, r, advanced = 0, volume = INF, flow = 0;

        if (!bfs()) return flow;

        // Current arc optimization.
        memcpy(current, head, sizeof(head));
        u = father[source] = source;

        while (d[source] < vertices)
        {
            advanced = 0;
            for (int &i = current[u]; ~i; i = arcs[i].next)
            {
                v = arcs[i].v, r = arcs[i].residual;
                if (d[u] == (d[v] + 1) && r > 0)
                {
                    // Advance.
                    father[v] = u, u = v;
                    volume = volume < r ? volume : r;
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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    ISAP isap;
    int n, m, u, v, w, B, D, capacity[110];

    while (cin >> n)
    {
        isap.initialize(2 * n + 2, 0, 2 * n + 1);

        for (int i = 1; i <= n; i++)
        {
            cin >> capacity[i];
            isap.addArc(i, n + i, capacity[i]);
        }
        
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            isap.addArc(n + u, v, w);
        }

        cin >> B >> D;
        for (int i = 1; i <= B; i++)
        {
            cin >> u;
            isap.addArc(0, u, capacity[u]);
            
        }
        for (int i = 1; i <= D; i++)
        {
            cin >> u;
            isap.addArc(n + u, 2 * n + 1, capacity[u]);
        }
        cout << isap.maxFlow() << '\n';
    }

    return 0;
}
