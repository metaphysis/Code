// Ordering T-Shirts
// UVa ID: 12022
// Verdict: Accepted
// Submission Date: 2018-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// http://oeis.org/A000670.

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r[] = {1, 1, 3, 13, 75, 541, 4683, 47293, 545835, 7087261, 102247563, 1622632573};
    int cases, n;
    cin >> cases;
    while (cases--) cin >> n, cout << r[n] << '\n';

    return 0;
}
