// Tug of War
// UVa ID: 10032
// Verdict: Accepted
// Submission Date: 2018-09-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void dp1()
{
    int cases, n, weight[110];
    int F[22501][51];

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
        for (int i = 0; i <= S / 2; i++)
            for (int j = 0; j <= (n + 1) / 2; j++)
                F[i][j] = 0;
        F[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = S / 2; j >= weight[i]; j--)
                for (int k = 1; k <= min(i, (n + 1) / 2); k++)
                    F[j][k] |= F[j - weight[i]][k - 1];
        int m = (n + 1) / 2;
        for (int i = S / 2; i >= 0; i--)
            if (F[i][m] || F[i][n - m])
            {
                cout << min(i, S - i) << ' ' << max(i, S - i) << '\n';
                break;
            }
    }
}

void dp2()
{
    int cases, n, weight[110];
    long long F[22501];

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
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // UVa Run Time: 1.090s.
    //dp1();

    // UVa Run Time: 0.030s.
    dp2();

    return 0;
}
