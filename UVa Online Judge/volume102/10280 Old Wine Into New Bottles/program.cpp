// Old Wine Into New Bottles
// UVa ID: 10280
// Verdict: Accepted
// Submission Date: 2023-05-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv []) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    int dp[500010], minv[110], maxv[110], upv[110], v[4600];
    for (int cs = 0; cs < T; cs++) {
        if (cs) cout << '\n';
        int n, m;
        cin >> n >> m;
        n *= 1000;
        int flag = 0;
        for (int i = 1, k1, k2; i <= m; i++) {
            cin >> k1 >> k2;
            upv[i] = (k1 * k2 + k2 - k1 - 1) / (k2 - k1);
            minv[i] = k1, maxv[i] = k2;
            if (n >= upv[i]) flag = 1;
        }
        if (flag) { cout << "0\n"; continue; }
        memset(v, 0, sizeof v);
        for (int i = 1; i <= m; i++)
            for (int j = minv[i]; j <= maxv[i] && j <= n; j++)
                v[j] = 1;
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        for (int i = 0; i <= 4500; i++)
            if (v[i])
                for (int j = i; j <= n; j++)
                    if (dp[j - i])
                        dp[j] = 1;
        if (dp[n]) cout << "0\n";
        else {
            for (int i = n; i >= 0; i--)
                if (dp[i]) {
                    cout << n - i << '\n';
                    break;
                }
        }
    }
    return 0;
}
