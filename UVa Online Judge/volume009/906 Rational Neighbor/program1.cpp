// Rational Neighbor
// UVa ID: 906
// Verdict: Accepted
// Submission Date: 2017-03-10
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    long long a, b;
    double epsilon;
    
    while (cin >> a >> b >> epsilon)
    {
        long double r1 = (long double)a / b, r2;
        for (long long d = 1, c; ; d++)
        {
            c = (long long)(r1 * d);
            while (a * d >= b * c) c++;
            r2 = (long double)c / d;
            if (r2 - r1 <= epsilon)
            {
                cout << c << ' ' << d << '\n';
                break;
            }
        }
    }
    
    return 0;
}
