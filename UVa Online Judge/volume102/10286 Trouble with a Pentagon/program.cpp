// Trouble with a Pentagon
// UVa ID: 10286
// Verdict: Accepted
// Submission Date: 2017-12-14
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    double F, PI = 2.0 * acos(0);
    double a = 63.0 / 180.0 * PI, b = 108.0 / 180.0 * PI;

    while (cin >> F)
    {
        cout << fixed << setprecision(10) << (F * sin(b) / sin(a)) << '\n';
    }

    return 0;
}
