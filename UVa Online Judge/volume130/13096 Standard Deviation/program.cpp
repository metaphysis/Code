// Standard Deviation
// UVa ID: 13096
// Verdict: Accepted
// Submission Date: 2022-10-28
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n)
    {
        if (n == 0) break;
        long long nn = n;
        n /= 2;
        if (nn & 1)
        {
            double r = 4 * n * (n + 1) * (2 * n + 1) / 3.0;
            cout << fixed << setprecision(6) << sqrt(r / (nn - 1)) << '\n';
        }
        else
        {
            double r = 2 * n * (2 * n - 1) * (2 * n + 1) / 3.0;
            cout << fixed << setprecision(6) << sqrt(r / (nn - 1)) << '\n';
        }
    }

    return 0;
}
