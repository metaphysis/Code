// Tri Tiling
// UVa ID: 10918
// Verdict: Accepted
// Submission Date: 2018-03-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// F(n) = 3 * F(n - 2) + 2 * F(n - 4) + 2 * F(n - 6) + .. + 2 * F(0)    [1]
// F(n - 2) = 3 * F(n - 4) + 2 * F(n - 6) + ... + 2 * F(0)              [2]
// [1] - [2] => F(n) = 4 * F(n - 2) - F(n - 4), F(0) = 1, F[2] = 4

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int tiling[32] = {1, 0, 3};
    for (int i = 3; i <= 30; i++)
    {
        if (i % 2)
            tiling[i] = 0;
        else
            tiling[i] = 4 * tiling[i - 2] - tiling[i - 4];
    }

    int n;
    while (cin >> n, n >= 0)
    {
        cout << tiling[n] << '\n';
    }

    return 0;
}
