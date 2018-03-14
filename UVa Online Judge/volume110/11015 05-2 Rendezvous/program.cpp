// 05-2 Rendezvous
// UVa ID: 11015
// Verdict: Accepted
// Submission Date: 2018-02-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    int n, m, u, v, w;
    string names[110];
    int cost[110][110];

    while (cin >> n >> m, n > 0)
    {
        for (int i = 1; i <= n; i++) cin >> names[i];

        memset(cost, 0x3f, sizeof(cost));
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v >> w;
            cost[u][v] = cost[v][u] = w;
        }
        for (int i = 1; i <= n; i++) cost[i][i] = 0;

        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

        int minCost = 0x3f3f3f3f, selectedI = -1;
        for (int i = 1; i <= n; i++)
        {
            int maxCost = 0;
            for (int j = 1; j <= n; j++) maxCost += cost[i][j];
            if (maxCost < minCost)
            {
                minCost = maxCost;
                selectedI = i;
            }
        }

        cout << "Case #" << ++cases << " : " << names[selectedI] << '\n';
    }

    return 0;
}
