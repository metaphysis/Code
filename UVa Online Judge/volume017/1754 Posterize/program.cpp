#include <bits/stdc++.h>
using namespace std;

long long getCost(const vector<long long>& sumP, const vector<long long>& sumR, const vector<long long>& sumR2, int l, int r) {
    long long p = sumP[r] - sumP[l - 1], s = sumR[r] - sumR[l - 1], q = sumR2[r] - sumR2[l - 1];
    long long v = s / p, ans = q - 2 * v * s + v * v * p;
    v++;
    ans = min(ans, q - 2 * v * s + v * v * p);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int d, k;
    while (cin >> d >> k) {
        vector<long long> sumP(d + 1), sumR(d + 1), sumR2(d + 1);
        for (int i = 1; i <= d; i++) {
            long long r, p;
            cin >> r >> p;
            sumP[i] = sumP[i - 1] + p;
            sumR[i] = sumR[i - 1] + r * p;
            sumR2[i] = sumR2[i - 1] + r * r * p;
        }
        const long long inf = LLONG_MAX / 4;
        vector<vector<long long>> dp(k + 1, vector<long long>(d + 1, inf));
        dp[0][0] = 0;
        for (int g = 1; g <= k; g++)
            for (int i = g; i <= d; i++)
                for (int j = g - 1; j < i; j++)
                    dp[g][i] = min(dp[g][i], dp[g - 1][j] + getCost(sumP, sumR, sumR2, j + 1, i));
        cout << dp[k][d] << '\n';
    }
    return 0;
}
