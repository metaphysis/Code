// Dromicpalin Substrings
// UVa ID: 12718
// Verdict: Accepted
// Submission Date: 2023-05-16
// UVa Run Time: 1.190s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string s;
int v[1010];
int ns, cnt, dp[1010][1010];

int dfs(int l, int r) {
    if (~dp[l][r]) return dp[l][r];
    if (l == r) { cnt++; return dp[l][r] = 1 << v[l]; }
    int bit = dfs(l, r - 1);
    bit = dfs(l + 1, r);
    bit ^= 1 << v[l];
    if (__builtin_popcount(bit) <= 1) cnt++;
    return dp[l][r] = bit;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> s;
        ns = s.length();
        for (int i = 0; i < ns; i++)
            for (int j = 0; j < ns; j++)
                dp[i][j] = -1;
        for (int i = 0; i < ns; i++) v[i] = s[i] - 'a';
        cnt = 0;
        dfs(0, ns - 1);
        cout << "Case " << cs << ": " << cnt << '\n';
    }
    return 0;
}
