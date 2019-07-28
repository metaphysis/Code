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

struct decision
{
    int v, j;
    decision (int v = 0, int j = 0): v(v), j(j) {}
    bool operator<(const decision &d) const
    {
        if (v != d.v) return v > d.v;
        return j < d.j;
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, C, N, dp[MAXN], W[MAXN], D1[MAXN], D2[MAXN];
    dp[0] = 0, W[0] = 0, D1[0] = 0, D2[0] = 0;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> C >> N;
        int rr = 0, cc  = 0, r, c, w;
        for (int i = 1; i <= N; i++) {
            cin >> r >> c >> w;
            W[i] = W[i - 1] + w, D1[i] = r + c, D2[i] = D2[i - 1] + abs(r - rr) + abs(c - cc);
            rr = r, cc = c;
        }
        priority_queue<decision> qd;
        qd.push(decision(dp[0] + D1[1] - D2[1], 0));
        for (int i = 1; i <= N; i++) {
            while (!qd.empty()) {
                decision d = qd.top();
                if (W[i] - W[d.j] <= C) {
                    dp[i] = d.v + (D1[i] + D2[i]);
                    break;
                }
                else qd.pop();
            }
            if (i < N) qd.push(decision(dp[i] + D1[i + 1] - D2[i + 1], i));
        }
        if (cs > 1) cout << '\n';
        cout << dp[N] << '\n';
    }
    return 0;
}
