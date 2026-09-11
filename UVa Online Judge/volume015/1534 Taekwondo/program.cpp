// Taekwondo
// UVa ID: 1534
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.480s


#include <bits/stdc++.h>
using namespace std;

double solveCase(int n1, int n2, vector<double>& g1, vector<double>& g2) {
    sort(g1.begin(), g1.end());
    sort(g2.begin(), g2.end());
    if (n1 > n2) {
        swap(n1, n2);
        swap(g1, g2);
    }
    const double INF = 1e18;
    vector<vector<double>> dp(n1 + 1, vector<double>(n2 + 1, INF));
    for (int j = 0; j <= n2; ++j) dp[0][j] = 0.0;
    for (int i = 1; i <= n1; ++i)
        for (int j = i; j <= n2; ++j)
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j - 1] + fabs(g1[i - 1] - g2[j - 1]));
    return dp[n1][n2];
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n1, n2;
        cin >> n1 >> n2;
        vector<double> g1(n1), g2(n2);
        for (int i = 0; i < n1; ++i) cin >> g1[i];
        for (int i = 0; i < n2; ++i) cin >> g2[i];
        double ans = solveCase(n1, n2, g1, g2);
        printf("%.1f\n", ans);
    }
    return 0;
}
