// Billiard
// UVa ID: 10387
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
    cout << fixed << setprecision(2);

    double a, b, s, m, n, vv, AA;
    while (cin >> a >> b >> s >> m >> n)
    {
        if (a == 0) break;
        double W = a * m, H = b * n;
        double L = sqrt(H * H + W * W);
        vv = L / s;
        AA = 180.0 * atan(H / W) / PI;
        cout << AA << ' ' << vv << '\n';
    }

    return 0;
}
