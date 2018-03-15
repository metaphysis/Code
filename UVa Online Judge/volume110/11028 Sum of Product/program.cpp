// Sum of Product
// UVa ID: 11028
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// https://oeis.org/. A007773, dartboard sequence.

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r[] = {0, 1, 1, 1, 3, 8, 21, 43, 69, 102, 145, 197, 261, 336, 425, 527, 645, 778, 929, 1097, 1285};
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case #" << ++cases << ": " << r[n] << '\n';
    }

    return 0;
}
