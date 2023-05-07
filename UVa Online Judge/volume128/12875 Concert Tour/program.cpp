// Concert Tour
// UVa ID: 12875
// Verdict: Accepted
// Submission Date: 2023-05-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int s, c, cost[110][110], profit[110][60];
int dp[110][60];

int dfs(int city, int concert) {
    if (concert > c) return 0;
    if (dp[city][concert] != -INF) return dp[city][concert];
    int r = 0;
    for (int i = 1; i <= s; i++)
        r = max(r, dfs(i, concert + 1) + profit[city][concert] - cost[city][i]);
    return dp[city][concert] = r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        cin >> s >> c;
        for (int i = 0; i <= s; i++)
            for (int j = 0; j <= c; j++)
                dp[i][j] = -INF;
        for (int i = 1; i <= s; i++)
            for (int j = 1; j <= c; j++)
                cin >> profit[i][j];
        for (int i = 1; i <= s; i++)
            for (int j = 1; j <= s; j++)
                cin >> cost[i][j];
        cout << dfs(0, 0) << '\n';
    }
    return 0;
}
