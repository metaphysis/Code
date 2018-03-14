// Kingdom Division
// UVa ID: 11164
// Verdict: Accepted
// Submission Date: 2017-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    double a, b, c;
    
    while (cin >> a >> b >> c)
    {
        if (a == -1.0) break;
        cout << "Set " << ++cases << ":\n";
        if (b * b <= a * c ) cout << "Poor King!\n";
        else
        {
            double d = a * c * (a + 2 * b + c) / (b * b - a * c);
            cout << fixed << setprecision(4) << d << '\n';
        }
    }

    return 0;
}
