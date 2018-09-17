// Tug of War
// UVa ID: 10032
// Verdict: Accepted
// Submission Date: 2018-09-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, weight[110];
    long long F[45010];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';

        cin >> n;
        int S = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> weight[i];
            S += weight[i];
        }
        memset(F, 0, sizeof(F));
        F[0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = S / 2; j >= weight[i]; j--)
                F[j] |= (F[j - weight[i]] << 1);
        int m = n / 2;
        for (int i = S / 2; i >= 0; i--)
            if ((F[i] & (1LL << m)) || (F[i] & (1LL << (n - m))))
            {
                cout << min(i, S - i) << ' ' << max(i, S - i) << '\n';
                break;
            }
    }

    return 0;
}
