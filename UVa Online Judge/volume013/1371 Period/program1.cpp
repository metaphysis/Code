// Period
// UVa ID: 1371
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 0.220s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 5004;
const int MAX_M = 52;

int n, m;
char yStr[MAX_M], xStr[MAX_N];
int dp[MAX_N][MAX_M];

bool check(int k) {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    
    for (int i = 0; i <= n; ++i) {
        if (dp[i][m] <= k) dp[i][0] = 0;
        
        for (int j = 0; j <= m; ++j) {
            if (dp[i][j] > k) continue;
            
            if (i < n && j < m) {
                int cost = (xStr[i + 1] == yStr[j + 1]) ? 0 : 1;
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + cost);
            }
            if (i < n) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            if (j < m) dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
        }
    }
    
    return dp[n][m] <= k;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", yStr + 1);
        scanf("%s", xStr + 1);
        m = strlen(yStr + 1);
        n = strlen(xStr + 1);
        
        int left = 0, right = m, ans = m;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid)) {
                ans = mid;
                right = mid - 1;
            } else left = mid + 1;
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
