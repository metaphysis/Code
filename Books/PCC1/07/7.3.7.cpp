#include <bits/stdc++.h>

using namespace std;

const int MAX_IT = 2, MAXN = 1000000;

map<long long, int> factors;

int primes[MAXN] = {}, cnt = 0;

void sieve()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }
}

long long multiplyMod(long long a, long long b, long long mod)
{
    long long r = 0, m = a % mod;
    while (b)
    {
        if (b & 1) r = (r + m) % mod;
        m = (m * 2) % mod;
        b >>= 1;
    }
    return r;
}

long long modulo(long long base, long long exponent, long long mod)
{
    long long x = 1, y = base;
    while (exponent)
    {
        if (exponent & 1) x = multiplyMod(x, y, mod);
        y = multiplyMod(y, y, mod);
        exponent >>= 1;
    }
    return x;
}

bool isPrime(long long p)
{
    if (p < 2) return false;
    if (p == 2) return true;
    if (!(p & 1)) return false;

    long long q = p - 1;
    while (!(q & 1)) q >>= 1;
    
    for (int i = 0; i < MAX_IT; i++)
    {
        long long a = rand() % (p - 1) + 1;
        long long t = q;
        long long mod = modulo(a, t, p);
        while (t != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = multiplyMod(mod, mod, p);
            t <<= 1;
        }
        if (mod != p - 1 && !(t & 1)) return false;
    }
    return true;
}

long long pollardRho(long long n, long long c)
{
    srand(time(NULL));
    long long i = 1, k = 2;
    long long x = rand() % n, y = x;
    while (true) {
        i++;
        x = (multiplyMod(x, x, n) + c) % n;
        long long d = __gcd(abs(y - x), n);
        if (d != 1 && d != n) return d;
        if (y == x) return n;
        if (i == k) y = x, k <<= 1;
    }
}

void factorize(long long n)
{
    if (n < 1e9)
    {
        for (int i = 0; i < cnt && primes[i] * primes[i] <= n; i++)
            if (n % primes[i] == 0)
            {
                while (n % primes[i] == 0)
                    factors[primes[i]]++, n /= primes[i];
            }
        if (n > 1) factors[n]++;
        return;
    }

    if (isPrime(n)) factors[n]++;
    else
    {
        long long d = n;
        while (d >= n) d = pollardRho(n, rand() % (n - 1) + 1);
        factorize(d);
        factorize(n / d);
    }
}

int main(int argc, char *argv[])
{
    sieve();

    int cases;
    long long n;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        factors.clear();
        factorize(n);
        
        cout << n << " =";
        int cnt = 0;
        for (auto pair : factors)
        {
            if (cnt) cout << " *";
            cout << ' ' << pair.first;
            if (pair.second > 1) cout << '^' << pair.second;
            cnt++;
        }
        cout << '\n';
    }

    return 0;
}
