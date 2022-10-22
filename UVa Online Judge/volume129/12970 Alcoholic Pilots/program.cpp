// Alcoholic Pilots
// UVa ID: 12970
// Verdict: Accepted
// Submission Date: 2022-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 1;
    long long v1, d1, v2, d2;
    while (cin >> v1 >> d1 >> v2 >> d2)
    {
        if (v1 == 0) break;
        cout << "Case #" << cases << ": ";
        if (d1 * v2 < d2 * v1) cout << "You owe me a beer!\n";
        else cout << "No beer for the captain.\n";
        cout << "Avg. arrival time: ";
        long long f1 = d1 * v2 + d2 * v1, f2 = 2LL * v1 * v2;
        long long g = __gcd(f1, f2);
        if (g > 1) f1 /= g, f2 /= g;
        if (f1 % f2 == 0) cout << f1 / f2;
        else cout << f1 << '/' << f2;
        cout << '\n';
        cases++;
    }

    return 0;
}
