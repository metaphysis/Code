// Great Numbers
// UVa ID: 12046
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000007;
const int MAX_LCM = 60;

// 预计算所有可能的LCM值
int lcmValues[] = {1,2,3,4,5,6,10,12,15,20,30,60};
int lcmIndex[61];
int lcmCount = 12;

// 计算两个数的LCM
int calcLCM(int a, int b) {
    return a / __gcd(a, b) * b;
}

int dp[41][MAX_LCM][12];

int countGreatNumbers(int n) {
    memset(dp, 0, sizeof dp);
    
    // 初始化：第一位数字
    for (int d = 1; d <= 6; d++) {
        int rem = d % MAX_LCM;
        int lcmIdx = lcmIndex[d];
        dp[1][rem][lcmIdx] = (dp[1][rem][lcmIdx] + 1) % MOD;
    }
    
    // 动态规划
    for (int pos = 1; pos < n; pos++) {
        for (int rem = 0; rem < MAX_LCM; rem++) {
            for (int idx = 0; idx < lcmCount; idx++) {
                if (dp[pos][rem][idx] == 0) continue;
                int currentLCM = lcmValues[idx];
                
                for (int d = 1; d <= 6; d++) {
                    int newRem = (rem * 10 + d) % MAX_LCM;
                    int newLCM = calcLCM(currentLCM, d);
                    int newLCMIdx = lcmIndex[newLCM];
                    
                    dp[pos + 1][newRem][newLCMIdx] = 
                        (dp[pos + 1][newRem][newLCMIdx] + dp[pos][rem][idx]) % MOD;
                }
            }
        }
    }
    
    // 统计结果：余数能被当前LCM整除
    int result = 0;
    for (int rem = 0; rem < MAX_LCM; rem++) {
        for (int idx = 0; idx < lcmCount; idx++) {
            int currentLCM = lcmValues[idx];
            if (rem % currentLCM == 0) {
                result = (result + dp[n][rem][idx]) % MOD;
            }
        }
    }
    return result;
}

int main() {
    // 初始化LCM索引
    memset(lcmIndex, -1, sizeof lcmIndex);
    for (int i = 0; i < lcmCount; i++) {
        lcmIndex[lcmValues[i]] = i;
    }
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << countGreatNumbers(n) << endl;
    }
    return 0;
}
