// Laser Pointer
// UVa ID: 11326
// Verdict: Accepted
// Submission Date: 2017-12-16
// UVa Run Time: 0.070s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double L, W, theta;
    int cases;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> L >> W >> theta;
        theta = theta / 180.0 * PI;
        double A = L / cos(theta);
        double H = L * tan(theta);
        double h = fmod(H, 2 * W);
        if (h > W) h = 2 * W - h;
        double B = sqrt(L * L + h * h);
        cout << fixed << setprecision(3) << (A / B) << '\n';
    }

    return 0;
}
