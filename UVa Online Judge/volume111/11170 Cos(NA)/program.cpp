// Cos(NA)
// UVa ID: 11170
// Verdict: Accepted
// Submission Date: 2018-04-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long sin2m[32][64] = {};
    for (int m = 0; m <= 25; m++)
    {
        sin2m[m][0] = 1;
        long long factor = 1, mm = m;
        for (int k = 1; k <= m; k++)
        {
            factor = factor * mm / k;
            sin2m[m][2 * k] = ((k & 1) ? -1 : 1) * factor;
            mm--;
        }
    }

    long long r[64][64] = {};
    for (int n = 1; n <= 50; n++)
    {
        long long factor = 1, nn = n, temp = 1;
        for (int m = 0; m <= (n / 2); m++)
        {
            if (m)
            {
                factor = factor * nn * (nn - 1) / (2 * m) / (2 * m - 1);
                temp = ((m & 1) ? -1 : 1) * factor;
                nn -= 2;
            }
            for (int k = 0; k <= m; k++)
                r[n][n - 2 * m + 2 * k] += temp * sin2m[m][2 * k];
        }
    }

    int x;
    while (cin >> x, x > 0)
    {
        bool printed = false;
        for (int e = x; e >= 0; e--)
        {
            if (r[x][e])
            {
                // Print sign.
                if (r[x][e] > 0 && printed) cout << '+';
                // Print coefficient.
                if (!e || abs(r[x][e]) > 1) cout << r[x][e];
                // print term.
                if (e > 1) cout << "Cos^" << e << "(A)";
                if (e == 1) cout << "Cos(A)";
                printed = true;
            }
        }
        cout << '\n';
    }
    
    return 0;
}
