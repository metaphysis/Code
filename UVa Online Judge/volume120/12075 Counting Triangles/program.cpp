// Counting Triangles
// UVa ID: 12075
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int MAX = 1005;
int64 dp[MAX][MAX];

int64 comb3(int64 n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}

void initialize() {
    for (int i = 2; i < MAX; ++i)
        for (int j = 2; j < MAX; ++j)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + __gcd(i, j) - 1;
    
    for (int i = 2; i < MAX; ++i)
        for (int j = 2; j < MAX; ++j)
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
}

int main() {
    initialize();
    int m, n;
    int caseNum = 1;
    while (cin >> m >> n && (m || n)) {
        m++; n++;
        int64 total = comb3(m * n);
        int64 horizontal = comb3(m) * n;
        int64 vertical = comb3(n) * m;
        int64 slant = dp[m - 1][n - 1] * 2;
        int64 result = total - horizontal - vertical - slant;
        cout << "Case " << caseNum++ << ": " << result << endl;
    }
    
    return 0;
}
