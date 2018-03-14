#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1 << 20;

int primes[MAXN] = {0}, cnt = 0;

void getPrimes()
{
    for (int i = 2; i * i < MAXN; i++)
        if (!primes[i])
            for (int j = i * i; j < MAXN; j += i)
                primes[j] = 1;
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
            primes[cnt++] = i;
}

int getMobius(int n)
{
    if (n == 1) return 1;
    int divisors = 0;
    for (int i = 0; i < cnt && n > 1; i++) {
        if (n % primes[i] == 0) {
            divisors++;
            int exponent = 0;
            while (n % primes[i] == 0) {
                exponent++;
                n /= primes[i];
            }
            if (exponent > 1) return 0;
        }
    }
    return (divisors & 1) * (-2) + 1;
}

int mobius[MAXN] = {0};

void getMobius()
{
    for (int i = 1; i < MAXN; i++) {
        int sigma = (i == 1 ? 1 : 0), delta = sigma - mobius[i];
        mobius[i] = delta;
        for (int j = i + i; j < MAXN; j += i)
            mobius[j] += delta;
    }
}

int main(int argc, char *argv[])
{
    getPrimes();
    getMobius();
    for (int i = 1; i <= 100; i++)
        cout << i << ' ' << getMobius(i) << ' ' << mobius[i] << '\n';

    return 0;
}
