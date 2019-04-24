#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;

int primes[MAXN], phi[MAXN] = {0, 1}, cnt = 0;

void sieve1(int *primes, int n, int &cnt)
{
    cnt = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i)
                primes[j] = 0;
        }
}

int getPhi(int m)
{
    int phi = m;
    for (int i = 0; i < cnt; i++) {
        if (primes[i] > m) break;
        if (m % primes[i] == 0)
        {
            while (m % primes[i] == 0)
                m /= primes[i];
            phi -= phi / primes[i];
        }
    }
    if (m > 1) phi -= phi / m;
    return phi;
}

void sieve2(int *primes, int n, int &cnt)
{
    cnt = 0; iota(phi, phi + n, 0);

    for (int i = 2; i < n; i++)
        if (phi[i] == i)
        {
            primes[cnt++] = i;
            for (int j = i; j < n; j += i)
                phi[j] -= phi[j] / i;
        }
}

void sieve3(int *primes, int n, int &cnt)
{
    cnt = 0; iota(primes, primes + n, 0);

    for (int i = 2; i < n; i++)
    {
        if (primes[i] == i)
        {
            phi[i] = i - 1;
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i)
                if (primes[j] == j)
                    primes[j] = i;
        }
        else
        {
            int k = i / primes[i];
            if (k % primes[i] == 0) phi[i] = primes[i] * phi[k];
            else phi[i] = (primes[i] - 1) * phi[k];
        }
    }
}

int main(int argc, char *argv[])
{
    sieve3(primes, MAXN, cnt);
    
    int n;
    while (cin >> n, n > 0)
        cout << getPhi(n) << '\n';
    cout << '\n';

    sieve2(primes, MAXN, cnt);
    for (int i = 0; i <= 1000; i++)
        cout << primes[i] << ' ' << getPhi(primes[i]) << '\n';
    cout << '\n';

    sieve3(primes, MAXN, cnt);
    for (int i = 0; i <= 1000; i++)
        cout << primes[i] << ' ' << phi[primes[i]] << '\n';

    return 0;
}
