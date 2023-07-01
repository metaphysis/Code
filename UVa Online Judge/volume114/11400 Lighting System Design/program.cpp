// Lighting System Design
// UVa ID: 11400
// Verdict: Accepted
// Submission Date: 2023-07-01
// UVa Run Time: 0.070s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct lamp {
    int V, K, C, L;
    bool operator<(const lamp &l) const { return V < l.V; }
} lamps[1010];

int sum[1010], dp[1010];

int dfs(int n) {
    if (n == 0) return 0;
    if (~dp[n]) return dp[n];
    int r = sum[n] * lamps[n].C;
    for (int j = 1; j < n; j++) r = min(r, dfs(j) + (sum[n] - sum[j]) * lamps[n].C);
    return dp[n] = r + lamps[n].K;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++)
            cin >> lamps[i].V >> lamps[i].K >> lamps[i].C >> lamps[i].L;
        sort(lamps + 1, lamps + n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + lamps[i].L;
        memset(dp, -1, sizeof dp);
        cout << dfs(n) << '\n';
    }
    return 0;
}
