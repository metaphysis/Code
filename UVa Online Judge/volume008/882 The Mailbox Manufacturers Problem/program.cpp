// The Mailbox Manufacturers Problem
// UVa ID: 882
// Verdict: Accepted
// Submission Date: 2018-09-29
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int K, M, dp[128][128][16];

int dfs(int left, int right, int mailbox)
{
    if (~dp[left][right][mailbox]) return dp[left][right][mailbox];
    int minimum = INF;
    if (mailbox == 1 || abs(right - left) <= 1)
        minimum = (right + left) * (right - left + 1) / 2;
    else
    {
        for (int i = left + 1; i < right; i++)
        {
            int maximum = 0;
            // Exploded.
            maximum = max(maximum, i + dfs(left, i - 1, mailbox - 1));
            // Unexploded.
            maximum = max(maximum, i + dfs(i + 1, right, mailbox));
            minimum = min(minimum, maximum);
        }
    }
    return dp[left][right][mailbox] = minimum;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> K >> M;
        memset(dp, -1, sizeof(dp));
        cout << dfs(1, M, K) << '\n';
    }
	return 0;
}
