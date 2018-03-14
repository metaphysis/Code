// Income Tax Hazard
// UVa ID: 11247
// Verdict: Accepted
// Submission Date: 2018-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long m, x;
    while (cin >> m >> x, m > 0)
    {
        if (x == 0 || x == 100) cout << "Not found\n";
        else
        {
            long long y = 100 * (m - 1) / (100 - x);
            if (100 * (m - 1) % (100 - x) == 0) y--;
            if (y == -1 || y < m) cout << "Not found\n";
            else cout << y << '\n';
        }
    }

    return 0;
}
