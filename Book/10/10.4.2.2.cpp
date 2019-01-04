const int MAXV = 100, MAXE = 10000, INF = 0x3f3f3f3f;

struct edge { int u, v, weight, next; } edges[MAXE];

int n, m, head[MAXV];
int dist[MAXV], parent[MAXV];
int visited[MAXV], cnt[MAXV];

bool spfa(int s)
{
    for (int i = 0; i < n; i++)
        dist[i] = INF, parent[i] = -1, visited[i] = 0, cnt[i] = 0;
    dist[s] = 0, visited[s] = 1;
    
    queue<int> q; q.push(s);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (cnt[u] > n) return true;
        visited[u] = 0;
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            int v = edges[i].v, w = edges[i].weight;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                if (!visited[v])
                {
                    q.push(v);
                    visited[v] = 1;
                    cnt[v]++;
                }
            }
        }
    }

    return false;
}
