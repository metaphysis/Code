// Brick Game
// UVa ID: 11587
// Verdict: Accepted
// Submission Date: 2023-03-12
// UVa Run Time: 0.660s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string LW;
int n, used, best, dp[110];

int dfs(int c) {
    if (~dp[c]) return dp[c];
    for (int i = 1; i <= min(c, 20); i++)
        if ((used & (1 << (i - 1))) && !dfs(c - i))
            return dp[c] = 1;
    return dp[c] = 0;
}

void backtrack(int d) {
    if (d >= min(20, n)) {
        int flag = 1;
        memset(dp, -1, sizeof dp);
        dp[0] = 0;
        for (int i = 0; i < n && flag; i++)
            if ("LW"[dfs(i + 1)] != LW[i])
                flag = 0;
        if (flag) {
            int c1 = __builtin_popcount(best);
            int c2 = __builtin_popcount(used);
            if (c1 > c2) best = used;
            if (c1 == c2) {
                for (int i = 0; i < min(20, n); i++)
                    if ((used & (1 << i)) != (best & (1 << i))) {
                        if (used & (1 << i) > (best & (1 << i)))
                            best = used;
                        break;
                    }
            }
        }
        return;
    }
    if (LW[d] == 'L') backtrack(d + 1);
    else {
        int flag = 1;
        memset(dp, -1, sizeof dp);
        dp[0] = 0;
        if (dfs(d + 1)) backtrack(d + 1);
        used |= (1 << d);
        backtrack(d + 1);
        used ^= (1 << d);
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases; cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cout << "Case " << cs << ':';
        cin >> LW;
        n = LW.length();
        used = 0, best = (1 << min(20, n)) - 1;
        backtrack(0);
        if (!best) cout << ' ' << 1 + n;
        else {
            for (int i = 0; i < min(20, n); i++)
                if (best & (1 << i))
                    cout << ' ' << i + 1;
        }
        cout << '\n';
    }
    return 0;
}
