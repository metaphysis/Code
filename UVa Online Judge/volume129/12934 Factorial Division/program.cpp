// Factorial Division
// UVa ID: 12934
// Verdict: Accepted
// Submission Date: 2022-10-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 1;
    long long k;
    while (cin >> k)
    {
        cout << "Case " << cases++ << ": ";
        if (k == 1)
        {
            cout << "Impossible\n";
            continue;
        }
        int flag = 0;
        int upk = (int)sqrt(k) + 1;
        for (int i = 1; i <= upk && !flag; i++)
        {
            long long f = 1;
            for (int j = i + 1; j <= upk && !flag && f <= k; j++)
            {
                f *= j;
                if (f == k)
                {
                    cout << j << ' ' << i << '\n';
                    flag = 1;
                }
            }
        }
        if (!flag) cout << k << ' ' << k - 1 << '\n';
    }

    return 0;
}
