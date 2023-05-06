// Funny Cardiologist
// UVa ID: 13122
// Verdict: Accepted
// Submission Date: 2023-05-06
// UVa Run Time: 1.320s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, m, xi[260], yi[260];
double dp[260][260][260];

double dfs(int idx, int last, int removed) {
    if (removed > m) return 1e10;
    if (idx == n - 1) {
        if (removed == m) return hypot(xi[n - 1] - xi[last], yi[n - 1] - yi[last]);
        return 1e10;
    }
    if (dp[idx][last][removed] >= 0) return dp[idx][last][removed];
    double r = dfs(idx + 1, last, removed + 1);
    r = min(r, dfs(idx + 1, idx, removed) + hypot(xi[idx] - xi[last], yi[idx] - yi[last]));
    return dp[idx][last][removed] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(3);
    while (cin >> n >> m) {
        for (int i = 0; i < n; i++) cin >> xi[i] >> yi[i];
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                for (int k = 0; k <= m; k++)
                    dp[i][j][k] = -1;
        cout << dfs(1, 0, 0) << '\n';
    }
    return 0;
}
