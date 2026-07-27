// Going Shopping with Grandma (I)
// UVa ID: 13061
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.120s
// https://blog.csdn.net/metaphysis/article/details/163229874

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 9999959999LL;
const int MAX_L = 1000;
const int MAX_J = 2000;          // l+s 的最大值

long long dp[MAX_L + 1][MAX_J + 1];

// 预处理所有状态 (i, j)，其中 0<=i<=1000, 0<=j<=2000
void precompute() {
    // 只有小药丸的情况 (i = 0)
    for (int j = 0; j <= MAX_J; ++j) dp[0][j] = (j + 1) % MOD;
    for (int i = 1; i <= MAX_L; ++i) {
        for (int j = 0; j <= MAX_J; ++j) {
            long long val = 1;                     // 根节点
            if (j + 1 <= MAX_J)                    // 左子树：取大药丸
                val += dp[i - 1][j + 1];
            if (j > 0)                             // 右子树：取小药丸
                val += dp[i][j - 1];
            dp[i][j] = val % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();
    int l, s;
    while (cin >> l >> s) {
        if (l == 0 && s == 0) break;
        cout << dp[l][s] << '\n';
    }
    return 0;
}
