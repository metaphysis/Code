// Mega Mans Missions
// UVa ID: 11795
// Verdict: Accepted
// Submission Date: 2023-01-14
// UVa Run Time: 0.030s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, w[32];
long long dp[1 << 20];

long long dfs(int mask, int weapon)
{
    if (!mask) return 1;
    if (~dp[mask]) return dp[mask];
    long long r = 0;
    for (int i = 0; i < n; i++)
        if ((mask & (1 << i)) && (weapon & (1 << i)))
            r += dfs(mask ^ (1 << i), weapon | w[i]);
    return dp[mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        memset(dp, -1, sizeof dp);
        memset(w, 0, sizeof w);
        cin >> n;
        char c;
        int mega = 0;
        for (int i = 0; i < n; i++) {
            cin >> c;
            mega |= ((c - '0') << i);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> c;
                w[i] |= ((c - '0') << j);
            }
        cout << dfs(((1 << n) - 1), mega) << '\n';
    }
    return 0;
}
