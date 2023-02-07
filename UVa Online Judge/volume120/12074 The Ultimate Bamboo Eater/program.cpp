// The Ultimate Bamboo Eater
// UVa ID: 12074
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

struct LAND {
    int xi, yi, wi, li;
    bool operator<(const LAND ld) const { return wi < ld.wi; }
} lands[MAXN];
int n, dp[MAXN];
int dfs(int idx) {
    if (~dp[idx]) return dp[idx];
    int r = 0;
    for (int i = idx + 1; i < n; i++) {
        if (abs(lands[i].xi - lands[idx].xi) +
            abs(lands[i].yi - lands[idx].yi) > lands[i].li) continue;
        r = max(r, dfs(i));
    }
    return dp[idx] = 1 + r;
}
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        cin >> n;
        memset(dp, -1, sizeof dp);
        for (int i = 0; i < n; i++) 
            cin >> lands[i].xi >> lands[i].yi >> lands[i].wi >> lands[i].li;
        sort(lands, lands + n);
        int m = 0;
        for (int i = 0; i < n; i++) m = max(m, dfs(i));
        cout << m << '\n';
    }
    return 0;
}
