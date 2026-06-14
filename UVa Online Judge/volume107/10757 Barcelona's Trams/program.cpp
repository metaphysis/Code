// Barcelona's Trams
// UVa ID: 10757
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

double solveTestCase(double M0, int n, const vector<double>& lengths) {
    // dp[i][c] = 从路段 i 开始，已发生 c 次事故的最小期望时间
    vector<vector<double>> dp(n + 1, vector<double>(M0 + 2, 0.0));
    
    for (int i = n - 1; i >= 0; --i) {
        double L = lengths[i];
        for (int c = 0; c <= M0; ++c) {
            double M = M0 - c;
            if (M <= 0) {
                dp[i][c] = 1e18;
                continue;
            }
            double Ec = dp[i + 1][c];
            double Ec1 = dp[i + 1][c + 1];
            double delta = 10.0 + L / 10.0 + Ec1 - Ec;
            double v = sqrt(L * M / delta);
            if (v > M) v = M;
            dp[i][c] = L / v + Ec - L / (2.0 * M) + v / M * delta;
        }
    }
    return dp[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        double M0;
        int n;
        ss >> M0 >> n;
        if (ss.fail()) break;
        
        vector<double> lengths(n);
        for (int i = 0; i < n; ++i) {
            ss >> lengths[i];
            if (ss.fail()) return 0;
        }
        
        double result = solveTestCase(M0, n, lengths);
        cout << fixed << setprecision(4) << result << '\n';
    }
    return 0;
}
