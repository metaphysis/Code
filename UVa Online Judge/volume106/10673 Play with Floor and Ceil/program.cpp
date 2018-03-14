// Play with Floor and Ceil
// UVa ID: 10673
// Verdict: Accepted
// Submission Date: 2018-03-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void extgcd(int a, int b, int &x, int &y)
{
    if (b == 0) x = 1, y = 0;
    else
    {
        extgcd(b, a % b, x, y);
        int t = x - a / b * y;
        x = y, y = t;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    long long x, k, a, b, c;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> x >> k;
        if (x % k == 0)
        {
            cout << 1 << ' ' << k - 1 << '\n';
        }
        else
        {
            a = x / k, b = x / k + 1;
            int p, q;
            extgcd(a, b, p, q);
            cout << x * p << ' ' << x * q << '\n';
        }
    }

    return 0;
}
