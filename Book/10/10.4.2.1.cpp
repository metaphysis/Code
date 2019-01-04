const int MAXV = 100, MAXE = 10000, INF = 0x3f3f3f3f;

struct edge { int u, v, weight; } edges[MAXE];
int dist[MAXV], parent[MAXV], n, m;

bool bellmanFord(int s)
{
    for (int i = 0; i < n; i++) dist[i] = INF, parent[i] = -1;
    dist[s] = 0;
    int updated = 1;
    for (int k = 1; k < n && updated; k++)
    {
        updated = 0;
        for (int i = 0; i < m; i++)
            if (dist[edges[i].v] > dist[edges[i].u] + edges[i].weight)
            {
                dist[edges[i].v] = dist[edges[i].u] + edges[i].weight;
                parent[edges[i].v] = edges[i].u;
                updated = 1;
            }
    }
    for (int i = 0; i < m; i++)
        if (dist[edges[i].v] > dist[edges[i].u] + edges[i].weight)
            return true;
    return false;
}
