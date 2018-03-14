// Simple Calculations
// UVa ID: 10014
// Verdict: Accepted
// Submission Date: 2018-02-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;
    double a0, an, ci, sum;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> a0 >> an;
        sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> ci;
            sum += (n - i) * ci;
        }
        double a1 = (n * a0 + an - 2 * sum) / (n + 1);
        if (c > 1) cout << '\n';
        cout << fixed << setprecision(2) << a1 << '\n';
    }

    return 0;
}
