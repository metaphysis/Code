#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;
int primes[MAXN], cnt;
    
void sieve(int *primes, int n, int &cnt)
{
    cnt = 0, memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i)
                primes[j] = 0;
        }
}

void sieve1(int *primes, int n, int &cnt)
{
    cnt = 0, memset(primes, 1, n * sizeof(int));

    for (int i = 2; i * i < n; i++)
        if (primes[i])
            for (int j = i * i; j < n; j += i)
                primes[j] = 0;
    for (int i = 2; i < n; i++)
        if (primes[i])
            primes[cnt++] = i;
}

void sieve2(int *primes, int n, int &cnt)
{
    cnt = 0, memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        if (primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < n; j++)
        {
            primes[i * primes[j]] = 0;
            if (!(i % primes[j])) break;
        }
    }
}

vector<int> findDivisor(int n)
{
    map<int, int> factors;
    for (int i = 0; i < cnt && n > 1; i++)
    {
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
    
    return divisors;
}

int main(int argc, char *argv[])
{
    sieve2(primes, MAXN, cnt);
    
    for (int i = 0; i < cnt; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
