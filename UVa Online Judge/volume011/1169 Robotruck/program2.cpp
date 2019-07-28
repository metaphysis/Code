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

int dp[MAXN], W[MAXN], D1[MAXN], D2[MAXN];

int F(int i)
{
    return dp[i] + D1[i + 1] - D2[i + 1];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, C, N;
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
        deque<int> dq;
        dq.push_front(0);
        for (int i = 1; i <= N; i++) {
            while (!dq.empty() && W[i] - W[dq.front()] > C) dq.pop_front();
            dp[i] = F(dq.front()) + D1[i] + D2[i];
            if (i < N) while (!dq.empty() && F(dq.back()) >= F(i)) dq.pop_back();
            dq.push_back(i);
        }
        if (cs > 1) cout << '\n';
        cout << dp[N] << '\n';
    }
    return 0;
}
