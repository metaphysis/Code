#include <iostream>
#include <cstring>

using namespace std;

void sieve(int *primes, int n, int &counterOfPrimes)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[counterOfPrimes++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

void sieve1(int *primes, int n, int &counterOfPrimes)
{
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        // 代码1：记录筛选得到的素数
        if (primes[i]) primes[counterOfPrimes++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counterOfPrimes && i * primes[j] < n; j++)
        {
            // 代码2：将素数的倍数标记为合数。
            primes[i * primes[j]] = 0;

            // 代码3：退出标记操作。
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    const int MAXN = 1000000;
    int primes[MAXN], counterOfPrimes = 0;

    sieve1(primes, MAXN, counterOfPrimes);
    
    for (int i = 0; i < counterOfPrimes; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
