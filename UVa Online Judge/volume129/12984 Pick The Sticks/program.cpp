#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n, l;
        cin >> n >> l;
        int limit = 2 * l;
        const long long negInf = -(1LL << 60);
        vector<vector<long long> > dp(3, vector<long long>(limit + 1, negInf));
        dp[0][0] = 0;
        long long maxValue = 0;
        for (int i = 0; i < n; i++) {
            int a;
            long long v;
            cin >> a >> v;
            maxValue = max(maxValue, v);
            for (int k = 2; k >= 0; k--)
                for (int j = limit; j >= 0; j--) {
                    if (dp[k][j] == negInf)
                        continue;
                    if (j + 2 * a <= limit)
                        dp[k][j + 2 * a] = max(dp[k][j + 2 * a], dp[k][j] + v);
                    if (k < 2 && j + a <= limit)
                        dp[k + 1][j + a] = max(dp[k + 1][j + a], dp[k][j] + v);
                }
        }
        long long answer = maxValue;
        for (int k = 0; k <= 2; k++)
            for (int j = 0; j <= limit; j++)
                answer = max(answer, dp[k][j]);
        cout << "Case #" << caseId << ": " << answer << '\n';
    }
    return 0;
}
