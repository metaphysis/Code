// The Brick Stops Here
// UVa ID: 10373
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 4.850s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> copper(n), price(n);
        for (int i = 0; i < n; i++)
            cin >> copper[i] >> price[i];

        int clients;
        cin >> clients;
        while (clients--) {
            int m, cmin, cmax;
            cin >> m >> cmin >> cmax;
            int low = m * cmin;
            int high = m * cmax;

            vector<vector<int>> dp(m + 1, vector<int>(high + 1, INF));
            dp[0][0] = 0;

            for (int k = 0; k < n; k++) {
                for (int i = m; i >= 1; i--) {
                    for (int j = high; j >= copper[k]; j--) {
                        if (dp[i - 1][j - copper[k]] != INF)
                            dp[i][j] = min(dp[i][j], dp[i - 1][j - copper[k]] + price[k]);
                    }
                }
            }

            int ans = INF;
            for (int j = low; j <= high; j++)
                ans = min(ans, dp[m][j]);

            if (ans == INF) cout << "impossible" << endl;
            else cout << ans << endl;
        }
        if (t) cout << endl;
    }
    return 0;
}
