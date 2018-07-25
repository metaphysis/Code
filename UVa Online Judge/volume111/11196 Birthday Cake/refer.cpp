#include <stdio.h>
#include <math.h>

#define N 12
#define inf 100000000L

long n, m, s;
void backtrack(long curv, long curs, long k, long r[], long h[], bool * f1);

int main(void)
{
    long a[N], b[N], test = 0;
    bool f1;
    while (scanf("%ld", &n) == 1 && n)
    {
        test++;
        scanf("%ld", &m);
        s = inf;
        a[0] = (long)sqrt(n) + 1;
        b[0] = n / (a[0] - 1) * (a[0] - 1) + 1;
        f1 = false;
        backtrack(0, 0, 0, a, b, &f1);
        printf("Case %ld: ", test);
        if (s >= inf)
            s = 0;
        printf("%ld\n", s);
    }
    return 0;
}

void backtrack(long curv, long curs, long k, long r[], long h[], bool * f1)
{
    if (k == m)
    {
        curs += r[1] * r[1];
        if (curs < s)
            s = curs;
        *f1 = true;
        return;
    }
    if (curv >= n)
        return;
    if (k > 1 && curs + r[1] * r[1] >= s)
        return;

    long maxr, maxh, maxvol, minvol, i, j, restl, restv, l, mins;

    restl = m - k;
    restv = n - curv;
    k++;
    minvol = (restl * restl * (restl + 1) * (restl + 1)) / 4;
    if (minvol + curv > n)
        return;

    mins = restl * (restl + 1) * (2 * restl + 1) / 3;
    if (k > 1 && mins + curs + r[1] * r[1] > s)
        return;

    maxr = (long)sqrt(n / k);
    if (k > 1 && (maxr >= r[k - 1]))
        maxr = r[k - 1] - 1;
    for (i = maxr; i >= restl; i--)
    {
        if (2 * restv / i + 1 >= s)
            return;

        maxh = restv / (i * i);
        if (k > 1 && (maxh >= h[k - 1]))
            maxh = h[k - 1] - 1;
        r[k] = i;

        *f1 = false;
        for (j = maxh; j >= restl; j--)
        {
            maxvol = 0;
            for (l = 0; l < restl; l++)
                maxvol += (i - l) * (i - l) * (j - l);
            if (curv + maxvol < n)
                break;

            mins = 0;
            for (l = 0; l > restl; l++)
                mins += (i - l) * (j - l);

            if (curs + mins > s) break;

            h[k] = j;
            backtrack(curv + i * i * j, curs + 2 * i * j, k, r, h, f1);
            if (*f1 && k == m - 1)
                break;
        }
    }
}
