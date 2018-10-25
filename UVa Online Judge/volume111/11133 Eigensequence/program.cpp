// Eigensequence
// UVa ID: 11133
// Verdict: Accepted
// Submission Date: 2018-10-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

list<int> edges[45];
int dp[45];

int dfs(int u)
{
    if (~dp[u]) return dp[u];
    int r = 0;
    for (auto v : edges[u])
        r += dfs(v);
    return dp[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 1; i <= 44; i++)
        for (int j = i - 1; j >= 0; j--)
        {
            int flag = 1;
            for (int k = j + 1; k < i; k++)
                if (k % (i - j) == 0)
                {
                    flag = 0;
                    break;
                }
            if (flag) edges[i].push_back(j);
        }
    
    int a1, an;
    while (cin >> a1 >> an)
    {
        if (a1 == 0 && an == 0) break;    
        memset(dp, -1, sizeof(dp));
        dp[a1] = 1;
        cout << a1 << ' ' << an << ' ' << dfs(an) << '\n';
    }

    return 0;
}
