const int MAXV = 500, INF = 0x3fffffff;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV];
int tx, ty;

int bfs()
{
    int dist = INF;
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy));

    queue<int> q;
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            q.push(i);
            dx[i] = 0;
        }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dx[u] > dist) break;
        for (int v = 0; v < ty; v++)
            if (g[u][v] && dy[v] == -1)
            {
                dy[v] = dx[u] + 1;

                if (cy[v] == -1)
                    dist = dy[v];
                else
                {
                    dx[cy[v]] = dy[v] + 1;
                    q.push(cy[v]);
                }
            }
    }
    return dist != INF;
}

int dfs(int u)
{
    int dist = INF;
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v] && dy[v] == (dx[u] + 1))
        {
            visited[v] = 1;
            if (cy[v] != -1 && dy[v] == dist) continue;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hopcroftKarp()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    while (bfs())
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < tx; i++)
            if (cx[i] == -1)
                matches += dfs(i);
    }
    return matches;
}
