// Palindromic Subsequence
// UVa ID: 11404
// Verdict: Accepted
// Submission Date: 2023-05-15
// UVa Run Time: 2.470s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct block {
    int n;
    string r;
    bool operator<(const block &b) const {
        if (n != b.n) return n > b.n;
        return r < b.r;
    }
} dp[1010][1010];

int ns;
string s;
static block empty = block{0, ""};

block dfs(int l, int r) {
    if (l > r) return empty;
    if (dp[l][r].n) return dp[l][r];
    if (s[l] == s[r]) {
        block b = dfs(l + 1, r - 1);
        dp[l][r] = block{b.n + 2, s[l] + b.r + s[r]};
    }
    return dp[l][r] = min(dp[l][r], min(dfs(l, r - 1), dfs(l + 1, r)));
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	while (cin >> s) {
        ns = s.length();
        for (int i = 0; i < ns; i++)
            for (int j = 0; j < ns; j++)
                dp[i][j].n = 0;
        for (int i = 0; i < ns; i++)
            dp[i][i] = block{1, string(1, s[i])};
        dfs(0, ns - 1);
        cout << dp[0][ns - 1].r << '\n';
    }
}
