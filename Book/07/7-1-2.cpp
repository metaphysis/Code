#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 1000000;

int primes[MAX_N], counter = 0;

void sieve()
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i < MAX_N; i++)
        if (!primes[i])
        {
            // 记录筛选得到的素数。
            primes[counter++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < MAX_N; j += i) primes[j] = -1;
        }
}

void sieve1()
{
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i < MAX_N; i++)
    {
        // 代码1：记录筛选得到的素数
        if (!primes[i]) primes[counter++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counter && i * primes[j] < MAX_N; j++)
        {
            // 代码2：将素数的倍数标记为合数。
            primes[i * primes[j]] = -1;

            // 代码3：退出标记操作。
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    sieve();
    
    for (int i = 0; i < counter; i++)
    {
        cout << primes[i] << " ";
        if ((i + 1) % 100 == 0)
            cout << "\n";
    }

    return 0;
}
