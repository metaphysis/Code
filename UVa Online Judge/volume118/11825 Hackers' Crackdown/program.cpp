// Hackers' Crackdown
// UVa ID: 11825
// Verdict: Accepted
// Submission Date: 2023-06-05
// UVa Run Time: 0.830s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int dp[1 << 16], mask[1 << 16], link[16], n;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    while (cin >> n, n) {
        for (int i = 0, m; i < n; i++) {
            link[i] = 1 << i;
            cin >> m;
            for (int j = 0, k; j < m; j++) {
                cin >> k;
                link[i] |= 1 << k;
            }
        }
        for (int i = 0; i < 1 << n; i++) {
            mask[i] = 0;
            for (int j = 0; j < n; j++)
                if (i & (1 << j))
                    mask[i] |= link[j];
        }
        int all = (1 << n) - 1;
        dp[0] = 0;
        for (int i = 1; i < 1 << n; i++) {
            dp[i] = 0;
            for (int s = i; s; s = (s - 1) & i)
                if (mask[s] == all)
                    dp[i] = max(dp[i], dp[i ^ s] + 1);
        }
        cout << "Case " << cases++ << ": " << dp[(1 << n) - 1] << '\n';
    }
    return 0;
}
