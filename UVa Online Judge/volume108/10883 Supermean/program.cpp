// Supermean
// UVa ID: 10883
// Verdict: Accepted
// Submission Date: 2017-08-26
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        double t = 0.0, di, mean = 0.0;

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> di;
            if (i) t += log2((double)(n - i) / i);
            if (fabs(di) > 0)
            {
                double sign = (di > 0 ? 1.0 : -1.0);
                mean += sign * pow(2, t + log2(fabs(di)) - (n - 1));
            }
        }

        cout << "Case #" << c << ": ";
        cout << fixed << setprecision(3) << mean << '\n';
    }

    return 0;
}
