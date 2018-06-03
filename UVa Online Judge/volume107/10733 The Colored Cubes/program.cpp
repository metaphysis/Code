// The Colored Cubes
// UVa ID: 10733
// Verdict: Accepted
// Submission Date: 2018-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// http://algorithmist.com/index.php/UVa_10733.

#include <bits/stdc++.h>

using namespace std;

long long powN(long long n, int k)
{
    long long r = 1;
    for (int i = 1; i <= k; i++)
        r *= n;
    return r;
}

long long getCnt(long long n)
{
    return (powN(n, 6) + 3 * powN(n, 4) + 12 * powN(n, 3) + 8 * powN(n, 2)) / 24;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n, n) cout << getCnt(n) << '\n';

    return 0;
}
