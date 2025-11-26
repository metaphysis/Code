// The Brick Stops Here
// UVa ID: 10373
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 2.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> copper(n), price(n);
        for (int i = 0; i < n; i++)
            cin >> copper[i] >> price[i];
        
        int clients;
        cin >> clients;
        while (clients--) {
            int m, cmin, cmax;
            cin >> m >> cmin >> cmax;
            int low = m * cmin;
            int high = m * cmax;
            
            if (low > high) {
                cout << "impossible" << endl;
                continue;
            }

            // 优化：限制状态空间大小
            int maxSum = min(high, m * 999);
            vector<vector<int>> dp(m + 1, vector<int>(maxSum + 1, INF));
            dp[0][0] = 0;
            
            int bestPrice = INF;
            
            for (int k = 0; k < n; k++) {
                int c = copper[k];
                int p = price[k];
                
                // 价格剪枝：如果当前砖块价格已经超过已知最优解，跳过
                if (p >= bestPrice) continue;
                
                for (int i = m - 1; i >= 0; i--) {
                    for (int j = min(maxSum - c, (i + 1) * 999); j >= 0; j--) {
                        if (dp[i][j] != INF) {
                            int newSum = j + c;
                            int newPrice = dp[i][j] + p;
                            
                            // 价格剪枝
                            if (newPrice >= bestPrice) continue;
                            
                            if (newSum <= maxSum) {
                                dp[i + 1][newSum] = min(dp[i + 1][newSum], newPrice);
                                
                                // 如果找到完整解，更新最优解
                                if (i + 1 == m && newSum >= low) {
                                    bestPrice = min(bestPrice, newPrice);
                                }
                            }
                        }
                    }
                }
            }
            
            // 最终检查
            for (int j = low; j <= maxSum; j++) {
                if (dp[m][j] != INF) {
                    bestPrice = min(bestPrice, dp[m][j]);
                }
            }

            if (bestPrice == INF) cout << "impossible" << endl;
            else cout << bestPrice << endl;
        }
        if (t) cout << endl;
    }
    return 0;
}
