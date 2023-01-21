// The Book-Shelver's Problem
// UVa ID: 10239
// Verdict: Accepted
// Submission Date: 2023-01-21
// UVa Run Time: 0.080s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int n;
double W, hi[1010], wi[1010], dp[1010], visited[1010];
double dfs(int idx) {
    if (dp[idx] > 0) return dp[idx];
    if (idx == n) return 0;
    int nxt = idx;
    double w = 0, H = 0, r = 1e8;
    while (nxt < n) {
        H = max(hi[nxt], H);
        w += wi[nxt];
        if (w - W > 1e-6) break;
        r = min(r, H + dfs(nxt + 1));
        nxt++;
    }
    return dp[idx] = r;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> W, n) {
        for (int i = 0; i < n; i++) cin >> hi[i] >> wi[i];
        for (int i = 0; i <= n; i++) dp[i] = -1.0;
        cout << fixed << setprecision(4) << dfs(0) << '\n';
    }
    return 0;
}
