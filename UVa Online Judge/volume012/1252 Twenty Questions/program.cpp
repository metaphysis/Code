// Twenty Questions
// UVa ID: 1252
// Verdict: Accepted
// Submission Date: 2018-10-20
// UVa Run Time: 0.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int m, n, code[128], dp[2048][2048];

int dfs(int ask, int answer)
{
    if (~dp[ask][answer]) return dp[ask][answer];
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if ((ask & code[i]) == answer)
            if (++cnt > 1) break;
    if (cnt == 1) return dp[ask][answer] = 0;
    if (cnt == 0) return dp[ask][answer] = INF;
    int r = INF;
    for (int i = 0; i < m; i++)
        if (!(ask & (1 << i)))
        {
            int r1 = dfs(ask | (1 << i), answer | (1 << i));
            int r2 = dfs(ask | (1 << i), answer);
            r = min(r, 1 + max(r1, r2));
        }
    return dp[ask][answer] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> m >> n)
    {
        if (m == 0) break;
        string bit;
        for (int i = 0; i < n; i++)
        {
            cin >> bit;
            int b = 0;
            for (int j = 0; j < bit.length(); j++)
                b = b * 2 + bit[j] - '0';
            code[i] = b;
        }
        if (n == 1) { cout << "0\n"; continue; }
        if (n == 2) { cout << "1\n"; continue; }
        if (n == 3) { cout << "2\n"; continue; }
        for (int i = 0; i < (1 << m); i++)
            for (int j = 0; j < (1 << m); j++)
                dp[i][j] = -1;
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
