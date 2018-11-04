// Speedy Escape
// UVa ID: 11693
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int n, m, e, b, p, dist[110][110], parent[110], visited[110], out[110];
double speed[110];
list<int> edges[110];

double dfs(int u)
{
    visited[u] = 1;
    if (u == b) return speed[u] = 0;
    if (u == p) return speed[u] = INF;
    if (dist[u][p] == 0) return speed[u] = INF;
    double r1 = dist[u][b] * 160.0 / dist[u][p];
    double r2 = INF;
    for (auto v : edges[u])
    {
        if (visited[v])
        {
            r2 = min(r2, speed[v]);
            continue;
        }
        r2 = min(r2, dfs(v));
    }
    return speed[u] = max(r1, r2);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m >> e;
        for (int i = 1; i <= n; i++)
            edges[i].clear();
        memset(dist, INF, sizeof(dist));
        for (int i = 1, aa, bb, ll; i <= m; i++)
        {
            cin >> aa >> bb >> ll;
            dist[aa][bb] = min(dist[aa][bb], ll);
            dist[bb][aa] = min(dist[bb][aa], ll);
            edges[aa].push_back(bb);
            edges[bb].push_back(aa);
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

        for (int i = 1; i <= e; i++)
            cin >> out[i];
        cin >> b >> p;

        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; i++)
            speed[i] = INF;
        for (int i = 1; i <= e; i++)
        {
            if (visited[out[i]]) continue;
            dfs(out[i]);
        }
        double min_speed = INF;
        for (int i = 1; i <= e; i++)
            min_speed = min(min_speed, speed[out[i]]);
        if (min_speed == INF) cout << "IMPOSSIBLE\n";
        else cout << fixed << setprecision(8) << min_speed << '\n';
    }

    return 0;
}
