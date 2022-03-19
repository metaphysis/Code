#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, MAXE = 1 << 20, INF = 0x7fffffff;

struct arc
{
    int u, v, capacity, residual, next;
} arcs[MAXE];

struct ISAP
{
    int idx, vertices, source, sink;
    int head[MAXV], d[MAXV], father[MAXV], current[MAXV], gap[MAXV], q[MAXV];

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
        int u, v, front, rear;

        memset(d, 0, sizeof(d));
        memset(gap, 0, sizeof(gap));
        memcpy(current, head, sizeof(head));

        gap[d[sink] = 1]++;
        q[front = rear = 0] = sink;

        while (front <= rear) {
            u = q[front++];
            for (int i = head[u]; ~i; i = arcs[i].next) {
                v = arcs[i].v;
                if (!d[v] && arcs[i ^ 1].residual) {
                    gap[d[v] = d[u] + 1]++;
                    q[++rear] = v;
                }
            }
        }

        return d[source] <= vertices;
    }

    int dfs(int u, int volume)
    {
        if (u == sink) return volume;
        int flow = 0;
        for (int &i = current[u]; ~i; i = arcs[i].next) {
            int v = arcs[i].v;
            if (d[u] == d[v] + 1 && arcs[i].residual) {
                int tmp = dfs(v, min(volume, arcs[i].residual));
                flow += tmp, volume -= tmp;
                arcs[i].residual -= tmp, arcs[i ^ 1].residual += tmp;
                if (!volume) return flow;
            }
        }
        if (!(--gap[d[u]])) d[source] = vertices + 1;
        gap[++d[u]]++, current[u] = head[u];
        return flow;
    }

    int maxFlow()
    {
        if (!bfs()) return 0;
        int flow = dfs(source, INF);
        while (d[source] <= vertices) flow += dfs(source, INF);
        return flow;
    }
};

int main(int argc, char *argv[])
{
    ISAP isap;

    isap.initialize(101, 0, 100);

    return 0;
}
