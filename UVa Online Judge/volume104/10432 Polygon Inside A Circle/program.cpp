// Polygon Inside A Circle
// UVa ID: 10432
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double r, n;
    
    while (cin >> r >> n)
    {
        double A = (n - 2) * PI / n;
        double S = r * r * cos(A / 2) * sin(A / 2) * n;
        cout << fixed << setprecision(3) << S << '\n';
    }

    return 0;
}
