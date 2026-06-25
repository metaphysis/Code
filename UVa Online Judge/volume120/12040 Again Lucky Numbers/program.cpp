// Again Lucky Numbers
// UVa ID: 12040
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    const int MOD = 10000007;

    while (T--) {
        int N;
        string M;
        cin >> N >> M;
        int len = (int)M.size();

        // 构建 KMP 前缀函数
        vector<int> nextArr(len, 0);
        for (int i = 1; i < len; ++i) {
            int j = nextArr[i - 1];
            while (j > 0 && M[i] != M[j]) j = nextArr[j - 1];
            if (M[i] == M[j]) ++j;
            nextArr[i] = j;
        }

        // 构建自动机转移表 trans[state][digit] -> 新状态（可能等于 len，表示完全匹配）
        vector<vector<int>> trans(len, vector<int>(10, 0));
        for (int state = 0; state < len; ++state) {
            for (int digit = 0; digit < 10; ++digit) {
                char c = char('0' + digit);
                int ns = state;
                while (ns > 0 && M[ns] != c) ns = nextArr[ns - 1];
                if (M[ns] == c) ++ns;
                trans[state][digit] = ns; // 可能为 len
            }
        }

        // dp[length][state]：长度 length 的串，匹配状态为 state 的方案数（允许前导零）
        vector<vector<int>> dp(N + 1, vector<int>(len, 0));
        dp[0][0] = 1;
        vector<int> f(N + 1, 0);
        f[0] = 1; // 空串

        for (int length = 1; length <= N; ++length) {
            for (int state = 0; state < len; ++state) {
                int cur = dp[length - 1][state];
                if (cur == 0) continue;
                for (int digit = 0; digit < 10; ++digit) {
                    int ns = trans[state][digit];
                    if (ns < len) { // 未完全匹配 M，合法
                        dp[length][ns] = (dp[length][ns] + cur) % MOD;
                    }
                }
            }
            int sum = 0;
            for (int state = 0; state < len; ++state)
                sum = (sum + dp[length][state]) % MOD;
            f[length] = sum;
        }

        int ans;
        if (N == 1) ans = f[1];
        else ans = (f[N] - f[N - 1] + MOD) % MOD;

        cout << ans << '\n';
    }

    return 0;
}
