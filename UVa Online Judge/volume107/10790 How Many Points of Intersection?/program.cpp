// How Many Points of Intersection?
// UVa ID: 10790
// Verdict: Accepted
// Submission Date: 2018-03-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// P(a, b) = a * (a - 1) * b * (b - 1) / 4.

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    long long a, b;
    while (cin >> a >> b, a > 0)
        cout << "Case " << ++cases << ": " << a * (a - 1) * b * (b - 1) / 4 << '\n';

    return 0;
}
