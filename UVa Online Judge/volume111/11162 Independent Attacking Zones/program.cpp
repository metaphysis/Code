// Independent Attacking Zones
// UVa ID: 11162
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 85;
string ring;
long long dp[MAXN][MAXN];

long long dfs(int l, int r) {
    int gap = r - l;
    if (gap == 0) return 1;
    if (gap % 3 != 0) return 0;
    if (~dp[l][r]) return dp[l][r];
    long long &cnt = dp[l][r];
    cnt = 0;
    for (int a = l + 1; a < r; ++a) {
        for (int b = a + 1; b < r; ++b) {
            int redCount = (ring[l] == 'R') + (ring[a] == 'R') + (ring[b] == 'R');
            if (redCount > 1) continue;
            long long ways1 = dfs(l + 1, a);
            long long ways2 = dfs(a + 1, b);
            long long ways3 = dfs(b + 1, r);
            cnt += ways1 * ways2 * ways3;
        }
    }
    return cnt;
}

int main() {
    int T; cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int P; cin >> P;
        string s; cin >> s;
        ring = s + s;
        memset(dp, -1, sizeof(dp));
        long long cnt = 0;
        for (int a = 1; a < P; ++a) {
            for (int b = a + 1; b < P; ++b) {
                int redCount = (ring[0] == 'R') + (ring[a] == 'R') + (ring[b] == 'R');
                if (redCount > 1) continue;
                long long ways1 = dfs(1, a);
                long long ways2 = dfs(a + 1, b);
                long long ways3 = dfs(b + 1, P);
                cnt += ways1 * ways2 * ways3;
            }
        }
        cout << "Case " << caseNo << ": " << cnt << '\n';
    }
    return 0;
}
