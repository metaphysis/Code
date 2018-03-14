// The Orc Attack
// UVa ID: 10793
// Verdict: Accepted
// Submission Date: 2018-02-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, INF = 0x3f3f3f3f;

int n, m, dist[MAXV][MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, u, v, w;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= n; i++) dist[i][i] = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            dist[u][v] = dist[v][u] = min(dist[u][v], w);
        }
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        int shortest = INF;
        for (int i = 6; i <= n; i++)
        {
            bool valid = true;
            if (dist[i][1] == INF) valid = false;
            for (int j = 2; j <= 5; j++)
                if (dist[i][j] != dist[i][j - 1])
                {
                    valid = false;
                    break;
                }
            if (valid)
            {
                int farthest = 0;
                for (int j = 1; j <= n; j++)
                    farthest = max(farthest, dist[i][j]);
                shortest = min(shortest, farthest);
            }
        }
        if (shortest == INF) shortest = -1;
        cout << "Map " << c << ": " << shortest << '\n';
    }

    return 0;
}
