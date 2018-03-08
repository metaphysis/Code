const int MAXV = 1100, MAXE = 2100, INF = 0x3fffffff;

struct edge { int from, to, weight; } edges[MAXE];
int dist[MAXV], parent[MAXV], n, m;

bool bellmanFord(int u)
{
    for (int i = 0; i <= n; i++) dist[i] = INF, parent[i] = -1;
    dist[u] = 0;

    for (int k = 1; k < n; k++)
    {
        bool updated = false;
        for (int i = 1; i <= m; i++)
            if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
            {
                dist[edges[i].to] = dist[edges[i].from] + edges[i].weight;
                parent[edges[i].to] = edges[i].from;
                updated = true;
            }
        if (!updated) break;
    }
    bool cycled = false;
    for (int i = 1; i <= m; i++)
        if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
        {
            cycled = true;
            break;
        }    

    return cycled;
}
