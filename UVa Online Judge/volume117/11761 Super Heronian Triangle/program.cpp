// Super Heronian Triangle
// UVa ID: 11761
// Verdict: Accepted
// Submission Date: 2019-02-15
// UVa Run Time: 1.970s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 40001;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long R, A;
    while (cin >> R >> A)
    {
        if (R == 0) break;
        // R = a * b * c / (4 * A);
        long long N = 4 * R * A, P, S, T;
        bool done = false;
        for (long long a = 1; a < MAXN; a++)
        {
            if (N % a != 0) continue;
            for (long long b = max(a, N / a / MAXN), c; a * b * b <= N && b < MAXN; b++)
            {
                c = N / a / b;
                if (c >= MAXN) continue;
                if (a >= b + c || b >= a + b || c >= a + b) continue;
                if ((a + b + c) % 2 == 1) continue;
                if ((a + b - c) % 2 == 1) continue;
                if ((a + c - b) % 2 == 1) continue;
                if ((b + c - a) % 2 == 1) continue;
                P = (a + b + c) / 2;
                S = P * (P - a) * (P - b) * (P - c);
                if (S != A * A) continue;
                T = a * b * c;
                if (T != 4 * R * A) continue;
                cout << a << ' ' << b << ' ' << c << '\n';
                done = true;
                goto out;
            }
        }
        out:
        if (!done) cout << "-1 -1 -1\n";
    }

    return 0;
}
