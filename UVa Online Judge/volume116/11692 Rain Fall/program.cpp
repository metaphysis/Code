// Rain Fall
// UVa ID: 11692
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cout.setf(ios::fixed);
    cout.precision(10);

    int cases;
    double L, K, T1, T2, H;

    cin >> cases;
    while (cases--)
    {
        cin >> L >> K >> T1 >> T2 >> H;
        
        if (H + EPSILON < L)
        {
            cout << H << ' ' << H << '\n';
            continue;
        }

        // T1 * x - (T1 - L / x) * K - T2 * K = H, x = rain fall rate.
        double a = T1;
        double b = -(T1 * K + T2 * K + H);
        double c = L * K;
        double x = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
        
        if (fabs(H - L) < EPSILON)
        {
            cout << H << ' ';
            cout << T1 * x << '\n';
            continue;
        }

        cout << T1 * x << ' ' << T1 * x << '\n';
    }

    return 0;
}
