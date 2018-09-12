// Forming Quiz Teams
// UVa ID: 10911
// Verdict: Accepted
// Submission Date: 2018-05-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 24, INF = 0x3f3f3f3f;

double dist[MAXN][MAXN], minDist;
int n, used[MAXN];

void dfs(int depth, double cost)
{
    if (cost > minDist) return;

    if (depth * 2 == n)
    {
        minDist = min(minDist, cost);
        return;
    }

    int u = 0;
    for (; u < n; u++)
        if (!used[u])
        {
            used[u] = 1;
            break;
        }
        
    for (int v = u + 1; v < n; v++)
        if (!used[v])
        {
            used[v] = 1;
            dfs(depth + 1, cost + dist[u][v]);
            used[v] = 0;
        }
        
    if (depth) used[u] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, xs[16], ys[16];
    string name;

    while (cin >> n, n > 0)
    {
        n *= 2;
        for (int i = 0; i < n; i++)
            cin >> name >> xs[i] >> ys[i];

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                dist[i][j] = dist[j][i] = hypot(xs[i] - xs[j], ys[i] - ys[j]);

        minDist = INF;
        memset(used, 0, sizeof(used));
        dfs(0, 0);            
        
        cout << "Case " << ++cases << ": ";
        cout << fixed << setprecision(2) << minDist << '\n';
    }

    return 0;
}
