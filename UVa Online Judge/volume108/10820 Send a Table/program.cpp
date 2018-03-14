// Send a Table
// UVa ID: 10820
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50001;

int cnt[MAXN], phi[MAXN];

void preCalculate()
{
    memset(cnt, 0, sizeof(cnt));
    iota(phi, phi + MAXN, 0);

    for (int i = 2; i < MAXN; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j < MAXN; j += i)
                phi[j] -= phi[j] / i;
        }
        
        cnt[i] = cnt[i - 1] + phi[i];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    preCalculate();

    int n;
    while (cin >> n, n > 0) cout << (2 * cnt[n] + 1) << '\n';

    return 0;
}
