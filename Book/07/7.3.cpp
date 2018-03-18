int rn = 0;
while (n)
{
    rn = rn * 10 + n % 10;
    n /= 10;
}

long long modPow(long long n, long long k, long long mod)
{
    if (k == 0) return 1;
    long long r = modPow(n * n % mod, k >> 1, mod);
    if (k & 1) r = r * n % mod;
    return r;
}
