// Critical Mass
// UVa ID: 580
// Verdict: Accepted
// Submission Date: 2016-09-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    // dp[i][0]：长度为i，不包含连续的三个U且末尾为0个U（即末尾为L）
    // dp[i][1]：长度为i，不包含连续的三个U且末尾为1个U
    // dp[i][2]：长度为i，不包含连续的三个U且末尾为2个U
    long long dp[32][3] = {0};
    dp[0][0] = 1;
    for (int i = 1; i <= 30; i++) {
        // 附加1个L
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2];
        // 附加1个U
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][1];
    }
    int n;
    while (cin >> n, n) cout << (1LL << n) - (dp[n][0] + dp[n][1] + dp[n][2]) << '\n';
    return 0;
}
