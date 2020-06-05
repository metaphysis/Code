long long mod;

struct matrix
{
    long long cell[2][2];
    matrix(long long a = 0, long long b = 0, long long c = 0, long long d = 0)
    {
        cell[0][0] = a, cell[0][1] = b, cell[1][0] = c, cell[1][1] = d;
    }
} one(1, 1, 1, 0);

matrix multiply(const matrix &a, const matrix &b)
{
    matrix r;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
            {
                r.cell[i][j] += a.cell[i][k] * b.cell[k][j] % mod;
                r.cell[i][j] %= mod;
            }
    return r;
}

matrix matrixPow(long long k)
{
    matrix r(1, 0, 1, 0);
    matrix cm(1, 1, 1, 0);
    while (k)
    {
        if (k & 1) r = multiply(r, cm);
        cm = multiply(cm, cm);
        k >>= 1;
    }
    return r;
}

matrix matrixPow(long long k)
{
    if (k == 1) return one;
    matrix r = matrixPow(k >> 1);
    r = multiply(r, r);
    if (k & 1) r = multiply(r, one);
    return r;
}
