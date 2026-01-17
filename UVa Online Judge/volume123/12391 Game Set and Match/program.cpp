// Game Set and Match
// UVa ID: 12391
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算组合数 C(n, k)
double comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    double res = 1.0;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

// 计算赢一局的概率
double winGame(double p) {
    double q = 1 - p;
    
    // 直接获胜的情况
    double directWin = 0;
    directWin += pow(p, 4);                    // 4:0
    directWin += 4 * pow(p, 4) * q;            // 4:1
    directWin += 10 * pow(p, 4) * pow(q, 2);   // 4:2
    
    // 达到 deuce 的情况
    double reachDeuce = 20 * pow(p, 3) * pow(q, 3);  // C(6,3)=20
    double winAfterDeuce = pow(p, 2) / (pow(p, 2) + pow(q, 2));
    
    return directWin + reachDeuce * winAfterDeuce;
}

// 计算赢抢七的概率
double winTiebreak(double p) {
    double q = 1 - p;
    
    // 直接获胜（对手得分 0-5）
    double directWin = 0;
    directWin += pow(p, 7);                     // 7:0
    directWin += 7 * pow(p, 7) * q;             // 7:1
    directWin += 28 * pow(p, 7) * pow(q, 2);    // 7:2
    directWin += 84 * pow(p, 7) * pow(q, 3);    // 7:3
    directWin += 210 * pow(p, 7) * pow(q, 4);   // 7:4
    directWin += 462 * pow(p, 7) * pow(q, 5);   // 7:5
    
    // 达到 6-6 后继续比赛的情况
    double reach66 = 924 * pow(p, 6) * pow(q, 6);  // C(12,6)=924
    double winAfter66 = pow(p, 2) / (pow(p, 2) + pow(q, 2));
    
    return directWin + reach66 * winAfter66;
}

// 计算赢一盘的概率（使用DP）
double winSetDP(double pg, double pt) {
    // dp[i][j]: Rafa赢i局，对手赢j局的概率
    vector<vector<double>> dp(13, vector<double>(13, 0.0));
    dp[0][0] = 1.0;
    
    double winProb = 0.0;
    
    for (int total = 0; total < 24; total++) {  // 最多12+12局
        for (int i = 0; i <= min(12, total); i++) {
            int j = total - i;
            if (j > 12 || dp[i][j] == 0) continue;
            
            // 检查是否已结束
            if (i >= 6 && i - j >= 2) {
                winProb += dp[i][j];
                continue;
            }
            if (j >= 6 && j - i >= 2) {
                continue;  // 已输，不再转移
            }
            if (i == 6 && j == 6) {
                // 进入抢七
                winProb += dp[i][j] * pt;
                continue;
            }
            
            // 继续比赛
            if (i < 12 && j < 12) {
                dp[i+1][j] += dp[i][j] * pg;
                dp[i][j+1] += dp[i][j] * (1 - pg);
            }
        }
    }
    
    return winProb;
}

int main() {
    double p;
    while (cin >> p, p != -1) {
        double pg = winGame(p);
        double pt = winTiebreak(p);
        double ps = winSetDP(pg, pt);
        double pm = ps * ps * (3 - 2 * ps);
        
        cout << fixed << setprecision(11) 
             << pg << " " << ps << " " << pm << endl;
    }
    return 0;
}
