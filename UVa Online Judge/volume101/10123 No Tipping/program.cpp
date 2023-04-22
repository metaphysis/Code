// No Tipping
// UVa ID: 10123
// Verdict: Accepted
// Submission Date: 2023-04-22
// UVa Run Time: 0.080s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

double L, W;
int n, p[20], w[20], dp[1 << 20];
bool dfs(int mask, double tl, double tr) {
    if (!mask) return true;
    if (~dp[mask]) return dp[mask];
    int bit = mask;
    while (bit) {
        int b = __builtin_ctz(bit);
        bit ^= (1 << b);
        double ntl = tl, ntr = tr;
        if (p[b] <= -1.5) {
            ntl -= abs(p[b] + 1.5) * w[b];
            ntr += abs(p[b] - 1.5) * w[b];
        } else if (p[b] <= 1.5) {
            ntl += abs(p[b] + 1.5) * w[b];
            ntr += abs(p[b] - 1.5) * w[b];
        } else {
            ntl += abs(p[b] + 1.5) * w[b];
            ntr -= abs(p[b] - 1.5) * w[b];
        }
        if (ntl > 0 || ntr > 0) continue;
        if (dfs(mask ^ (1 << b), ntl, ntr))
            return dp[mask] = b + 1;
    }
    return dp[mask] = 0;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> L >> W >> n) {
        if (L == 0) break;
        cout << "Case " << cases++ << ":\n";
        double tl = W * (pow(L / 2 - 1.5, 2) - pow(L / 2 + 1.5, 2)) / (2 * L);
        double tr = tl;
        for (int i = 0; i < n; i++) {
            cin >> p[i] >> w[i];
            if (p[i] <= -1.5) {
                tl += abs(p[i] + 1.5) * w[i];
                tr -= abs(p[i] - 1.5) * w[i];
            } else if (p[i] <= 1.5) {
                tl -= abs(p[i] + 1.5) * w[i];
                tr -= abs(p[i] - 1.5) * w[i];
            } else {
                tl -= abs(p[i] + 1.5) * w[i];
                tr += abs(p[i] - 1.5) * w[i];
            }
        }
        if (tl > 0 || tr > 0) { cout << "Impossible\n"; continue; }
        memset(dp, -1, sizeof(int) * (1 << n));
        int mask = (1 << n) - 1;
        if (dfs(mask, tl, tr)) {
            while (mask) {
                int b = dp[mask] - 1;
                cout << p[b] << ' ' << w[b] << '\n';
                mask ^= (1 << b);
            }
        } else cout << "Impossible\n";
    }
    return 0;
}
