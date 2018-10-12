// Avoiding Jungle in the Dark
// UVa ID: 11545
// Verdict: Accepted
// Submission Date: 2018-10-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

string jungle;
int dp[1010][20][30];

int dfs(int idx, int walked, int hour)
{
    if (idx + 1 == jungle.length()) return 0;
    if ((hour <= 6 || hour >= 18) && jungle[idx] == '*') return INF;
    if (walked == 16 && jungle[idx] == '*') return INF;
    if (~dp[idx][walked][hour]) return dp[idx][walked][hour];
    int elpased = INF;
    if (walked <= 15) elpased = min(elpased, 1 + dfs(idx + 1, walked + 1, (hour + 1) % 24));
    elpased = min(elpased, 9 + dfs(idx + 1, 1, (hour + 9) % 24));
    return dp[idx][walked][hour] = min(INF, elpased);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> jungle;
        memset(dp, -1, sizeof(dp));
        cout << "Case #" << cs << ": ";
        int elpased = dfs(0, 0, 6);
        if (elpased == INF) cout << "-1\n";
        else cout << elpased << '\n';
    }

    return 0;
}
