// Blocks
// UVa ID: 10559
// Verdict: Accepted
// Submission Date: 2020-04-02
// UVa Run Time: 0.570s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210;

struct STONES { int c, n; } s[MAXV];

int dp[MAXV][MAXV][MAXV];

int dfs(int i, int j, int k)
{
    if (i > j) return 0;
    if (i == j) return (s[i].n + k) * (s[i].n + k);
    if (~dp[i][j][k]) return dp[i][j][k];
    int r = dfs(i, j - 1, 0) + (s[j].n + k) * (s[j].n + k);
    for (int q = j - 1; q >= i; q--)
        if (s[q].c == s[j].c && s[q + 1].c != s[j].c)
            r = max(r, dfs(i, q, s[j].n + k) + dfs(q + 1, j - 1, 0));
    return dp[i][j][k] = r;
}

int main(int argc, char *argv[])
{
    int cases, n, cnt;
    vector<int> segs;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> n;
        cnt = 0;
        segs.clear();
        for (int i = 0, c; i < n; i++) {
            cin >> c;
            if (segs.size() == 0 || segs.back() == c)
                segs.push_back(c);
            else {
                s[cnt].c = segs.front();
                s[cnt++].n = segs.size();
                segs.clear();
                segs.push_back(c);
            }
        }
        s[cnt].c = segs.front();
        s[cnt++].n = segs.size();
        segs.clear();
        memset(dp, -1, sizeof dp);
        cout << "Case " << cs << ": " << dfs(0, cnt - 1, 0) << '\n';
    }
    return 0;
}
