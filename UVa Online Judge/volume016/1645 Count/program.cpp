// Count
// UVa ID: 1645
// Verdict: Accepted
// Submission Date: 2023-06-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int dp[1010], MOD = 1000000007;
    dp[1] = 1;
    for (int i = 2; i <= 1000; i++) {
        dp[i] = 0;
        for (int j = 1; j < i; j++)
            if ((i - 1) % j == 0)
                dp[i] = (dp[i] + dp[j]) % MOD;
    }
    int cases = 1, n;
    while (cin >> n)
        cout << "Case " << cases++ << ": " << dp[n] << '\n';
    return 0;
}
