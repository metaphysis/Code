// Stochastic Digit Generator
// UVa ID: 10953
// Verdict: Accepted
// Submission Date: 2025-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseNo = 1;
    int D;
    while (cin >> D && D != 0) {
        vector<int> digits(D);
        vector<double> prob(D);
        for (int i = 0; i < D; i++) cin >> digits[i] >> prob[i];

        int Q;
        cin >> Q;
        vector<string> format(Q);
        vector<int> remainder(Q);
        for (int i = 0; i < Q; i++) cin >> format[i] >> remainder[i];

        cout << "Case " << caseNo++ << ":\n";
        cout << fixed << setprecision(8);

        for (int q = 0; q < Q; q++) {
            string s = format[q];
            int targetRem = remainder[q];
            int len = s.size();

            // dp[pos][rem]：处理到第pos位（从右往左数），当前余数为rem的概率
            vector<vector<double>> dp(len + 1, vector<double>(11, 0.0));
            dp[0][0] = 1.0; // 初始：0位数字，余数为0的概率为1

            for (int pos = 0; pos < len; pos++) {
                int charIndex = len - 1 - pos; // 从右往左对应字符串下标
                char c = s[charIndex];
                
                // 计算 10^pos mod 11 的值
                int powerMod;
                if (pos % 2 == 0) powerMod = 1;  // 偶数位置
                else powerMod = 10;              // 奇数位置
                
                for (int rem = 0; rem < 11; rem++) {
                    if (dp[pos][rem] == 0.0) continue;
                    
                    if (c == '*') {
                        // 可以生成任意数字
                        for (int i = 0; i < D; i++) {
                            int d = digits[i];
                            double p = prob[i];
                            // 计算新余数：(rem + d * (10^pos % 11)) % 11
                            int newRem = (rem + d * powerMod) % 11;
                            dp[pos + 1][newRem] += dp[pos][rem] * p;
                        }
                    } else {
                        // 固定数字
                        int d = c - '0';
                        int newRem = (rem + d * powerMod) % 11;
                        dp[pos + 1][newRem] += dp[pos][rem];
                    }
                }
            }

            cout << dp[len][targetRem] << "\n";
        }
    }
    return 0;
}
