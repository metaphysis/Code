// Combination! Once Again
// UVa ID: 10532
// Verdict: Accepted
// Submission Date: 2018-06-03
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 56;

int labels[MAXN];
long long cnt[MAXN][MAXN];

long long dp(int n, int r)
{
    if (n == 0 && r == 0) return 1LL;
    if (n == 0) return 0;
    if (~cnt[n][r]) return cnt[n][r];
    cnt[n][r] = 0;
    for (int i = 0; i <= labels[n]; i++)
        cnt[n][r] += dp(n - 1, r - i);
    return cnt[n][r];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, m, r, tag;
    while (cin >> n >> m)
    {
        if (n == 0) break;
        memset(labels, 0, sizeof(labels));
        for (int i = 0; i < n; i++)
        {
            cin >> tag;
            labels[tag]++;
        }
        cout << "Case " << ++cases << ":\n";
        for (int i = 0; i < m; i++)
        {
            cin >> r;
            memset(cnt, -1, sizeof(cnt));
            dp(n, r);
            cout << cnt[n][r] << '\n';
        }
    }

    return 0;
}
