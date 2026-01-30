// Cousin
// UVa ID: 11104
// Verdict: Accepted
// Submission Date: 2026-01-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算最长公共子序列长度
int lcsLength(const string& a, const string& b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        string x, y;
        cin >> x >> y;
        if (x == "0" && y == "0") break;
        int lcs = lcsLength(x, y);
        int cousin = 1;
        int lenx = x.length(), leny = y.length();
        if (lenx > leny) swap(lenx, leny);
        while (lcs + lcs < leny) {
            lcs += lenx, lenx <<= 1;
            cousin++;
        }
        cout << cousin << '\n';
    }
    return 0;
}
