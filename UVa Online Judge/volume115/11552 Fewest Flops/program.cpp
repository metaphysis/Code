// Fewest Flops
// UVa ID: 11552
// Verdict: Accepted
// Submission Date: 2019-12-14
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

string S;
int K, s[1024], dp[1024][26], cnt[26];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> K >> S;
        for (int i = 0; i < S.length(); i++)
            s[i] = S[i] - 'a';
        int blocks = S.length() / K;
        memset(dp, INF, sizeof(dp));
        for (int i = 0; i < 26; i++) dp[0][i] = 0;
        for (int i = 1; i <= blocks; i++)
        {
            memset(cnt, 0, sizeof(cnt));
            int chunks = 0;
            for (int j = (i - 1) * K; j < i * K; j++) cnt[s[j]]++;
            for (int j = 0; j < 26; j++) chunks += (cnt[j] > 0);
            for (int j = 0; j < 26; j++)
            {
                if (dp[i - 1][j] == INF) continue;
                for (int m = 0; m < 26; m++)
                {
                    if (cnt[m] == 0) continue;
                    for (int n = 0; n < 26; n++)
                    {
                        if (cnt[n] == 0) continue;
                        dp[i][n] = min(dp[i][n], dp[i - 1][j] + chunks + (m == n && cnt[m] < K) - (m == j && i > 1));
                    }
                }
            }
        }
        int r = INF;
        for (int i = 0; i < 26; i++) r = min(r, dp[blocks][i]);
        cout << r << '\n';
    }
    return 0;
}
