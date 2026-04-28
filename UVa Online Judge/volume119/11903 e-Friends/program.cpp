// e-Friends
// UVa ID: 11903
// Verdict: Accepted
// Submission Date: 2026-04-27
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, k, q;
        cin >> n >> k >> q;
        
        // 敌人关系矩阵，isEnemy[i][j] 表示 i 认为 j 是敌人
        vector<vector<bool>> isEnemy(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            for (int j = 0; j < t; ++j) {
                int enemy;
                cin >> enemy;
                isEnemy[i][enemy - 1] = true;  // 转为 0-based
            }
        }
        
        int fullMask = (1 << n) - 1;
        int maxCnt = n - 1;  // 最多 n-1 次不满
        
        // dp[mask][last][cnt]
        vector<vector<vector<long long>>> dp(1 << n, vector<vector<long long>>(n, vector<long long>(maxCnt + 1, 0)));
        
        // 初始化：每个人作为第一个
        for (int i = 0; i < n; ++i)
            dp[1 << i][i][0] = 1;
        
        // DP 转移
        for (int mask = 1; mask <= fullMask; ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1 << last))) continue;
                for (int cnt = 0; cnt <= maxCnt; ++cnt) {
                    long long ways = dp[mask][last][cnt];
                    if (ways == 0) continue;
                    for (int nxt = 0; nxt < n; ++nxt) {
                        if (mask & (1 << nxt)) continue;
                        int newCnt = cnt + (isEnemy[nxt][last] ? 1 : 0);
                        if (newCnt > maxCnt) continue;
                        dp[mask | (1 << nxt)][nxt][newCnt] += ways;
                    }
                }
            }
        }
        
        // 统计每种不满次数的总排列数
        vector<long long> cntArr(maxCnt + 1, 0);
        for (int last = 0; last < n; ++last)
            for (int c = 0; c <= maxCnt; ++c)
                cntArr[c] += dp[fullMask][last][c];
        
        // 预处理前缀和
        vector<long long> prefix(maxCnt + 2, 0);
        for (int c = 0; c <= maxCnt; ++c)
            prefix[c + 1] = prefix[c] + cntArr[c];
        
        // 计算 n!
        long long fact = 1;
        for (int i = 2; i <= n; ++i) fact *= i;
        
        cout << "Case " << caseNo << ":\n";
        
        for (int queryIdx = 0; queryIdx < q; ++queryIdx) {
            int r;
            cin >> r;
            
            if (k == 0) {
                cout << fact << "\n";
                continue;
            }
            
            int maxAllowedCnt = r / k;
            if (maxAllowedCnt >= maxCnt) {
                cout << fact << "\n";
            } else {
                cout << prefix[maxAllowedCnt + 1] << "\n";
            }
        }
    }
    
    return 0;
}
