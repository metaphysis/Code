// Allergy Test
// UVa ID: 11691
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 1.540s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int numCases;
    cin >> numCases;
    while (numCases--) {
        int k;
        cin >> k;
        vector<int> d(k);
        for (int i = 0; i < k; i++) cin >> d[i];
        
        int totalStates = 1 << k;
        vector<vector<int>> dp(totalStates, vector<int>(8, INF));
        
        for (int i = 0; i < k; i++) 
            dp[1 << i][d[i] - 1] = d[i];
        
        for (int mask = 0; mask < totalStates; mask++) {
            for (int free = 0; free < 8; free++) {
                if (dp[mask][free] == INF) continue;
                for (int i = 0; i < k; i++) {
                    if (mask >> i & 1) continue;
                    for (int overlap = 0; overlap <= min(free, d[i] - 1); overlap++) {
                        int newFree = d[i] - overlap - 1;
                        if (newFree < 0) continue;
                        int addedDays = d[i] - overlap;
                        int newMask = mask | (1 << i);
                        dp[newMask][newFree] = min(dp[newMask][newFree], dp[mask][free] + addedDays);
                    }
                }
            }
        }
        
        int ans = INF;
        for (int free = 0; free < 8; free++) 
            ans = min(ans, dp[totalStates - 1][free]);
        cout << ans << endl;
    }
    return 0;
}
