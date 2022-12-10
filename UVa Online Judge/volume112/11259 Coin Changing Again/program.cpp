// Coin Changing Again
// UVa ID: 11259
// Verdict: Accepted
// Submission Date: 2022-12-09
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
long long dp[MAXN];
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases, c[4], q, d[4], v;
    cin >> cases;
    while (cases--) {
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        for (int i = 0; i < 4; i++) cin >> c[i];
        cin >> q;
        for (int i = 0; i < 4; i++)
            for (int j = c[i]; j < MAXN; j++)
                dp[j] += dp[j - c[i]];
        while (q--) {
            for (int i = 0; i < 4; i++) cin >> d[i];
            cin >> v;
            long long answer = 0;
            for (int i = 0; i < 16; i++) {
                int tmp = v, flag = 1;
                for (int j = 0; j < 4; j++)
                    if (i & (1 << j)) {
                        flag = -flag;
                        tmp -= (d[j] + 1) * c[j];
                    }
                if (tmp >= 0) answer += flag * dp[tmp];
            }
            cout << answer << '\n';
        }
    }
    return 0;
}
