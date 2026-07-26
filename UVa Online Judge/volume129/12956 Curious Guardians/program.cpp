// Curious Guardians
// UVa ID: 12956
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
long long C[105][105];

void init() {
    for (int i = 0; i <= 100; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    int N, K;
    while (cin >> N >> K) {
        if (N == 1) { cout << 1 << "\n"; continue; }
        if (N == 2) { cout << 1 << "\n"; continue; }
        int L = N - 2;
        int M = K - 1;
        vector<vector<long long>> dp(N + 1, vector<long long>(L + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j <= L; ++j) {
                if (dp[i-1][j] == 0) continue;
                int maxX = min(M, L - j);
                for (int x = 0; x <= maxX; ++x)
                    dp[i][j + x] = (dp[i][j + x] + dp[i-1][j] * C[L - j][x]) % MOD;
            }
        }
        cout << dp[N][L] << "\n";
    }
    return 0;
}
