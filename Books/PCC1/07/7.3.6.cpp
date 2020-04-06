int CRT(int a[], int m[], int n)
{
    int M = 1, r = 0;
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0, Mi, x, y; i < n; i++)
    {
        Mi = M / m[i];
        extgcd(Mi, m[i], x, y);
        r = (r + a[i] * Mi * x) % M;
    }
    if (r < 0) r += M;
    return r;
}
