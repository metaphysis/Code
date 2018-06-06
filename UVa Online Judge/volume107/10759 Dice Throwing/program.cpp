// Dice Throwing
// UVa ID: 10759
// Verdict: Accepted
// Submission Date: 2018-06-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long all[32] = {1}, cnt[32][156];
    for (int i = 1; i <= 24; i++)
        all[i] = all[i - 1] * 6;
    int n, x;
    while (cin >> n >> x, n > 0)
    {
        memset(cnt, 0, sizeof(cnt));
        cnt[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= 6; j++)
                for (int k = 6 * i; k >= j; k--)
                    cnt[i][k] += cnt[i - 1][k - j];
        long long tot = 0;
        for (int i = 0; i < x; i++)
            tot += cnt[n][i];
        tot = all[n] - tot;
        if (tot == 0) cout << "0\n";
        else if (tot == all[n]) cout << "1\n";
        else
        {
            long long g = __gcd(tot, all[n]);
            cout << tot / g << '/' << all[n] / g << '\n';
        }
    }

    return 0;
}
