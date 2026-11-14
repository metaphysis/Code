#include <bits/stdc++.h>

using namespace std;

const int MAX_ITERATIONS = 5;

long long multiplyMod(long long a, long long b, long long mod)
{
    long long x = 0, y = a % mod;
    while (b)
    {
        if (b & 1) x = (x + y) % mod;
        y = (y * 2) % mod;
        b >>= 1;
    }
    return x;
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
    
    for (int i = 0; i < MAX_ITERATIONS; i++)
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

int main(int argc, char *argv[])
{
    long long n;

    cout << "Enter a integer to test primality: ";
    cin >> n;
    if (isPrime(n))
        cout << n << " is prime.\n";
    else
        cout << n << " is not prime.\n";

    return 0;
}



