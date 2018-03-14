// Save from Radiation
// UVa ID: 11986
// Verdict: Accepted
// Submission Date: 2018-03-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long n, x, t, r;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        int x = 0;
        while (n) x++, n /= 2;
        cout << "Case " << c << ": " << x << '\n';
    }

    return 0;
}
