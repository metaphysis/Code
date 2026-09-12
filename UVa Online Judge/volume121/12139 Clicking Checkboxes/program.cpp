#include <bits/stdc++.h>
using namespace std;

unsigned long long dp[2][64][64], nextDp[2][64][64];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, caseNum = 1;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        int pos, last, cnt, change, cur;
        for (pos = 0; pos < n; pos++) {
            memset(nextDp, 0, sizeof(nextDp));
            for (last = 0; last <= 1; last++)
                for (cnt = 0; cnt <= pos; cnt++)
                    for (change = 0; change <= pos; change++)
                        if (dp[last][cnt][change] != 0)
                            for (cur = 0; cur <= 1; cur++)
                                nextDp[cur][cnt + cur][change + (last != cur)] += dp[last][cnt][change];
            memcpy(dp, nextDp, sizeof(dp));
        }
        unsigned long long toggleCount = 0, normalCount = 0;
        for (last = 0; last <= 1; last++)
            for (cnt = m; cnt <= n; cnt++)
                for (change = 0; change <= n; change++) {
                    if (change < cnt) toggleCount += dp[last][cnt][change];
                    if (change > cnt) normalCount += dp[last][cnt][change];
                }
        cout << "Case " << caseNum++ << ": " << toggleCount << " " << normalCount << "\n";
    }
    return 0;
}
