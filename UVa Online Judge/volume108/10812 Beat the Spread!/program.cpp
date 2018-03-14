// Beat the Spread!
// UVa ID: 10812
// Verdict: Accepted
// Submission Date: 2017-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long s, d, a, b;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> s >> d;
        a = s + d;

        if (a % 2 == 1)
        {
            cout << "impossible\n";
            continue;
        }
        
        a /= 2;
        b = s - a;
        
        if (a >= b && b >= 0)
        {
            cout << a << ' ' << b << '\n';
        }
        else
        {
            cout << "impossible\n";
        }
    }

    return 0;
}
