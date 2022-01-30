// On a Diet
// UVa ID: 12621
// Verdict: Accepted
// Submission Date: 2022-01-30
// UVa Run Time: 0.030s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n, p, c[110], sum[26000] = {0};
        cin >> n >> p;
        n /= 10;
        for (int i = 1; i <= p; i++)
        {
            cin >> c[i];
            c[i] /= 10;
        }
        sum[0] = 1;
        int t = 0;
        for (int i = 1; i <= p; i++)
        {
            for (int j = t; j >= 0; j--)
                if (sum[j])
                    sum[j + c[i]] = 1;
            t += c[i];
        }
        int printed = 0;
        for (int i = n; i <= t; i++)
        {
            if (sum[i])
            {
                cout << i * 10 << '\n';
                printed = 1;
                break;
            }
        }
        if (!printed) cout << "NO SOLUTION\n";
    }

    return 0;
}
