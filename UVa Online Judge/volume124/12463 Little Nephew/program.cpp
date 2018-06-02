// Little Nephew
// UVa ID: 12463
// Verdict: Accepted
// Submission Date: 2018-06-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long a, b, c, d, e;

    while (true)
    {
        cin >> a >> b >> c >> d >> e;
        if (a == 0) break;
        long long r = a * b * c * d * d * e * e;
        cout << r << '\n';
    }

    return 0;
}
