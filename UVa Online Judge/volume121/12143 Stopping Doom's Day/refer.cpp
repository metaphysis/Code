#include <bits/stdc++.h>

#if defined( _WIN32 )
typedef __int64 az_int64_t;
typedef unsigned __int64 az_uint64_t;
#define I64(x) x ## I64
#define F64 "I64"
#else
typedef long long az_int64_t;
typedef unsigned long long az_uint64_t;
#define I64(x) x ## ll
#define F64 "ll"
#endif

#define AZ_MAXUI64 I64(0xffffffffffffffffu)

az_int64_t nsum(int n)
{
    int i, j, k, l, m;
    az_int64_t sum = 0;

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            for (k = 1; k <= n; ++k)
                for (l = 1; l <= n; ++l)
                    for (m = 1; m <= n; ++m)
                    {
                        int v = 1;
                        if (i <= j)
                            v *= j - i;
                        else
                            v *= i - j;
                        if (j <= k)
                            v *= k - j;
                        else
                            v *= j - k;
                        if (k <= l)
                            v *= l - k;
                        else
                            v *= k - l;
                        if (l <= m)
                            v *= m - l;
                        else
                            v *= l - m;
                        if (m <= i)
                            v *= i - m;
                        else
                            v *= m - i;
                        sum += v;
                    }

    return sum;
}

#define MAXN 24
az_int64_t sum[MAXN + 2][MAXN + 2];

void gen(void)
{
    int n, d;

    sum[0][0] = 0;

    printf("Orig:\n");
    for (n = 1; n <= MAXN; ++n)
    {
        sum[0][n] = nsum(n);
        printf("  %2d: %" F64 "d, %d\n", n, sum[0][n], (int)(sum[0][n] % 10007));
    }
    printf("\n");

    for (d = 1; d <= 12; ++d)
    {
        printf("diff level %d:\n", d);
        for (n = 1; n <= MAXN - d; ++n)
        {
            sum[d][n] = sum[d - 1][n + 1] - sum[d - 1][n];
            printf("  %2d: %" F64 "d, %d\n", n, sum[d][n], (int)(sum[d][n] % 10007));
        }
        printf("\n");
    }
}

int main(void)
{
    gen();

    return 0;
}
