// Factorial
// UVa ID: 12955
// Verdict: Accepted
// Submission Date: 2019-04-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int factorial[9] = {0, 1};
    for (int i = 2; i < 9; i++)
        factorial[i] = factorial[i - 1] * i;
    int n;
    while (cin >> n)
    {
        int idx = 8, cnt = 0;
        while (n)
        {
            if (n >= factorial[idx])
            {
                n -= factorial[idx];
                cnt++;
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
