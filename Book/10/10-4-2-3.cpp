const int MAXV = 110, INF = 0x3fffffff;

struct edge
{
    int u, v, weight;
};

list<edge> edges[MAXV];
int dist[MAXV], visited[MAXV], counter[MAXV], n;

bool spfa(int u)
{
    for(int i = 0; i < MAXV; i++) dist[i] = INF, visited[i] = 1, counter[i] = 0;

    queue<int> q; q.push(u);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        
        if (counter[u] > n) return true;
        
        visited[u] = 0;
        for (auto e : edges[u])
        {
            if(dist[e.v] > dist[u] + e.weight)
            {
                dist[e.v] = dist[u] + e.weight;
                if(!visited[e.v])
                {
                    q.push(e.v);
                    visited[e.v] = 1, counter[e.v]++;
                }
            }
        }
    }

    return false;
}
