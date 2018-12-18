// Cylinder
// UVa ID: 11232
// Verdict: Accepted
// Submission Date: 2018-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double w, h;
    while (cin >> w >> h)
    {
        if (w < 1e-7) break;
        double r1 = min(w / 2, h / (2 * PI + 2));
        double v1 = PI * pow(r1, 2) * w;
        double r2 = w / (2 * PI);
        double v2 = PI * pow(r2, 2) * (h - 2 * r2);
        cout << fixed << setprecision(3) << max(v1, v2) << '\n';
    }

    return 0;
}
