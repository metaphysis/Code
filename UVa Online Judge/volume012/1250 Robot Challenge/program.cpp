// Robot Challenge
// UVa ID: 1250
// Verdict: Accepted
// Submission Date: 2018-12-09
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, visited[1024];
double X[1024], Y[1024], P[1024], dist[1024][1024], dp[1024];

double dfs(int u)
{
    if (u == N - 1) return 0;
    if (visited[u]) return dp[u];
    visited[u] = 1;
    double r = 1e20, p = 0;
    for (int i = u + 1; i < N; i++)
    {
        r = min(r, dist[u][i] + p + 1.0 + dfs(i));
        p += P[i];
    }
    return dp[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N)
    {
        if (N == 0) break;
        for (int i = 1; i <= N; i++)
            cin >> X[i] >> Y[i] >> P[i];
        X[0] = 0, Y[0] = 0, P[0] = 0;
        X[N + 1] = 100, Y[N + 1] = 100, P[N + 1] = 0;
        N += 2;
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                dist[i][j] = sqrt(pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));
        memset(visited, 0, sizeof(visited));
        double r = dfs(0);
        cout << fixed << setprecision(3) << r << '\n';
    }

    return 0;
}
