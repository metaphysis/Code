// Anagram Division
// UVa ID: 11084
// Verdict: Accepted
// Submission Date: 2018-09-22
// UVa Run Time: 0.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string s;
int d, L, dp[1 << 10][10001];

int dfs(int mask, int mod)
{
    if (mask == (1 << L) - 1) return dp[mask][mod] = (mod == 0);
    if (~dp[mask][mod]) return dp[mask][mod];
    int r = 0, last = -1;
    for (int i = 0; i < L; i++)
        if (s[i] - '0' != last && !(mask & (1 << i)))
        {
            last = s[i] - '0';
            r += dfs(mask | (1 << i), (mod * 10 + s[i] - '0') % d);
        }
    return dp[mask][mod] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> s >> d;
        sort(s.begin(), s.end());
        L = s.length();
        for (int i = 0; i < (1 << L); i++)
            for (int j = 0; j <= d; j++)
                dp[i][j] = -1;
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
