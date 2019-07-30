// Robotruck
// UVa ID: 1169
// Verdict: Accepted
// Submission Date: 2019-07-25
// UVa Run Time: 0.030s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

int dp[MAXN], sw[MAXN], sd1[MAXN], d2[MAXN];

int G(int j) { return dp[j] + d2[j + 1] - sd1[j + 1]; }

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, C, N;
    dp[0] = 0, sw[0] = 0, sd1[0] = 0, d2[0] = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> C >> N;
        int xx = 0, yy  = 0, x, y, w;
        for (int i = 1; i <= N; i++) {
            cin >> x >> y >> w;
            sw[i] = sw[i - 1] + w;
            sd1[i] = sd1[i - 1] + abs(x - xx) + abs(y - yy);
            d2[i] = x + y;
            xx = x, yy = y;
        }
        deque<int> dq;
        dq.push_front(0);
        for (int i = 1; i <= N; i++) {
            while (!dq.empty() && sw[i] - sw[dq.front()] > C) dq.pop_front();
            dp[i] = G(dq.front()) + sd1[i] + d2[i];
            if (i < N) while (!dq.empty() && G(dq.back()) >= G(i)) dq.pop_back();
            dq.push_back(i);
        }
        if (cs > 1) cout << '\n';
        cout << dp[N] << '\n';
    }
    return 0;
}
