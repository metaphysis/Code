// The Archery Puzzle
// UVa ID: 12840
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.640s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, S;
int P[60], dp[310][2];

int dfs(int s)
{
    if (!s) return dp[s][0] = 0;
    if (dp[s][0] != 0x3f3f3f3f) return dp[s][0];
    for (int i = N - 1; i >= 0; i--)
    {
        if (P[i] > s) continue;
        if (dfs(s - P[i]) + 1 < dp[s][0])
        {
            dp[s][0] = dp[s - P[i]][0] + 1;
            dp[s][1] = P[i];
        }
    }
    return dp[s][0];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cout << "Case " << cs << ": ";
        cin >> N >> S;
        for (int i = 0; i < N; i++) cin >> P[i];
        memset(dp, 0x3f, sizeof dp);
        if (dfs(S) == 0x3f3f3f3f) cout << "impossible\n";
        else
        {
            cout << '[' << dp[S][0] << ']';
            while (true)
            {
                cout << ' ' << dp[S][1];
                S -= dp[S][1];
                if (!S) break;
            }
            cout << '\n';
        }
    }
    return 0;
}
