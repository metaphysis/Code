// Binary Search Tree
// UVa ID: 12809
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.050s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<double> p(N);
        for (int i = 0; i < N; ++i) cin >> p[i];
        vector<double> prefixSum(N + 1, 0.0);
        for (int i = 0; i < N; ++i) prefixSum[i + 1] = prefixSum[i] + p[i];
        vector<vector<double>> dp(N, vector<double>(N, 0.0));
        for (int len = 1; len <= N; ++len) {
            for (int i = 0; i + len <= N; ++i) {
                int j = i + len - 1;
                double total = prefixSum[j + 1] - prefixSum[i];
                double best = 1e100;
                for (int k = i; k <= j; ++k) {
                    double leftCost = (k > i) ? dp[i][k - 1] : 0.0;
                    double rightCost = (k < j) ? dp[k + 1][j] : 0.0;
                    double cost = leftCost + rightCost + total;
                    if (cost < best) best = cost;
                }
                dp[i][j] = best;
            }
        }
        double answer = (N > 0) ? dp[0][N - 1] : 0.0;
        cout << fixed << setprecision(4) << answer << "\n";
    }
    return 0;
}
