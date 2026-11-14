#include <bits/stdc++.h>

using namespace std;
    
const int MAXN = 7000000;
int primes[MAXN], cnt;
    
void sieve1()
{
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < MAXN; j += i)
                primes[j] = 1;
        }
}

void sieve2()
{
    for (int i = 2; i * i < MAXN; i++)
        if (!primes[i])
            for (int j = i * i; j < MAXN; j += i)
                primes[j] = 1;
    for (int i = 2; i < MAXN; i++)
        if (!primes[i])
            primes[cnt++] = i;
}

void sieve3()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

#define GET(x) (B[x >> 5] & (1 << (x & 0x1F)))
#define SET(x) (B[x >> 5] |= (1 << (x & 0x1F)))

const int MAXB = 100000001;
int B[MAXB >> 5] = {};

void sieve4()
{
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

int main(int argc, char *argv[])
{
    sieve4();
    
    for (int i = 0; i < cnt; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
