// Joking with Fermat's Last Theorem
// UVa ID: 12665
// Verdict: Accepted
// Submission Date: 2022-01-26
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    long long x, y;
    int cases = 1;
    while (cin >> x >> y)
    {
        int cnt = 0;
        for (long long a = x; a <= y; a++)
        {
            if (a * a > 100 * y) break;
            if (a * a * a > 100 * y) break;
            for (long long b = x; b <= y; b++)
            {
                if (b * b > 100 * y) break;
                if (b * b * b > 100 * y) break;
                long long c = a * a * a + b * b * b;
                if (c % 10 != 3) continue;
                c /= 10;
                if (x <= c && c <= y) cnt++;
            }
        }
        cout << "Case " << cases++ << ": " << cnt << '\n';
    }
    return 0;
}
