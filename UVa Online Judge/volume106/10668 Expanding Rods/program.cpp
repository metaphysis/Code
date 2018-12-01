// Expanding Rods
// UVa ID: 10668
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double L, n, C;
    while (cin >> L >> n >> C)
    {
        if (L < 0) break;
        double L1 = L * (1 + n * C);
        double lowR = L / 2, highR = 1e20, R;
        int cnt = 0;
        while (true)
        {
            R = (lowR + highR) / 2.0;
            double L2 = 2 * R * asin(L / 2 / R);
            if (L2 > L1) lowR = R;
            else highR = R;
            if (fabs(L2 - L1) < 1e-8) break;
        }

        double H = R - sqrt(R * R - L * L / 4);
        cout << fixed << setprecision(3) << H << '\n';
    }

    return 0;
}
