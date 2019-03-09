// Polygon
// UVa ID: 11971
// Verdict: Accepted
// Submission Date: 2019-03-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, k;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> k;
        cout << "Case #" << cs << ": ";
        long long a = k + 1, b = 1LL << k;
        long long g = __gcd(a, b);
        a /= g, b /= g;
        a = b - a;
        cout << a << '/' << b << '\n';
    }

    return 0;
}
