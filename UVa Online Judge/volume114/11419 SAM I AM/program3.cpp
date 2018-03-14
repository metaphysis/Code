// SAM I AM
// UVa ID: 11419
// Verdict: Accepted
// Submission Date: 2017-10-09
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, INF = 0x3fffffff;

vector<int> edges[MAXV];
int visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV], tx, ty;
int inx[MAXV], iny[MAXV], mx[MAXV], my[MAXV];

int bfs()
{
    int dist = INF;
    memset(dx, -1, sizeof(dx)); memset(dy, -1, sizeof(dy));

    queue<int> q;
    for (int i = 1; i <= tx; i++)
        if (!cx[i])
        {
            q.push(i);
            dx[i] = 0;
        }
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dx[u] > dist) break;
        for (auto v : edges[u])
            if (dy[v] == -1)
            {
                dy[v] = dx[u] + 1;

                if (!cy[v])
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
    for (auto v : edges[u])
        if (!visited[v] && dy[v] == (dx[u] + 1))
        {
            visited[v] = 1;
            if (cy[v] && dy[v] == dist) continue;
            if (!cy[v] || dfs(cy[v]))
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
    memset(cx, 0, sizeof(cx)); memset(cy, 0, sizeof(cy));
    while (bfs())
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= tx; i++)
            if (!cx[i])
                matches += dfs(i);
    }
    return matches;
}

void mark(int u)
{
    mx[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
        {
            visited[v] = 1, my[v] = 1;
            mark(cy[v]);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r, c, n, x, y;
    while (cin >> r >> c >> n, r > 0)
    {
        tx = r, ty = c;

        for (int i = 1; i <= tx; i++)
            edges[i].clear();

        memset(inx, 0, sizeof inx); memset(iny, 0, sizeof iny);
        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y;
            edges[x].push_back(y);
            inx[x] = iny[y] = 1;
        }
        
        cout << hopcroftKarp();
        
        memset(mx, 0, sizeof mx); memset(my, 0, sizeof my);
        for (int u = 1; u <= tx; u++)
            if (inx[u] && !cx[u])
            {
                memset(visited, 0, sizeof visited);
                mark(u);
            }
        
        for (int i = 1; i <= tx; i++)
            if (inx[i] && !mx[i]) cout << " r" << i;
        for (int i = 1; i <= ty; i++)
            if (iny[i] && my[i]) cout << " c" << i;

        cout << '\n';
    }

    return 0;
}
