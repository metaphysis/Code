// Coupons
// UVa ID: 10288
// Verdict: Accepted
// Submission Date: 2018-04-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n)
    {
        long long r1 = 0, r2 = 0, r3 = 1;
        for (long long i = 1; i <= n; i++)
        {
            r1 += n / i;
            long long k = n % i;
            long long t1 = k * r3 + r2 * i;
            long long t2 = i * r3;
            long long g = __gcd(t1, t2);
            r2 = t1 / g, r3 = t2 / g;
            r1 += r2 / r3, r2 %= r3;
        }

        if (r2 == 0)
        {
            cout << r1 << '\n';
        }
        else
        {
            int length1 = to_string(r1).length();
            int length2 = to_string(r3).length();
            for (int i = 0; i <= length1; i++)
                cout << ' ';
            cout << r2 << '\n';
            cout << r1 << ' ';
            for (int i = 0; i < length2; i++)
                cout << '-';
            cout << '\n';
            for (int i = 0; i <= length1; i++)
                cout << ' ';
            cout << r3 << '\n';
        }
    }

    return 0;
}
