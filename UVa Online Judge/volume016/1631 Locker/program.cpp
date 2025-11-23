// Locker
// UVa ID: 1631
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int dp[1005][10][10];
int origin[1005], target[1005];

int main() {
    string s1, s2;
    while (cin >> s1 >> s2) {
        int n = s1.length();
        for (int i = 0; i < n; i++) {
            origin[i] = s1[i] - '0';
            target[i] = s2[i] - '0';
        }
        
        memset(dp, 0x3f, sizeof(dp));
        dp[0][origin[0]][origin[1]] = 0;
        
        for (int i = 0; i < n; i++) {
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    if (dp[i][x][y] == INF) continue;
                    
                    int up = (target[i] - x + 10) % 10;
                    int down = (10 - up) % 10;
                    
                    // 向上旋转
                    for (int j = 0; j <= up; j++) {
                        for (int k = 0; k <= j; k++) {
                            int nx = (i + 1 < n) ? (y + j) % 10 : 0;
                            int ny = (i + 2 < n) ? (origin[i + 2] + k) % 10 : 0;
                            dp[i + 1][nx][ny] = min(dp[i + 1][nx][ny], dp[i][x][y] + up);
                        }
                    }
                    
                    // 向下旋转  
                    for (int j = 0; j <= down; j++) {
                        for (int k = 0; k <= j; k++) {
                            int nx = (i + 1 < n) ? (y - j + 10) % 10 : 0;
                            int ny = (i + 2 < n) ? (origin[i + 2] - k + 10) % 10 : 0;
                            dp[i + 1][nx][ny] = min(dp[i + 1][nx][ny], dp[i][x][y] + down);
                        }
                    }
                }
            }
        }
        
        cout << dp[n][0][0] << endl;
    }
    return 0;
}
