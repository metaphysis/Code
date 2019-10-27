// Arif in Dhaka
// UVa ID: 10294
// Verdict: Accepted
// Submission Date: 2019-10-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, t;
    long long p[64] = {1};
    while (cin >> n >> t)
    {
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * t;
        long long s = 0;
        for (int i = 0; i < n; i++) s += p[__gcd(n, i)];
        cout << s / n << ' ';
        if (n & 1) s += p[1 + (n - 1) / 2] * n;
        else s += (p[2 + (n - 2) / 2] + p[n / 2]) * n / 2;
        cout << s / (2 * n) << '\n';
    }

    return 0;
}
