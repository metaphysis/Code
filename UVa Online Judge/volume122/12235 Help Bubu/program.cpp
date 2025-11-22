// Help Bubu
// UVa ID: 12235
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 0.370s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[105][105][1 << 8][9];
int books[105];
int heightCount[8];

int main() {
    int n, k, caseNum = 1;
    
    while (cin >> n >> k && (n || k)) {
        memset(heightCount, 0, sizeof(heightCount));
        for (int i = 0; i < n; i++) {
            cin >> books[i];
            books[i] -= 25;
            heightCount[books[i]]++;
        }
        
        memset(dp, INF, sizeof(dp));
        dp[0][0][0][8] = 0;
        
        for (int i = 0; i < n; i++) {
            int h = books[i];
            for (int j = 0; j <= i; j++) {
                for (int mask = 0; mask < (1 << 8); mask++) {
                    for (int last = 0; last <= 8; last++) {
                        if (dp[i][j][mask][last] == INF) continue;
                        
                        int val = dp[i][j][mask][last];
                        
                        // 选择1: 不保留当前书
                        dp[i + 1][j][mask][last] = min(dp[i + 1][j][mask][last], val);
                        
                        // 选择2: 保留当前书
                        int newMask = mask | (1 << h);
                        int newVal = val;
                        if (h != last) newVal++;
                        
                        dp[i + 1][j + 1][newMask][h] = min(dp[i + 1][j + 1][newMask][h], newVal);
                    }
                }
            }
        }
        
        int answer = INF;
        for (int j = max(1, n - k); j <= n; j++) {
            int removed = n - j;  // 实际取出的书数量
            if (removed > k) continue;
            
            for (int mask = 0; mask < (1 << 8); mask++) {
                for (int last = 0; last < 8; last++) {
                    if (dp[n][j][mask][last] == INF) continue;
                    
                    int baseSegments = dp[n][j][mask][last];
                    int extraSegments = 0;
                    
                    // 计算必须创建新段的高度
                    for (int h = 0; h < 8; h++) {
                        if (!(mask & (1 << h))) {  // 这个高度在保留书中没有
                            if (heightCount[h] > 0) {  // 但这个高度在原书中存在
                                // 说明这个高度的书都被取出了，需要创建新段
                                extraSegments++;
                            }
                        }
                    }
                    
                    answer = min(answer, baseSegments + extraSegments);
                }
            }
        }
        
        cout << "Case " << caseNum++ << ": " << answer << endl << endl;
    }
    
    return 0;
}
