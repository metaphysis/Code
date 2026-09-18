#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

vector<vector<long long>> calcDp(int pos, int minDigit, const vector<vector<long long>>& nextDp, const vector<string>& a) {
    int n = a.size();
    vector<vector<long long>> res(n, vector<long long>(n, inf));
    vector<vector<int>> pre(10, vector<int>(n + 1, 0));
    for (int d = 0; d <= 9; d++)
        for (int i = 0; i < n; i++)
            pre[d][i + 1] = pre[d][i] + (a[i][pos] - '0' != d);
    for (int l = 0; l < n; l++) {
        vector<long long> cur(n + 1, inf);
        cur[l] = 0;
        for (int d = minDigit; d <= 9; d++) {
            vector<long long> nxt = cur;
            for (int r = l; r < n; r++) {
                for (int st = l; st <= r; st++) {
                    if (cur[st] == inf || nextDp[st][r] == inf)
                        continue;
                    long long cost = cur[st] + nextDp[st][r] + pre[d][r + 1] - pre[d][st];
                    nxt[r + 1] = min(nxt[r + 1], cost);
                }
            }
            cur = nxt;
        }
        for (int r = l; r < n; r++)
            res[l][r] = cur[r + 1];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n;
        cin >> n;
        vector<string> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        int len = a[0].size();
        vector<vector<long long>> dp(n, vector<long long>(n, inf));
        for (int i = 0; i < n; i++)
            dp[i][i] = 0;
        for (int pos = len - 1; pos >= 1; pos--)
            dp = calcDp(pos, 0, dp, a);
        vector<vector<long long>> ansDp = calcDp(0, 1, dp, a);
        long long ans = ansDp[0][n - 1];
        if (ans == inf)
            ans = -1;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
