// Cheerleaders
// UVa ID: 11806
// Verdict: Accepted
// Submission Date: 2023-04-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int dp[510][510] = {}, MOD = 1000007;
    dp[0][0] = 1;
    for (int i = 1; i <= 500; i++) {
        dp[i][0] = dp[i][i] = 1;
        for (int j = 1; j < i; j++)
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
    }    
    int T, M, N, K;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> M >> N >> K;
        if (K > M * N) { cout << 0 << '\n'; continue; }
        if (K == M * N) { cout << 1 << '\n'; continue; }
        int cnt = 0;
        for (int i = 0; i < 16; i++) {
            int r = M, c = N;
            if (i & 1) r--;
            if (i & 2) r--;
            if (i & 4) c--;
            if (i & 8) c--;
            cnt += MOD + dp[r * c][K] * (__builtin_popcount(i) % 2 ? -1 : 1);
            cnt %= MOD;
        }
        cout << cnt << '\n';
    }
    return 0;
}
