#include <bits/stdc++.h>

using namespace std;
    
const int MAXN = 1000000;
int primes[MAXN], cnt;
    
void sieve(int *primes, int n, int &cnt)
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

void sieve1(int *primes, int n, int &cnt)
{
    cnt = 0;
    memset(primes, 1, n * sizeof(int));

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
    cnt = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        if (primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < n; j++)
        {
            primes[i * primes[j]] = 0;
            if (i % primes[j] == 0) break;
        }
    }
}

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] |= (1 << (x & 0x1F)))

const int MAXB = 100000001;
int B[MAXB >> 5] = {};

void sieve3(int *primes, int n, int &cnt)
{
    cnt = 0;
    memset(primes, 1, n * sizeof(int));
    for (int i = 2; i < MAXB; i++)
    {
        if (!GET(i)) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXB; j++)
        {
            SET(i * primes[j]);
            if (i % primes[j] == 0) break;
        }
    }
}

void sieve4(int *primes, int n, int &cnt)
{
    cnt = 0;
    memset(primes, 1, n * sizeof(int));
    
    for (int i = 2; i * i < n; i++)
        if (primes[i])
            for (int j = i * i; j < n; j += i)
                primes[j] = 0;
    for (int i = 2; i < n; i++)
        if (primes[i])
            primes[cnt++] = i;
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
