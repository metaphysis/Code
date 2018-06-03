// Hapless Hedonism
// UVa ID: 11554
// Verdict: Accepted
// Submission Date: 2018-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long f[1000010] = {0};

    for (long long i = 4; i <= 1000000; i++) f[i] = f[i - 1] + (i - 2) * (i - 2) / 4;

    int cases, n;
    cin >> cases;
    while (cases--) cin >> n, cout << f[n] << '\n';

    return 0;
}
