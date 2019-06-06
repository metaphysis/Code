// Divisibility of Factors
// UVa ID: 10484
// Verdict: Accepted
// Submission Date: 2018-03-09
// UVa Run Time: 0.130s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[1 << 16] = {0}, cnt = 0;
    for (int i = 2; i * i < (1 << 16); i++)
        if (!primes[i])
            for (int j = i * i; j < (1 << 16); j += i)
                primes[j] = 1;
    for (int i = 2; i < (1 << 16); i++)
        if (!primes[i])
            primes[cnt++] = i;

    int N, D;
    while (cin >> N >> D)
    {
        if (N == 0 && D == 0) break;
        D = abs(D);

        map<int, int> divisorOfN, divisorOfD;
        for (int i = 2; i <= N; i++)
        {
            int x = i;
            for (int j = 0; j < cnt; j++)
            {
                if (primes[j] > x) break;
                while (x % primes[j] == 0)
                {
                    divisorOfN[primes[j]]++;
                    x /= primes[j];
                }
            }
        }

        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] > D) break;
            while (D % primes[i] == 0)
            {
                divisorOfD[primes[i]]++;
                D /= primes[i];
            }
        }
        if (D > 1) divisorOfD[D]++;

        bool divisible = true;
        for (auto it = divisorOfD.begin(); it != divisorOfD.end(); it++)
        {
            int p = it->first, c = it->second;
            if (divisorOfN.find(p) == divisorOfN.end() || c > divisorOfN[p])
            {
                divisible = false;
                break;
            }
            divisorOfN[p] -= c;
        }
        
        long long cnt = 0;
        if (divisible)
        {
            cnt = 1;
            for (auto it = divisorOfN.begin(); it != divisorOfN.end(); it++)
                cnt *= (it->second + 1);
        }
        cout << cnt << '\n';
    }
        
    return 0;
}
