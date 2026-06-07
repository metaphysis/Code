// The Counting Problem
// UVa ID: 1640
// Verdict: Accepted
// Submission Date: 2026-06-07
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dp[12][12][2][2];  // dp[pos][cnt][tight][lead]
string s;
int t;  // 目标数字

ll dfs(int pos, int cnt, bool tight, bool lead) {
    if (pos == s.size()) return cnt;
    if (~dp[pos][cnt][tight][lead]) return dp[pos][cnt][tight][lead];
    ll r = 0;
    int limit = tight ? s[pos] - '0' : 9;
    for (int d = 0; d <= limit; d++) {
        bool nextTight = tight && (d == limit), nextLead = lead || d;
        int add = nextLead && (d == t);
        r += dfs(pos + 1, cnt + add, nextTight, nextLead);
    }
    return dp[pos][cnt][tight][lead] = r;
}

ll solve(ll n, int d) {
    if (n < 0) return 0;
    s = to_string(n);
    t = d;
    memset(dp, -1, sizeof(dp));
    return dfs(0, 0, true, false);
}

int main() {
    ll a, b;
    while (cin >> a >> b && (a || b)) {
        if (a > b) swap(a, b);
        for (int d = 0; d < 10; ++d) {
            if (d) cout << ' ';
            cout << solve(b, d) - solve(a - 1, d);
        }
        cout << '\n';
    }
    return 0;
}
