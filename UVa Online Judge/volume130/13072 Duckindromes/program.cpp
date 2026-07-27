// Duckindromes
// UVa ID: 13072
// Verdict: Accepted
// Submission Date: 2026-07-27
// UVa Run Time: 0.020s
// https://blog.csdn.net/metaphysis/article/details/163233097

#include <bits/stdc++.h>
using namespace std;

string buildLPS(const string& s, const vector<vector<int>>& dp, int i, int j) {
    if (i > j) return "";
    if (i == j) return string(1, s[i]);
    if (s[i] == s[j])
        return s[i] + buildLPS(s, dp, i + 1, j - 1) + s[j];
    if (dp[i + 1][j] >= dp[i][j - 1])
        return buildLPS(s, dp, i + 1, j);
    return buildLPS(s, dp, i, j - 1);
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        int n = (int)line.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) dp[i][i] = 1;
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                int j = i + len - 1;
                if (line[i] == line[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        cout << buildLPS(line, dp, 0, n - 1) << '\n';
    }
    return 0;
}
