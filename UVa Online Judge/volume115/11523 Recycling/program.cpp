// Recycling
// UVa ID: 11523
// Verdict: Accepted
// Submission Date: 2023-06-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110, INF = 0x3f3f3f3f;
int n, m[MAXN], dp[MAXN][MAXN];
int dfs(int l, int r) {
    if (l > r) return 0;
    if (~dp[l][r]) return dp[l][r];
    if (!m[l]) return dp[l][r] = dfs(l + 1, r);
    int a = dfs(l + 1, r) + 1;
    for (int i = l + 1; i <= r; i++) {
        if (!m[i]) break;
        if (m[i] == m[l]) a = min(a, dfs(l + 1, i - 1) + dfs(i, r));
    }
    return dp[l][r] = a;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> n;
        string s;
        map<string, int> indexer;
        int cnt = 1;
        for (int i = 0; i < n; i++) {
            cin >> s;
            if ('A' <= s[0] && s[0] <= 'Z') m[i] = 0;
            else {
                if (indexer.count(s)) m[i] = indexer[s];
                else {
                    indexer[s] = cnt;
                    m[i] = cnt++;
                }
            }
        }
        memset(dp, -1, sizeof dp);
        cout << "Case " << cs << ": " << dfs(0, n - 1) << '\n';
    }
    return 0;
}
