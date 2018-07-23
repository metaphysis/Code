// Routing
// UVa ID: 1057
// Verdict: Accepted
// Submission Date: 2018-07-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// http://apps.topcoder.com/forums/?module=Thread&threadID=662332&start=0

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int dist[105][105], dp[105][105], visited[105][105];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, x, y;
    int cases = 0;
    while (cin >> n >> m, n)
    {
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = INF;

        for (int i = 0; i < m; i++)
        {
            cin >> x >> y;
            dist[x][y] = 1;
        }

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dp[i][j] = INF;

        queue<pair<int, int>> q;
        q.push(make_pair(1, 1));

        dp[1][1] = 1;
        pair<int, int> p;
        while (!q.empty())
        {
            p = q.front(), q.pop();
            x = p.first, y = p.second;
            visited[x][y] = 0;
            for (int i = 1; i <= n; i++)
            {
                int cost = (x != i && y != i);
                if (dist[x][i] == 1 && dp[i][y] > dp[x][y] + cost)
                {
                    dp[i][y] = dp[x][y] + cost;
                    if (!visited[i][y])
                    {
                        visited[i][y] = 1;
                        q.push(make_pair(i, y));
                    }
                }
                if (dist[i][y] == 1 && dp[x][i] > dp[x][y] + cost)
                {
                    dp[x][i] = dp[x][y] + cost;
                    if (!visited[x][i])
                    {
                        visited[x][i] = 1;
                        q.push(make_pair(x, i));
                    }
                }
            }
            if (x != y)
            {
                if (dp[y][x] > dp[x][y] + dist[x][y] - 1)
                {
                    dp[y][x] = dp[x][y] + dist[x][y] - 1;
                    if (!visited[y][x])
                    {
                        visited[y][x] = 1;
                        q.push(make_pair(y, x));
                    }
                }
            }
        }

        cout << "Network " << ++cases << "\n";
        if (dp[2][2] == INF) cout << "Impossible\n";
        else cout << "Minimum number of nodes = " << dp[2][2] << '\n';
        cout << '\n';
    }

    return 0;
}
