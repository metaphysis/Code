// Tobby and Query
// UVa ID: 13095
// Verdict: Accepted
// Submission Date: 2022-10-29
// UVa Run Time: 0.120s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int dp[100010][10];
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, q, x;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> x;
            for (int j = 0; j < 10; j++) dp[i][j] = dp[i - 1][j];
            dp[i][x]++;
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            int l, r, answer = 0;
            cin >> l >> r;
            for (int j = 0; j < 10; j++) answer += (dp[r][j] - dp[l - 1][j]) > 0;
            cout << answer << '\n';
        }
    }
    return 0;
}
