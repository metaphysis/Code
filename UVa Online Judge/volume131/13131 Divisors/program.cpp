// Divisors
// UVa ID: 13131
// Verdict: Accepted
// Submission Date: 2019-04-15
// UVa Run Time: 0.080s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500010;

int primes[MAXN] = {}, cnt = 0;

vector<int> findDivisor(int n)
{
    map<int, int> factors;
    for (int i = 0; i < cnt; i++)
    {
        if (primes[i] * primes[i] > n) break;
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            factors[primes[i]]++;
        }
    }

    if (n > 1) factors[n]++;

    vector<int> divisors = {1};
    for (auto f : factors)
    {
        int base = 1, countOfDivisors = divisors.size();
        for (int i = 1; i <= f.second; i++)
        {
            base *= f.first;
            for (int j = 0; j < countOfDivisors; j++)
                divisors.push_back(divisors[j] * base);
        }
    }

    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
    
    return divisors;
}

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

    int cases, N, K;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> K;
        int S = 0;
        for (auto d : findDivisor(N))
            if (d % K != 0)
                S += d;
        cout << S << '\n';
    }

    return 0;
}
