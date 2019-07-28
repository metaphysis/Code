// Robotruck
// UVa ID: 1169
// Verdict: Accepted
// Submission Date: 2019-07-28
// UVa Run Time: 0.040s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, INF = 0x7f7f7f7f;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, C, N, dp[MAXN], sw[MAXN], sd1[MAXN], d2[MAXN];
    dp[0] = sw[0] = sd1[0] = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> C >> N;
        for (int i = 1, xx = 0, yy = 0, x, y, w; i <= N; i++) {
            cin >> x >> y >> w;
            sw[i] = sw[i - 1] + w;
            sd1[i] = sd1[i - 1] + abs(x - xx) + abs(y - yy);
            d2[i] = x + y;
            xx = x, yy = y;
            dp[i] = INF;
            for (int j = i - 1; sw[i] - sw[j] <= C && j >= 0; j--)
                dp[i] = min(dp[i], dp[j] + d2[j + 1] + (sd1[i] - sd1[j + 1]) + d2[i]);
        }
        if (cs > 1) cout << '\n';
        cout << dp[N] << '\n';
    }
    return 0;
}
