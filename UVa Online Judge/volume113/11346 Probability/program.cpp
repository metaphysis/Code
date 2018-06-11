// Probability
// UVa ID: 11346
// Verdict: Accepted
// Submission Date: 2018-06-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    double a, b, S;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a >> b >> S;
        double r = 100.0;
        if (S > 0)
        {
            r = (a * b - S * (1.0 + log(a * b / S)));
            r /= (a * b);
            r *= 100.0;
        }
        if (a * b < S) r = 0.0;

        cout << fixed << setprecision(6) << r << "%\n";
    }

    return 0;
}
