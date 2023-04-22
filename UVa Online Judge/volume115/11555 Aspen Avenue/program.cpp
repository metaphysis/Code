// Aspen Avenue
// UVa ID: 11555
// Verdict: Accepted
// Submission Date: 2023-04-22
// UVa Run Time: 0.460s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, x[2010];
double L, W, s, dp[1010][1010], T;

double dfs(int up, int down) {
    if (up == T && down == T) return 0;
    if (dp[up][down] >= 0) return dp[up][down];
    double r = 1e10;
    if (up < T) r = abs(x[up + down + 1] - s * up) + dfs(up + 1, down);
    if (down < T) 
        r = min(r, sqrt(W * W + pow(x[up + down + 1] - s * down, 2)) + dfs(up, down + 1));
    return dp[up][down] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    while (cin >> n) {
        cin >> L >> W;
        T = n / 2;
        for (int i = 0; i <= T; i++)
            for (int j = 0; j <= T; j++)
                dp[i][j] = -1;
        for (int i = 1; i <= n; i++) cin >> x[i];
        sort(x + 1, x + n + 1);
        s = L / (T - 1);
        cout << dfs(0, 0) << '\n';
    }
    return 0;
}
