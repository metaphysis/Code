// Mint
// UVa ID: 10717
// Verdict: Accepted
// Submission Date: 2018-11-28
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, t;
    long long coins[51], tables[11], low[11], high[11];
    while (cin >> n >> t)
    {
        if (n == 0) break;
        for (int i = 0; i < n; i++) cin >> coins[i];
        for (int i = 0; i < t; i++) cin >> tables[i];
        for (int i = 0; i < t; i++) low[i] = high[i] = -1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    for (int l = k + 1; l < n; l++)
                    {
                        long long a = coins[i], b = coins[j], c = coins[k], d = coins[l];
                        long long lcm = a / __gcd(a, b) * b ;
                        lcm = lcm / __gcd(lcm, c) * c;
                        lcm = lcm / __gcd(lcm, d) * d;
                        for (int m = 0; m < t; m++)
                        {
                            int q = tables[m] / lcm, r = tables[m] % lcm;
                            if (~low[m]) low[m] = max(low[m], q * lcm);
                            else low[m] = q * lcm;
                            if (~high[m]) high[m] = min(high[m], (q + (r ? 1 : 0)) * lcm);
                            else high[m] = (q + (r ? 1 : 0)) * lcm;
                            
                        }
                    }
        for (int i = 0; i < t; i++) cout << low[i] << ' ' << high[i] << '\n';
    }

    return 0;
}
