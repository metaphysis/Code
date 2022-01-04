// Help Cupid
// UVa ID: 12861
// Verdict: Accepted
// Submission Date: 2021-12-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, Ti[1024];
    while (cin >> n)
    {
        for (int i = 0; i < n; i++) cin >> Ti[i];
        sort(Ti, Ti + n);
        int ttd1 = 0, ttd2 = 0;
        for (int i = 0; i < n; i += 2)
        {
            ttd1 += min(abs(Ti[i] - Ti[(i + 1) % n]), 24 - abs(Ti[i] - Ti[(i + 1) % n]));
            ttd2 += min(abs(Ti[i] - Ti[(i - 1 + n) % n]), 24 - abs(Ti[i] - Ti[(i - 1 + n) % n]));
        }
        cout << min(ttd1, ttd2) << '\n';
    }
    return 0;
}
