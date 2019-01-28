// Counting Zeroes
// UVa ID: 12090
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.470s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

const int MAXN = 3300000;

using namespace std;

int primes[MAXN] = {}, cnt;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    
    long long n, nn;
    while (cin >> n, n > 0)
    {
        nn = n;
        map<long long, int> factors;
        for (int i = 0; i < cnt && n > 1; i++)
            if (n % primes[i] == 0)
            {
                while (n % primes[i] == 0)
                {
                    factors[primes[i]]++;
                    n /= primes[i];
                }
            }
        if (n > 1) factors[n]++;
        
        vector<long long> divisors;
        divisors.push_back(1);
        for (auto f : factors)
        {
            int cntOfDivisors = divisors.size();
            long long base = 1;
            for (int i = 1; i <= f.second; i++)
            {
                base *= f.first;
                for (int j = 0; j < cntOfDivisors; j++)
                    divisors.push_back(divisors[j] * base);
            }
        }
        sort(divisors.begin(), divisors.end());
        divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());

        int zeros = 0;
        for (int i = 0; i < divisors.size(); i++)
        {
            if (divisors[i] == 1) continue;
            n = nn;
            while (n % divisors[i] == 0)
            {
                zeros++;
                n /= divisors[i];
            }
        }
        cout << nn << ' ' << zeros << '\n';
    }

    return 0;
}
