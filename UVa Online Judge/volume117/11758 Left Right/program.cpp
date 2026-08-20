#include <bits/stdc++.h>
using namespace std;

const int maxN = 10000;
const int maxK = 105;
const long long mod = 1000000007;

long long comb[maxN + 1][maxK];

void initComb() {
    for (int i = 0; i <= maxN; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= min(i, maxK - 1); j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k, d;
    cin >> t;
    initComb();
    while (t--) {
        cin >> n >> k >> d;
        k /= 2;
        int limit = n - 2 * k;
        vector<vector<long long>> dp(16, vector<long long>(limit + 1, 0));
        dp[0][0] = 1;
        for (int level = 0; level < 15; level++) {
            for (int j = 0; j * (1 << level) <= n && j <= k; j += d + 1) {
                int num = j * (1 << level);
                for (int sum = limit; sum >= num; sum--)
                    dp[level + 1][sum] = (dp[level + 1][sum] + dp[level][sum - num] * comb[k][j]) % mod;
            }
        }
        long long ans = comb[n][2 * k];
        for (int i = 0; i <= limit; i++) {
            long long lose = comb[n - i - k][k] * dp[15][i] % mod;
            ans = (ans - lose + mod) % mod;
        }
        cout << ans << '\n';
    }
    return 0;
}
