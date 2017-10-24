const int MAXV = 1100, MAXE = 2100, INF = 100000000;

struct edge { int from, to, weight; } edge edges[MAXE];
int dist[MAXV], parent[MAXV], n, m;

// edges为边列表，predecessor保存各顶点的前驱，n为顶点数目，m为边的数目，
// source为起始顶点的序号。
bool bellmanFord(int source)
{
    // 初始化距离为无限大。各顶点的前驱顶点为未定义。
    for (int i = 0; i <= n; i++) dist[i] = INF, parent[i] = -1;
    dist[source] = 0;
    
    // 松弛。迭代次数为顶点数目减一。
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
            
        // 若距离未更新，退出迭代。
        if (!updated) break;
    }

    // 检查是否存在权和为负值的环。
    bool cycled = false;
    for (int i = 1; i <= m; i++)
        if (dist[edges[i].to] > dist[edges[i].from] + edges[i].weight)
        {
            cycled = true;
            break;
        }
    
    // 返回是否存在权和为负值的环。
    return cycled;
}
