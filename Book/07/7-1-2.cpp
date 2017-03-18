#include <iostream>
#include <cstring>

using namespace std;

void sieve(int *primes, int n, int &counter)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[counter++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

void sieve1(int *primes, int n, int &counter)
{
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        // 代码1：记录筛选得到的素数
        if (primes[i]) primes[counter++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counter && i * primes[j] < n; j++)
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
    int primes[MAXN], counter = 0;

    sieve1(primes, MAXN, counter);
    
    for (int i = 0; i < counter; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
