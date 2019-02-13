// So You Want to Be a 2n-aire?
// UVa ID: 10900
// Verdict: Accepted
// Submission Date: 2019-02-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double t;

    while (cin >> n >> t)
    {
        if (n == 0) break;

        //if (fabs(1 - t) <= 1e-7)
        //{
        //    cout << fixed << setprecision(3) << pow(2, n) << '\n';
        //    continue;
        //}

        double fk = pow(2, n);
        for (int i = 1; i <= n; i++)
        {
            double m = pow(2, n - i) / fk;
            if (m <= t)
                fk = (1 + t) * fk / 2;
            else
                fk = pow(2, n - i) * (m - t) / (1 - t) + (1 - m * m) * fk / (1 - t) / 2;
        }
        cout << fixed << setprecision(3) << fk << '\n';
    }

    return 0;
}
