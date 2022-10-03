// Little Rakin
// UVa ID: 12703
// Verdict: Accepted
// Submission Date: 2022-10-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long fib[42] = {0, 1};
    for (int i = 2; i < 42; i++) fib[i] = fib[i - 1] + fib[i - 2];

    int ps[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 32, 37, 41};
    int T, n, a, b;
    cin >> T;
    while (T--)
    {
        cin >> n >> a >> b;
        // Fn = ab^(n - 1)
        map<int, int> f;
        for (int i = 0; i < 13 && ps[i] <= a; i++)
            while (a % ps[i] == 0)
            {
                f[ps[i]] += fib[n - 1];
                a /= ps[i];
            }
        if (a > 1) f[a] += fib[n - 1];
        for (int i = 0; i < 13 && ps[i] <= b; i++)
            while (b % ps[i] == 0)
            {
                f[ps[i]] += fib[n];
                b /= ps[i];
            }
        if (b > 1) f[b] += fib[n];
        for (auto p = f.begin(); p != f.end(); p++)
            cout << p->first << ' ' << p->second << '\n';
        cout << '\n';
    }

    return 0;
}
