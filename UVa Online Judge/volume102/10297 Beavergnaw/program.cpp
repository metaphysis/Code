// Beavergnaw
// UVa ID: 10297
// Verdict: Accepted
// Submission Date: 2017-12-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double D, V;

    while (cin >> D >> V)
    {
        if (D == 0) break;
        
        double V1 = PI * D * D * D / 4;
        double d = pow((V1 - V - PI * D * D * D / 12) * 6 / PI, 1.0 / 3.0);
        cout << fixed << setprecision(3) << d << '\n';
    }

    return 0;
}
