#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        int m, t, ed;
        cin >> m >> t;
        ed = m + 1;
        vector<int> mv(ed + 1), lose(ed + 1);
        for (int i = 1; i <= m; i++) {
            string s;
            cin >> s;
            if (s == "L") lose[i] = 1;
            else if (s != "0") mv[i] = stoi(s);
        }
        long double dp[55][2] = {}, ndp[55][2] = {};
        dp[0][0] = 1.0L;
        for (int turn = 0; turn < t; turn++) {
            memset(ndp, 0, sizeof(ndp));
            for (int pos = 0; pos <= ed; pos++) {
                for (int lost = 0; lost <= 1; lost++) {
                    long double p = dp[pos][lost];
                    if (p == 0.0L) continue;
                    if (pos == ed) {
                        ndp[pos][lost] += p;
                        continue;
                    }
                    if (lost) {
                        ndp[pos][0] += p;
                        continue;
                    }
                    for (int step = 1; step <= 2; step++) {
                        int land = min(pos + step, ed), nx = land, nl = 0;
                        if (land != ed) {
                            if (mv[land] != 0) nx += mv[land];
                            else if (lose[land]) nl = 1;
                        }
                        ndp[nx][nl] += p * 0.5L;
                    }
                }
            }
            memcpy(dp, ndp, sizeof(dp));
        }
        long double ans = dp[ed][0] + dp[ed][1];
        if (ans > 0.5L) cout << "Bet for. ";
        else if (ans < 0.5L) cout << "Bet against. ";
        else cout << "Push. ";
        cout << fixed << setprecision(4) << (double)ans << '\n';
    }
    return 0;
}
